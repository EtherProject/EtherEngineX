#include "EtherData.h"
using namespace std;

unordered_map<DataType, vector<EtherData>> EtherData::dataInUse;
unordered_map<DataType, vector<EtherData>> EtherData::dataNotInUse;