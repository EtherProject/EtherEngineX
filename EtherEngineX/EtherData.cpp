#include "EtherData.h"
using namespace std;

//��vectorʵ�ֿ��ܻᵼ��Ч��ƫ��,���Ǹ���
unordered_map<DataType, vector<EtherData*>> dataInUse;
unordered_map<DataType, vector<EtherData*>> dataNotInUse;