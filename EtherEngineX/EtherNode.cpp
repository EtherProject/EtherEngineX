#include "EtherNode.h"

using namespace std;

EtherNode::EtherNode() : EtherData(), x(0), y(0), depth(0), parent(nullptr)
{
	type = DataType::Node;
	dataInUse[type].push_back(*this);
	key = dataInUse[type].size() - 1;
}

void EtherNode::Release()
{
	vector<EtherData>::iterator temp = dataInUse[type].begin() + key;
	dataInUse[type].erase(temp);
	dataNotInUse[type].push_back(*this);
	key = dataNotInUse[type].size() - 1;
}

EtherNode::~EtherNode()
{
	vector<EtherData>::iterator temp = dataInUse[type].begin() + key;
	dataInUse[type].erase(temp);
}

