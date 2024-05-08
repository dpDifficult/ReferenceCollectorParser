#pragma once
#include<iostream>
#include<vector>
#include<array>
#include"MonoBehaviour.h"
#include"Data.h"

/*
һ��gameObject���Ͽ��ܻ��ж��MonoBehaviour��gameObject�����Ϳ����Ƕ���ģ�
�ڻ�ȡ���͵������ķ����������ܹ�����Type::GameObject����
*/

class GameObject {
public :
	std::string  m_Name;
	std::vector<std::string>fileID;
	std::vector<MonoBehaviour> monoBehaviour;
	
	static std::vector<GameObject>gameObjectList;

	GameObject();

	GameObject(const std::string& name,const std::vector<std::string>& fileid,const std::vector<MonoBehaviour>& mono, bool isform);

	static bool NameIsForm(const std::string& name);

	static GameObject* FindByFileID(const std::string& id);//��̬������ͨ��id����GameObject
	
	gameObjectType::Type GetMonoBehaviourType(const std::string& id,bool FindNotReturnByPriority);//ͨ��id���ҵ�monobehaviour��������������

	gameObjectType::Type GetTypeByPriority();//ͨ�����ȼ���������

	bool hasReferenceCollector();

	MonoBehaviour GetReferenceCollector();

	static void PrintInfo();


}; 