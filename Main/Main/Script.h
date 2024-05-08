#pragma once
#include<iostream>
#include <unordered_map>

namespace gameObjectType {
	enum Type {
		GameObject, Text, Image, Button,Slider, ReferenceCollector, MyScrController
	};
}


class Script {
public:
	std::string guid;

	Script();
    Script(const std::string& id);

	static std::unordered_map<std::string, gameObjectType::Type> guidType;

	gameObjectType::Type GetType();//��guid��ȡ��������ʱ�����ǻ᷵��Type::GameObject


};