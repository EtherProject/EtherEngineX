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

	//�����ڶ�Ӧ���͵Ķ�ջ�е�key
	int key;
	//���ݵ�����,��ΪdataInUse�е�key
	DataType type;
};

#endif // !_DATA_H_