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
	//�Ը��ڵ�Ϊ����,�ڵ��Ӧ������
	int x, y;
	//�ڵ��z������,���������ڵ���ϵ
	int depth;
	//���ڵ�
	EtherNode* parent;
	//�ӽڵ�����
	std::vector<EtherNode*> children;
};

#endif // !_NODE_H_