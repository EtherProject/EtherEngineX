#ifndef _DATA_H_
#define _DATA_H_

#include<unordered_map>
#include<string>

class EtherData
{
public:
	//��dataInUse�еĽڵ�ŵ�dataNotInUse��,�ȴ���һ������
	virtual void release() = 0;
protected:
	//�����ڶ�Ӧ���͵Ķ�ջ�е�key
	int key;
	//���ݵ�����,��ΪdataInUse�е�key
	std::string type;

	EtherData();
	virtual ~EtherData();
private:
	static std::unordered_map<std::string, std::vector<EtherData&>> dataInUse;
	static std::unordered_map<std::string, std::vector<EtherData&>> dataNotInUse;
};

#endif // !_DATA_H_