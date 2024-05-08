#include "Script.h"

std::unordered_map<std::string, gameObjectType::Type> Script::guidType = {
	{"502d8cafd6a5a0447ab1db9a24cdcb10", gameObjectType::Type::ReferenceCollector},
	{"fe87c0e1cc204ed48ad3b37840f39efc", gameObjectType::Type::Image},
	{"5f7201a12d95ffc409449d95f23cf332", gameObjectType::Type::Text},
	{"4e29b1a8efbd4b44bb3f3716e73f07ff",gameObjectType::Type::Button },
	{"67db9e8f0e2ae9c40bc1e2b64352a6b4",gameObjectType::Type::Slider},
	{"94c0679c20326fe42bf4b39f1e9b26a7",gameObjectType::Type::MyScrController}
};

Script::Script()
{
}

Script::Script(const std::string& id) : guid(id)
{
}



gameObjectType::Type Script::GetType()
{
	auto it = this->guidType.find(this->guid);

	if (it == this->guidType.end()) {
		return gameObjectType::Type::GameObject;
	}

	return it->second;
}
