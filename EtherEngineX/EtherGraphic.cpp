#include "EtherGraphic.h"

#include <cmath>

//管理动作的list
std::vector<EtherNodeAction*> vAction;

ModuleGraphic& ModuleGraphic::Instance()
{
	static ModuleGraphic* _instance = new ModuleGraphic();
	return *_instance;
}

EtherText::EtherText(const char* content)
{
	pContent = content;
}

EtherImage::~EtherImage()
{
	SDL_DestroyTexture(pTexture);
}

EtherNodeAction::~EtherNodeAction()
{
	for (int i = vAction.size() - 1; i >= 0; i--)
		delete vAction[i];
}

//各个动作对应的function
std::unordered_map<ACTION_TYPE, std::function<void(EtherNode*, EtherAction*)> > mapFunction =
{
	{ACTION_TYPE::MOVEBY, [](EtherNode* pNode, EtherAction* pAction) ->void
		{
			pNode->copyRect.x += pAction->mPoint.x / pAction->last;
			pNode->copyRect.y += pAction->mPoint.y / pAction->last;
		}
	},

	{ACTION_TYPE::MOVETO, [](EtherNode* pNode, EtherAction* pAction) ->void
		{
			pNode->copyRect.x += (pAction->mPoint.x - pNode->copyRect.x) / (pAction->last - pAction->progress);
			pNode->copyRect.y += (pAction->mPoint.y - pNode->copyRect.y) / (pAction->last - pAction->progress);
		}
	},

	{ACTION_TYPE::SPINTO, [](EtherNode* pNode, EtherAction* pAction) ->void
		{
			if (pAction->mDirection == (Uint8)ROTATION::CLOCKWISE)
			{
				double dAngle = fmod(pAction->mAngle, 360.0);
				double sAngle = fmod(pNode->pImage->angle, 360.0);
				if (dAngle < sAngle)
					pNode->pImage->angle += (dAngle + 360.0 - sAngle) / (pAction->last - pAction->progress);
				else if (dAngle > sAngle)
					pNode->pImage->angle += (dAngle - sAngle) / (pAction->last - pAction->progress);
			}
			else
			{
				double dAngle = fmod(pAction->mAngle, 360.0);
				double sAngle = fmod(pNode->pImage->angle, 360.0);
				if (sAngle < dAngle)
					pNode->pImage->angle -= (sAngle + 360.0 - dAngle) / (pAction->last - pAction->progress);
				else if (sAngle > sAngle)
					pNode->pImage->angle -= (sAngle - dAngle) / (pAction->last - pAction->progress);
			}
		}
	},

	{ACTION_TYPE::SPINBY, [](EtherNode* pNode, EtherAction* pAction) ->void
		{
			pNode->pImage->angle = fmod(pNode->pImage->angle + pAction->mAngle / pAction->last, 360.0);
		}
	},
	{ACTION_TYPE::SCALETO, [](EtherNode* pNode, EtherAction* pAction) ->void
		{
			pNode->copyRect.w += (pAction->mWidth - pNode->copyRect.w) / (pAction->last - pAction->progress);
			pNode->copyRect.h += (pAction->mHeight - pNode->copyRect.h) / (pAction->last - pAction->progress);
		}
	},

	{ACTION_TYPE::FADETO, [](EtherNode* pNode, EtherAction* pAction) ->void
		{
			//由于alpha值为int，而当前的动作管理有可能将其变为小数
			//所以暂时不方便实现FADETO功能
			//敬请之后推出
		}
	}
};

ModuleGraphic::ModuleGraphic()
{
	TTF_Init();
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

	_vCMethods =
	{
		{"LoadImageFromFile", LoadImageFromFile},
		{"LoadImageFromData", LoadImageFromData},
		{"CreateNode", CreateNode},
		{"LoadFontFromFile", LoadFontFromFile},
		{"LoadFontFromData", LoadFontFromData},
		{"CreateTextImage", CreateTextImage}
	};

	_vMacros =
	{
		{"FLIP_HORIZONTAL", SDL_FLIP_HORIZONTAL},
		{"FLIP_VERTICAL", SDL_FLIP_VERTICAL},
		{"FLIP_NONE", SDL_FLIP_NONE},

		{"FONT_STYLE_BOLD", TTF_STYLE_BOLD},
		{"FONT_STYLE_ITALIC", TTF_STYLE_ITALIC},
		{"FONT_STYLE_NORMAL", TTF_STYLE_NORMAL},
		{"FONT_STYLE_STRIKETHROUGH", TTF_STYLE_STRIKETHROUGH},
		{"FONT_STYLE_UNDERLINE", TTF_STYLE_UNDERLINE},

		{"TEXT_PATTERN_SOLID", (int)TEXT_PATTERN::SOLID},
		{"TEXT_PATTERN_SHADED", (int)TEXT_PATTERN::SHADED},
		{"TEXT_PATTERN_BLENDED", (int)TEXT_PATTERN::BLENDED},

		{"CODE_FORMAT_NORMAL", (int)CODE_FORMAT::NORMAL},
		{"CODE_FORMAT_UTF8", (int)CODE_FORMAT::UTF8}
	};

	_vMetaData =
	{
		{
			"EtherImage",
			nullptr,
			{
				{"SetImageDynamic", image_SetImageDynamic},
				{"SetRendererFlip", image_SetRendererFlip},
				{"SetAnchorPoint", image_SetAnchorPoint},
				{"GetAnchorPoint", image_GetAnchorPoint},
				{"SetImageRect", image_SetImageRect},
				{"GetImageRect", image_GetImageRect},
				{"SetAlpha", image_SetAlpha},
				{"GetAlpha", image_GetAlpha},
				{"SetPlaySpeed", image_SetPlaySpeed},
				{"GetPlaySpeed", image_GetPlaySpeed},
				{"SetCurrentFrame", image_SetCurrentFrame},
				{"GetCurrentFrame", image_GetCurrentFrame},
				{"SetAngle", image_SetAngle},
				{"GetAngle", image_GetAngle}
			},
			__gc_Image
		},

		{
			"EtherText",
			"EtherImage",
			{
				{"GetContent", text_GetContent},
				{"ResetText", text_ResetText}
			},
			__gc_Text
		},

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
				{"DeleteChild", node_DeleteChild},
				{"RunAction", node_RunAction},
				{"SetPause", node_SetPause}
			},
			__gc_Node
		},

		{
			"EtherFont",
			nullptr,
			{
				{"GetStyle", font_GetStyle},
				{"SetStyle", font_SetStyle},
				{"GetOutlineWidth", font_GetOutlineWidth},
				{"SetOutlineWidth", font_SetOutlineWidth},
				{"GetKerning", font_GetKerning},
				{"SetKerning", font_SetKerning},
				{"GetHeight", font_GetHeight},
				{"GetTextSize", font_GetTextSize},
				{"GetUTF8TextSize", font_GetUTF8TextSize}
			},
			__gc_Font
		}
	};
}

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
	worldCopyRect.w = copyRect.w;
	worldCopyRect.h = copyRect.h;

	if (pImage->isDynamic)
	{
		pImage->imageFrameEnd = SDL_GetTicks();
		if ((pImage->imageFrameEnd - pImage->imageFrameStart) * (ETHER_FRAME / 1000) >= pImage->playSpeed)
		{
			pImage->imageFrameStart = pImage->imageFrameEnd;
			pImage->imageRect.x = (pImage->currentFrame % pImage->xAmount) * pImage->imageRect.w;
			pImage->imageRect.y = (pImage->currentFrame / pImage->xAmount) * pImage->imageRect.h;
			SDL_RenderCopyExF(pRenderer, pImage->pTexture, &pImage->imageRect, &worldCopyRect, pImage->angle, &pImage->anchorPoint, pImage->mode);
			pImage->currentFrame = (pImage->currentFrame + 1) % pImage->frameAmount;
		}
		else
			SDL_RenderCopyExF(pRenderer, pImage->pTexture, &pImage->imageRect, &worldCopyRect, pImage->angle, &pImage->anchorPoint, pImage->mode);
	}
	else
		SDL_RenderCopyExF(pRenderer, pImage->pTexture, &pImage->imageRect, &worldCopyRect, pImage->angle, &pImage->anchorPoint, pImage->mode);

	if (!children.empty())
		for (vector<EtherNode*>::iterator iter = children.begin(); iter != children.end(); iter++)
			(*iter)->Draw();
}

ETHER_API LoadImageFromFile(lua_State* L)
{
	EtherImage* pImage = new EtherImage();

	pImage->pSurface = IMG_Load(luaL_checkstring(L, 1));
	luaL_argcheck(L, pImage->pSurface, 1, "load image from data failed");

	pImage->imageRect.x = 0;
	pImage->imageRect.y = 0;
	pImage->imageRect.w = pImage->pSurface->w;
	pImage->imageRect.h = pImage->pSurface->h;

	EtherImage** uppImage = (EtherImage**)lua_newuserdata(L, sizeof(EtherImage*));
	*uppImage = pImage;
	luaL_getmetatable(L, "EtherImage");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API LoadImageFromData(lua_State* L)
{
	EtherImage* pImage = new EtherImage();

	size_t size = 0;
	pImage->pSurface = IMG_Load_RW(SDL_RWFromMem((void*)luaL_checklstring(L, 1, &size), size), 1);
	luaL_argcheck(L, pImage->pSurface, 1, "load image from data failed");

	pImage->imageRect.x = 0;
	pImage->imageRect.y = 0;
	pImage->imageRect.w = pImage->pSurface->w;
	pImage->imageRect.h = pImage->pSurface->h;

	EtherImage** uppImage = (EtherImage**)lua_newuserdata(L, sizeof(EtherImage*));
	*uppImage = pImage;
	luaL_getmetatable(L, "EtherImage");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API image_SetImageDynamic(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));
	pImage->isDynamic = lua_toboolean(L, 2);

	if (pImage->isDynamic)
	{
		if (lua_isnumber(L, 3))
		{
			//如果是动图则需要自己告诉程序一共有多少帧
			//以及动图每帧图片的大小
			pImage->frameAmount = lua_tonumber(L, 3);
			pImage->imageRect.w = lua_tonumber(L, 4);
			pImage->imageRect.h = lua_tonumber(L, 5);
			pImage->xAmount = pImage->pSurface->w / pImage->imageRect.w;
		}
		else
		{
			pImage->isDynamic = false;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error Occured:", "The frame's amount must be a number!", nullptr);
		}
	}
	return 0;
}

ETHER_API image_SetAnchorPoint(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));
	pImage->anchorPoint.x = lua_tonumber(L, 2);
	pImage->anchorPoint.y = lua_tonumber(L, 3);

	return 0;
}

ETHER_API image_GetAnchorPoint(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));

	lua_newtable(L);
	lua_pushstring(L, "x");
	lua_pushnumber(L, pImage->anchorPoint.x);
	lua_settable(L, -3);
	lua_pushstring(L, "y");
	lua_pushnumber(L, pImage->anchorPoint.y);
	lua_settable(L, -3);

	return 1;
}

ETHER_API image_SetRendererFlip(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));

	lua_pushnil(L);
	while (lua_next(L, 2))
	{
		if (!lua_isnumber(L, -1))
		{
			luaL_error(L, "bad argument #1 to 'SetRendererFlip' (table elements must be MACRO number, got %s)", luaL_typename(L, -1));
		}
		else
		{
			switch ((int)lua_tonumber(L, -1))
			{
			case SDL_FLIP_HORIZONTAL:
				pImage->mode = (SDL_RendererFlip)(pImage->mode | SDL_FLIP_HORIZONTAL);
				break;
			case SDL_FLIP_VERTICAL:
				pImage->mode = (SDL_RendererFlip)(pImage->mode | SDL_FLIP_VERTICAL);
				break;
			case SDL_FLIP_NONE:
				pImage->mode = (SDL_RendererFlip)(pImage->mode | SDL_FLIP_NONE);
				break;
			default:
				luaL_error(L, "bad argument #1 to 'SetRendererFlip' (table elements must be MACRO number, got %s)", luaL_typename(L, -1));
				break;
			}
		}
		lua_pop(L, 1);
	}

	return 0;
}

ETHER_API image_SetImageRect(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));

	SDL_Rect reshapeRect = GetRectParam(L, 2);
	pImage->imageRect = reshapeRect;

	return 0;
}

ETHER_API image_GetImageRect(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));

	lua_newtable(L);
	lua_pushstring(L, "x");
	lua_pushnumber(L, pImage->imageRect.x);
	lua_settable(L, -3);
	lua_pushstring(L, "y");
	lua_pushnumber(L, pImage->imageRect.y);
	lua_settable(L, -3);
	lua_pushstring(L, "w");
	lua_pushnumber(L, pImage->imageRect.w);
	lua_settable(L, -3);
	lua_pushstring(L, "h");
	lua_pushnumber(L, pImage->imageRect.h);
	lua_settable(L, -3);

	return 1;
}

ETHER_API image_SetAlpha(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));

	if (pImage->refCount != 0)
		SDL_SetTextureAlphaMod(pImage->pTexture, luaL_checknumber(L, 2));
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Error Occured During Setting Alpha", "You can't set alpha for a unopened image!", nullptr);

	return 0;
}

ETHER_API image_GetAlpha(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));

	Uint8 alpha;
	SDL_GetTextureAlphaMod(pImage->pTexture, &alpha);
	lua_pushnumber(L, alpha);

	return 1;
}

ETHER_API image_SetPlaySpeed(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));
	unsigned short playSpeed = lua_tonumber(L, 2);
	pImage->playSpeed = playSpeed;

	return 0;
}

ETHER_API image_GetPlaySpeed(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));
	lua_pushnumber(L, pImage->playSpeed);

	return 1;
}

ETHER_API image_SetCurrentFrame(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));
	if (pImage->isDynamic)
	{
		pImage->currentFrame = lua_tonumber(L, 2);
		pImage->imageRect.x = (pImage->currentFrame % pImage->xAmount) * pImage->imageRect.w;
		pImage->imageRect.y = (pImage->currentFrame / pImage->xAmount) * pImage->imageRect.h;
	}
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Frame Failed", "You can't set frame for a static image", nullptr);

	return 0;
}

ETHER_API image_GetCurrentFrame(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));
	if (pImage->isDynamic)
		lua_pushnumber(L, pImage->currentFrame);
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Get Frame Failed", "You can't get frame from a static image", nullptr);

	return 1;
}

ETHER_API image_SetAngle(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));
	double angle = lua_tonumber(L, 2);

	return 0;
}

ETHER_API image_GetAngle(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 1));
	lua_pushnumber(L, pImage->angle);

	return 1;
}

ETHER_API __gc_Image(lua_State* L)
{
	EtherImage* pImage = (EtherImage*)(*(void**)luaL_checkudata(L, 1, "EtherImage"));
	delete pImage;

	return 0;
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
	EtherImage* pImage = (EtherImage*)(*(void**)lua_touserdata(L, 2));

	if (pImage == pNode->pImage) 
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Set Image Failed", "Same as current image", nullptr);;

	if (pImage != nullptr)
	{
		if (pNode->pImage != nullptr)
			if (--pNode->pImage->refCount == 0)
				SDL_DestroyTexture(pNode->pImage->pTexture);

		if (pImage->refCount == 0)
		{
			pImage->pTexture = SDL_CreateTextureFromSurface(pNode->pRenderer, pImage->pSurface);
			SDL_SetTextureBlendMode(pImage->pTexture, SDL_BLENDMODE_BLEND);
		}
		pImage->refCount++;
		pNode->pImage = pImage;
	}
	else
	{
		if (--pNode->pImage->refCount == 0)
			SDL_DestroyTexture(pNode->pImage->pTexture);
		pNode->pImage = nullptr;
	}

	return 0;
}

ETHER_API node_GetImage(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));

	EtherImage** uppImage = (EtherImage**)lua_newuserdata(L, sizeof(EtherImage*));
	*uppImage = pNode->pImage;
	luaL_getmetatable(L, "EtherImage");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API node_SetCopyRect(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));

	SDL_FRect rect = GetFRectParam(L, 2);
	pNode->copyRect.x = rect.x;
	pNode->copyRect.y = rect.y;
	pNode->copyRect.w = rect.w;
	pNode->copyRect.h = rect.h;

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
	pNode->pRenderer = parent->pRenderer;
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

	pChild->pRenderer = pNode->pRenderer;
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

ETHER_API node_RunAction(lua_State* L)
{
	using namespace std;

	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));
	int size = lua_gettop(L);

	EtherNodeAction* pNodeAction = new EtherNodeAction();
	pNodeAction->pNode = pNode;

	EtherAction* pAction;

	//将需要加入的动作塞进去
	for (int i = 2; i <= size; i++)
	{
		pAction = (EtherAction*)(*(void**)lua_touserdata(L, i));
		EtherAction* pActionCopy = new EtherAction(*pAction);

		pNodeAction->vAction.emplace_back(pActionCopy);
		pNodeAction->vNodeAction.emplace_back(mapFunction[pActionCopy->type]);
	}

	//交给动作管理列表
	vAction.push_back(pNodeAction);

	return 0;
}

ETHER_API node_SetPause(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));
	pNode->isRuning = lua_toboolean(L, 2);

	return 0;
}

ETHER_API __gc_Node(lua_State* L)
{
	EtherNode* pNode = (EtherNode*)(*(void**)lua_touserdata(L, 1));
	delete pNode;

	return 0;
}

ETHER_API LoadFontFromFile(lua_State* L)
{
	TTF_Font* pFont = TTF_OpenFont(luaL_checkstring(L, 1), luaL_checknumber(L, 2));
	luaL_argcheck(L, pFont, 1, "load font failed");

	TTF_Font** uppFont = (TTF_Font**)lua_newuserdata(L, sizeof(TTF_Font*));
	*uppFont = pFont;
	luaL_getmetatable(L, "EtherFont");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API LoadFontFromData(lua_State* L)
{
	size_t size = 0;
	TTF_Font* pFont = TTF_OpenFontRW(SDL_RWFromMem((void*)luaL_checklstring(L, 1, &size), size), 1, luaL_checknumber(L, 2));
	luaL_argcheck(L, pFont, 1, "load font failed");

	TTF_Font** uppFont = (TTF_Font**)lua_newuserdata(L, sizeof(TTF_Font*));
	*uppFont = pFont;
	luaL_getmetatable(L, "EtherFont");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API font_GetStyle(lua_State* L)
{
	TTF_Font* pFont = (TTF_Font*)(*(void**)luaL_checkudata(L, 1, "EtherFont"));
	luaL_argcheck(L, pFont, 1, "get font failed");

	lua_newtable(L);
	int style = TTF_GetFontStyle(pFont);
	if (style == TTF_STYLE_NORMAL)
	{
		lua_pushnumber(L, 1);
		lua_pushnumber(L, TTF_STYLE_NORMAL);
		lua_settable(L, -3);
	}
	else
	{
		int index = 1;
		if (style & TTF_STYLE_BOLD)
		{
			lua_pushnumber(L, index);
			lua_pushnumber(L, TTF_STYLE_BOLD);
			lua_settable(L, -3);
			index++;
		}
		if (style & TTF_STYLE_ITALIC)
		{
			lua_pushnumber(L, index);
			lua_pushnumber(L, TTF_STYLE_ITALIC);
			lua_settable(L, -3);
			index++;
		}
		if (style & TTF_STYLE_UNDERLINE)
		{
			lua_pushnumber(L, index);
			lua_pushnumber(L, TTF_STYLE_UNDERLINE);
			lua_settable(L, -3);
			index++;
		}
		if (style & TTF_STYLE_STRIKETHROUGH)
		{
			lua_pushnumber(L, index);
			lua_pushnumber(L, TTF_STYLE_STRIKETHROUGH);
			lua_settable(L, -3);
			index++;
		}
	}
	return 1;
}

ETHER_API font_SetStyle(lua_State* L)
{
	TTF_Font* pFont = (TTF_Font*)(*(void**)luaL_checkudata(L, 1, "EtherFont"));
	luaL_argcheck(L, pFont, 1, "get font failed");
	luaL_argcheck(L, lua_istable(L, 2), 2, "table expected");

	int style = 0;
	lua_pushnil(L);
	while (lua_next(L, 2))
	{
		lua_pushvalue(L, -2);
		if (!lua_isnumber(L, -2))
			luaL_error(L, "bad argument #2 to 'SetFontStyle' (table elements must be MACRO number, got %s)", luaL_typename(L, -2));
		else
		{
			switch ((int)lua_tonumber(L, -2))
			{
			case TTF_STYLE_BOLD:
				style |= TTF_STYLE_BOLD;
				break;
			case TTF_STYLE_ITALIC:
				style |= TTF_STYLE_ITALIC;
				break;
			case TTF_STYLE_UNDERLINE:
				style |= TTF_STYLE_UNDERLINE;
				break;
			case TTF_STYLE_STRIKETHROUGH:
				style |= TTF_STYLE_STRIKETHROUGH;
				break;
			case TTF_STYLE_NORMAL:
				style |= TTF_STYLE_NORMAL;
				break;
			default:
				luaL_error(L, "bad argument #2 to 'SetFontStyle' (table elements must be MACRO number, got %s)", luaL_typename(L, -2));
				break;
			}
		}
		lua_pop(L, 2);
	}

	TTF_SetFontStyle(pFont, style);

	return 0;
}

ETHER_API font_GetOutlineWidth(lua_State* L)
{
	TTF_Font* pFont = (TTF_Font*)(*(void**)luaL_checkudata(L, 1, "EtherFont"));
	luaL_argcheck(L, pFont, 1, "get font failed");

	lua_pushnumber(L, TTF_GetFontOutline(pFont));

	return 1;
}


ETHER_API font_SetOutlineWidth(lua_State* L)
{
	TTF_Font* pFont = (TTF_Font*)(*(void**)luaL_checkudata(L, 1, "EtherFont"));
	luaL_argcheck(L, pFont, 1, "get font failed");

	TTF_SetFontOutline(pFont, luaL_checknumber(L, 2));

	return 0;
}

ETHER_API font_GetKerning(lua_State* L)
{
	TTF_Font* pFont = (TTF_Font*)(*(void**)luaL_checkudata(L, 1, "EtherFont"));
	luaL_argcheck(L, pFont, 1, "get font failed");

	lua_pushnumber(L, TTF_GetFontKerning(pFont));

	return 1;
}


ETHER_API font_SetKerning(lua_State* L)
{
	TTF_Font* pFont = (TTF_Font*)(*(void**)luaL_checkudata(L, 1, "EtherFont"));
	luaL_argcheck(L, pFont, 1, "get font failed");

	TTF_SetFontKerning(pFont, luaL_checknumber(L, 2));

	return 0;
}


ETHER_API font_GetHeight(lua_State* L)
{
	TTF_Font* pFont = (TTF_Font*)(*(void**)luaL_checkudata(L, 1, "EtherFont"));
	luaL_argcheck(L, pFont, 1, "get font failed");

	lua_pushnumber(L, TTF_FontHeight(pFont));

	return 1;
}


ETHER_API font_GetTextSize(lua_State* L)
{
	TTF_Font* pFont = (TTF_Font*)(*(void**)luaL_checkudata(L, 1, "EtherFont"));
	luaL_argcheck(L, pFont, 1, "get font failed");

	int width, height;
	TTF_SizeText(pFont, luaL_checkstring(L, 2), &width, &height);
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);

	return 2;
}


ETHER_API font_GetUTF8TextSize(lua_State* L)
{
	TTF_Font* pFont = (TTF_Font*)(*(void**)luaL_checkudata(L, 1, "EtherFont"));
	luaL_argcheck(L, pFont, 1, "get font failed");

	int width, height;
	TTF_SizeUTF8(pFont, luaL_checkstring(L, 2), &width, &height);
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);

	return 2;
}

ETHER_API __gc_Font(lua_State* L)
{
	TTF_Font* pFont = (TTF_Font*)(*(void**)luaL_checkudata(L, 1, "EtherFont"));
	luaL_argcheck(L, pFont, 1, "get font failed");

	TTF_CloseFont(pFont);
	pFont = nullptr;

	return 0;
}

ETHER_API CreateTextImage(lua_State* L)
{
	TTF_Font* pFont = (TTF_Font*)(*(void**)luaL_checkudata(L, 1, "EtherFont"));
	luaL_argcheck(L, pFont, 1, "get font failed");

	const char* content = luaL_checkstring(L, 2);
	TEXT_PATTERN paramPattern = (TEXT_PATTERN)lua_tonumber(L, -2);
	CODE_FORMAT paramFormat = (CODE_FORMAT)lua_tonumber(L, -1);

	EtherText* pText = new EtherText(content);
	switch (paramPattern)
	{
	case TEXT_PATTERN::SOLID:
		SDL_Color color = GetColorParam(L, 3);
		if (paramFormat == CODE_FORMAT::NORMAL)
			pText->pSurface = TTF_RenderText_Solid(pFont, content, color);
		else
			pText->pSurface = TTF_RenderUTF8_Solid(pFont, content, color);
		break;
	case TEXT_PATTERN::SHADED:
		SDL_Color fgColor = GetColorParam(L, 3);
		SDL_Color bgColor = GetColorParam(L, 4);
		if (paramFormat == CODE_FORMAT::NORMAL)
			pText->pSurface = TTF_RenderText_Shaded(pFont, content, fgColor, bgColor);
		else
			pText->pSurface = TTF_RenderUTF8_Shaded(pFont, content, fgColor, bgColor);
		break;
	case TEXT_PATTERN::BLENDED:
		SDL_Color _color = GetColorParam(L, 3);
		if (paramFormat == CODE_FORMAT::NORMAL)
			pText->pSurface = TTF_RenderText_Blended(pFont, content, _color);
		else
			pText->pSurface = TTF_RenderUTF8_Blended(pFont, content, _color);
	}
	luaL_argcheck(L, pText->pSurface, 1, "create text image failed");

	pText->imageRect.x = 0;
	pText->imageRect.y = 0;
	pText->imageRect.w = pText->pSurface->w;
	pText->imageRect.h = pText->pSurface->h;

	EtherText** uppText = (EtherText**)lua_newuserdata(L, sizeof(EtherText*));
	*uppText = pText;
	luaL_getmetatable(L, "EtherText");
	lua_setmetatable(L, -2);

	return 1;
}

ETHER_API text_ResetText(lua_State* L)
{
	TTF_Font* pFont = (TTF_Font*)(*(void**)luaL_checkudata(L, 1, "EtherFont"));
	luaL_argcheck(L, pFont, 1, "get font failed");

	const char* content = luaL_checkstring(L, 2);
	TEXT_PATTERN paramPattern = (TEXT_PATTERN)lua_tonumber(L, -2);
	CODE_FORMAT paramFormat = (CODE_FORMAT)lua_tonumber(L, -1);

	EtherText* pText = new EtherText(content);
	switch (paramPattern)
	{
	case TEXT_PATTERN::SOLID:
		SDL_Color color = GetColorParam(L, 3);
		if (paramFormat == CODE_FORMAT::NORMAL)
			pText->pSurface = TTF_RenderText_Solid(pFont, content, color);
		else
			pText->pSurface = TTF_RenderUTF8_Solid(pFont, content, color);
		break;
	case TEXT_PATTERN::SHADED:
		SDL_Color fgColor = GetColorParam(L, 3);
		SDL_Color bgColor = GetColorParam(L, 4);
		if (paramFormat == CODE_FORMAT::NORMAL)
			pText->pSurface = TTF_RenderText_Shaded(pFont, content, fgColor, bgColor);
		else
			pText->pSurface = TTF_RenderUTF8_Shaded(pFont, content, fgColor, bgColor);
		break;
	case TEXT_PATTERN::BLENDED:
		SDL_Color _color = GetColorParam(L, 3);
		if (paramFormat == CODE_FORMAT::NORMAL)
			pText->pSurface = TTF_RenderText_Blended(pFont, content, _color);
		else
			pText->pSurface = TTF_RenderUTF8_Blended(pFont, content, _color);
	}
	return 0;
}

ETHER_API text_GetContent(lua_State* L)
{
	EtherText* pText = (EtherText*)(*(void**)luaL_checkudata(L, 1, "EtherText"));
	lua_pushstring(L, pText->pContent);

	return 1;
}

ETHER_API __gc_Text(lua_State* L)
{
	EtherText* pText = (EtherText*)(*(void**)luaL_checkudata(L, 1, "EtherText"));
	delete pText;

	return 0;
}