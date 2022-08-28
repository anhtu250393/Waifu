#include "Data.h"
#include "Scene/Level/MapManager.h"
USING_NS_CC;

LocalData* LocalData::instance = NULL;

LocalData* LocalData::getInstance()
{
	if (!instance)
	{
		instance = new LocalData();
	}
	return instance;
}

LocalData::LocalData()
{
	m_data.insert(pair<string, int>("Id_Map", 1));
}

LocalData::~LocalData()
{
}

void LocalData::WriteDadta()
{
	int id_map = MapManager::getInstance()->GetIdMap();
	if (id_map < m_data["Id_Map"])
	{
		return;
	}

	m_data["Id_Map"] = id_map;
	map<string, int>::iterator itr;
	for (itr = m_data.begin(); itr != m_data.end(); ++itr)
	{
		cocos2d::UserDefault::getInstance()->setIntegerForKey(itr->first.c_str(), itr->second);
	}
}

void LocalData::ReadData()
{
	map<string, int>::iterator itr;
	for (itr = m_data.begin(); itr != m_data.end(); ++itr)
	{
		m_data[itr->first] = cocos2d::UserDefault::getInstance()->getIntegerForKey(itr->first.c_str(), 1);
	}
}

void LocalData::NewKeyData(string key, int value)
{
	m_data.insert(pair<string, int>(key, 0));
}

void LocalData::DeleteKeyData(string key)
{
	m_data.erase(key);
}

void LocalData::setData(string key, int value)
{
	m_data[key] = value;
}

int LocalData::getData(string key)
{
	return m_data[key];;
}
