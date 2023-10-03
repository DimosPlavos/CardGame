#pragma once
#include <iostream>
#include <string>
#include "Player1.h"
using namespace std;


class CentralCardRight : public Cards {
protected:
	int value;
	string name;
	float m_pos[2];
	float m_color[3];
	bool c_highlighted = false;
	int i;
public:
	void draw(vector <Cards*> k, int l);
	void update();
	CentralCardRight(string in_name, int in_value) :name(in_name), value(in_value) {};
	CentralCardRight();
	int getvalue(vector <Cards*> k, int i) const;
	string getname(vector <Cards*> k, int i) const;
	void setname(vector <Cards*> k, int i, string k_name);
	void setvalue(vector <Cards*> k, int i, int k_value);
	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	void setName(string k) { name = k; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }
	void setHighlight(bool h, int j) { c_highlighted = h; i = j; }
};

