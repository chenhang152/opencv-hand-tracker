/*
 * particle.h
 *
 *  Created on: Oct 1, 2012
 *      Author: malcom
 */
#include <stdio.h>

#ifndef PARTICLE_H_
#define PARTICLE_H_

#define partDIM	 15



class particle {
public:
	particle();
	virtual ~particle();

	float posa[partDIM];
	float posaBest[partDIM];
	float vposa[partDIM];

	float errore_posa;
	float errore_posaBest;
};

#endif /* PARTICLE_H_ */
