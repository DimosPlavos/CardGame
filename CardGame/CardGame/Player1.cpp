#include "Player1.h"
#include "sgg/graphics.h"
#include "defines.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;



Cards::Cards()
{
	
}

Cards::~Cards()
{	//EDW THA DIAGRAPSW TON PINAKA KKK


	/*for (int i = 0; i < N; i++) {
		delete arrayy[i];
	}
	delete[] arrayy;  */
}


int Cards::getvalue() const
{
	return value;
}

string Cards::getname() const
{
	return name;
}

void Cards::setname(string k_name)
{
	name = k_name;
}

void Cards::setvalue(int k_value)
{
	value = k_value;
}







