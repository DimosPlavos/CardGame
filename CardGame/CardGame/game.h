#pragma once
#include <list>
#include "Card1A.h"
#include "CentralCard1.h"
#include "CardsRight.h"
#include "CentralCardRight.h"


class Game
{
public:
	void draw(); //to paixnidi analamvanei na sxediasei ton eayto toy
	void update();
	void init();
	void renew();
	bool notpossiblechanges();
	enum state_t { STATE_START, STATE_PLAYING, STATE_DUKU , STATE_OVER};
	~Game();

	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
	static Game* getInstance();

protected:
	state_t m_state = STATE_START;
	vector <Cards*> kkk; //vector with all of the 52 cards
	vector <Cards*> halfcards1; //cards of Player1
	vector <Cards*> halfcards2; //cards of Player2
	vector <Cards*> usedcards; //cards used as center cards
	Cards* temp;
	bool duku = false;
	static Game* m_instance;
	vector <Cards1A*>leftcards; //{cad1A,card1B,card1C,card1D}
	vector <CardsRight*>rightcards; //{cadR1,cardR2,cardR3,cardR4}
	vector <bool> usedL; //oso uparxei karta se mia apo tis 4 theseis
	vector <bool> usedR; //an teleiwsoun oi kartes kai h thesh meinei kenh
	int cur_positionL; //twrinh thesh tou paikth 1
	int cur_positionR; //twrinh thesh tou paikth 2
	int positionbackL; //an o paikths1 metakinhthei se mia kentrikh karta, otan thelei na epistrepsei, epistrefei sthn prohgoumenh karta positionbackL

	int positionbackR;//an o paikths2 metakinhthei se mia kentrikh karta, otan thelei na epistrepsei, epistrefei sthn prohgoumenh karta positionbackR
	Cards1A* cardL1 = new Cards1A();
	Cards1A* cardL2 = new Cards1A();
	Cards1A* cardL3 = new Cards1A();
	Cards1A* cardL4 = new Cards1A();
	CardsRight* cardR1 = new CardsRight();
	CardsRight* cardR2 = new CardsRight();
	CardsRight* cardR3 = new CardsRight();
	CardsRight* cardR4 = new CardsRight();
	CentralCard1* c_card1 = new CentralCard1();
	CentralCardRight* c_card2 = new CentralCardRight();
	
	Game(); 
	int l1 = 0, l2 = 1,l3 = 2,l4 = 3,l5 = 4;
	int r1 = 0, r2 = 1, r3 = 2, r4 = 3, r5 = 4;
	bool Pl1_sel_for_dukuL = false;
	bool Pl1_sel_for_dukuR = false;
	bool Pl2_sel_for_dukuL = false;
	bool Pl2_sel_for_dukuR = false;
	int previous_changeL = l5; //sthn previous change kratame kai to index toy teleytaiou fullou pou exei prostetheti pou einai kai max
	int previous_changeR = r5;
	int lastchangesL = 0;
	int lastchangesR = 0;
	bool flag = false;
	bool flag1 = false;
	bool f = false;
	bool duku1 = false;
	bool duku2 = false;
	int winner;
	bool still_changes = true;
	bool is_cardL1_selected = false;
	bool is_cardL2_selected = false;
	bool is_cardL3_selected = false;
	bool is_cardL4_selected = false;
	bool is_cardR1_selected = false;
	bool is_cardR2_selected = false;
	bool is_cardR3_selected = false;
	bool is_cardR4_selected = false;
	Cards *cur_cardL = nullptr;
	Cards* cur_cardR = nullptr;
	Cards1A* prev_card_to_come_backL = nullptr;
	CardsRight* prev_card_to_come_backR = nullptr;
	Cards1A* selected_cardL = nullptr;
	CardsRight* selected_cardR = nullptr;
	int number_ofselcardL;
	int number_ofselcardR;
};



