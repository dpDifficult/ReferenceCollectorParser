#pragma once
#include<iostream>
#include<vector>
#include<array>
#include"MonoBehaviour.h"
#include"Data.h"

/*
一个gameObject身上可能会有多个MonoBehaviour，gameObject的类型可能是多个的，
在获取类型的这样的方法中总是能够返回Type::GameObject类型
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

	static GameObject* FindByFileID(const std::string& id);//静态方法，通过id查找GameObject
	
	gameObjectType::Type GetMonoBehaviourType(const std::string& id,bool FindNotReturnByPriority);//通过id查找到monobehaviour并返回它的类型

	gameObjectType::Type GetTypeByPriority();//通过优先级返回类型

	bool hasReferenceCollector();

	MonoBehaviour GetReferenceCollector();

	static void PrintInfo();


}; 