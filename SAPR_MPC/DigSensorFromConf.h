#pragma once
#include "framework.h"
#include <list>
class CDigSensor {
public:
	CDigSensor MakeSensor(std::string &line);
	int GetID() const;
	int GetNum_1() const;
	int GetNum_2() const;
	std::string GetName() const;
	std::string GetType() const;
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
void printToRtf(std::list<CDigSensor> &DigSensorArray);