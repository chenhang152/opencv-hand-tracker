/*
 * particle.h
 *
 *  Created on: Oct 1, 2012
 *      Author: malcom
 */
#include <stdio.h>

#ifndef PARTICLE_H_
#define PARTICLE_H_

#define partDIM	 2



class particle {
public:
	particle();
	virtual ~particle();

	float posa[6];
	float posaBest[6];
	float vposa[6];

	float errore_posa;
	float errore_posaBest;
};

#endif /* PARTICLE_H_ */
