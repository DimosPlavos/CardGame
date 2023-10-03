#include "sgg/graphics.h"
#include "defines.h"
#include <string>
#include <iostream>
#include "CentralCardRight.h"

CentralCardRight::CentralCardRight()
{
	SETCOLOR(m_color, 1.0f, 1.0f, 1.0f);

}

int CentralCardRight::getvalue(vector <Cards*> k, int i) const
{
	return k.at(i)->getvalue();
}

string CentralCardRight::getname(vector <Cards*> k, int i) const
{
	return k.at(i)->getname();
}

void CentralCardRight::setname(vector <Cards*> k, int i, string k_name)
{
	k.at(i)->setname(k_name);
}

void CentralCardRight::setvalue(vector <Cards*> k, int i, int k_value)
{
	k.at(i)->setvalue(k_value);
}


void CentralCardRight::draw(vector <Cards*> k, int l)
{
	graphics::Brush br;

	float h = 1.0f * c_highlighted;
	if (i == 1) {
		SETCOLOR(br.fill_color, h, h, h * 0.0f);
	}
	else if (i == 2) {
		SETCOLOR(br.fill_color, h, h * 0.0f, h);
	}
	graphics::drawRect(m_pos[0], m_pos[1], CARD_WIDTH + 0.13f, CARD_HEIGHT + 0.13f, br);

	SETCOLOR(br.fill_color, m_color[0], m_color[1], m_color[2]);
	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + std::string(k.at(l)->getname());
	graphics::drawRect(m_pos[0], m_pos[1], CARD_WIDTH, CARD_HEIGHT, br);

}

void CentralCardRight::update() {
}