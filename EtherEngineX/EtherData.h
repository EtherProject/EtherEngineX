#ifndef _DATA_H_
#define _DATA_H_

#include <iostream>
#include <vector>

//����,���ж���̳�����
class EtherData
{
private:
	//��̬�����ڹ�����е�key
	std::vector<EtherData*>::iterator key;
	//��̬�����ڴ�����
	static std::vector<EtherData*> AllData;
public:
	//���캯���Ὣ�Լ����뵽�ڴ�������
	EtherData();
	//���������Ὣ�Լ����ڴ��������Ƴ�
	virtual ~EtherData();
};

#endif