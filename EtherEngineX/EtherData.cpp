#include "EtherData.h"

vector<EtherData*> EtherData::AllData;

EtherData::EtherData()
{
	AllData.push_back(this);
	key = AllData.end();
	cout << "There has a data created, now the vector has" << endl;
	for (auto iter = AllData.begin(); iter != AllData.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
}

EtherData::~EtherData()
{
	AllData.erase(key);
	cout << "There has a data deleted, now the vector has" << endl;
	for (auto iter = AllData.begin(); iter != AllData.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
}