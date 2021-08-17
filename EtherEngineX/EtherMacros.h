#ifndef _MACROS_H_
#define _MACROS_H_

#define _VERSION_ "0.0.1"

#define ETHER_API extern "C" int

struct EtherMacro
{
	const char* name;
	int value;
};

#endif // !_MACROS_H_