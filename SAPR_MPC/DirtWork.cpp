#include "pch.h"
#include <fstream>
#include <string>
#include "DigSensorFromConf.h"
#include "AnSensorFromConf.h"
#include "DirtWork.h"
#include <cmath>
#include <codecvt>
#include <locale>
#include <vector>

std::list<CAnSensor>SensorArrayAn;
std::list<CDigSensor>SensorArrayDig;


void readfile(CString &NameConfig, CString &NameRTF, CString &station, BOOL &SimpAnalyze, BOOL &An) {
	CString FileName;
	if (An)  FileName = makeAn(NameConfig, NameRTF, station, SimpAnalyze);
	else  FileName = makeDig(NameConfig, NameRTF, station, SimpAnalyze);
	if (An) printToRtfAn(SensorArrayAn, FileName, station);
	else printToRtfDig(SensorArrayDig, FileName, station);
	SensorArrayDig.erase(SensorArrayDig.begin(), SensorArrayDig.end());
	SensorArrayAn.erase(SensorArrayAn.begin(), SensorArrayAn.end());
}

bool SensorDescribe(std::string &line) {
	if (line.find('@') != -1) return true;
	else return false;
}
template <class T>
bool IsNotGap(T &Prev, T &Next) {
	if (Prev.GetID() + 1 == Next.GetID()) return true;
	else return false;
}

int MakeNumber(char c) {
	return (int)c - 48;
}

void printToRtfDig(std::list<CDigSensor> &SensorArray, CString &nameRTF, CString &station) {
	std::ofstream output(nameRTF);
	CT2CA pszConvertedAnsiString(station);
	std::string out = (pszConvertedAnsiString);
	output << "{\\rtf1 \n\\par";
	output << "{\\viewkind4 \\uc1 \\pard \\sa200 \\sl276 \\slmult1 \\qc \\b Перечень дискретных данных АПК-ДК для передачи в МПЦ-ЭЛ";
	output << '(' << out << ')';
	output << "\\par}" << std::endl;
	output << "\\trowd \\trql \\trgaph108 \\trrh280 \\trleft36 \\clbrdrt \\brdrth \\clbrdrl \\brdrth \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx1036 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx3536 \\clbrdrt \\brdrth \\clbrdrl\\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx7036 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx10036 \\pard \\intbl";
	output << " \\qc№";
	output << "\\cell \\pard \\intbl";
	output << " \\qcНазвание объекта";
	output << "\\cell \\pard \\intbl";
	output << " \\qcТип объекта";
	output << "\\cell \\pard \\intbl";
	output << " \\qc№ датчика в массиве";
	output << "\\cell \\pard \\intbl \\row \n";
	for (const auto &elem : SensorArray) {
		if (elem.GetID() == 0) continue;
		output << "\\trowd \\trql \\trgaph108 \\trrh280 \\trleft36 \\clbrdrt \\brdrth \\clbrdrl \\brdrth \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx1036 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx3536 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx7036 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx8536 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx10036 \\pard \\intbl \\qc ";
		output << elem.GetID();
		output << "\\cell \\pard \\intbl \\qc";
		output << elem.GetName();
		output << "\\cell \\pard \\intbl";
		output << elem.GetType();
		output << "\\cell \\pard \\intbl \\qc";
		output << elem.GetNum_1();
		output << "\\cell \\pard \\intbl \\qc";
		output << elem.GetNum_2();
		output << "\\cell \\pard \\intbl \\row\n";
	}
	output << "\\pard }";
	output.close();

	ShellExecute(0, L"open", nameRTF, 0, L"", SW_SHOW);
}

void printToRtfAn(std::list<CAnSensor> &SensorArray, CString &nameRTF, CString &station) {
	std::ofstream output(nameRTF);
	CT2CA pszConvertedAnsiString(station);
	std::string out = (pszConvertedAnsiString);
	output << "{\\rtf1 \n \\par ";
	output << "{\\viewkind4\\uc1 \\pard\\sa200\\sl276\\slmult1\\qc\\bПеречень аналоговых данных АПК-ДК для передачи в МПЦ-ЭЛ ";
	output << '(' << out << ')';
	output << "\\par}" << std::endl;
	output << "\\trowd \\trql\\trgaph108\\trrh280\\trleft36 \\clbrdrt\\brdrth \\clbrdrl\\brdrth \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx1036\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx3336\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx5636 \\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx6836\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx8636\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx9936\\pard\\intbl";
	output << "\\qc№";
	output << "\\cell\\pard\\intbl";
	output << "\\qcНазвание объекта";
	output << " \\cell\\pard \\intbl";
	output << "\\qcТип объекта";
	output << "\\cell\\pard \\intbl";
	output << "\\qc№ датчика в массиве";
	output << "\\cell\\pard \\intbl";
	output << "\\qcЕденицы измерения";
	output << "\\cell\\pard \\intbl";
	output << "\\qcИсточник данных (система)";
	output << "\\cell\\pard \\intbl\\row \n";
	for (const auto &elem : SensorArray) {
		if (elem.GetID() == 0) continue;
		output << "\\trowd \\trql\\trgaph108\\trrh280\\trleft36 \\clbrdrt\\brdrth \\clbrdrl\\brdrth \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx1036\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx3336\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx5636 \\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx6836\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx8636\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx9936\\pard\\intbl\\qc ";
		output << elem.GetID();
		output << "\\cell\\pard\\intbl\\qc";
		output << elem.GetName();
		output << "\\cell\\pard\\intbl";
		output << elem.GetType();
		output << "\\cell\\pard\\intbl\\qc ";
		output << elem.GetNum_1();
		output << "\\cell\\pard\\intbl\\qc";
		output << elem.GetUnit();
		output << "\\cell\\pard\\intbl\\qc";
		output << " ";
		output << "\\cell\\pard\\intbl\\row \n";
	}
	output << "\\pard }";
	output.close();

	ShellExecute(0, L"open", nameRTF, 0, L"", SW_SHOW);
}

CString makeDig(CString &NameConfig, CString &NameRTF, CString &station, BOOL &SimpAnalyze) {
	CString FileName;
	FileName = NameRTF + '\\' + station;
	FileName += L" Перечень дискретных данных АПК-ДК для передачи в МПЦ-ЭЛ.rtf";
	setlocale(LC_ALL, "Russian");
	std::ifstream config(NameConfig);
	std::string line;
	if (config.is_open()) {
		CDigSensor node;
		SensorArrayDig.push_back(node);
		while (getline(config, line)) {
			line = O2A(line);
			if (SensorDescribe(line) && line.find_first_of("1234567890") == 0) {
				CDigSensor node;
				node.MakeSensor(line, SimpAnalyze);
				while (!IsNotGap(SensorArrayDig.back(), node)) {
					CDigSensor newnode((SensorArrayDig.back().GetID() + 1));
					SensorArrayDig.push_back(newnode);
				}
				SensorArrayDig.push_back(node);
			}
		}
	}
	return FileName;
}

CString makeAn(CString &NameConfig, CString &NameRTF, CString &station, BOOL &SimpAnalyze) {
	CString FileName;
	FileName = NameRTF + '\\' + station;
	FileName += L" Перечень аналоговых данных АПК-ДК для передачи в МПЦ-ЭЛ.rtf";
	setlocale(LC_ALL, "Russian");
	std::ifstream config(NameConfig);
	std::string line;
	if (config.is_open()) {
		CAnSensor node;
		SensorArrayAn.push_back(node);
		while (getline(config, line)) {
			line = O2A(line);
			if (SensorDescribe(line) && line.find_first_of("1234567890") == 0) {
				CAnSensor node;
				node.MakeSensor(line, SimpAnalyze);
				while (!IsNotGap(SensorArrayAn.back(), node)) {
					CAnSensor newnode((SensorArrayAn.back().GetID() + 1));
					SensorArrayAn.push_back(newnode);
				}
				SensorArrayAn.push_back(node);
			}
		}
	}
	return FileName;
}

std::string O2A(std::string &line) {
	char *ex = (char*)alloca(strlen(line.c_str())+1);
	OemToAnsi(line.c_str(), ex);
	line = ex;
	return line;
}