#include "pch.h"
#include <list>
#include <fstream>
#include <string>
#include "DigSensorFromConf.h"
#include <cmath>


std::list<CDigSensor>DigSensorArray;


void readfile(CString &NameConfig) {
	bool WriteFlag = false;
	setlocale(LC_ALL, "Russian");
	std::ifstream config(NameConfig);
	std::string line;
	if (config.is_open()) {
		CDigSensor node;
		DigSensorArray.push_back(node);
		while (getline(config, line)) {
			if (WriteFlag) {
				CDigSensor node; 
				node.MakeSensor(line);
				while (!IsNotGap(DigSensorArray.back(), node)) {
					CDigSensor newnode((DigSensorArray.back().GetID()+1));
					DigSensorArray.push_back(newnode);
				}
				DigSensorArray.push_back(node);
			}
			if (SensorDescribe(line)) WriteFlag = true;
		}
	}
}

bool SensorDescribe(std::string &line) {
	if ("// Раздел описания датчиков" == line) return true;
	else return false;
}
CDigSensor CDigSensor::MakeSensor(std::string &line){
	this->NumberWrite(IDFind(line));
	this->ObjWrite(this->NameFind(line), this->TypeFind(line));
	return *this;
}
int CDigSensor::IDFind(std::string &line) {
	int NewID = 0, pos_1 = 0, pos_2 = 0;
	pos_1 = line.find_first_of("1234567890", 2);
	pos_2 = line.find_first_not_of("1234567890", pos_1);
	for (int i = pos_2 - 1; i > pos_1 - 1; i--) {
		NewID += MakeNumber(line[i])*pow(10, pos_2 - 1 - i);
	}
	return NewID;
}
std::string CDigSensor::NameFind(std::string &line) {
	int pos_1, pos_2;
	pos_1 = line.find("//") + 3;
	pos_2 = line.find(": ", pos_1);
	if (pos_2 == -1) pos_2 = line.find_first_of(" ", pos_1);
	return line.substr(pos_1, pos_2-pos_1);
}
std::string CDigSensor::TypeFind(std::string &line) {
	int pos_1, pos_1_1;
	pos_1_1  = line.find("//") + 3;
	pos_1 = line.find(": ", pos_1_1) + 2;
	if (pos_1 == -1) pos_1 = line.find_first_of(" ", pos_1_1) + 1;
	return line.substr(pos_1);
}
void CDigSensor::NumberWrite(int NewID) {
	ID = NewID;
	numOfSensor_1 = ID * 2 - 2;
	numOfSensor_2 = ID * 2 - 1;
}
void CDigSensor::ObjWrite(std::string &Name, std::string &Type) {
	Name_obj = Name;
	Type_obj = Type;
}
bool IsNotGap(CDigSensor &Prev, CDigSensor &Next) {
	if (Prev.GetID() + 1 == Next.GetID()) return true;
	else return false;
}

int CDigSensor::GetID() const{
	return this->ID;
}
CDigSensor::CDigSensor(int NewID) : Name_obj(" "), Type_obj(" ") {
	ID = NewID;
	numOfSensor_1 = ID * 2 - 2;
	numOfSensor_1 = ID * 2 - 1;
}
CDigSensor::CDigSensor() : Name_obj(" "), Type_obj(" ") {
	ID = 0;
	numOfSensor_1 = 0;
	numOfSensor_2 = 0;
}
int MakeNumber(char c) {
	return (int)c - 48;
}