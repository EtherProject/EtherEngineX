#ifndef _NODE_H_
#define _NODE_H_

#include <vector>

class EtherNode
{
public:

private:
	//�Ը��ڵ�Ϊ����,�ڵ��Ӧ������
	int x, y;
	//�ڵ��z������,���������ڵ���ϵ
	int depth;
	//���ڵ�
	EtherNode* father;
	//�ӽڵ�����
	std::vector<EtherNode*> children;
};

#endif // !_NODE_H_