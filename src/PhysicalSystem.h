#ifndef PHYSICALSYSTEM_H
#define PHYSICALSYSTEM_H

#include "extra.h"
#include <vector>

#include "particleSystem.h"

class PhysicalSystem: public ParticleSystem
{

public:
	PhysicalSystem(int numParticles=0);

	int getParticlePosIndex(int particleIndex);

	Vector3f getParticlePos(int particleIndex);

	int getParticleVelIndex(int particleIndex);

	Vector3f getParticleVel(int particleIndex);
	
	virtual vector<Vector3f> evalF(vector<Vector3f> state) = 0;
	
	virtual void draw() = 0;

protected:

	float m; // const mass for all particles

	float dragConst;

	Vector3f g;
	
};

#endif
