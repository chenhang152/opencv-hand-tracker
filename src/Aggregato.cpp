/*
 * Aggregato.cpp
 *
 *  Created on: Nov 12, 2012
 *      Author: malcom
 */

#include "Aggregato.h"

Aggregato::Aggregato() {


	int offset=70;

	dita[0]= new KinematicChain(0,0,0);
	dita[1]= new KinematicChain(50,0,0);
	dita[2]= new KinematicChain(100,0,0);
	dita[3]= new KinematicChain(150,0,0);
	dita[4]= new KinematicChain(200,0,0);

	parametri[0]=&(dita[0]->parametri[0]);
	parametri[1]=&(dita[0]->parametri[1]);
	parametri[2]=&(dita[0]->parametri[2]);

	parametri[3]=&(dita[1]->parametri[0]);
	parametri[4]=&(dita[1]->parametri[1]);
	parametri[5]=&(dita[1]->parametri[2]);

	parametri[6]=&(dita[2]->parametri[0]);
	parametri[7]=&(dita[2]->parametri[1]);
	parametri[8]=&(dita[2]->parametri[2]);

	parametri[9]=&(dita[3]->parametri[0]);
	parametri[10]=&(dita[3]->parametri[1]);
	parametri[11]=&(dita[3]->parametri[2]);

	parametri[12]=&(dita[4]->parametri[0]);
	parametri[13]=&(dita[4]->parametri[1]);
	parametri[14]=&(dita[4]->parametri[2]);

}

Aggregato::~Aggregato() {

}


void Aggregato::Draw() {

	dita[0]->Draw();
	dita[1]->Draw();
	dita[2]->Draw();
	dita[3]->Draw();
	dita[4]->Draw();


}

void Aggregato::update() {

	dita[0]->update();
	dita[1]->update();
	dita[2]->update();
	dita[3]->update();
	dita[4]->update();

}
