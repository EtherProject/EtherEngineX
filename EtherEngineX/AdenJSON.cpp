#include "AdenJSON.h"

AdenJSONNode::~AdenJSONNode()
{
}

bool AdenJSONNode::Empty()
{
	return _pCJSONNode == nullptr;
}

std::string AdenJSONNode::GetKey(bool* ok)
{
	if (!_pCJSONNode)
	{
		if (ok) *ok = false;
		return std::string();
	}

	if (ok) *ok = true;
	return _pCJSONNode->string;
}

std::string AdenJSONNode::GetStringValue(bool* ok) const
{
	if (!_pCJSONNode || _type != AdenJSONNodeType::String)
	{
		if (ok) *ok = false;
		return std::string();
	}
	
	if (ok) *ok = true;
	return _pCJSONNode->valuestring;
}

int AdenJSONNode::GetIntValue(bool* ok) const
{
	if (!_pCJSONNode || _type != AdenJSONNodeType::Number)
	{
		if (ok) *ok = false;
		return 0;
	}

	if (ok) *ok = true;
	return _pCJSONNode->valueint;
}

double AdenJSONNode::GetDoubleValue(bool* ok) const
{
	if (!_pCJSONNode || _type != AdenJSONNodeType::Number)
	{
		if (ok) *ok = false;
		return 0.0;
	}

	if (ok) *ok = true;
	return _pCJSONNode->valuedouble;
}

bool AdenJSONNode::SetStringValue(const std::string& value)
{
	if (!_pCJSONNode || _type != AdenJSONNodeType::String)
		return false;

	cJSON_SetValuestring(_pCJSONNode, value.c_str());
	return true;
}

bool AdenJSONNode::SetIntValue(int value)
{
	if (!_pCJSONNode || _type != AdenJSONNodeType::Number)
		return false;

	cJSON_SetIntValue(_pCJSONNode, value);
	return true;
}

bool AdenJSONNode::SetDoubleValue(double value)
{
	if (!_pCJSONNode || _type != AdenJSONNodeType::Number)
		return false;

	cJSON_SetNumberValue(_pCJSONNode, value);
	return true;
}

int AdenJSONNode::GetArraySize(bool* ok) const
{
	if (_type != AdenJSONNodeType::Array)
	{
		if (ok) *ok = false;
		return 0;
	}
	
	if (ok) *ok = true;
	return cJSON_GetArraySize(_pCJSONNode);
}

bool AdenJSONNode::HasObjectItem(const std::string& key, bool* ok)
{
	if (!_pCJSONNode)
	{
		if (ok) *ok = false;
		return 0.0;
	}

	if (ok) *ok = true;
	return cJSON_GetObjectItemCaseSensitive(_pCJSONNode, key.c_str()) ? true : false;
}

AdenJSONNode AdenJSONNode::AddNewItemToArray()
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array || !(newNode._pCJSONNode = cJSON_CreateNull()))
		return newNode;

	if (!cJSON_AddItemToArray(_pCJSONNode, newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Null;
	return newNode;
}

AdenJSONNode AdenJSONNode::AddNewItemToArray(bool value)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array || !(newNode._pCJSONNode = value ? cJSON_CreateTrue() : cJSON_CreateFalse()))
		return newNode;

	if (!cJSON_AddItemToArray(_pCJSONNode, newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = value ? AdenJSONNodeType::True : AdenJSONNodeType::False;
	return newNode;
}

AdenJSONNode AdenJSONNode::AddNewItemToArray(double value)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array || !(newNode._pCJSONNode = cJSON_CreateNumber(value)))
		return newNode;

	if (!cJSON_AddItemToArray(_pCJSONNode, newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Number;
	return newNode;
}

AdenJSONNode AdenJSONNode::AddNewItemToArray(const std::string& value)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array || !(newNode._pCJSONNode = cJSON_CreateString(value.c_str())))
		return newNode;

	if (!cJSON_AddItemToArray(_pCJSONNode, newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::String;
	return newNode;
}

AdenJSONNode AdenJSONNode::AddNewArrayItemToArray()
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array || !(newNode._pCJSONNode = cJSON_CreateArray()))
		return newNode;

	if (!cJSON_AddItemToArray(_pCJSONNode, newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Array;
	return newNode;
}

AdenJSONNode AdenJSONNode::AddNewObjectItemToArray()
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array || !(newNode._pCJSONNode = cJSON_CreateObject()))
		return newNode;

	if (!cJSON_AddItemToArray(_pCJSONNode, newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Object;
	return newNode;
}

AdenJSONNode AdenJSONNode::AddNewItemToObject(const std::string& key)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object || !(newNode._pCJSONNode = cJSON_CreateNull()))
		return newNode;

	if (!cJSON_AddItemToObject(_pCJSONNode, key.c_str(), newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Null;
	return newNode;
}

AdenJSONNode AdenJSONNode::AddNewItemToObject(const std::string& key, bool value)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object || !(newNode._pCJSONNode = value ? cJSON_CreateTrue() : cJSON_CreateFalse()))
		return newNode;

	if (!cJSON_AddItemToObject(_pCJSONNode, key.c_str(), newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = value ? AdenJSONNodeType::True : AdenJSONNodeType::False;
	return newNode;
}

AdenJSONNode AdenJSONNode::AddNewItemToObject(const std::string& key, double value)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object || !(newNode._pCJSONNode = cJSON_CreateNumber(value)))
		return newNode;

	if (!cJSON_AddItemToObject(_pCJSONNode, key.c_str(), newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Number;
	return newNode;
}

AdenJSONNode AdenJSONNode::AddNewItemToObject(const std::string& key, const std::string& value)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object || !(newNode._pCJSONNode = cJSON_CreateString(value.c_str())))
		return newNode;

	if (!cJSON_AddItemToObject(_pCJSONNode, key.c_str(), newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::String;
	return newNode;
}

AdenJSONNode AdenJSONNode::AddNewArrayItemToObject(const std::string& key)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object || !(newNode._pCJSONNode = cJSON_CreateArray()))
		return newNode;

	if (!cJSON_AddItemToObject(_pCJSONNode, key.c_str(), newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Array;
	return newNode;
}

AdenJSONNode AdenJSONNode::AddNewObjectItemToObject(const std::string& key)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object || !(newNode._pCJSONNode = cJSON_CreateObject()))
		return newNode;

	if (!cJSON_AddItemToObject(_pCJSONNode, key.c_str(), newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Object;
	return newNode;
}

AdenJSONNode AdenJSONNode::ReplaceItemInArray(int idx)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array || !(newNode._pCJSONNode = cJSON_CreateNull()))
		return newNode;

	if (!cJSON_ReplaceItemInArray(_pCJSONNode, idx, newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Null;
	return newNode;
}

AdenJSONNode AdenJSONNode::ReplaceItemInArray(int idx, bool new_value)
{
	
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array || !(newNode._pCJSONNode = new_value ? cJSON_CreateTrue() : cJSON_CreateFalse()))
		return newNode;

	if (!cJSON_ReplaceItemInArray(_pCJSONNode, idx, newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = new_value ? AdenJSONNodeType::True : AdenJSONNodeType::False;
	return newNode;
}

AdenJSONNode AdenJSONNode::ReplaceItemInArray(int idx, double new_value)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array || !(newNode._pCJSONNode = cJSON_CreateNumber(new_value)))
		return newNode;

	if (!cJSON_ReplaceItemInArray(_pCJSONNode, idx, newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Number;
	return newNode;
}

AdenJSONNode AdenJSONNode::ReplaceItemInArray(int idx, const std::string& new_value)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array || !(newNode._pCJSONNode = cJSON_CreateString(new_value.c_str())))
		return newNode;

	if (!cJSON_ReplaceItemInArray(_pCJSONNode, idx, newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::String;
	return newNode;
}

AdenJSONNode AdenJSONNode::ReplaceItemInArrayWithArray(int idx)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array || !(newNode._pCJSONNode = cJSON_CreateArray()))
		return newNode;

	if (!cJSON_ReplaceItemInArray(_pCJSONNode, idx, newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Array;
	return newNode;
}

AdenJSONNode AdenJSONNode::ReplaceItemInArrayWithObject(int idx)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array || !(newNode._pCJSONNode = cJSON_CreateObject()))
		return newNode;

	if (!cJSON_ReplaceItemInArray(_pCJSONNode, idx, newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Object;
	return newNode;
}

AdenJSONNode AdenJSONNode::ReplaceItemInObject(const std::string& key)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object || !(newNode._pCJSONNode = cJSON_CreateNull()))
		return newNode;

	if (!cJSON_ReplaceItemInObjectCaseSensitive(_pCJSONNode, key.c_str(), newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Null;
	return newNode;
}

AdenJSONNode AdenJSONNode::ReplaceItemInObject(const std::string& key, bool new_value)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object || !(newNode._pCJSONNode = new_value ? cJSON_CreateTrue() : cJSON_CreateFalse()))
		return newNode;

	if (!cJSON_ReplaceItemInObjectCaseSensitive(_pCJSONNode, key.c_str(), newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = new_value ? AdenJSONNodeType::True : AdenJSONNodeType::False;
	return newNode;
}

AdenJSONNode AdenJSONNode::ReplaceItemInObject(const std::string& key, double new_value)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object || !(newNode._pCJSONNode = cJSON_CreateNumber(new_value)))
		return newNode;

	if (!cJSON_ReplaceItemInObjectCaseSensitive(_pCJSONNode, key.c_str(), newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Number;
	return newNode;
}

AdenJSONNode AdenJSONNode::ReplaceItemInObject(const std::string& key, const std::string& new_value)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object || !(newNode._pCJSONNode = cJSON_CreateString(new_value.c_str())))
		return newNode;

	if (!cJSON_ReplaceItemInObjectCaseSensitive(_pCJSONNode, key.c_str(), newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::String;
	return newNode;
}

AdenJSONNode AdenJSONNode::ReplaceItemInObjectWithArray(const std::string& key)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object || !(newNode._pCJSONNode = cJSON_CreateArray()))
		return newNode;

	if (!cJSON_ReplaceItemInObjectCaseSensitive(_pCJSONNode, key.c_str(), newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Array;
	return newNode;
}

AdenJSONNode AdenJSONNode::ReplaceItemInObjectWithObject(const std::string& key)
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object || !(newNode._pCJSONNode = cJSON_CreateObject()))
		return newNode;

	if (!cJSON_ReplaceItemInObjectCaseSensitive(_pCJSONNode, key.c_str(), newNode._pCJSONNode))
	{
		free(newNode._pCJSONNode);
		newNode._pCJSONNode = nullptr;
		return newNode;
	}

	newNode._type = AdenJSONNodeType::Object;
	return newNode;
}

bool AdenJSONNode::DeleteItemFromArray(int idx)
{
	if (_type != AdenJSONNodeType::Array)
		return false;

	cJSON_DeleteItemFromArray(_pCJSONNode, idx);
	return true;
}

bool AdenJSONNode::DeleteItemFromObject(const std::string& key)
{
	if (_type != AdenJSONNodeType::Object)
		return false;

	cJSON_DeleteItemFromObjectCaseSensitive(_pCJSONNode, key.c_str());
	return true;
}

bool AdenJSONNode::ArrayForEach(std::function<bool(int idx, AdenJSONNode& node)> handler)
{
	if (_type != AdenJSONNodeType::Array)
		return false;

	int _idx = 0;
	AdenJSONNode _node;
	cJSON_ArrayForEach(_node._pCJSONNode, _pCJSONNode)
	{
		_node._type = (AdenJSONNodeType)_node._pCJSONNode->type;
		if (!handler(_idx, _node)) break;
		++_idx;
	}

	return true;
}

bool AdenJSONNode::ObjectForEach(std::function<bool(const std::string& key, AdenJSONNode& node)> handler)
{
	if (_type != AdenJSONNodeType::Object)
		return false;

	AdenJSONNode _node;
	cJSON_ArrayForEach(_node._pCJSONNode, _pCJSONNode)
	{
		_node._type = (AdenJSONNodeType)_node._pCJSONNode->type;
		if (!handler(_node._pCJSONNode->string, _node)) break;
	}

	return true;
}

std::string AdenJSONNode::Print(bool formatted) const
{
	if (!_pCJSONNode)
		return std::string();

	char* strRawJSON = formatted ? cJSON_Print(_pCJSONNode) : cJSON_PrintUnformatted(_pCJSONNode);
	std::string strWrappedJSON = std::string(strRawJSON);
	free(strRawJSON);

	return strWrappedJSON;
}

AdenJSONNode::operator bool() const
{
	return _pCJSONNode != nullptr;
}

bool AdenJSONNode::operator==(const AdenJSONNode& node) const
{
	return _pCJSONNode == node._pCJSONNode;
}

bool AdenJSONNode::operator!=(const AdenJSONNode& node) const
{
	return _pCJSONNode != node._pCJSONNode;
}

AdenJSONNode AdenJSONNode::operator[](const int idx) const
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Array && _type != AdenJSONNodeType::Object)
		return newNode;

	int arraySize = cJSON_GetArraySize(_pCJSONNode);

	if (idx >= 0 && idx < arraySize)
		newNode._pCJSONNode = cJSON_GetArrayItem(_pCJSONNode, idx);
	else if (idx < 0 && abs(idx) <= arraySize)
		newNode._pCJSONNode = cJSON_GetArrayItem(_pCJSONNode, idx + arraySize);

	if (newNode._pCJSONNode)
		newNode._type = (AdenJSONNodeType)newNode._pCJSONNode->type;

	return newNode;
}

AdenJSONNode AdenJSONNode::operator[](const std::string& key) const
{
	AdenJSONNode newNode;

	if (_type != AdenJSONNodeType::Object)
		return newNode;

	newNode._pCJSONNode = cJSON_GetObjectItemCaseSensitive(_pCJSONNode, key.c_str());

	if (newNode._pCJSONNode)
		newNode._type = (AdenJSONNodeType)newNode._pCJSONNode->type;

	return newNode;
}

AdenJSONParseResult AdenJSONDocument::LoadFromFile(const std::string& path)
{
	if (_pCJSONNode)
	{
		cJSON_Delete(_pCJSONNode);
		_pCJSONNode = nullptr;
	}

	AdenJSONParseResult result;
	std::ifstream fin(path);
	if (!fin.good())
	{
		result.status = AdenJSONParseStatus::IOError;
		result.description = "open file failed";
		return result;
	}

	std::stringstream ssContent;
	ssContent << fin.rdbuf();
	fin.close(); fin.clear();

	_LoadFromStringImpl(ssContent.str(), result);

	ssContent.clear();

	return result;
}

AdenJSONParseResult AdenJSONDocument::LoadFromString(const std::string& str)
{
	AdenJSONParseResult result;
	
	_LoadFromStringImpl(str, result);

	return result;
}

bool AdenJSONDocument::SaveAsFile(const std::string& path, bool formatted)
{
	std::ofstream fout(path);
	if (!fout.good()) return false;

	std::string strJSON;

	_SaveAsStringImpl(strJSON, formatted);

	fout << strJSON << std::endl;
	fout.close(); fout.clear();

	return true;
}

std::string AdenJSONDocument::SaveAsString(bool formatted)
{
	std::string strJSON;

	_SaveAsStringImpl(strJSON, formatted);

	return strJSON;
}

AdenJSONNode::AdenJSONNode()
{
}

void AdenJSONDocument::_LoadFromStringImpl(const std::string& str, AdenJSONParseResult& result)
{
	if (_pCJSONNode)
	{
		cJSON_Delete(_pCJSONNode);
		_pCJSONNode = nullptr;
	}

	if (!(_pCJSONNode = cJSON_Parse(str.c_str())))
	{
		result.status = AdenJSONParseStatus::ParseError;
		result.description = std::string("JSON parse error before: ").append(cJSON_GetErrorPtr());
		cJSON_Delete(_pCJSONNode);
		_pCJSONNode = nullptr;
		return;
	}

	result.status = AdenJSONParseStatus::Success;
	result.description = "no error";
	_type = (AdenJSONNodeType)_pCJSONNode->type;
}

void AdenJSONDocument::_SaveAsStringImpl(std::string& str, bool formatted)
{
	str = Print(formatted);
}

AdenJSONDocument::AdenJSONDocument()
{
}

AdenJSONDocument::~AdenJSONDocument()
{
	cJSON_Delete(_pCJSONNode);
	_pCJSONNode = nullptr;
}