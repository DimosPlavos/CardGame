#include "sgg/graphics.h"
#include "defines.h"
#include <string>
#include <iostream>
#include "Card1A.h"

Cards1A::Cards1A()
{
	
	SETCOLOR(m_color, 1.0f, 1.0f, 1.0f);

}

int Cards1A::getvalue(vector <Cards*> k, int i) const
{
	return k.at(i)->getvalue();
}

string Cards1A::getname(vector <Cards*> k, int i) const
{
	return k.at(i)->getname();
}

void Cards1A::setname(vector <Cards*> k, int i,string k_name)
{
	k.at(i)->setname(k_name);
}

void Cards1A::setvalue(vector <Cards*> k, int i ,int k_value)
{
	k.at(i)->setvalue(k_value);
}


void Cards1A::draw(vector <Cards*> k,int l)
{

	graphics::Brush br;

	float h = 1.0f * c_highlighted;
	SETCOLOR(br.fill_color, h , h , h * 0.0f);
	graphics::drawRect(m_pos[0], m_pos[1], CARD_WIDTH + 0.13f, CARD_HEIGHT + 0.13f, br);

	SETCOLOR(br.fill_color, m_color[0], m_color[1], m_color[2]);
	br.outline_opacity = 0.0f;
	if (l == -1) {
		br.texture = ASSET_PATH + std::string("CardBack.png");
	}
	else {
		br.texture = ASSET_PATH + std::string(k.at(l)->getname());
	}
	
	graphics::drawRect(m_pos[0], m_pos[1], CARD_WIDTH, CARD_HEIGHT, br);

}



void Cards1A::update()
{
}

