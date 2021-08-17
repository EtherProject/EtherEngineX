#include "EtherData.h"
using namespace std;

vector<EtherData*> EtherData::AllData;

EtherData::EtherData()
{
	AllData.push_back(this);
	key = AllData.end();
}

EtherData::~EtherData()
{
	AllData.erase(key);
}