#ifndef CLOTHSYSTEM_H
#define CLOTHSYSTEM_H

#include "extra.h"
#include <vector>

#include "SpringSystem.h"

class ClothSystem: public SpringSystem
{

public:
	ClothSystem(int dimension);

	vector<Vector3f> evalF(vector<Vector3f> state);

	int getIndex(int i, int j);
	
	int getHorNeighborIndex(int i);

	int getVerNeighborIndex(int i);

	void setStructuralSprings();

	void setShearSprings();

	void setFlexSprings();

	void foward();

	void backward();
	
	void draw();

	void drawSprings();

private:

	float particleDist;

	int m_dimension;

};


#endif
