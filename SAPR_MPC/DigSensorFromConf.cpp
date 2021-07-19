#include "pch.h"
#include <fstream>
#include <string>
#include "DigSensorFromConf.h"
#include <cmath>
#include <codecvt>
#include <locale>
#include <vector>
#include "DirtWork.h"

CDigSensor CDigSensor::MakeSensor(std::string &line, BOOL &simple){
	this->NumberWrite(IDFind(line));
	if (simple) this->ObjWrite(simpleMake(line), simpleMake(line));
	else 
	this->ObjWrite(this->NameFind(line), this->TypeFind(line));
	return *this;
}
int CDigSensor::IDFind(std::string &line) {
	int NewID = 0, pos_1 = 0, pos_2 = 0, pos_3;
	pos_1 = line.find_first_of("1234567890", 0);
	pos_3 = line.find_first_of("1234567890", pos_1+1);
	pos_2 = line.find_first_not_of("1234567890", pos_3);
	for (int i = pos_2 - 1; i > pos_3 - 1; i--) {
		NewID += MakeNumber(line[i])*pow(10, pos_2 - 1 - i);
	}
	return NewID;
}

std::string CDigSensor::simpleMake(std::string &line) {
	int pos_1;
	pos_1 = line.find("//") + 3;
	if (line.find("信桥新") != -1) return "信桥新";
	return line.substr(pos_1);
}
std::string CDigSensor::NameFind(std::string &line) {
	if (line.find("信桥新") != -1) return "信桥新";
	int pos_1, pos_2;
	pos_1 = line.find("//") + 3;
	pos_2 = line.find(": ", pos_1);
	if (pos_2 == -1) pos_2 = line.find_first_of(" ", pos_1);
	return line.substr(pos_1, pos_2-pos_1);
}
std::string CDigSensor::TypeFind(std::string &line) {
	if (line.find("信桥新") != -1) return "信桥新";
	int pos_1, pos_2;
	pos_1 = line.find("//") + 3;
	pos_2 = line.find(": ", pos_1);
	if (pos_2 == -1) pos_2 = line.find_first_of(" ", pos_1);
	return line.substr(pos_2+1);
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

int CDigSensor::GetID() const{
	return this->ID;
}
int CDigSensor::GetNum_1() const {
	return this->numOfSensor_1;
}
int CDigSensor::GetNum_2() const {
	return this->numOfSensor_2;
}
std::string CDigSensor::GetName()const {
	return this->Name_obj;
}
std::string CDigSensor::GetType() const {
	return this->Type_obj;
}
CDigSensor::CDigSensor(int NewID) : Name_obj(" "), Type_obj(" ") {
	ID = NewID;
	numOfSensor_1 = ID * 2 - 2;
	numOfSensor_2 = ID * 2 - 1;
}
CDigSensor::CDigSensor() : Name_obj(" "), Type_obj(" ") {
	ID = 0;
	numOfSensor_1 = 0;
	numOfSensor_2 = 0;
}
