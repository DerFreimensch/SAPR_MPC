#pragma once

class CAnSensor {
public:
	CAnSensor MakeSensor(std::string &line, BOOL &simple);
	int GetID() const;
	int GetNum_1() const;
	std::string simpleMake(std::string &line);
	std::string GetName() const;
	std::string GetType() const;
	std::string GetUnit() const;
	CAnSensor(int NewID);
	CAnSensor();
protected:
	int IDFind(std::string &line);
	std::string NameFind(std::string &line);
	std::string TypeFind(std::string &line);
	void NumberWrite(int NewID);
	void ObjWrite(std::string& Name, std::string &Type);
private:
	int ID, numOfSensor_1;
	std::string  Name_obj, Type_obj, Unit, Sourse;
};