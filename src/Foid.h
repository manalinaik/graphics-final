#ifndef FOID_H
#define FOID_H

#include "extra.h"
#include <vector>

using namespace std;

class Foid
{
public:
	Foid(float mass, Vector3f pos, Vector3f vel);
	
	Vector3f getPos();

	void setPos(Vector3f pos);

	Vector3f getVel();

	void setVel(Vector3f vel);

	float getMass();

	Vector3f color;
	
	float m_tail[3]; 
	
	int mult;
	
	float increment;

protected:
	Vector3f m_pos;

	Vector3f m_vel;

	float m_mass;
	
};

#endif
