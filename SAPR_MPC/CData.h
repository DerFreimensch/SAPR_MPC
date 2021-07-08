#pragma once
#include "list"
class CData
{
public:
	std::list<CString> GetData();
	void fillData(CString &File);
	void AddData(CString &sensor);
private:
	std::list<CString> SensorList;
};

