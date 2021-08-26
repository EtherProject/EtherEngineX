#ifndef _DATA_H_
#define _DATA_H_

#include "EtherMacros.h"
#include "EtherModule.h"

#include<unordered_map>
#include<lua.hpp>

enum class DataType
{
	Node = 0,
	Image,
	Layer
};

class EtherData
{
public:
	EtherData() {}
	virtual ~EtherData() {}

	//数据在对应类型的堆栈中的key
	int key;
	//数据的类型,作为dataInUse中的key
	DataType type;
};

#endif // !_DATA_H_