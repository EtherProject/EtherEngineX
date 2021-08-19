#ifndef _ADEN_JSON_H_
#define _ADEN_JSON_H_

#include <cJSON.h>

#include <string>
#include <fstream>
#include <sstream>
#include <functional>

//解析状态
enum class AdenJSONParseStatus
{
	Success = 0,
	IOError,
	ParseError
};

//解析获取的数据类型
enum class AdenJSONNodeType
{
	Invalid = cJSON_Invalid,
	False = cJSON_False,
	True = cJSON_True,
	Null = cJSON_NULL,
	Number = cJSON_Number,
	String = cJSON_String,
	Array = cJSON_Array,
	Object = cJSON_Object,
	Raw = cJSON_Raw,
};

//解析获得的结果
struct AdenJSONParseResult
{
	AdenJSONParseStatus status;
	std::string description;
};

class AdenJSONNode
{
public:
	virtual ~AdenJSONNode();
	bool Empty();
	std::string GetKey(bool* ok = nullptr);
	std::string GetStringValue(bool* ok = nullptr) const;
	int GetIntValue(bool* ok = nullptr) const;
	double GetDoubleValue(bool* ok = nullptr) const;
	bool SetStringValue(const std::string& value);
	bool SetIntValue(int value);
	bool SetDoubleValue(double value);
	int GetArraySize(bool* ok = nullptr) const;
	bool HasObjectItem(const std::string& key, bool* ok = nullptr);

	AdenJSONNode AddNewItemToArray();
	AdenJSONNode AddNewItemToArray(bool value);
	AdenJSONNode AddNewItemToArray(double value);
	AdenJSONNode AddNewItemToArray(const std::string& value);
	AdenJSONNode AddNewArrayItemToArray();
	AdenJSONNode AddNewObjectItemToArray();
	AdenJSONNode AddNewItemToObject(const std::string& key);
	AdenJSONNode AddNewItemToObject(const std::string& key, bool value);
	AdenJSONNode AddNewItemToObject(const std::string& key, double value);
	AdenJSONNode AddNewItemToObject(const std::string& key, const std::string& value);
	AdenJSONNode AddNewArrayItemToObject(const std::string& key);
	AdenJSONNode AddNewObjectItemToObject(const std::string& key);

	AdenJSONNode ReplaceItemInArray(int idx);
	AdenJSONNode ReplaceItemInArray(int idx, bool new_value);
	AdenJSONNode ReplaceItemInArray(int idx, double new_value);
	AdenJSONNode ReplaceItemInArray(int idx, const std::string& new_value);
	AdenJSONNode ReplaceItemInArrayWithArray(int idx);
	AdenJSONNode ReplaceItemInArrayWithObject(int idx);
	AdenJSONNode ReplaceItemInObject(const std::string& key);
	AdenJSONNode ReplaceItemInObject(const std::string& key, bool new_value);
	AdenJSONNode ReplaceItemInObject(const std::string& key, double new_value);
	AdenJSONNode ReplaceItemInObject(const std::string& key, const std::string& new_value);
	AdenJSONNode ReplaceItemInObjectWithArray(const std::string& key);
	AdenJSONNode ReplaceItemInObjectWithObject(const std::string& key);

	bool DeleteItemFromArray(int idx);
	bool DeleteItemFromObject(const std::string& key);
	bool ArrayForEach(std::function<bool(int idx, AdenJSONNode& node)> handler);
	bool ObjectForEach(std::function<bool(const std::string& key, AdenJSONNode& node)> handler);
	std::string Print(bool formatted = true) const;
	operator bool() const;
	bool operator==(const AdenJSONNode& node) const;
	bool operator!=(const AdenJSONNode& node) const;
	AdenJSONNode operator[](int idx) const;
	AdenJSONNode operator[](const std::string& key) const;

protected:
	AdenJSONNode();
	AdenJSONNodeType _type = AdenJSONNodeType::Null;
	cJSON* _pCJSONNode = nullptr;
};

class AdenJSONDocument : public AdenJSONNode
{
public:
	AdenJSONDocument();
	~AdenJSONDocument();
	AdenJSONParseResult LoadFromFile(const std::string& path);
	AdenJSONParseResult LoadFromString(const std::string& str);
	bool SaveAsFile(const std::string& str, bool formatted = true);
	std::string SaveAsString(bool formatted = true);

private:
	void _LoadFromStringImpl(const std::string& str, AdenJSONParseResult& result);
	void _SaveAsStringImpl(std::string& str, bool formatted);
};

#endif // !_ADEN_JSON_H_