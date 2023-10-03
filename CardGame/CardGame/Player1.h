#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Cards {
public:
	Cards();
	virtual ~Cards();
	Cards(string in_name, int in_value) :name(in_name), value(in_value) {};
	int getvalue() const;
	string getname() const;
	void setname(string k_name);
	void setvalue(int k_value);
protected:
	int value;
	string name;
};
