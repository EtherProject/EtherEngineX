#ifndef _NODE_H_
#define _NODE_H_

#include "EtherAction.h"

#include <vector>
#include <lua.hpp>
#include <SDL_image.h>
#include <SDL_ttf.h>

class EtherImage
{
public:
	EtherImage() {}

	virtual ~EtherImage();

	bool isDynamic = false;
	double angle = 0;

	//动图x轴上一共有几张图片
	unsigned short xAmount = 0;
	//一共有多少帧
	unsigned short frameAmount = 0;
	//动图的播放速度(帧/一次)
	unsigned short playSpeed = 60;
	//当前帧
	unsigned short currentFrame = 0;
	//动图开始播放的时间(用于计算切换下一帧是什么时候)
	unsigned int imageFrameStart = SDL_GetTicks();
	//当前时间(用于计算切换下一帧是什么时候)
	unsigned int imageFrameEnd = 0;

	SDL_Surface* pSurface = nullptr;
	SDL_Texture* pTexture = nullptr;

	SDL_RendererFlip mode = SDL_FLIP_NONE;
	SDL_Rect imageRect = { 0,0,0,0 };
	SDL_FPoint anchorPoint = { 0,0 };

	//引用计数
	int refCount = 0;
};

enum class TEXT_PATTERN
{
	SOLID = 0,
	SHADED,
	BLENDED
};

enum class CODE_FORMAT
{
	NORMAL = 0,
	UTF8
};

class EtherText : public EtherImage
{
public:
	EtherText(const char*);
	~EtherText() {}

	const char* pContent = nullptr;
	TEXT_PATTERN pattern = TEXT_PATTERN::BLENDED;
	CODE_FORMAT format = CODE_FORMAT::NORMAL;
};

class EtherNode
{
public:
	//将其丢进内存管理池中
	EtherNode() {}
	//将其从内存管理池中删除
	~EtherNode() {}
	//绘制当前节点的内容
	virtual void Draw();
	//以父节点左上角的坐标作为参考,该节点的矩形
	SDL_FRect copyRect = { 0,0,0,0 };
	//节点对应的世界矩形
	SDL_FRect worldCopyRect = { 0,0,0,0 };
	//节点的z轴坐标,用于描述遮挡关系
	int depth = -1;
	//是否持续更新
	bool isRuning = true;
	//是否绘制出来
	bool isShown = true;
	//对应的渲染器
	SDL_Renderer* pRenderer = nullptr;
	//对应的图片
	EtherImage* pImage = nullptr;
	//父节点
	EtherNode* parent = nullptr;
	//子节点向量
	std::vector<EtherNode*> children;
};

class EtherNodeAction
{
public:
	//NodeAction中的Action全为副本,在析构时应一一删除
	~EtherNodeAction();
	//动作是否完成,完成后在下一次会被删除
	bool isDone = false;
	//当前运行到的动作
	unsigned int index = 0;

	EtherNode* pNode;

	std::vector<EtherAction*> vAction;

	std::vector<std::function<void(EtherNode*, EtherAction*)> > vNodeAction;
};

class ModuleGraphic : public EtherModule
{
public:
	static ModuleGraphic& Instance();
	~ModuleGraphic() {}
private:
	ModuleGraphic();
};

ETHER_API LoadImageFromFile(lua_State* L);

ETHER_API LoadImageFromData(lua_State* L);

ETHER_API image_SetImageDynamic(lua_State* L);

ETHER_API image_SetRendererFlip(lua_State* L);

ETHER_API image_SetAnchorPoint(lua_State* L);

ETHER_API image_GetAnchorPoint(lua_State* L);

ETHER_API image_SetImageRect(lua_State* L);

ETHER_API image_GetImageRect(lua_State* L);

ETHER_API image_SetAlpha(lua_State* L);

ETHER_API image_GetAlpha(lua_State* L);

ETHER_API image_SetPlaySpeed(lua_State* L);

ETHER_API image_GetPlaySpeed(lua_State* L);

ETHER_API image_SetCurrentFrame(lua_State* L);

ETHER_API image_GetCurrentFrame(lua_State* L);

ETHER_API image_SetAngle(lua_State* L);

ETHER_API image_GetAngle(lua_State* L);

ETHER_API __gc_Image(lua_State* L);

ETHER_API CreateNode(lua_State* L);

ETHER_API node_SetImage(lua_State* L);

ETHER_API node_GetImage(lua_State* L);

ETHER_API node_SetCopyRect(lua_State* L);

ETHER_API node_GetCopyRect(lua_State* L);

ETHER_API node_SetParent(lua_State* L);

ETHER_API node_GetParent(lua_State* L);

ETHER_API node_SetDepth(lua_State* L);

ETHER_API node_GetDepth(lua_State* L);

ETHER_API node_AddChild(lua_State* L);

ETHER_API node_DeleteChild(lua_State* L);

ETHER_API node_RunAction(lua_State* L);

ETHER_API node_SetPause(lua_State* L);

ETHER_API __gc_Node(lua_State* L);

ETHER_API LoadFontFromFile(lua_State* L);

ETHER_API LoadFontFromData(lua_State* L);

ETHER_API font_GetStyle(lua_State* L);

ETHER_API font_SetStyle(lua_State* L);

ETHER_API font_GetOutlineWidth(lua_State* L);

ETHER_API font_SetOutlineWidth(lua_State* L);

ETHER_API font_GetKerning(lua_State* L);

ETHER_API font_SetKerning(lua_State* L);

ETHER_API font_GetHeight(lua_State* L);

ETHER_API font_GetTextSize(lua_State* L);

ETHER_API font_GetUTF8TextSize(lua_State* L);

ETHER_API __gc_Font(lua_State* L);

ETHER_API CreateTextImage(lua_State* L);

ETHER_API text_ResetText(lua_State* L);

ETHER_API text_GetContent(lua_State* L);

ETHER_API __gc_Text(lua_State* L);

#endif // !_NODE_H_