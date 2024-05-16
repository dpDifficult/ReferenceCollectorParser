#pragma once
#include<iostream>
#include <vector>

class Target {
public:
	std::string fileID;
	std::string value;

	static std::vector<Target>targetList;
	static bool hasTarget;

	Target();

	Target(const std::string& fileID, const std::string& value);
};