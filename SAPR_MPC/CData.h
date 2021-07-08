#pragma once
#include "list"
class CData
{
public:
	std::list<CString> GetData();
private:
	std::list<CString> SensorList;
};

