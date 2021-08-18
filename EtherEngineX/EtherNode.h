#ifndef _NODE_H_
#define _NODE_H_

#include "EtherData.h"

#include <vector>

class EtherNode :public EtherData
{
private:
	//以父节点为基础,节点对应的坐标
	int x, y;
	//节点的z轴坐标,用于描述遮挡关系
	int z;
	//父节点
	EtherNode* father;
	//子节点向量
	std::vector<EtherNode*> children;
public:
};

#endif // !_NODE_H_