/*
 * particle.h
 *
 *  Created on: Oct 1, 2012
 *      Author: malcom
 */
#include <stdio.h>

#ifndef PARTICLE_H_
#define PARTICLE_H_

#define angolo1 0
#define angolo2 1
#define angolo3 2
#define global1 3
#define global2 4
#define global3 5
#define partDIM	 6



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
