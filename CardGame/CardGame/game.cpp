#include "defines.h"
#include "game.h"
#include "sgg/graphics.h"
#include "sgg/scancodes.h"
#include <time.h>
using namespace std;


Game::Game()
{
	
}

void Game::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f; 
	//sto state_start emfanizetai h prwth eikona pou ekshgei touw kanones tou paixnidiou
	if (m_state == STATE_START) {
		br.texture = ASSET_PATH + std::string("StartImage.png");
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	}
	else if (m_state == STATE_PLAYING) {
		br.texture = ASSET_PATH + std::string("DukuBackground.png");
		\
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		if (flag1 == false) { //sxediazw tis arxikes kartes pou emfanizontai sthn othonh
			cardL1->draw(halfcards1, 0);
			cardL2->draw(halfcards1, 1);
			cardL3->draw(halfcards1, 2);
			cardL4->draw(halfcards1, 3);

			cardR1->draw(halfcards2, 0);
			cardR2->draw(halfcards2, 1);
			cardR3->draw(halfcards2, 2);
			cardR4->draw(halfcards2, 3);

			c_card1->draw(halfcards1, 4);
			c_card2->draw(halfcards2, 4);

			usedcards.push_back(halfcards1.at(5));
			usedcards.push_back(halfcards2.at(5));
			flag1 = true;
		}
		
		//sxediazw se kathe kare tis kartes tou kamva
		if (usedL.at(0)) { cardL1->draw(halfcards1, l1); } else { cardL1->draw(halfcards1, -1); }
		if (usedL.at(1)) { cardL2->draw(halfcards1, l2); } else { cardL2->draw(halfcards1, -1); }
		if (usedL.at(2)) { cardL3->draw(halfcards1, l3); } else { cardL3->draw(halfcards1, -1); }
		if (usedL.at(3)) { cardL4->draw(halfcards1, l4); } else { cardL4->draw(halfcards1, -1); }
		if (usedR.at(0)) { cardR1->draw(halfcards2, r1);} else { cardR1->draw(halfcards2, -1); }
		if (usedR.at(1)) { cardR2->draw(halfcards2, r2);} else { cardR2->draw(halfcards2, -1); }
		if (usedR.at(2)) { cardR3->draw(halfcards2, r3);} else { cardR3->draw(halfcards2, -1); }
		if (usedR.at(3)) { cardR4->draw(halfcards2, r4);} else { cardR4->draw(halfcards2, -1); }
		c_card1->draw(halfcards1, l5);
		c_card2->draw(halfcards2, r5);
		
	}
	//otan ginetai duku emfanizetai mhnuma oti egine duku apo ton ekastote player (me allagh ths eikonas)
	else if (m_state == STATE_DUKU) {
		if (duku1){ br.texture = ASSET_PATH + std::string("Duku1.png"); }
		if (duku2) { br.texture = ASSET_PATH + std::string("Duku2.png"); }
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		if (f == false) {
			f = true;
		}
		m_state = STATE_PLAYING;
	}

	//teleiwnei to paixnidi kai emfanizetai katallhlh eikona kai to antistoixo mhnyma toy nikhth
	else if (m_state == STATE_OVER) {
		if (winner==0){ br.texture = ASSET_PATH + std::string("Draw.png");}
		if (winner == 1) { br.texture = ASSET_PATH + std::string("Player1wins.png"); }
		if (winner == 2) { br.texture = ASSET_PATH + std::string("Player2wins.png"); }
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
		graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	}

}

void Game::update()
{
	//an pathseis space ksekinaei to paixnidi
	if (m_state == STATE_START) {
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			m_state = STATE_PLAYING;
		}
	}
	else if (m_state == STATE_PLAYING) {
		//to mhnuma tou duku tha emfanistei gia 1500 ns
		if (f == true) { sleep(1500); f = false; }

		cardL1->update();
		cardL2->update();
		cardL3->update();
		cardL4->update();

		cardR1->update();
		cardR2->update();
		cardR3->update();
		cardR4->update();

		c_card1->update();
		c_card2->update();

		//--------------AN DEN YPARXOUN PITHANES ALLAGES , ANANEWSE TA XARTIA--------------------------// 
		//kai kanw mikrh paush (sto renew) kai ananewnw aytomata ta c_card1, c_card2
		if(notpossiblechanges())
		{
			still_changes = false;
			if (c_card1->getvalue(halfcards1, l5) != c_card2->getvalue(halfcards2, r5) || c_card1->getvalue(halfcards1, l5) == c_card2->getvalue(halfcards2, r5) && 
				(previous_changeR < halfcards2.size() - 1) && (previous_changeL< halfcards1.size() - 1)) {
				renew();
			}

		}


		if (flag == false) { //EKTELEITAI MIA FORA KAI KANEI HIGHLIGHT TIS ARXIKES KARTES
			cardL1->setHighlight(true);
			cardR1->setHighlight(true);
			cur_cardL = cardL1;
			cur_cardR = cardR1;
			cur_positionL = 0;
			cur_positionR = 0;
			flag = true;
		}


//----------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------M E R O S  A--------------------------------------------------//
//----------------------------------------------METAKINHSEIS PLAYER 1---------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
		//pataw D, metakinoumai sto fullo deksia
		if (graphics::getKeyState(graphics::SCANCODE_D) && cur_cardL != c_card2 && cur_cardL != c_card1) {
			for (int i = cur_positionL + 1; i < 4; i++) {
				if (usedL.at(i)) {
					sleep(180);
					leftcards.at(cur_positionL)->setHighlight(false);
					cur_positionL = i;
					cur_cardL = leftcards.at(i);
					leftcards.at(i)->setHighlight(true);
					break;
				}
			}
		}
		//pataw A, metakinoumai sto fullo aristera
		if (graphics::getKeyState(graphics::SCANCODE_A) && cur_cardL != c_card1 && cur_cardL != c_card2) {
			for (int i = cur_positionL - 1; i >= 0; i--) {
				if (usedL.at(i)) {
					sleep(180);
					leftcards.at(cur_positionL)->setHighlight(false);
					cur_positionL = i;
					cur_cardL = leftcards.at(i);
					leftcards.at(i)->setHighlight(true);
					break;
				}
			}
		}
		//pataw W, metakinoumai sto fullo panw
		if (graphics::getKeyState(graphics::SCANCODE_W) && cur_cardL != c_card1 && cur_cardL != c_card2) {
			leftcards.at(cur_positionL)->setHighlight(false);
			prev_card_to_come_backL = leftcards.at(cur_positionL);
			positionbackL = cur_positionL;
			cur_cardL = c_card1;
			c_card1->setHighlight(true, 1);
		}

		//pataw D, epilegw fullo gia metakinhsh
		if (graphics::getKeyState(graphics::SCANCODE_Q) && cur_cardL != c_card1 && cur_cardL != c_card2) {
			if (cur_positionL == 0) { is_cardL1_selected = true; selected_cardL = cardL1; number_ofselcardL = l1; is_cardL2_selected = false; is_cardL3_selected = false; is_cardL4_selected = false;}
			if (cur_positionL == 1) { is_cardL2_selected = true; selected_cardL = cardL2; number_ofselcardL = l2; is_cardL1_selected = false; is_cardL3_selected = false; is_cardL4_selected = false;
			}
			if (cur_positionL == 2) { is_cardL3_selected = true; selected_cardL = cardL3; number_ofselcardL = l3; is_cardL1_selected = false; is_cardL2_selected = false; is_cardL4_selected = false;
			}
			if (cur_positionL == 3) { is_cardL4_selected = true; selected_cardL = cardL4; number_ofselcardL = l4; is_cardL1_selected = false; is_cardL2_selected = false; is_cardL3_selected = false;
			}
		}

		//an exw epileksei karta kai paw stis kentrikes gia na ginei h allagh
		else if (cur_cardL == c_card1) {
			if (graphics::getKeyState(graphics::SCANCODE_Q)) {
				if (is_cardL1_selected || is_cardL2_selected || is_cardL3_selected || is_cardL4_selected) {
					//ELEGXW AN THROUNTAI OI PROYPOTHESEIS GIA ALLAGH KARTAS
					if (selected_cardL->getvalue(halfcards1, number_ofselcardL) == c_card1->getvalue(halfcards1, l5) + 1 ||
						selected_cardL->getvalue(halfcards1, number_ofselcardL) == c_card1->getvalue(halfcards1, l5) - 1 ||
						selected_cardL->getvalue(halfcards1, number_ofselcardL) == 13 && c_card1->getvalue(halfcards1, l5) == 1 ||
						selected_cardL->getvalue(halfcards1, number_ofselcardL) == 1 && c_card1->getvalue(halfcards1, l5) == 13) {
						//KANW THN ALLAGH
						c_card1->setname(halfcards1, l5, selected_cardL->getname(halfcards1, number_ofselcardL));
						c_card1->setvalue(halfcards1, l5, selected_cardL->getvalue(halfcards1, number_ofselcardL));
						//AN TA ENAPOMEINANTA FULLA EINAI AUTA POY FAINONTAI STON KANVA
						if (previous_changeL == halfcards1.size() - 1) {
							lastchangesL++;
							if (is_cardL1_selected) { usedL.at(0) = false; }
							if (is_cardL2_selected) { usedL.at(1) = false; }
							if (is_cardL3_selected) { usedL.at(2) = false; }
							if (is_cardL4_selected) { usedL.at(3) = false; }
						}
						//VAZW STO USEDCARDS TO SYNOLO TWN KARTWN POY EXOYN XRHSIMOPOIHTHEI GIA ALLAGH
						else {
							selected_cardL = nullptr;
							if (is_cardL1_selected) { usedcards.push_back(halfcards1.at(l1)); l1 = previous_changeL + 1; previous_changeL++; }
							else if (is_cardL2_selected) { usedcards.push_back(halfcards1.at(l2)); l2 = previous_changeL + 1; previous_changeL++; }
							else if (is_cardL3_selected) { usedcards.push_back(halfcards1.at(l3)); l3 = previous_changeL + 1; previous_changeL++; }
							else if (is_cardL4_selected) { usedcards.push_back(halfcards1.at(l4)); l4 = previous_changeL + 1; previous_changeL++; }
						}
						is_cardL1_selected = false;
						is_cardL2_selected = false;
						is_cardL3_selected = false;
						is_cardL4_selected = false;
					}
				}
			}

			//AN VRISKOMAI STO PRWTO KENTRIKO FYLLO KAI PATHSW S, KATEVAINW STO FYLLO APO TO OPOIO EIXA ANEVEI
			if (graphics::getKeyState(graphics::SCANCODE_S)) {
					c_card1->setHighlight(false, 1);
					if (usedL.at(positionbackL)) {
						cur_cardL = prev_card_to_come_backL;
						prev_card_to_come_backL->setHighlight(true);//OMOIWS NA GINEI STO KATW
					}
					else {
						cur_positionL = 3;
						if (usedL.at(2) && !usedL.at(3)) { cur_positionL = 2; }
						if (usedL.at(1) && !usedL.at(3) && !usedL.at(2)) { cur_positionL = 1; }
						if (usedL.at(0) && !usedL.at(3) && !usedL.at(2) && !usedL.at(1)) { cur_positionL = 0; }
						cur_cardL = leftcards.at(cur_positionL);
						leftcards.at(cur_positionL)->setHighlight(true);
					}

			}
			//ME D, METAKINOUMAI APO TO KENTRIKO FYLLO ARISTERA, STO KENTRIKO FYLLO DEKSIA
			if (graphics::getKeyState(graphics::SCANCODE_D)) {
				sleep(180);
				c_card1->setHighlight(false, 1);
				cur_cardL = c_card2;
				c_card2->setHighlight(true, 1);
			}
			//AN PATHSW 1, EPILEGW FYLLO GIA DUKU 
			if (graphics::getKeyState(graphics::SCANCODE_1) && cur_cardL == c_card1) {
				Pl1_sel_for_dukuL = true;
			}
			//H ENTOLH AYTH XREIAZETAI ETSI WSTE OTAN KAI OI DYO PAIKTES EXOYN HIGHLIGHTED TO IDIO FYLLO KAI O ENAS FYGEI, AYTO TO FYLLO NA PARAMEINEI HIGHLIGHTED STON ALLO
			if (cur_cardL != c_card1) {
				if (cur_cardR == c_card1) c_card1->setHighlight(true, 2);
			}
		}
		//AN O PAIKTHS 1 VRISKETAI STO FYLLO 2
		else if (cur_cardL == c_card2) {
			if (graphics::getKeyState(graphics::SCANCODE_Q)) {
				// H IDIA DIADIKASIA 
				if (is_cardL1_selected || is_cardL2_selected || is_cardL3_selected || is_cardL4_selected) {
					if (selected_cardL->getvalue(halfcards1, number_ofselcardL) == c_card2->getvalue(halfcards2, r5) + 1 ||
						selected_cardL->getvalue(halfcards1, number_ofselcardL) == c_card2->getvalue(halfcards2, r5) - 1 ||
						selected_cardL->getvalue(halfcards1, number_ofselcardL) == 13 && c_card2->getvalue(halfcards2, r5) == 1 ||
						selected_cardL->getvalue(halfcards1, number_ofselcardL) == 1 && c_card2->getvalue(halfcards2, r5) == 13) {
						
						c_card2->setname(halfcards2, r5, selected_cardL->getname(halfcards1, number_ofselcardL));
						c_card2->setvalue(halfcards2, r5, selected_cardL->getvalue(halfcards1, number_ofselcardL));
						
						if (previous_changeL == halfcards1.size() - 1) {
							lastchangesL++;
							if (is_cardL1_selected) { usedL.at(0) = false; }
							if (is_cardL2_selected) { usedL.at(1) = false; }
							if (is_cardL3_selected) { usedL.at(2) = false; }
							if (is_cardL4_selected) { usedL.at(3) = false; }
						}
						else {
							selected_cardL = nullptr;
							if (is_cardL1_selected) { usedcards.push_back(halfcards1.at(l1)); l1 = previous_changeL + 1; previous_changeL++; }
							else if (is_cardL2_selected) { usedcards.push_back(halfcards1.at(l2)); l2 = previous_changeL + 1; previous_changeL++; }
							else if (is_cardL3_selected) { usedcards.push_back(halfcards1.at(l3)); l3 = previous_changeL + 1; previous_changeL++; }
							else if (is_cardL4_selected) { usedcards.push_back(halfcards1.at(l4)); l4 = previous_changeL + 1; previous_changeL++; }
						}
						is_cardL1_selected = false;
						is_cardL2_selected = false;
						is_cardL3_selected = false;
						is_cardL4_selected = false;
					}
				}
			}
			//ME A METAKINOUMAI APO TO KENTRIKO FYLLO DEKSIA, STO KENTRIKO FYLLO ARISTERA
			if (graphics::getKeyState(graphics::SCANCODE_A)) {
				sleep(180);
				c_card2->setHighlight(false, 1);
				cur_cardL = c_card1;
				c_card1->setHighlight(true, 1);
			}
			//OTAN EIMAI STO KENTRIKO FYLLO DEKSIA KAI PATHSW S, KATEVAINW KATHE FORA STO DEKSIA FYLLO
			if (graphics::getKeyState(graphics::SCANCODE_S)) {
				sleep(180);
				c_card2->setHighlight(false, 1);

				// AN DEN YPARXEI TO DEKSIA FYLLO STO AMESWS EPOMENO K.O.K
				if (usedL.at(3)) { cur_positionL = 3; }
				else if (usedL.at(2)) { cur_positionL = 2; }
				else if (usedL.at(1)) { cur_positionL = 1; }
				else if (usedL.at(0)) { cur_positionL = 0; }
				cur_cardL = leftcards.at(cur_positionL);
				leftcards.at(cur_positionL)->setHighlight(true);

			}
			//EPILEGW TO KENTRIKO FYLLO ARISTERA GIA DUKU
			if (graphics::getKeyState(graphics::SCANCODE_1) && cur_cardL == c_card2) {
				Pl1_sel_for_dukuR = true;
			}
			if (cur_cardL != c_card2) {
				if (cur_cardR == c_card2) c_card2->setHighlight(true, 2);
			}
		}

		//AN EXOYN EPILEGEI KAI TA DYO FYLLA KAI EINAI OMOIA, GINETAI DUKU APO APO PAIKTH 1 //DEN GINETAI DUKU AN TA TELEUTAIA FULLA TWN DYO PAIKTWN EINAI AYTA POY EMFANIZONTAI STON KANVA
		if (Pl1_sel_for_dukuL && Pl1_sel_for_dukuR && duku == false && !(previous_changeR == halfcards2.size() - 1) && !(previous_changeL == halfcards1.size() - 1)) {
			if (c_card1->getvalue(halfcards1, l5) == c_card2->getvalue(halfcards2, r5)) {
				duku = true;
				duku1 = true;
				m_state = STATE_DUKU;
				//for (int i = 0; i < 4; i++) { usedR.at(i) = true; }  //xreiazetai mono an tou epitrepsw na kanei duku akoma ki an teleiwsoun ta enapomeinanta xartia tou enos
				//ANAKATEPSE TA XARTIA POY THA MOIRASEIS STON PAIKTH 2
				srand(time(0));
				for (int i = 0; i < usedcards.size(); i++) {
					int d = rand() % usedcards.size();
					temp = kkk[i];
					kkk[i] = kkk[d];
					kkk[d] = temp;
				}
				//MOIRASE TA XARTIA STON PAIKTH 2
				for (int i = 0; i < usedcards.size(); i++) {
					halfcards2.push_back(usedcards.at(i));
				}
				usedcards.clear();
			}
			Pl1_sel_for_dukuL = false;
			Pl2_sel_for_dukuR = false;
		}
		// AN TELEIWSOUN TA FULLA TOY 1, EINAI O NIKHTHS
		if (lastchangesL == 4) {
			winner = 1;
			m_state = STATE_OVER;
		}

//----------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------M E R O S  B--------------------------------------------------//
//----------------------------------------------METAKINHSEIS PLAYER 2---------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//

		//OMOIWS PAROUSIAZONTAI OI METAKINHSEIS TOU PAIKTH 2, METAKSY TWN 4 FYLLWN KAI TWN 2 KENTRIKWN

		if (graphics::getKeyState(graphics::SCANCODE_RIGHT) && cur_cardR != c_card2 && cur_cardR != c_card1) {
			for (int i = cur_positionR + 1; i < 4; i++) {
				if (usedR.at(i)) {
					sleep(180);
					rightcards.at(cur_positionR)->setHighlight(false);
					cur_positionR = i;
					cur_cardR = rightcards.at(i);
					rightcards.at(i)->setHighlight(true);
					break;
				}
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_LEFT) && cur_cardR != c_card1 && cur_cardR != c_card2) {
			for (int i = cur_positionR - 1; i >= 0; i--) {
				if (usedR.at(i)) {
					sleep(180);
					rightcards.at(cur_positionR)->setHighlight(false);
					cur_positionR = i;
					cur_cardR = rightcards.at(i);
					rightcards.at(i)->setHighlight(true);
					break;
				}
			}
		}
		if (graphics::getKeyState(graphics::SCANCODE_UP) && cur_cardR != c_card1 && cur_cardR != c_card2) {
			rightcards.at(cur_positionR)->setHighlight(false);
			prev_card_to_come_backR = rightcards.at(cur_positionR);
			positionbackR = cur_positionR;
			cur_cardR = c_card2;
			c_card2->setHighlight(true, 2);

		}
		if (graphics::getKeyState(graphics::SCANCODE_SLASH) && cur_cardR != c_card1 && cur_cardR != c_card2) {
			if (cur_positionR == 0) { is_cardR1_selected = true; selected_cardR = cardR1; number_ofselcardR = r1; is_cardR2_selected = false; is_cardR3_selected = false; is_cardR4_selected = false; }
			if (cur_positionR == 1) { is_cardR2_selected = true; selected_cardR = cardR2; number_ofselcardR = r2; is_cardR1_selected = false; is_cardR3_selected = false; is_cardR4_selected = false; }
			if (cur_positionR == 2) { is_cardR3_selected = true; selected_cardR = cardR3; number_ofselcardR = r3; is_cardR1_selected = false; is_cardR2_selected = false; is_cardR4_selected = false; }
			if (cur_positionR == 3) { is_cardR4_selected = true; selected_cardR = cardR4; number_ofselcardR = r4; is_cardR1_selected = false; is_cardR2_selected = false; is_cardR3_selected = false; }
		}

		else if (cur_cardR == c_card2) {
			if (graphics::getKeyState(graphics::SCANCODE_SLASH)) {
				if (is_cardR1_selected || is_cardR2_selected || is_cardR3_selected || is_cardR4_selected) {

					if (selected_cardR->getvalue(halfcards2, number_ofselcardR) == c_card2->getvalue(halfcards2, r5) + 1 ||
						selected_cardR->getvalue(halfcards2, number_ofselcardR) == c_card2->getvalue(halfcards2, r5) - 1 ||
						selected_cardR->getvalue(halfcards2, number_ofselcardR) == 13 && c_card2->getvalue(halfcards2, r5) == 1 ||
						selected_cardR->getvalue(halfcards2, number_ofselcardR) == 1 && c_card2->getvalue(halfcards2, r5) == 13) {
						
						c_card2->setname(halfcards2, r5, selected_cardR->getname(halfcards2, number_ofselcardR));
						c_card2->setvalue(halfcards2, r5, selected_cardR->getvalue(halfcards2, number_ofselcardR));
						
						if (previous_changeR == halfcards2.size() - 1) {
							lastchangesR++;
							if (is_cardR1_selected) { usedR.at(0) = false; }
							if (is_cardR2_selected) { usedR.at(1) = false; }
							if (is_cardR3_selected) { usedR.at(2) = false; }
							if (is_cardR4_selected) { usedR.at(3) = false; }
						}
						else {
							selected_cardR = nullptr;
							if (is_cardR1_selected) { usedcards.push_back(halfcards2.at(r1)); r1 = previous_changeR + 1; previous_changeR++; }
							else if (is_cardR2_selected) { usedcards.push_back(halfcards2.at(r2)); r2 = previous_changeR + 1; previous_changeR++; }
							else if (is_cardR3_selected) { usedcards.push_back(halfcards2.at(r3)); r3 = previous_changeR + 1; previous_changeR++; }
							else if (is_cardR4_selected) { usedcards.push_back(halfcards2.at(r4)); r4 = previous_changeR + 1; previous_changeR++; }
						}
						is_cardR1_selected = false;
						is_cardR2_selected = false;
						is_cardR3_selected = false;
						is_cardR4_selected = false;
					}
				}
			}
			if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {

				c_card2->setHighlight(false, 2);
				if (usedR.at(positionbackR)) {
					cur_cardR = prev_card_to_come_backR;
					prev_card_to_come_backR->setHighlight(true);
				}
				else {
					cur_positionR = 0;
					if (usedR.at(1) && !usedR.at(0)) { cur_positionR = 1; }
					if (usedR.at(2) && !usedR.at(1) && !usedR.at(0)) { cur_positionR = 2; }
					if (usedR.at(3) && !usedR.at(1) && !usedR.at(2) && !usedR.at(0)) { cur_positionR = 3; }
					cur_cardR = rightcards.at(cur_positionR);
					rightcards.at(cur_positionR)->setHighlight(true);
				}
			}
			if (graphics::getKeyState(graphics::SCANCODE_LEFT)) {
				sleep(180);
				c_card2->setHighlight(false, 2);
				cur_cardR = c_card1;
				c_card1->setHighlight(true, 2);
			}
			if (graphics::getKeyState(graphics::SCANCODE_L) && cur_cardR == c_card2) {
				Pl2_sel_for_dukuR = true;
			}
			if (cur_cardR != c_card2) {
				if (cur_cardL == c_card2) c_card2->setHighlight(true, 1);
			}
		}
		else if (cur_cardR == c_card1) {
			if (graphics::getKeyState(graphics::SCANCODE_SLASH)) {
				if (is_cardR1_selected || is_cardR2_selected || is_cardR3_selected || is_cardR4_selected) {
	
					if (selected_cardR->getvalue(halfcards2, number_ofselcardR) == c_card1->getvalue(halfcards1, l5) + 1 ||
						selected_cardR->getvalue(halfcards2, number_ofselcardR) == c_card1->getvalue(halfcards1, l5) - 1 ||
						selected_cardR->getvalue(halfcards2, number_ofselcardR) == 13 && c_card1->getvalue(halfcards1, l5) == 1 ||
						selected_cardR->getvalue(halfcards2, number_ofselcardR) == 1 && c_card1->getvalue(halfcards1, l5) == 13) {
						
						c_card1->setname(halfcards1, l5, selected_cardR->getname(halfcards2, number_ofselcardR));
						c_card1->setvalue(halfcards1, l5, selected_cardR->getvalue(halfcards2, number_ofselcardR));

						if (previous_changeR == halfcards2.size() - 1) {
							lastchangesR++;
							if (is_cardR1_selected) { usedR.at(0) = false; }
							if (is_cardR2_selected) { usedR.at(1) = false; }
							if (is_cardR3_selected) { usedR.at(2) = false; }
							if (is_cardR4_selected) { usedR.at(3) = false; }
						}
						else {
							selected_cardR = nullptr;
							if (is_cardR1_selected) { usedcards.push_back(halfcards2.at(r1)); r1 = previous_changeR + 1; previous_changeR++; }
							else if (is_cardR2_selected) { usedcards.push_back(halfcards2.at(r2)); r2 = previous_changeR + 1; previous_changeR++; }
							else if (is_cardR3_selected) { usedcards.push_back(halfcards2.at(r3)); r3 = previous_changeR + 1; previous_changeR++; }
							else if (is_cardR4_selected) { usedcards.push_back(halfcards2.at(r4)); r4 = previous_changeR + 1; previous_changeR++; }
						}
						is_cardR1_selected = false;
						is_cardR2_selected = false;
						is_cardR3_selected = false;
						is_cardR4_selected = false;
					}
				}
			}
			if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) {
				sleep(180);
				c_card1->setHighlight(false, 2);
				cur_cardR = c_card2;
				c_card2->setHighlight(true, 2);
			}
			if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {
				sleep(180);
				c_card1->setHighlight(false, 2);
				
				if (usedR.at(0)) { cur_positionR = 0; }
				else if (usedR.at(1)) { cur_positionR = 1; }
				else if (usedR.at(2)) { cur_positionR = 2; }
				else if (usedR.at(3)) { cur_positionR = 3; }
				cur_cardR = rightcards.at(cur_positionR);
				rightcards.at(cur_positionR)->setHighlight(true);
			}
			if (graphics::getKeyState(graphics::SCANCODE_L) && cur_cardR == c_card1) {
				Pl2_sel_for_dukuL = true;
			}
			if (cur_cardR != c_card1) {
				if (cur_cardL == c_card1) c_card1->setHighlight(true, 1);
			}
		}
		//DUKU APO PAIKTH 2
		if (Pl2_sel_for_dukuL && Pl2_sel_for_dukuR && duku == false && !(previous_changeR == halfcards2.size() - 1) && !(previous_changeL == halfcards1.size() - 1)) {
			if (c_card1->getvalue(halfcards1, l5) == c_card2->getvalue(halfcards2, r5)) {
				
				duku = true;
				duku2 = true;
				m_state = STATE_DUKU;
				//for (int i = 0; i < 4; i++) { usedL.at(i) = true; } //xreiazetai mono an tou epitrepsw na kanei duku akoma ki an teleiwsoun ta enapomeinanta xartia tou enos
				
				srand(time(0));
				for (int i = 0; i < usedcards.size(); i++) {
					int d = rand() % usedcards.size();
					temp = kkk[i];
					kkk[i] = kkk[d];
					kkk[d] = temp;
				}
				//MOIRASE TA XARTIA STON PAIKTH 1
				for (int i = 0; i < usedcards.size(); i++) {
					halfcards1.push_back(usedcards.at(i));
				}
				usedcards.clear();
			}
			Pl2_sel_for_dukuL = false;
			Pl2_sel_for_dukuR = false;
		}

		if (duku) { renew(); duku = false; }

		if (lastchangesR == 4) {
			winner = 2;
			m_state = STATE_OVER;
		}

	}
	
}


void Game::renew()
{
	// AN OI PAIKTES EXOUN KAI OI DYO ENAPOMEINANTA FYLLA, EKTOS TWN FYLLWN POY EMFANIZONTAI STHN OTHONH, TOTE OTAN KALEITAI H ANANEWSH TWN FYLLWN
	// O PAIKTHS 1 ANANEWNEI TO KENTRIKO FYLLO ARISTERA KAI O PAIKTHS 2 TO DEKSIA

	if (previous_changeL < halfcards1.size() - 1 && previous_changeR < halfcards2.size() - 1) 
	{
		sleep(2000);

		usedcards.push_back(halfcards1.at(l5));
		usedcards.push_back(halfcards2.at(r5));

		l5 = previous_changeL + 1;
		previous_changeL++;
		r5 = previous_changeR + 1;
		previous_changeR++;
		
	} 
	//AN MONO O 1 EXEI ENAPOMEINANTA FYLLA, ANANEWNEI MONO AYTOS TO KENTRIKO FYLLO ARISTERA
	else if (previous_changeL < halfcards1.size() - 1 && previous_changeR == halfcards2.size() - 1) { //an oi kartes tou 2 teleiwsan, tou 1 oxi
		sleep(2000);
		usedcards.push_back(halfcards1.at(l5));
		l5 = previous_changeL + 1;
		previous_changeL++;
	}
	//AN MONO O 2 EXEI ENAPOMEINANTA FYLLA, ANANEWNEI MONO AYTOS TO KENTRIKO FYLLO ARISTERA
	else if (previous_changeR < halfcards2.size() - 1 && previous_changeL == halfcards1.size() - 1) {  //an oi kartes tou 1 teleiwsan tou 2 oxi
		sleep(2000);
		usedcards.push_back(halfcards2.at(r5));
		r5 = previous_changeR + 1;
		previous_changeR++;
	}
	//AN OI PAIKTES EXOYN MEINEI ME TA FYLLA POY EMFANIZONTAI STON KANVA KAI DEN YPARXOUN PITHANES ALLAGES, TOTE ISOPALIA
	else if (previous_changeR == halfcards2.size() - 1 && previous_changeL == halfcards1.size() - 1) {
		sleep(2000);
		winner = 0;
		m_state = STATE_OVER;

	}
}


void Game::init()
{

		leftcards.push_back(cardL1);
		leftcards.push_back(cardL2);
		leftcards.push_back(cardL3);
		leftcards.push_back(cardL4);
		rightcards.push_back(cardR1);
		rightcards.push_back(cardR2);
		rightcards.push_back(cardR3);
		rightcards.push_back(cardR4);
		usedL.push_back(true);
		usedL.push_back(true);
		usedL.push_back(true);
		usedL.push_back(true);
		usedR.push_back(true);
		usedR.push_back(true);
		usedR.push_back(true);
		usedR.push_back(true);

		//DHMIOYRGEITAI PINAKAS
		kkk.push_back(new Cards("2_of_clubs.png", 2));
		kkk.push_back(new Cards("2_of_hearts.png", 2));
		kkk.push_back(new Cards("2_of_spades.png", 2));
		kkk.push_back(new Cards("2_of_diamonds.png", 2));
		kkk.push_back(new Cards("3_of_clubs.png", 3));
		kkk.push_back(new Cards("3_of_hearts.png", 3));
		kkk.push_back(new Cards("3_of_spades.png", 3));
		kkk.push_back(new Cards("3_of_diamonds.png", 3));
		kkk.push_back(new Cards("4_of_clubs.png", 4));
		kkk.push_back(new Cards("4_of_hearts.png", 4));
		kkk.push_back(new Cards("4_of_spades.png", 4));
		kkk.push_back(new Cards("4_of_diamonds.png", 4));
		kkk.push_back(new Cards("5_of_clubs.png", 5));
		kkk.push_back(new Cards("5_of_hearts.png", 5));
		kkk.push_back(new Cards("5_of_spades.png", 5));
		kkk.push_back(new Cards("5_of_diamonds.png", 5));
		kkk.push_back(new Cards("6_of_clubs.png", 6));
		kkk.push_back(new Cards("6_of_hearts.png", 6));
		kkk.push_back(new Cards("6_of_spades.png", 6));
		kkk.push_back(new Cards("6_of_diamonds.png", 6));
		kkk.push_back(new Cards("7_of_clubs.png", 7));
		kkk.push_back(new Cards("7_of_hearts.png", 7));
		kkk.push_back(new Cards("7_of_spades.png", 7));
		kkk.push_back(new Cards("7_of_diamonds.png", 7));
		kkk.push_back(new Cards("8_of_clubs.png", 8));
		kkk.push_back(new Cards("8_of_hearts.png", 8));
		kkk.push_back(new Cards("8_of_spades.png", 8));
		kkk.push_back(new Cards("8_of_diamonds.png", 8));
		kkk.push_back(new Cards("9_of_clubs.png", 9));
		kkk.push_back(new Cards("9_of_hearts.png", 9));
		kkk.push_back(new Cards("9_of_spades.png", 9));
		kkk.push_back(new Cards("9_of_diamonds.png", 9));
		kkk.push_back(new Cards("10_of_clubs.png", 10));
		kkk.push_back(new Cards("10_of_hearts.png", 10));
		kkk.push_back(new Cards("10_of_spades.png", 10));
		kkk.push_back(new Cards("10_of_diamonds.png", 10));
		kkk.push_back(new Cards("jack_of_clubs.png", 11));
		kkk.push_back(new Cards("jack_of_hearts.png", 11));
		kkk.push_back(new Cards("jack_of_spades.png", 11));
		kkk.push_back(new Cards("jack_of_diamonds.png", 11));
		kkk.push_back(new Cards("queen_of_clubs.png", 12));
		kkk.push_back(new Cards("queen_of_hearts.png", 12));
		kkk.push_back(new Cards("queen_of_spades.png", 12));
		kkk.push_back(new Cards("queen_of_diamonds.png", 12));
		kkk.push_back(new Cards("king_of_clubs.png", 13));
		kkk.push_back(new Cards("king_of_hearts.png", 13));
		kkk.push_back(new Cards("king_of_spades.png", 13));
		kkk.push_back(new Cards("king_of_diamonds.png", 13));
		kkk.push_back(new Cards("ace_of_clubs.png", 1));
		kkk.push_back(new Cards("ace_of_hearts.png", 1));
		kkk.push_back(new Cards("ace_of_spades.png", 1));
		kkk.push_back(new Cards("ace_of_diamonds.png", 1));

		//TYXAIO ANAKATEMA THS TRAPOULAS //SRAND ETSI WSTE NA EINAI DIAFORETIKO SE KATHE NEO PAIXNIDI
		srand(time(0));
		for (int i = 0; i < 52; i++) {
			int d = rand() % 52;
			temp = kkk[i];
			kkk[i] = kkk[d];
			kkk[d] = temp;
		}


		for (int i = 0; i < 26; i++) {
			halfcards1.push_back(kkk[i]);
		}
		for (int i = 26; i < 52; i++) {
			halfcards2.push_back(kkk[i]);
		}

		cardL1->setPosX(CANVAS_WIDTH * 1 / 10.0f);
		cardL1->setPosY(CANVAS_HEIGHT * (4 - 0.5f) / 4.0f);

		cardL2->setPosX(CANVAS_WIDTH * 2 / 10.0f);
		cardL2->setPosY(CANVAS_HEIGHT * (4 - 0.5f) / 4.0f);

		cardL3->setPosX(CANVAS_WIDTH * 3 / 10.0f);
		cardL3->setPosY(CANVAS_HEIGHT * (4 - 0.5f) / 4.0f);

		cardL4->setPosX(CANVAS_WIDTH * 4 / 10.0f);
		cardL4->setPosY(CANVAS_HEIGHT * (4 - 0.5f) / 4.0f);

		cardR1->setPosX(CANVAS_WIDTH * 6 / 10.0f);
		cardR1->setPosY(CANVAS_HEIGHT * (4 - 0.5f) / 4.0f);

		cardR2->setPosX(CANVAS_WIDTH * 7 / 10.0f);
		cardR2->setPosY(CANVAS_HEIGHT * (4 - 0.5f) / 4.0f);

		cardR3->setPosX(CANVAS_WIDTH * 8 / 10.0f);
		cardR3->setPosY(CANVAS_HEIGHT * (4 - 0.5f) / 4.0f);

		cardR4->setPosX(CANVAS_WIDTH * 9 / 10.0f);
		cardR4->setPosY(CANVAS_HEIGHT * (4 - 0.5f) / 4.0f);

		c_card1->setPosX(CANVAS_WIDTH * (4 + 0.5f) / 10.0f);
		c_card1->setPosY(CANVAS_HEIGHT * 2 / 4.0f);

		c_card2->setPosX(CANVAS_WIDTH * (5 + 0.5f) / 10.0f);
		c_card2->setPosY(CANVAS_HEIGHT * 2 / 4.0f);
	
}


bool Game::notpossiblechanges()
{
	//if(sygkrinw 1h karta kai 1h kai 2h kentrikh)...kai to idio gia tis ypoloipes 
	return (!usedL.at(0) || (!(cardL1->getvalue(halfcards1, l1) == c_card1->getvalue(halfcards1, l5) + 1 || cardL1->getvalue(halfcards1, l1) == c_card1->getvalue(halfcards1, l5) - 1)
		&& !(cardL1->getvalue(halfcards1, l1) == c_card2->getvalue(halfcards2, r5) + 1 || cardL1->getvalue(halfcards1, l1) == c_card1->getvalue(halfcards2, r5) - 1)
		&& !(cardL1->getvalue(halfcards1, l1) == 13 && c_card1->getvalue(halfcards1, l5) == 1 || cardL1->getvalue(halfcards1, l1) == 1 && c_card1->getvalue(halfcards1, l5) == 13)
		&& !(cardL1->getvalue(halfcards1, l1) == 13 && c_card2->getvalue(halfcards1, r5) == 1 || cardL1->getvalue(halfcards1, l1) == 1 && c_card2->getvalue(halfcards2, r5) == 13)))

		&& (!usedL.at(1) || (!(cardL2->getvalue(halfcards1, l2) == c_card1->getvalue(halfcards1, l5) + 1 || cardL2->getvalue(halfcards1, l2) == c_card1->getvalue(halfcards1, l5) - 1)
		&& !(cardL2->getvalue(halfcards1, l2) == c_card2->getvalue(halfcards2, r5) + 1 || cardL2->getvalue(halfcards1, l2) == c_card1->getvalue(halfcards2, r5) - 1)
		&& !(cardL2->getvalue(halfcards1, l2) == 13 && c_card1->getvalue(halfcards1, l5) == 1 || cardL2->getvalue(halfcards1, l2) == 1 && c_card1->getvalue(halfcards1, l5) == 13)
		&& !(cardL2->getvalue(halfcards1, l2) == 13 && c_card2->getvalue(halfcards2, r5) == 1 || cardL2->getvalue(halfcards1, l2) == 1 && c_card2->getvalue(halfcards2, r5) == 13)))

		&& (!usedL.at(2) || (!(cardL3->getvalue(halfcards1, l3) == c_card1->getvalue(halfcards1, l5) + 1 || cardL3->getvalue(halfcards1, l3) == c_card1->getvalue(halfcards1, l5) - 1)
		&& !(cardL3->getvalue(halfcards1, l3) == c_card2->getvalue(halfcards2, r5) + 1 || cardL3->getvalue(halfcards1, l3) == c_card1->getvalue(halfcards2, r5) - 1)
		&& !(cardL3->getvalue(halfcards1, l3) == 13 && c_card1->getvalue(halfcards1, l5) == 1 || cardL3->getvalue(halfcards1, l3) == 1 && c_card1->getvalue(halfcards1, l5) == 13)
		&& !(cardL3->getvalue(halfcards1, l3) == 13 && c_card2->getvalue(halfcards2, r5) == 1 || cardL3->getvalue(halfcards1, l3) == 1 && c_card2->getvalue(halfcards2, r5) == 13)))

		&& (!usedL.at(3) || (!(cardL4->getvalue(halfcards1, l4) == c_card1->getvalue(halfcards1, l5) + 1 || cardL4->getvalue(halfcards1, l4) == c_card1->getvalue(halfcards1, l5) - 1)
		&& !(cardL4->getvalue(halfcards1, l4) == c_card2->getvalue(halfcards2, r5) + 1 || cardL4->getvalue(halfcards1, l4) == c_card1->getvalue(halfcards2, r5) - 1)
		&& !(cardL4->getvalue(halfcards1, l4) == 13 && c_card1->getvalue(halfcards1, l5) == 1 || cardL4->getvalue(halfcards1, l4) == 1 && c_card1->getvalue(halfcards1, l5) == 13)
		&& !(cardL4->getvalue(halfcards1, l4) == 13 && c_card2->getvalue(halfcards2, r5) == 1 || cardL4->getvalue(halfcards1, l4) == 1 && c_card2->getvalue(halfcards2, r5) == 13)))

		&& (!usedR.at(0) || (!(cardR1->getvalue(halfcards2, r1) == c_card1->getvalue(halfcards1, l5) + 1 || cardR1->getvalue(halfcards2, r1) == c_card1->getvalue(halfcards1, l5) - 1)
		&& !(cardR1->getvalue(halfcards2, r1) == c_card2->getvalue(halfcards2, r5) + 1 || cardR1->getvalue(halfcards2, r1) == c_card1->getvalue(halfcards2, r5) - 1)
		&& !(cardR1->getvalue(halfcards2, r1) == 13 && c_card1->getvalue(halfcards1, l5) == 1 || cardR1->getvalue(halfcards2, r1) == 1 && c_card1->getvalue(halfcards1, l5) == 13)
		&& !(cardR1->getvalue(halfcards2, r1) == 13 && c_card2->getvalue(halfcards2, r5) == 1 || cardR1->getvalue(halfcards2, r1) == 1 && c_card2->getvalue(halfcards2, r5) == 13)))

		&& (!usedR.at(1) || (!(cardR2->getvalue(halfcards2, r2) == c_card1->getvalue(halfcards1, l5) + 1 || cardR2->getvalue(halfcards2, r2) == c_card1->getvalue(halfcards1, l5) - 1)
		&& !(cardR2->getvalue(halfcards2, r2) == c_card2->getvalue(halfcards2, r5) + 1 || cardR2->getvalue(halfcards2, r2) == c_card1->getvalue(halfcards2, r5) - 1)
		&& !(cardR2->getvalue(halfcards2, r2) == 13 && c_card1->getvalue(halfcards1, l5) == 1 || cardR2->getvalue(halfcards2, r2) == 1 && c_card1->getvalue(halfcards1, l5) == 13)
		&& !(cardR2->getvalue(halfcards2, r2) == 13 && c_card2->getvalue(halfcards2, r5) == 1 || cardR2->getvalue(halfcards2, r2) == 1 && c_card2->getvalue(halfcards2, r5) == 13)))

		&& (!usedR.at(2) || (!(cardR3->getvalue(halfcards2, r3) == c_card1->getvalue(halfcards1, l5) + 1 || cardR3->getvalue(halfcards2, r3) == c_card1->getvalue(halfcards1, l5) - 1)
		&& !(cardR3->getvalue(halfcards2, r3) == c_card2->getvalue(halfcards2, r5) + 1 || cardR3->getvalue(halfcards2, r3) == c_card1->getvalue(halfcards2, r5) - 1)
		&& !(cardR3->getvalue(halfcards2, r3) == 13 && c_card1->getvalue(halfcards1, l5) == 1 || cardR3->getvalue(halfcards2, r3) == 1 && c_card1->getvalue(halfcards1, l5) == 13)
		&& !(cardR3->getvalue(halfcards2, r3) == 13 && c_card2->getvalue(halfcards2, r5) == 1 || cardR3->getvalue(halfcards2, r3) == 1 && c_card2->getvalue(halfcards2, r5) == 13)))

		&& (!usedR.at(3) || (!(cardR4->getvalue(halfcards2, r4) == c_card1->getvalue(halfcards1, l5) + 1 || cardR4->getvalue(halfcards2, r4) == c_card1->getvalue(halfcards1, l5) - 1)
		&& !(cardR4->getvalue(halfcards2, r4) == c_card2->getvalue(halfcards2, r5) + 1 || cardR4->getvalue(halfcards2, r4) == c_card1->getvalue(halfcards2, r5) - 1)
		&& !(cardR4->getvalue(halfcards2, r4) == 13 && c_card1->getvalue(halfcards1, l5) == 1 || cardR4->getvalue(halfcards2, r4) == 1 && c_card1->getvalue(halfcards1, l5) == 13)
		&& !(cardR4->getvalue(halfcards2, r4) == 13 && c_card2->getvalue(halfcards2, r5) == 1 || cardR4->getvalue(halfcards2, r4) == 1 && c_card2->getvalue(halfcards2, r5) == 13)));

}

Game::~Game()
{

	delete cardL1;
	delete cardL2;
	delete cardL3;
	delete cardL4;

	delete cardR1;
	delete cardR2;	
	delete cardR3;
	delete cardR4;

	delete c_card1; 
	delete c_card2;
}

Game* Game::getInstance()
{
	if (!m_instance)
		m_instance = new Game();
	return m_instance;
}


Game* Game::m_instance = nullptr;