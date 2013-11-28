#ifndef FLOCKSYSTEM_H
#define FLOCKSYSTEM_H

#include "extra.h"
#include <vector>
#include <cstdlib>

#include "particleSystem.h"
#include "Foid.h"

class FlockSystem: public ParticleSystem
{
public:
	FlockSystem(int numParticles=0);

	int getParticlePosIndex(int particleIndex);

	Vector3f getParticlePos(int particleIndex);

	int getParticleVelIndex(int particleIndex);

	Vector3f getParticleVel(int particleIndex);
	
	vector<Vector3f> evalF(vector<Vector3f> state);

	Vector3f separation(int particleIndex, vector<Vector3f> state);

	Vector3f align(int particleIndex, vector<Vector3f> state);

	Vector3f center(Vector3f pos, Vector3f vel);

	void limit(Vector3f desired, Vector3f vel);
	
	void draw();

protected:
	vector<Foid> flock;
	float maxSep;
	float maxSpeed;
	float maxForce;
	
};

#endif
