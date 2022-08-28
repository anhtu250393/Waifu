#pragma once

#include "GameObjects/BaseObject.h"
#include "Scene\Menu\InGameScene.h"

class MapManager
{
public:
	MapManager();
	~MapManager();

	static MapManager* getInstance();

	void InitMap(Layer* layer);
	void LoadMap();
	void SetMap(int m_Num);
	void LoadNextMap();
	void ResetMap();
	void DeleteObjects();

	vector<BaseObject*> &getObjects();
	ValueMap GetBoxCollision(string name_box);
	void SetIdMap(int id);
	int GetIdMap();

private:
	void CreateObjects();
	void CreateMainCharactor();
	void CreatePhysics();
	void CreateEnemies();
	void CreateCollectibles();
	void CreateInteractive();
	void CreateGoals();

	static MapManager* instance;
	int m_IdMaps;
	string m_MapName;
	TMXTiledMap* tiledMap;
	Layer* m_Layer;

	vector<BaseObject*> m_Objects;
};