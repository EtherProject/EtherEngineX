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
	//将dataInUse中的节点放到dataNotInUse中,等待下一步操作
	virtual void Release() {};

	EtherData() {}
	virtual ~EtherData() {}

protected:
	//数据在对应类型的堆栈中的key
	int key;
	//数据的类型,作为dataInUse中的key
	DataType type;
	
	//用vector保存这些数据效率会比较低,以后可能会更换
	static std::unordered_map<DataType, std::vector<EtherData>> dataInUse;
	static std::unordered_map<DataType, std::vector<EtherData>> dataNotInUse;
};

#endif // !_DATA_H_