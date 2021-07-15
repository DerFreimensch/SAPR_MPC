#include "pch.h"
#include "CData.h"
#include "list"
#include <fstream>
#include "DirtWork.h"
#include <fstream>
std::list<CString> CData::GetData() {
	return c_sensorList;
}
void CData::AddData(CString &sensor) {
	c_sensorList.push_back(sensor);
}
void CData::FillData(CString &File) {
	std::ifstream input(File);
	std::string line;
	if (input.is_open()) {
		CData NewData;
		while (getline(input, line)) {
			line = O2A(line);
			if (line.find_first_of("123456789") == 0) {
				int pos_1, pos_2, pos_3;
				std::string SubData;
				pos_1 = line.find(' ');
				pos_2 = line.find_first_not_of(' ', pos_1) + 12;
				pos_3 = line.find_first_not_of(' ', pos_2);
				SubData = line.substr(0, pos_1) + ' ' + line.substr(pos_3);
				CString SubDataMain(SubData.c_str());
				this->AddData(SubDataMain);
			}
		}
	}
}
void CData::EraseAll() {
	c_sensorList.erase(c_sensorList.begin(), c_sensorList.end());
	c_choiseSensor.erase(c_choiseSensor.begin(), c_choiseSensor.end());
}
void CData::FillSensor(std::list<CString> &t_newList) {
	for (int i = 0; i < t_newList.size(); i++) {
		c_choiseSensor.resize(t_newList.size());
		c_choiseSensor = t_newList;
	}
}
void CData::EraseList() {
	c_sensorList.erase(c_sensorList.begin(), c_sensorList.end());
}
CString CData::GetNumber(CString &line) {
	return line.Left(line.Find(' '));
}
CString CData::GetComm(CString &line) {
	return line.Right(line.GetLength() - (line.Find(' ')+1));
}
std::string CData::MakeASpace(int i) {
	std::string ex;
	for (int j = 0; j < i; j++) {
		ex = ex + " ";
	}
	return ex;
}
int CData::FileAdd(CString &File, CString &Name, int &i) {
	std::ofstream output(CT2CA(File), std::ios_base::app);
	for (auto &elem : c_choiseSensor) {
		i++;
		std::string ex = std::to_string(i);
		output << "1" << this->MakeASpace(6 - ex.size()) << i << "   " << CT2CA(Name) << this->MakeASpace(8-(this->GetNumber(elem)).GetLength()) << CT2CA(this->GetNumber(elem)) << "   @   0   0   0   0   // " << CT2CA(this->GetComm(elem)) << std::endl;
	}
	output << std::endl;
	output.close();
	return i;
}

