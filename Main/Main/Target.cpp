#include"Target.h"

std::vector<Target> Target::targetList = std::vector<Target>(0);
bool Target::hasTarget = false;

Target::Target()
{
}

Target::Target(const std::string& fileID, const std::string& value)
	:fileID(fileID),value(value)
{
	hasTarget = true;
	targetList.push_back(*this);
}
