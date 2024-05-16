#include"GameObject.h"

std::vector<GameObject> GameObject::gameObjectList = std::vector<GameObject>(0);



GameObject::GameObject(const std::string& name,const std::vector<std::string>&fileid,const std::vector<MonoBehaviour>& mono,bool isform = false)
	: m_Name(name), fileID(fileid), monoBehaviour(mono)
{
	//构造完毕后加入gameObjectList,放到堆上
	gameObjectList.emplace_back(*this);
}

GameObject::GameObject()
{
}

GameObject* GameObject::FindByFileID(const std::string& id)
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		GameObject &go = gameObjectList[i];
		for (int j = 0; j < go.fileID.size(); ++j) {
			if (id == go.fileID[j]) {
				return &go;
			}
		}
	}

	return nullptr;
}

bool GameObject::NameIsForm(const std::string& name)
{
	if (name.find("Form") != std::string::npos) {
		return true;
	}
	return false;
}

gameObjectType::Type GameObject::GetMonoBehaviourType(const std::string& id,bool FindNotReturnByPriority) {
	for (int i = 0; i < this->monoBehaviour.size(); ++i) {
		if (monoBehaviour[i].id == id) {
			return monoBehaviour[i].GetType();
		}
	}

	//如果用id查找不到monobehaviour说明这个可能是gameoject或者其他脚本，考虑使用优先级的方式返回类型
	if (FindNotReturnByPriority) {
		return GetTypeByPriority();
	}
	return gameObjectType::Type::GameObject;
}

bool GameObject::hasReferenceCollector() {
	for(auto& var : monoBehaviour)
	{
		if (var.IsReferenceCollector()) {
			return true;
		}
	}
	return false;
}

void GameObject::PrintInfo()
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		std::cout << "m_Name: " << gameObjectList[i].m_Name << ",  " << "Type: " << gameObjectList[i].GetTypeByPriority() << std::endl;
	}
}

gameObjectType::Type GameObject::GetTypeByPriority()
{
	if (monoBehaviour.empty()) {
		return gameObjectType::Type::GameObject;
	}

	auto maxScript = std::max_element(monoBehaviour.begin(), monoBehaviour.end(), [](auto b1, auto b2) {
		return b1.m_Script.GetType() < b2.m_Script.GetType();
		});
	
	if (maxScript == monoBehaviour.end()) {
		return gameObjectType::Type::GameObject;
	}

	return maxScript->GetType();
}

MonoBehaviour GameObject::GetReferenceCollector() {
	for (int i = 0; i < monoBehaviour.size(); ++i) {
		if (monoBehaviour[i].IsReferenceCollector()) {
			return monoBehaviour[i];
		}
	}
	return MonoBehaviour();
}





