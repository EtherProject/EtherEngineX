#ifndef _DATA_H_
#define _DATA_H_

#include<unordered_map>

enum class DataType
{
	Node = 0,
	Image,
	Layer
};

class EtherData
{
public:
	//��dataInUse�еĽڵ�ŵ�dataNotInUse��,�ȴ���һ������
	virtual void Release() {};

	EtherData() {}
	virtual ~EtherData() {}

protected:
	//�����ڶ�Ӧ���͵Ķ�ջ�е�key
	int key;
	//���ݵ�����,��ΪdataInUse�е�key
	DataType type;
	
	//��vector������Щ����Ч�ʻ�Ƚϵ�,�Ժ���ܻ����
	static std::unordered_map<DataType, std::vector<EtherData>> dataInUse;
	static std::unordered_map<DataType, std::vector<EtherData>> dataNotInUse;
};

#endif // !_DATA_H_