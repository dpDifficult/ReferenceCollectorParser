#include<iostream>
#include<string>
#include<fstream>
#include<regex>
#include<vector>
#include"GameObject.h"

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

/*
����һ��prefab����ȡ���е�gameobject

���ң�
�ж�һ��gameobject�ǲ���form���ж��Ƿ���ReferenceCollector�ű���gameobject����

ReferenceCollector�Ľű����й����ӽڵ����Ϣ�������������fileid�����fileid�����ҵ��������Լ��������monobehavior��Ϣ

*/

std::string TypeToString(gameObjectType::Type t) {
    switch (t)
    {
    case gameObjectType::Image:
        return "Image";
    case gameObjectType::Text:
        return "Text";
    case gameObjectType::Button:
        return "Button";
    case gameObjectType::MyScrController:
        return "MyScrController";
    case gameObjectType::Slider:
        return "Slider";
    default:
        return "GameObject";
    }
}

//ȥ����Ҫ���еķ��ţ� ��&�� �� ��:��
static std::string CutStringBySymbol(const std::string& str,const std::string& cut) {
    int pos = str.find(cut);

    int num = (cut == "&") ? 1 : 2;

    if (pos != std::string::npos) { 
        std::string after = str.substr(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(pos) + num);
        return after;
    }
    
    return "";
}

//ȥ��������
static std::string CutBraces(const std::string& str) {
    return str.substr(1, str.length() - 2);
}

//- component: {fileID: 6252306275538468442} ���������ַ����ϻ�ȡfileid
static std::string GetFileIDString(const std::string& str, const std::string& cut) {
    return CutStringBySymbol(CutBraces(CutStringBySymbol(str, cut)),":");
}

// fileID: 11500000, guid : 502d8cafd6a5a0447ab1db9a24cdcb10, type : 3 
//���������ַ����ϻ�ȡguid
static std::string GetGuid(const std::string& str) {
    // �ҵ� guid: ��λ��
    size_t guidStartPos = str.find("guid: ");
    if (guidStartPos != std::string::npos) { // ����ҵ��� guid: 
        // �ҵ����ŵ�λ��
        size_t commaPos = str.find(",", guidStartPos);
        if (commaPos != std::string::npos) { // ����ҵ��˶���
            // ��ȡ guid
            return str.substr(guidStartPos + 6, commaPos - (guidStartPos + 6));
        }
        else {
            std::cout << "δ�ҵ�����" << std::endl;
            return "";
        }
    }
    else {
        std::cout << "δ�ҵ� guid: " << std::endl;
        return "";
    }

    return "";
}

//��ȡScript�ϵ�guid
static std::string GetScriptString(const std::string& str, const std::string& cut) {
    return GetGuid(CutBraces(CutStringBySymbol(str, cut)));
}

static void ParsePrefab() {
    std::string path;
    std::cin >> path;

    std::ifstream file(path);
    if (!file.is_open()) {

        std::cerr << "�޷����ļ���" << std::endl;
        return ;
    }

    std::string line;

    while (std::getline(file, line)) {

        static std::vector<MonoBehaviour> monoList;
        static MonoBehaviour mono;
        static Data data;
        static Script script;
        static std::string m_Name;
        static std::vector<std::string>fileid;

        static bool getname = true;
        static bool getmono_ing = false;

        if (line.find("---") != std::string::npos) {
            if (getmono_ing) {
                getmono_ing = !getmono_ing;
                monoList.emplace_back(mono);
            }
            std::string id = CutStringBySymbol(line, "&");
            if (std::getline(file, line)) {
                if(line.find("GameObject:") != std::string::npos) {

                    GameObject go(m_Name, fileid, monoList, GameObject::NameIsForm(m_Name));
                    //������Ϻ�������м��ϣ���ֹ�´ι������ݶѻ�
                    
                    mono.dataList.clear();
                    monoList.clear();
                    fileid.clear();
                    fileid.push_back(id);
                    getname = true;
                }
                else if (line.find("MonoBehaviour:") != std::string::npos) {
                    getmono_ing = true;
                    mono.id = id;
                }
            }
        }
        else if (line.find("- component") != std::string::npos) {
            fileid.push_back(GetFileIDString(line,":"));
        }
        else if (line.find("m_Name") != std::string::npos) {
            if (!getname) continue;
            m_Name = CutStringBySymbol(line,":");
            getname = false;

        }
        else if (line.find("m_Script") != std::string::npos) {
            script.guid = GetScriptString(line, ":");
            mono.m_Script = script;
        }
        else if (line.find("- key") != std::string::npos) {
            data.key = CutStringBySymbol(line, ":");
        }
        else if (line.find("gameObject") != std::string::npos) {
            data.fileID = GetFileIDString(line, ":");
            mono.dataList.push_back(data);
        }

        
    }

    file.close();
}

static std::string Output() {
    std::string outputStr;

    if (GameObject::gameObjectList.empty()) {
        std::cout << "gameObejctList is empty";
            return outputStr;
    }

    for (int i = 0; i < GameObject::gameObjectList.size(); i++)
    {
            //ֻ��form�Ķ���
        if (GameObject::NameIsForm(GameObject::gameObjectList[i].m_Name) && GameObject::gameObjectList[i].hasReferenceCollector()) {

            outputStr += ANSI_COLOR_YELLOW + GameObject::gameObjectList[i].m_Name + " :" + ANSI_COLOR_RESET + "\n";

            auto mono = GameObject::gameObjectList[i].GetReferenceCollector();

                //�ж�monobehaviour�Ƿ���ReferenceCollector
                if (mono.IsReferenceCollector()) {
                    std::vector<std::string>nameList;
                    std::vector<std::string>typeList;
                    for (int j = 0; j < mono.dataList.size(); ++j) {
                        //�õ��Ӷ�������ֺ�fileid
                        Data son = mono.dataList[j];
                        //��id�õ��Ӷ���
                        GameObject* go = GameObject::FindByFileID(son.fileID);
                        if (!go) {
                            continue;
                        }
                        std::string type = TypeToString(go->GetMonoBehaviourType(son.fileID, true));
                        std::string name = go->m_Name;
                        typeList.push_back(type);
                        nameList.push_back(name);

                        outputStr += "public " + type + " " + name + ";" + "\n";
                    }
                    outputStr += "\n";
                    outputStr += ANSI_COLOR_CYAN + GameObject::gameObjectList[i].m_Name + "System :" + ANSI_COLOR_RESET + "\n";
                    for (int j = 0; j < typeList.size(); ++j) {
                        
                        outputStr +=  "self." + nameList[j] + " = self.Collector.Get<" + typeList[j] + ">(\"" + nameList[j] + "\");" + "\n";
                    }
                }
                
            outputStr += "\n";

        }
        
        
    }
    return outputStr;
}

int main() {
   
    while (1) {
        ParsePrefab();

        std::cout << Output() << std::endl;

        GameObject::gameObjectList.clear();

        std::cout << "\n" << "press any key to next input" << std::endl;
        std::cin.get();
        std::cin.get();

        system("cls");
    }

    

    return 0;
}

