#ifndef _NODE_H_
#define _NODE_H_

#include "EtherData.h"

#include <vector>

class EtherNode :public EtherData
{
private:
	//�Ը��ڵ�Ϊ����,�ڵ��Ӧ������
	int x, y;
	//�ڵ��z������,���������ڵ���ϵ
	int z;
	//���ڵ�
	EtherNode* father;
	//�ӽڵ�����
	std::vector<EtherNode*> children;
public:
};

#endif // !_NODE_H_