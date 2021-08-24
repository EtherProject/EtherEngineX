#ifndef _NODE_H_
#define _NODE_H_

#include "EtherData.h"
#include "EtherMacros.h"

#include <vector>
#include <lua.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class EtherNode :public EtherData
{
public:
	EtherNode();
	virtual void Release();

protected:
	virtual ~EtherNode();
private:
	//以父节点为基础,节点对应的坐标
	int x, y;
	//节点的z轴坐标,用于描述遮挡关系
	int depth;
	//父节点
	EtherNode* parent;
	//子节点向量
	std::vector<EtherNode*> children;
};

#endif // !_NODE_H_