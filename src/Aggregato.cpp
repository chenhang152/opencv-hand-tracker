/*
 * Aggregato.cpp
 *
 *  Created on: Nov 12, 2012
 *      Author: malcom
 */

#include "Aggregato.h"

Aggregato::Aggregato() {


	dita[0]= new KinematicChain(0,0,0);
	dita[1]= new KinematicChain(100,0,0);

	parametri[0]=&(dita[0]->parametri[0]);
	parametri[1]=&(dita[0]->parametri[1]);
	parametri[2]=&(dita[0]->parametri[2]);

	parametri[3]=&(dita[1]->parametri[0]);
	parametri[4]=&(dita[1]->parametri[1]);
	parametri[5]=&(dita[1]->parametri[2]);

}

Aggregato::~Aggregato() {

}


void Aggregato::Draw() {

	dita[0]->Draw();
	dita[1]->Draw();
}

void Aggregato::update() {
	dita[0]->update();
	dita[1]->update();

}
