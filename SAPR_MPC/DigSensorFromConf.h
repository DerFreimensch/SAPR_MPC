#pragma once
#include "framework.h"

class CDigSensor {
public:
	CDigSensor MakeSensor(std::string &line);
	int GetID() const;
	CDigSensor(int NewID);
	CDigSensor();
protected:
	int IDFind(std::string &line);
	std::string NameFind(std::string &line);
	std::string TypeFind(std::string &line);
	void NumberWrite(int NewID);
	void ObjWrite(std::string& Name, std::string &Type);
private:
	int ID, numOfSensor_1, numOfSensor_2;
	std::string  Name_obj, Type_obj;
};

void readfile(CString &NameConfig);
bool SensorDescribe(std::string &line);
bool IsNotGap(CDigSensor &Prev, CDigSensor &Next);
int MakeNumber(char c);