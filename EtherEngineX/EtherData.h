#ifndef _DATA_H_
#define _DATA_H_

#include <iostream>
#include <vector>
using namespace std;

//����,���ж���̳�����
class EtherData
{
private:
	//��̬�����ڹ�����е�key
	vector<EtherData*>::iterator key;
	//��̬�����ڴ�����
	static vector<EtherData*> AllData;
public:
	//���캯���Ὣ�Լ����뵽�ڴ�������
	EtherData();
	//���������Ὣ�Լ����ڴ��������Ƴ�
	~EtherData();
};

#endif