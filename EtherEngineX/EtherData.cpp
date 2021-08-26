#include "EtherData.h"
using namespace std;

//用vector实现可能会导致效率偏低,考虑更换
unordered_map<DataType, vector<EtherData*>> dataInUse;
unordered_map<DataType, vector<EtherData*>> dataNotInUse;