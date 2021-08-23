#ifndef _DATA_H_
#define _DATA_H_

#include<unordered_map>
#include<string>

class EtherData
{
public:
	//将dataInUse中的节点放到dataNotInUse中,等待下一步操作
	virtual void release() = 0;
protected:
	//数据在对应类型的堆栈中的key
	int key;
	//数据的类型,作为dataInUse中的key
	std::string type;

	EtherData();
	virtual ~EtherData();
private:
	static std::unordered_map<std::string, std::vector<EtherData&>> dataInUse;
	static std::unordered_map<std::string, std::vector<EtherData&>> dataNotInUse;
};

#endif // !_DATA_H_