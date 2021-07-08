#include "pch.h"
#include "CData.h"
#include "list"
#include <fstream>
#include "DirtWork.h"
std::list<CString> CData::GetData() {
	return SensorList;
}
void CData::AddData(CString &sensor) {
	SensorList.push_back(sensor);
}
void CData::fillData(CString &File) {
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
				pos_2 = line.find_first_of("0123456789", pos_1);
				pos_3 = line.find_first_not_of(' ', pos_2 + 13);
				SubData = line.substr(0, pos_1) + ' ' + line.substr(pos_3);
				CString SubDataMain(SubData.c_str());
				this -> AddData(SubDataMain);
			}
		}
	}
}