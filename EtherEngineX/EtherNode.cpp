#include "EtherNode.h"

ModuleNode& ModuleNode::Instance()
{
	static ModuleNode* _instance = new ModuleNode();
	return *_instance;
}

ModuleNode::ModuleNode()
{
	_vCMethods =
	{
		{"CreateNode", CreateNode}
	};

	_vMetaData =
	{
		{
			"EtherNode",
			nullptr,
			{
				{"SetImage", node_SetImage},
				{"GetImage", node_GetImage},
				{"SetCopyRect", node_SetCopyRect},
				{"GetCopyRect", node_GetCopyRect},
				{"SetParent", node_SetParent},
				{"GetParent", node_GetParent},
				{"SetDepth", node_SetDepth},
				{"GetDepth", node_GetDepth},
				{"AddChild", node_AddChild},
				{"DeleteChild", node_DeleteChild}
			},
			__gc_Node
		}
	};
}

//这里应当再实现子节点随父节点的移动而移动
void EtherNode::Draw()
{
	using namespace std;

	if (parent != nullptr)
	{
		worldCopyRect.x = parent->worldCopyRect.x + copyRect.x;
		worldCopyRect.y = parent->worldCopyRect.y + copyRect.y;
	}
	else
	{
		worldCopyRect.x = copyRect.x;
		worldCopyRect.y = copyRect.y;
	}

	if (pImage->isRotated)
	{
		if (pImage->isDynamic)
		{
			pImage->imageFrameEnd = SDL_GetTicks();
			if ((pImage->imageFrameEnd - pImage->imageFrameStart) * 0.06 >= pImage->playSpeed)
			{
				pImage->imageFrameStart = pImage->imageFrameEnd;
				pImage->imageRect.x = (pImage->currentFrame % pImage->xAmount) * pImage->imageRect.w;
				pImage->imageRect.y = (pImage->currentFrame / pImage->xAmount) * pImage->imageRect.h;
				SDL_RenderCopyEx(pRenderer, pImage->pTexture, &pImage->imageRect, &worldCopyRect, pImage->angle, &pImage->anchorPoint, pImage->mode);
				pImage->currentFrame = (pImage->currentFrame + 1) % pImage->frameAmount;
			}
			else
				SDL_RenderCopyEx(pRenderer, pImage->pTexture, &pImage->imageRect, &worldCopyRect, pImage->angle, &pImage->anchorPoint, pImage->mode);
		}
		else
			SDL_RenderCopyEx(pRenderer, pImage->pTexture, &pImage->imageRect, &worldCopyRect, pImage->angle, &pImage->anchorPoint, pImage->mode);
	}
	else
	{
		if (pImage->isDynamic)
		{
			pImage->imageFrameEnd = SDL_GetTicks();
			if ((pImage->imageFrameEnd - pImage->imageFrameStart) * 0.06 >= pImage->playSpeed)
			{
				pImage->imageFrameStart = pImage->imageFrameEnd;
				pImage->imageRect.x = (pImage->currentFrame % pImage->xAmount) * pImage->imageRect.w;
				pImage->imageRect.y = (pImage->currentFrame / pImage->xAmount) * pImage->imageRect.h;
				SDL_RenderCopy(pRenderer, pImage->pTexture, &pImage->imageRect, &worldCopyRect);
				pImage->currentFrame = (pImage->currentFrame + 1) % pImage->frameAmount;
			}
			else
				SDL_RenderCopy(pRenderer, pImage->pTexture, &pImage->imageRect, &worldCopyRect);
		}
		else
			SDL_RenderCopy(pRenderer, pImage->pTexture, &pImage->imageRect, &worldCopyRect);
	}
	
	if (!children.empty())
		for (vector<EtherNode*>::iterator iter = children.begin(); iter != children.end(); iter++)
			(*iter)->Draw();
}

ETHER_API CreateNode(lua_State* L)
{
	EtherNode* pNode = new EtherNode();
	EtherNode** uppNode = (EtherNode**)lua_newuserdata(L, sizeof(EtherNode*));
	*uppNode = pNode;
	luaL_getmetatable(L, "EtherNode");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API node_SetImage(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 2, "EtherImage"));

	pImage->pTexture = SDL_CreateTextureFromSurface(pNode->pRenderer, pImage->pSurface);
	pImage->isOpened = true;

	pNode->pImage = pImage;

	return 0;
}

ETHER_API node_GetImage(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));

	EtherImage** uppImage = (EtherImage**)lua_newuserdata(L, sizeof(EtherImage*));
	*uppImage = pNode->pImage;
	luaL_getmetatable(L, "EtherImage");
	lua_setmetatable(L, -2);

	return 0;
}

ETHER_API node_SetCopyRect(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));

	SDL_Rect rect = GetRectParam(L, 2);
	pNode->copyRect.x = rect.x;
	pNode->copyRect.y = rect.y;
	pNode->copyRect.w = rect.w;
	pNode->copyRect.h = rect.h;
	pNode->worldCopyRect.w = rect.w;
	pNode->worldCopyRect.h = rect.h;

	return 0;
}

ETHER_API node_GetCopyRect(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));

	lua_newtable(L);
	lua_pushstring(L, "x");
	lua_pushnumber(L, pNode->copyRect.x);
	lua_settable(L, -3);
	lua_pushstring(L, "y");
	lua_pushnumber(L, pNode->copyRect.y);
	lua_settable(L, -3);
	lua_pushstring(L, "w");
	lua_pushnumber(L, pNode->copyRect.w);
	lua_settable(L, -3);
	lua_pushstring(L, "h");
	lua_pushnumber(L, pNode->copyRect.h);
	lua_settable(L, -3);

	return 1;
}

ETHER_API node_SetParent(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));
	EtherNode* parent = (EtherNode*)(*(void**)lua_touserdata(L, 2));
	pNode->parent = parent;
	parent->children.push_back(pNode);

	return 0;
}

ETHER_API node_GetParent(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));
	EtherNode** uppNode = (EtherNode**)lua_newuserdata(L, sizeof(EtherNode*));
	*uppNode = pNode->parent;
	luaL_getmetatable(L, "EtherNode");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API node_SetDepth(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));
	int depth = lua_tonumber(L, 2);
	pNode->depth = depth;

	return 0;
}

ETHER_API node_GetDepth(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));
	lua_pushnumber(L, pNode->depth);

	return 1;
}

ETHER_API node_AddChild(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));
	EtherNode* pChild = (EtherNode*)(*(void**)lua_touserdata(L, 2));
	pNode->children.push_back(pChild);
	pChild->parent = pNode;

	return 0;
}

ETHER_API node_DeleteChild(lua_State* L)
{
	using namespace std;
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));
	int index = lua_tonumber(L, 2) - 1;
	pNode->children[index]->parent = nullptr;
	vector<EtherNode*>::iterator iterNode = pNode->children.begin() + index;
	pNode->children.erase(iterNode);
	
	return 0;
}

ETHER_API __gc_Node(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));
	delete pNode;

	return 0;
}