#pragma once

#include "config.h"

using namespace std;

class LocalData
{
public:
	LocalData();
	~LocalData();

	static LocalData* getInstance();

	//read & write data to Json
	void WriteDadta();
	void ReadData();

	//create new & remove one value on data 
	void NewKeyData(string key, int value);
	void DeleteKeyData(string key);

	//get & set new data
	void setData(string key, int value);
	int getData(string key);

private:
	static LocalData* instance;

	map<string, int> m_data;
};

