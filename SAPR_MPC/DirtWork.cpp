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
#include "CInfoBox.h"


std::list<CAnSensor>SensorArrayAn;
std::list<CDigSensor>SensorArrayDig;



void readfile(CString &NameConfig, CString &NameRTF, CString &station, BOOL &SimpAnalyze, BOOL &An) {
	int flag;
	if (An)  flag = makeAn(NameConfig, NameRTF, station, SimpAnalyze);
	else  flag = makeDig(NameConfig, NameRTF, station, SimpAnalyze);
	if (flag == 0 || flag == 2) {
		if (An) printToRtfAn(SensorArrayAn, NameRTF, station);
		else printToRtfDig(SensorArrayDig, NameRTF, station);
	}
	else if (flag == 1) {
		printToRtfAsOneBit(SensorArrayDig, NameRTF, station);
	}
	SensorArrayDig.erase(SensorArrayDig.begin(), SensorArrayDig.end());
	SensorArrayAn.erase(SensorArrayAn.begin(), SensorArrayAn.end());
}

bool SensorDescribe(std::string &line) {
	if (line.find('@') != -1) return true;
	else return false;
}
template <class T>
bool IsNotGap(T &Prev, T &Next) {
	if (Prev.GetID() + 1 >= Next.GetID()) return true;
	else return false;
}

int MakeNumber(char c) {
	return (int)c - 48;
}

void printToRtfDig(std::list<CDigSensor> &SensorArray, CString &nameRTF, CString &station) {
	CString FileName;
	FileName = nameRTF + '\\' + station;
	FileName += L" �������� ���������� ������ ���-�� ��� �������� � ���-��.rtf";
	nameRTF = FileName;
	setlocale(LC_ALL, "Russian");
	std::ofstream output(nameRTF);
	CT2CA pszConvertedAnsiString(station);
	std::string out = (pszConvertedAnsiString);
	output << "{\\rtf1 \n\\par";
	output << "{\\viewkind4 \\uc1 \\pard \\sa200 \\sl276 \\slmult1 \\qc \\b �������� ���������� ������ ���-�� ��� �������� � ���-��";
	output << ' (' << out << ')';
	output << "\\par}" << std::endl;
	output << "\\trowd \\trql \\trgaph108 \\trrh280 \\trleft36 \\clbrdrt \\brdrth \\clbrdrl \\brdrth \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx1036 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx3536 \\clbrdrt \\brdrth \\clbrdrl\\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx7036 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx10036 \\pard \\intbl";
	output << " \\qc�";
	output << "\\cell \\pard \\intbl";
	output << " \\qc�������� �������";
	output << "\\cell \\pard \\intbl";
	output << " \\qc��� �������";
	output << "\\cell \\pard \\intbl";
	output << " \\qc� ������� � �������";
	output << "\\cell \\pard \\intbl \\row \n";
	for (const auto &elem : SensorArray) {
		if (elem.GetID() == 0) continue;
		output << "\\trowd \\trql \\trgaph108 \\trrh280 \\trleft36 \\clbrdrt \\brdrth \\clbrdrl \\brdrth \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx1036 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx3536 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx7036 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx8536 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx10036 \\pard \\intbl \\qc ";
		output << elem.GetID();
		output << "\\cell \\pard \\intbl \\qc ";
		output << elem.GetName();
		output << "\\cell \\pard \\intbl ";
		output << elem.GetType();
		output << "\\cell \\pard \\intbl \\qc ";
		output << elem.GetNum_1();
		output << "\\cell \\pard \\intbl \\qc ";
		output << elem.GetNum_2();
		output << "\\cell \\pard \\intbl \\row\n";
	}
	output << "\\pard }";
	output.close();

	ShellExecute(0, L"open", nameRTF, 0, L"", SW_SHOW);
}

void printToRtfAn(std::list<CAnSensor> &SensorArray, CString &nameRTF, CString &station) {
	CString FileName;
	FileName = nameRTF + '\\' + station;
	FileName += L" �������� ���������� ������ ���-�� ��� �������� � ���-��.rtf";
	nameRTF = FileName;
	setlocale(LC_ALL, "Russian");
	std::ofstream output(nameRTF);
	CT2CA pszConvertedAnsiString(station);
	std::string out = (pszConvertedAnsiString);
	output << "{\\rtf1 \n \\par ";
	output << "{\\viewkind4\\uc1 \\pard\\sa200\\sl276\\slmult1\\qc\\b�������� ���������� ������ ���-�� ��� �������� � ���-�� ";
	output << ' (' << out << ')';
	output << "\\par}" << std::endl;
	output << "\\trowd \\trql\\trgaph108\\trrh280\\trleft36 \\clbrdrt\\brdrth \\clbrdrl\\brdrth \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx1036\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx3336\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx5636 \\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx6836\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx8636\\clbrdrt\\brdrth \\clbrdrl\\brdrdb \\clbrdrb\\brdrdb \\clbrdrr\\brdrdb \\cellx9936\\pard\\intbl";
	output << "\\qc�";
	output << "\\cell\\pard\\intbl";
	output << "\\qc�������� �������";
	output << " \\cell\\pard \\intbl";
	output << "\\qc��� �������";
	output << "\\cell\\pard \\intbl";
	output << "\\qc� ������� � �������";
	output << "\\cell\\pard \\intbl";
	output << "\\qc������� ���������";
	output << "\\cell\\pard \\intbl";
	output << "\\qc�������� ������ (�������)";
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

void printToRtfAsOneBit(std::list<CDigSensor> &SensorArray, CString &nameRTF, CString &station) {
	CString FileName;
	FileName = nameRTF + '\\' + station;
	FileName += L" �������� ���������� ������ ���-�� ��� �������� � ���-��.rtf";
	nameRTF = FileName;
	setlocale(LC_ALL, "Russian");
	std::ofstream output(nameRTF);
	CT2CA pszConvertedAnsiString(station);
	std::string out = (pszConvertedAnsiString);
	output << "{\\rtf1 \n\\par";
	output << "{\\viewkind4 \\uc1 \\pard \\sa200 \\sl276 \\slmult1 \\qc \\b �������� ���������� ������ ���-�� ��� �������� � ���-��";
	output << ' (' << out << ')';
	output << "\\par}" << std::endl;
	output << "\\trowd \\trql \\trgaph108 \\trrh280 \\trleft36 \\clbrdrt \\brdrth \\clbrdrl \\brdrth \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx1036 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx4236 \\clbrdrt \\brdrth \\clbrdrl\\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx8536 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx10036 \\pard \\intbl";
	output << " \\qc�";
	output << "\\cell \\pard \\intbl";
	output << " \\qc�������� �������";
	output << "\\cell \\pard \\intbl";
	output << " \\qc��� �������";
	output << "\\cell \\pard \\intbl";
	output << " \\qc� ������� � �������";
	output << "\\cell \\pard \\intbl \\row \n";
	for (const auto &elem : SensorArray) {
		if (elem.GetID() == 0) continue;
		output << "\\trowd \\trql \\trgaph108 \\trrh280 \\trleft36 \\clbrdrt \\brdrth \\clbrdrl \\brdrth \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx1036 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx4236 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx8536 \\clbrdrt \\brdrth \\clbrdrl \\brdrdb \\clbrdrb \\brdrdb \\clbrdrr \\brdrdb \\cellx10036 \\pard \\intbl \\qc ";
		output << elem.GetID();
		output << "\\cell \\pard \\intbl \\qc ";
		output << elem.GetName();
		output << "\\cell \\pard \\intbl ";
		output << elem.GetType();
		output << "\\cell \\pard \\intbl \\qc ";
		output << elem.GetID()-1;
		output << "\\cell \\pard \\intbl \\row\n";
	}
	output << "\\pard }";
	output.close();

	ShellExecute(0, L"open", nameRTF, 0, L"", SW_SHOW);
}

int makeDig(CString &NameConfig, CString &NameRTF, CString &station, BOOL &SimpAnalyze) {
	setlocale(LC_ALL, "Russian");
	std::ifstream config(NameConfig);
	std::string line;
	int flag= 0;
	if (config.is_open()) {
		CDigSensor node;
		SensorArrayDig.push_back(node);
		while (getline(config, line)) {
			line = O2A(line);
			if (line.find("$Bits_number") != -1) {
				flag = line[line.find_first_of("12")]-48;
				std::string it;
				it = std::to_string(flag);
				CString its (it.c_str());
				its += ": ���������� ����� �� ������";
				if (AfxMessageBox(its, MB_OKCANCEL) == IDCANCEL) return 4;
				else continue;
			}
			if (SensorDescribe(line) && IsRight(line)) {
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
	return flag;
}

int makeAn(CString &NameConfig, CString &NameRTF, CString &station, BOOL &SimpAnalyze) {
	setlocale(LC_ALL, "Russian");
	std::ifstream config(NameConfig);
	std::string line;
	int flag =0;
	if (config.is_open()) {
		CAnSensor node;
		SensorArrayAn.push_back(node);
		while (getline(config, line)) {
			line = O2A(line);
			if (line.find("$Bits_number") != -1) {
				flag = line[line.find_first_of("12")];
			}
			if (SensorDescribe(line) && IsRight(line)) {
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
	return flag;
}
std::string O2A(std::string &line) {
	char *ex = (char*)alloca(strlen(line.c_str()) + 1);
	OemToAnsi(line.c_str(), ex);
	line = ex;
	return line;
}

std::string A2O(std::string &line) {
	char *ex = (char*)alloca(strlen(line.c_str()) + 1);
	AnsiToOem(line.c_str(), ex);
	line = ex;
	return line;
}

BOOL IsRight(std::string &line) {
	int pos_1;
	pos_1 = line.find_first_of("1234567890", 0);
	if (pos_1 == -1) return false;
	for (int i = 0; i < pos_1; i++) {
		if (line[i] == ' ') continue;
		else return false;
	}
	return true;
}

CString Translate(CString line) {
	char mas[44][2] = { 
	{'a', '�'},
	{'b','�'},
	{'c','�'},
	{'d','�'},
	{'e','�'},
	{'f','�'},
	{'g','�'},
	{'h','�'},
	{'i','�'},
	{'k','�'},
	{'l','�'},
	{'m','�'},
	{'n','�'},
	{'o','�'},
	{'p','�'},
	{'r','�'},
	{'s','�'},
	{'t','�'},
	{'u','�'},
	{'v','�'},
	{'w','�'},
	{'z','�'},
	{'A','�'},
	{'B','�'},
	{'C','�'},
	{'D','�'},
	{'E','�'},
	{'F','�'},
	{'G','�'},
	{'H','�'},
	{'I','�'},
	{'K','�'},
	{'L','�'},
	{'M','�'},
	{'N','�'},
	{'O','�'},
	{'P','�'},
	{'R','�'},
	{'S','�'},
	{'T','�'},
	{'U','�'},
	{'V','�'},
	{'W','�'},
	{'Z','�'}
	};
	CT2CA pszConvertedAnsiString(line);
	std::string newline(pszConvertedAnsiString);
	if (newline.find_first_of("������������������������������")!= -1) {
		return line;
	}
	else {
		for (int i = 0; i < newline.size(); i++) {
			for (int k = 0; k < 44; k++) {
				if (mas[k][0] == line.GetAt(i)) {
					newline[i] = mas[k][1];
					continue;
				}
			}
		}
		line = newline.c_str();
		return line;
	}
}