#include"MonoBehaviour.h"

MonoBehaviour::MonoBehaviour()
{
}

MonoBehaviour::MonoBehaviour(const std::string& id,const Script& script,const std::vector<Data>&datalist)
	:  id(id), m_Script(script), dataList(datalist)
{
}

gameObjectType::Type MonoBehaviour::GetType()
{
	return this->m_Script.GetType();
}

bool MonoBehaviour::IsReferenceCollector()
{
	if (this->m_Script.GetType() == gameObjectType::Type::ReferenceCollector) {
		return true;
	}

	return false;
}

