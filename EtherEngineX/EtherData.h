#ifndef _DATA_H_
#define _DATA_H_

#include <iostream>
#include <vector>

//超类,所有对象继承于他
class EtherData
{
private:
	//静态变量在管理池中的key
	std::vector<EtherData*>::iterator key;
	//静态变量内存管理池
	static std::vector<EtherData*> AllData;
public:
	//构造函数会将自己加入到内存管理池中
	EtherData();
	//析构函数会将自己从内存管理池中移除
	virtual ~EtherData();
};

#endif