#ifndef FLOCKSYSTEM_H
#define FLOCKSYSTEM_H

#include "extra.h"
#include <vector>
#include <cstdlib>
#include <cfloat>

#include "particleSystem.h"
#include "Foid.h"
#include "Food.h"

class FlockSystem: public ParticleSystem
{
public:
	FlockSystem(int numParticles=0);

	int getParticlePosIndex(int particleIndex);

	Vector3f getParticlePos(int particleIndex);

	int getParticleVelIndex(int particleIndex);

	Vector3f getParticleVel(int particleIndex);
	
	vector<Vector3f> evalF(vector<Vector3f> state);

	void limitZ(Vector3f pos, Vector3f& vel, Vector3f& a);

	Vector3f separation(int particleIndex, vector<Vector3f> state);

	Vector3f alignment(int particleIndex, vector<Vector3f> state);

	Vector3f cohesion(int particleIndex, vector<Vector3f> state);

	Vector3f center(Vector3f pos, Vector3f vel);

	Vector3f hunger(Vector3f pos, Vector3f vel);

	void limit(Vector3f& desired, Vector3f vel);
	
	void draw();

	Vector3f depthColor(float z, Vector3f color);

	void addFood(Vector3f loc);

protected:
	vector<Foid> flock;
	vector<Food*> food;
	float maxSep;
	float maxSpeed;
	float maxForce;
	float eatDist;
	Vector3f waterColor;
	
};

#endif
