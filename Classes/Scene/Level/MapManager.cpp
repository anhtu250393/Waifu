#include "MapManager.h"
#include "Data.h"
#include "GameObjects/DynamicObjects/MovingPlatform.h"
#include "GameObjects/DynamicObjects/CollapsePlatform.h"
#include "GameObjects/DynamicObjects/Collectible.h"
#include "GameObjects/AnimationObjects/Lever.h"
#include "GameObjects/AnimationObjects/Door.h"
#include "GameObjects/AnimationObjects/Goal.h"
#include "GameObjects/StaticObjects/BackGround.h"
#include "GameObjects/StaticObjects/Floor.h"
#include "GameObjects/StaticObjects/Pedestal.h"
#include "GameObjects/StaticObjects/Wall.h"
#include "GameObjects/MovingObjects/MainCharacter.h"
#include "GameObjects/MovingObjects/MonsterChase.h"
#include "GameObjects/Tutorial.h"
#include "Scene/Menu/MSelectLevelScene.h"
#include "Scene/Menu/EndScene.h"

MapManager* MapManager::instance = 0;

MapManager* MapManager::getInstance()
{
	if (!instance)
	{
		instance = new MapManager();
	}
	return instance;
}

MapManager::MapManager()
{
	m_MapName = "";
	m_IdMaps = 1;
	m_Layer = nullptr;
}

MapManager::~MapManager()
{
	DeleteObjects();
	m_Layer = nullptr;
}

void MapManager::DeleteObjects()
{
	//Delete object
	for (int i = 0; i < m_Objects.size(); i++)
	{
		if (dynamic_cast<MainCharacter*>(m_Objects[i]))
			continue;
		//delete m_Objects[i];		
	}
	m_Objects.clear();
}

void MapManager::InitMap(Layer* layer)
{
	m_Layer = layer;

	//Load map
	m_MapName = "tilemap/FMlv" + to_string(m_IdMaps) + ".tmx";
	LoadMap();
}

void MapManager::LoadMap()
{
	if (!m_Layer)
	{
		return;
	}

	tiledMap = TMXTiledMap::create(m_MapName);

	if (m_IdMaps < 5)
	{
		Tutorial *tutorial = new Tutorial();
		tutorial->Init(m_Layer, "Image/tutorial/tutorial_" + to_string(m_IdMaps) + ".png");
	}

	CreateObjects();
}

void MapManager::LoadNextMap()
{
	DeleteObjects();

	//Next map
	m_IdMaps++;
	m_MapName = "tilemap/FMlv" + to_string(m_IdMaps) + ".tmx";
	LocalData::getInstance()->WriteDadta();

	Scene* scene;
	if (m_IdMaps > NUMLEVEL)
	{
		scene = EndScene::createScene();
	}
	else
	{
		scene = InGameScene::createScene();
	}

	if (scene != nullptr) 
	{
		Director::getInstance()->replaceScene(scene);
	}
}

void MapManager::ResetMap()
{
	DeleteObjects();

	Scene* scene = InGameScene::createScene();
	if (scene != nullptr) 
	{
		Director::getInstance()->replaceScene(scene);
	}
}

void MapManager::SetMap(int m_Num)
{
	DeleteObjects();

	//Next map
	m_IdMaps = m_Num;
	m_MapName = "tilemap/FMlv" + to_string(m_IdMaps) + ".tmx";
}

void MapManager::CreateObjects()
{
	CreatePhysics();
	CreateEnemies();
	CreateMainCharactor();
	CreateInteractive();
	CreateCollectibles();
	CreateGoals();
}

void MapManager::CreatePhysics()
{
	BackGround *m_BackGround = new BackGround();
	m_BackGround->Init(m_Layer);
	m_Objects.push_back(m_BackGround);

	auto colliderMap = tiledMap->getObjectGroup("Physics");
	if (colliderMap)
	{
		for (auto object : colliderMap->getObjects())
		{
			ValueMap value = object.asValueMap();
			string Name = value.at("name").asString();

			if (Name.compare("Wall") == 0)
			{
				Wall *wall = new Wall();
				wall->Init(m_Layer, value);
			}
			else if (Name.compare("Pedestal") == 0)
			{
				Pedestal *pedestal = new Pedestal();
				pedestal->Init(m_Layer, value);
			}
			else if (Name.compare("Floor") == 0)
			{
				Floor *floor = new Floor();
				floor->Init(m_Layer, value, GetBoxCollision(Name + "_box"));
			}
		}
	}
}

void MapManager::CreateMainCharactor()
{
	MainCharacter *m_MCharacter = MainCharacter::getInstance();
	m_MCharacter->Init(m_Layer ,tiledMap->getObjectGroup("MC")->objectNamed("MC"), GetBoxCollision("MC_box"));
}

void MapManager::CreateEnemies() 
{
	auto enemyObject = tiledMap->getObjectGroup("Enemy");
	if (enemyObject)
	{
		for (auto object : enemyObject->getObjects())
		{
			ValueMap value = object.asValueMap();
			string Name = value.at("name").asString();

			MonsterChase *monster = new MonsterChase();
			monster->Init(m_Layer, value, GetBoxCollision(Name + "_box"));
		}
	}
}

void MapManager::CreateCollectibles() {

	//create collectible
	auto collectibles = tiledMap->getObjectGroup("Collectible");

	if (collectibles)
	{
		for (auto object : collectibles->getObjects())
		{
			auto value = object.asValueMap();
			Collectible *collectible = new Collectible();
			collectible->Init(m_Layer, value);
		}
	}
}

void MapManager::CreateGoals()
{
	auto goalObject = tiledMap->getObjectGroup("Goal");
	if (goalObject)
	{
		for (auto object : goalObject->getObjects())
		{
			auto value = object.asValueMap();
			Goal *goal = new Goal();
			goal->Init(m_Layer, value);
		}
	}
}

void MapManager::CreateInteractive()
{

	auto objects = tiledMap->getObjectGroup("Interactive");
	if (!objects)
		return;

	for (auto object : objects->getObjects())
	{
		ValueMap value = object.asValueMap();
		string Name = value.at("name").asString();

		if (Name.compare("Platform") == 0)
		{
			MovingPlatform* platform = new MovingPlatform();
			platform->Init(m_Layer, value);
		}
		else if (Name.compare("Collapse") == 0)
		{
			CollapsePlatform* collapse = new CollapsePlatform();
			collapse->Init(m_Layer, value);
		}
		else if (Name.compare("Door") == 0)
		{
			Door* door = new Door();
			door->Init(m_Layer, value, GetBoxCollision(Name + "_box"));
		}
	}

	for (Value object : objects->getObjects())
	{
		auto value = object.asValueMap();
		string Name = value.at("name").asString();

		if (Name.compare("Lever") == 0)
		{
			int controller = value.at("controlObj").asInt();
			Lever* lever = new Lever();
			for (int id = 0; id < m_Objects.size(); ++id)
			{
				if (m_Objects[id]->getID() == controller)
				{
					lever->Init(m_Layer, value, GetBoxCollision(Name + "_box"), m_Objects[id]);
				}
			}
		}
	}
}

ValueMap MapManager::GetBoxCollision(string name_box)
{
	ValueMap _values;
	_values.clear();

	Vector<TMXObjectGroup*> _gruops = tiledMap->getObjectGroups();
	for (TMXObjectGroup* _objects : _gruops)
	{
		ValueMap _values = _objects->getObject(name_box);
		if (!_values.empty())
		{
			return _values;
		}
	}
	return _values;
}

void MapManager::SetIdMap(int id)
{
	m_IdMaps = id;
}

int MapManager::GetIdMap()
{
	return m_IdMaps;
}

vector<BaseObject*>& MapManager::getObjects()
{
	return m_Objects;
}
