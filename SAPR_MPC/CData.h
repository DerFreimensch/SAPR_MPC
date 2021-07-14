#pragma once
#include "list"
class CData
{
public:
	std::list<CString> GetData();
	void FillData(CString &File);
	void AddData(CString &sensor);
	void EraseAll();
	void FillSensor(std::list<CString> &t_newList);
	void EraseList();
	int FileAdd(CString &File, CString &Name, int &i);
	CString GetNumber(CString &line);
	CString GetComm(CString &line);
private:
	std::list<CString> c_sensorList;
	std::list<CString> c_choiseSensor;
};

