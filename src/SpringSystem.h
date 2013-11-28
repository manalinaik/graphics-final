#ifndef SPRINGSYSTEM_H
#define SPRINGSYSTEM_H

#include "extra.h"
#include <vector>

#include "PhysicalSystem.h"

class SpringSystem: public PhysicalSystem
{

public:
	SpringSystem(int numParticles=0);

	//int getParticlePosIndex(int particleIndex);

	//Vector3f getParticlePos(int particleIndex);

	//int getParticleVelIndex(int particleIndex);

	//Vector3f getParticleVel(int particleIndex);
	
	virtual vector<Vector3f> evalF(vector<Vector3f> state) = 0;
	
	virtual void draw() = 0;

	virtual void drawSprings() = 0;

	bool drawAllSprings;

protected:

	//float m; // const mass for all particles

	//float dragConst;

	//Vector3f g;

	struct Spring
	{
	    int p1;
	    int p2;
	    float k;
	    float restLength;
	};

	vector<Spring> springs;
	
};

#endif
