#ifndef FOOD_H
#define FOOD_H

#include "extra.h"
#include <vector>

using namespace std;

class Food
{
public:
	Food(Vector3f pos);
	
	Vector3f getPos();

	Vector3f color;

	void draw();

protected:
	Vector3f m_pos;

	Vector3f rippleColor;

	Vector3f waterColor;

	int remainingRipples;

	void drawRipples();

	float spawningR;

	float maxR;

	float initR;

	vector<float> ripples;

	void drawCircle(float r, int numSegments);

	Vector3f radiusColor(float r);
	
};

#endif
