#include "AnSensorFromConf.h"
#include "DigSensorFromConf.h"

void readfile(CString &NameConfig, CString &NameRTF, CString &station, BOOL &SimpAnalyze, BOOL &An);
CString makeDig(CString &NameConfig, CString &NameRTF, CString &station, BOOL &SimpAnalyze);
CString makeAn(CString &NameConfig, CString &NameRTF, CString &station, BOOL &SimpAnalyze);
bool SensorDescribe(std::string &line);
template <class T>
bool IsNotGap(T &Prev, T &Next);
int MakeNumber(char c);
void printToRtfDig(std::list<CDigSensor> &SensorArray, CString &nameRTF, CString &station);
void printToRtfAn(std::list<CAnSensor> &SensorArray, CString &nameRTF, CString &station);
std::string O2A(std::string &line);
std::string A2O(std::string &line);
BOOL IsRight(std::string &line);