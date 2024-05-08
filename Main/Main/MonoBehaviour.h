#pragma once
#include<iostream>
#include<vector>
#include"Script.h"
#include"Data.h"

class MonoBehaviour {
public :
	std::string id;
	Script m_Script; 
	std::vector<Data>dataList;

	MonoBehaviour();

	MonoBehaviour(const std::string& id,const Script& script,const std::vector<Data>& datalist);

	gameObjectType::Type GetType();//��ȡ��ǰ����

	bool IsReferenceCollector();
};