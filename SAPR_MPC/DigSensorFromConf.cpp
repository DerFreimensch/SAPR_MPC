#include "pch.h"
#include <fstream>
#include <string>
#include "DigSensorFromConf.h"
#include <cmath>


std::list<CDigSensor>DigSensorArray;


void readfile(CString &NameConfig, CString &NameRTF, CString &station, BOOL &SimpAnalyze) {
	CString FileName;
	FileName = NameRTF + L"\\" + station + L".rtf";
	bool WriteFlag = false;
	setlocale(LC_ALL, "Russian");
	std::ifstream config(NameConfig);
	std::string line;
	if (config.is_open()) {
		CDigSensor node;
		DigSensorArray.push_back(node);
		while (getline(config, line)) {
			if (WriteFlag && line.find_first_of("1234567890") == 0) {
				CDigSensor node; 
				node.MakeSensor(line, SimpAnalyze);
				while (!IsNotGap(DigSensorArray.back(), node)) {
					CDigSensor newnode((DigSensorArray.back().GetID()+1));
					DigSensorArray.push_back(newnode);
				}
				DigSensorArray.push_back(node);
			}
			if (SensorDescribe(line)) WriteFlag = true;
		}
	}
	printToRtf(DigSensorArray, FileName, station);
	DigSensorArray.erase(DigSensorArray.begin(), DigSensorArray.end());
}

bool SensorDescribe(std::string &line) {
	if ("// Раздел описания датчиков" == line) return true;
	else return false;
}
CDigSensor CDigSensor::MakeSensor(std::string &line, BOOL &simple){
	this->NumberWrite(IDFind(line));
	if (simple) this->ObjWrite(simpleMake(line), simpleMake(line));
	else 
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

std::string CDigSensor::simpleMake(std::string &line) {
	int pos_1, pos_2, pos_ex;
	pos_1 = line.find("//") + 3;
	pos_ex = line.find("Состояние", pos_1);
	if (pos_ex != -1) return line.substr(pos_ex);
	pos_2 = line.find(": ", pos_1);
	if (pos_2 == -1) pos_2 = line.find_first_of(" ", pos_1);
	return line.substr(pos_1, pos_2 - pos_1);
}
std::string CDigSensor::NameFind(std::string &line) {
	int pos_1, pos_2;
	pos_1 = line.find("//") + 3;
	pos_2 = line.find(": ", pos_1);
	if (pos_2 == -1) pos_2 = line.find_first_of(" ", pos_1);
	return line.substr(pos_1, pos_2-pos_1);
}
std::string CDigSensor::TypeFind(std::string &line) {
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
bool IsNotGap(CDigSensor &Prev, CDigSensor &Next) {
	if (Prev.GetID() + 1 == Next.GetID()) return true;
	else return false;
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
int MakeNumber(char c) {
	return (int)c - 48;
}

void printToRtf(std::list<CDigSensor> &DigSensorArray, CString &nameRTF, CString &station) {
	std::ofstream output(nameRTF);
	CT2CA pszConvertedAnsiString(station);
	std::string out = (pszConvertedAnsiString);
	output << "{\\rtf1 \n \\par ";
	output << "{\\viewkind4\\uc1 \\pard\\sa200\\sl276\\slmult1\\qc\\b Перечень дискретных данных АПК-ДК для передачи в МПЦ-ЭЛ ";
	output << out;
	output << " \\par}" << std::endl;
	output << "\\trowd \\trql\\trgaph108\\trrh280\\trleft36 \\clbrdrt\\brdrth \\clbrdrl\\brdrth \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx1036\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx3536\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx7036 \\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx10036\\pard\\intbl ";
	output << "№";
	output << " \\cell \\pard \\intbl ";
	output << "Название объекта";
	output << " \\cell \\pard  \\intbl ";
	output << "Тип объекта";
	output << " \\cell \\pard  \\intbl ";
	output << "№ датчика в массиве";
	output << " \\cell \\pard  \\intbl \\row \n";
	for (const auto &elem : DigSensorArray) { 
		if (elem.GetID() == 0) continue;
		output << "\\trowd \\trql\\trgaph108\\trrh280\\trleft36 \\clbrdrt\\brdrth \\clbrdrl\\brdrth \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx1036\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx3536\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx7036 \\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx8536\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx10036\\pard\\intbl ";
		output << elem.GetID();
		output << " \\cell \\pard \\intbl ";
		output << elem.GetName();
		output << " \\cell \\pard  \\intbl ";
		output << elem.GetType();
		output << " \\cell \\pard  \\intbl ";
		output << elem.GetNum_1();
		output << " \\cell \\pard  \\intbl ";
		output << elem.GetNum_2();
		output << " \\cell \\pard  \\intbl \\row \n";
	}
	output << "\\pard }";
	output.close();

	ShellExecute(0, L"open", nameRTF, 0, L"", SW_SHOW);
}