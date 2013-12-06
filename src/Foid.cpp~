#include "Foid.h"

Foid::Foid(float mass, Vector3f pos, Vector3f vel) {
	m_mass = mass;
	m_pos = pos;
	m_vel = vel;
	mult = rand()%2*2 - 1;
	
	m_tail[0] = rand()%10 * 0.002;
	m_tail[1] = rand()%10 * 0.002;
	m_tail[2] = rand()%10 * 0.002;
}

Vector3f Foid::getPos() {
	return m_pos;
}

void Foid::setPos(Vector3f pos) {
	m_pos = pos;
}

Vector3f Foid::getVel() {
	return m_vel;
}

void Foid::setVel(Vector3f vel) {
	m_vel = vel;
}

float Foid::getMass() {
	return m_mass;
}
