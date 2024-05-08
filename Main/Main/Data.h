#pragma once
#include<iostream>

class Data {
public:
	std::string key;
	std::string fileID;

	Data();
	Data(const std::string& key, const std::string& fileID);

};