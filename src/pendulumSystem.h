#ifndef PENDULUMSYSTEM_H
#define PENDULUMSYSTEM_H

#include "extra.h"
#include <vector>

#include "SpringSystem.h"

class PendulumSystem: public SpringSystem
{
public:
	PendulumSystem(int numParticles, int showSpringParticle);
	
	vector<Vector3f> evalF(vector<Vector3f> state);
	
	void draw();

	void drawSprings();

protected:

	int highlightParticle;
	
};

#endif
