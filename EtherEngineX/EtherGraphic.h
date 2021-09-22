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

	//��ͼx����һ���м���ͼƬ
	unsigned short xAmount = 0;
	//һ���ж���֡
	unsigned short frameAmount = 0;
	//��ͼ�Ĳ����ٶ�(֡/һ��)
	unsigned short playSpeed = 60;
	//��ǰ֡
	unsigned short currentFrame = 0;
	//��ͼ��ʼ���ŵ�ʱ��(���ڼ����л���һ֡��ʲôʱ��)
	unsigned int imageFrameStart = SDL_GetTicks();
	//��ǰʱ��(���ڼ����л���һ֡��ʲôʱ��)
	unsigned int imageFrameEnd = 0;

	SDL_Surface* pSurface = nullptr;
	SDL_Texture* pTexture = nullptr;

	SDL_RendererFlip mode = SDL_FLIP_NONE;
	SDL_Rect imageRect = { 0,0,0,0 };
	SDL_FPoint anchorPoint = { 0,0 };

	//���ü���
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
	//���䶪���ڴ�������
	EtherNode() {}
	//������ڴ�������ɾ��
	~EtherNode() {}
	//���Ƶ�ǰ�ڵ������
	virtual void Draw();
	//�Ը��ڵ����Ͻǵ�������Ϊ�ο�,�ýڵ�ľ���
	SDL_FRect copyRect = { 0,0,0,0 };
	//�ڵ��Ӧ���������
	SDL_FRect worldCopyRect = { 0,0,0,0 };
	//�ڵ��z������,���������ڵ���ϵ
	int depth = -1;
	//�Ƿ��������
	bool isRuning = true;
	//�Ƿ���Ƴ���
	bool isShown = true;
	//��Ӧ����Ⱦ��
	SDL_Renderer* pRenderer = nullptr;
	//��Ӧ��ͼƬ
	EtherImage* pImage = nullptr;
	//���ڵ�
	EtherNode* parent = nullptr;
	//�ӽڵ�����
	std::vector<EtherNode*> children;
};

class EtherNodeAction
{
public:
	//NodeAction�е�ActionȫΪ����,������ʱӦһһɾ��
	~EtherNodeAction();
	//�����Ƿ����,��ɺ�����һ�λᱻɾ��
	bool isDone = false;
	//��ǰ���е��Ķ���
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