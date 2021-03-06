#include "Food.h"
#include <iostream>

#define DEG2RAD 3.14159/180;

Food::Food(Vector3f pos) 
{
    m_pos = pos + Vector3f(0, 0, 0.1);
    color = Vector3f(0.8f, 0.8f, 0.6f);
    rippleColor = Vector3f(0.5f, 0.7f, 0.9f);
    waterColor = Vector3f(0.0f, 0.4f, 0.6f);
    remainingRipples = 3;
    spawningR = 0.3;
    maxR = 1;
    initR = 0.01;
    ripples.push_back(initR);
}

Vector3f Food::getPos() 
{
    return m_pos;
}

void Food::draw() 
{
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(m_pos[0], m_pos[1], m_pos[2] );
    glColor3f(color[0], color[1], color[2]);
    glutSolidSphere(0.075f,10.0f,10.0f);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    if (ripples.size() > 0)
	drawRipples();
}

void Food::drawRipples() 
{
    if (ripples.front() > spawningR && remainingRipples > 0) {
	ripples.insert(ripples.begin(), initR);
	remainingRipples--;
    }
    glDisable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(3);
    for (int i=0; i < ripples.size(); i++) {
	float r = ripples[i];
        glPushMatrix();
        glTranslatef(m_pos[0], m_pos[1], m_pos[2] );
	Vector3f c = radiusColor(r);
        glColor3f(c[0], c[1], c[2]);
        drawCircle(r, 100);
        glPopMatrix();
	ripples[i] += .02 - r * (.01);
    }
    glEnable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (ripples.back() > maxR)
	ripples.pop_back();
}

void Food::drawCircle(float r, int num_segments) 
{ 
	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 

		glVertex2f(x, y);//output vertex 

	} 
	glEnd(); 
}

Vector3f Food::radiusColor(float r)
{
    Vector3f diff = waterColor - rippleColor;
    diff = diff * r;
    return rippleColor + diff;
}
