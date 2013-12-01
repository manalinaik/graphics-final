#include "FlockSystem.h"
#include <iostream>

#define PI 3.14159265

FlockSystem::FlockSystem(int numParticles):ParticleSystem(numParticles)
{
	maxSep = 2.5;
	maxSpeed = .5;
	maxForce = .03;
	eatDist = .1;
	waterColor = Vector3f(0.0f, 0.4f, 0.6f);
	for (int i=0; i < numParticles; i++) {
		// Random location
		float x = 0.01 * (rand() % 400) - 2;
		float y = 0.01 * (rand() % 400) - 2;
		float z = -0.01 * (rand() % 60) - 0.2;
		Vector3f pos = Vector3f(x, y, z);

		// Random velocity
		int xSign = (rand() % 2) * 2 - 1;
		x = xSign * 0.01 * (rand() % 50) + 0.1;
		int ySign = (rand() % 2) * 2 - 1;
		y = ySign * 0.01 * (rand() % 50) + 0.1;
		int zSign = (rand() % 2) * 2 - 1;
		z = zSign * 0.01 * (rand() % 25);
		Vector3f vel = Vector3f(x, y, z);

		Foid foid = Foid(0.1, pos, vel);
		float r = 0.01 * (rand() % 20) + 0.6;
		float g = 0.01 * (rand() % 20) + 0.3;
		float b = 0.01 * (rand() % 20);
		foid.color = Vector3f(r, g, b);
		flock.push_back(foid);

		// Add to state
		m_vVecState.push_back(pos);
		m_vVecState.push_back(vel);
	}
}

int FlockSystem::getParticlePosIndex(int particleIndex)
{
	return 2*particleIndex;
}

Vector3f FlockSystem::getParticlePos(int particleIndex)
{
	return m_vVecState[getParticlePosIndex(particleIndex)];
}

int FlockSystem::getParticleVelIndex(int particleIndex)
{
	return 2*particleIndex + 1;
}

Vector3f FlockSystem::getParticleVel(int particleIndex)
{
	return m_vVecState[getParticleVelIndex(particleIndex)];
}

// for a given state, evaluate f(X,t)
vector<Vector3f> FlockSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	// push velocities (and intermediate values of a) onto f
	// calculate acceleration caused by gravity and drag forces
	for ( int i = 0; i < m_numParticles; i++ )
	{
	    Vector3f pos = state[getParticlePosIndex(i)];
	    Vector3f vel = state[getParticleVelIndex(i)];
	    
	    Vector3f a;
	    a += separation(i, state) * 1.5;
	    a += center(pos, vel);
	    a += alignment(i, state);
	    a += cohesion(i, state);
	    if (food.size() > 0)
	        a += hunger(pos, vel) * 1.5;
	    limitZ(pos, vel, a);
	    f.push_back(vel);
	    f.push_back(a / flock[i].getMass());
	}

	return f;
}

void FlockSystem::limitZ(Vector3f pos, Vector3f& vel, Vector3f& a)
{
    if (pos[2] > 0) {
	vel[2] /= 2;
	a[2] = -0.05;
    }
    if (pos[2] < -0.8) {
	vel[2] /= 2;
	a[2] = 0.05;
    }
    if (vel[2] > 0.25)
	vel[2] = 0.25;
    if (vel[2] < -0.25)
	vel[2] = -0.25;
}

Vector3f FlockSystem::separation(int particleIndex, vector<Vector3f> state)
{
    int count = 0;
    Vector3f sep;
    Vector3f pos = state[getParticlePosIndex(particleIndex)];
    Vector3f vel = state[getParticleVelIndex(particleIndex)];
    for (int j = 0; j < m_numParticles; j++) {
	if (particleIndex == j) 
	    continue;
	Vector3f dist = pos - state[getParticlePosIndex(j)];
	if (dist.abs() > 0 && dist.abs() < maxSep) {
	    dist.normalize();
	    sep += (dist / dist.abs());
	    count++;
	    if (abs(dist[2]) < 0.1) {
		int sign = (rand() % 2) * 2 - 1;
		float z = sign * 0.01 * (rand() % 5);
		sep += Vector3f(0, 0, z);
	    }
	}
    }
    if (count > 0)
	sep = sep / count;
    limit(sep, vel);
    return sep;
}

Vector3f FlockSystem::alignment(int particleIndex, vector<Vector3f> state)
{
    int count = 0;
    Vector3f align;
    Vector3f pos = state[getParticlePosIndex(particleIndex)];
    Vector3f vel = state[getParticleVelIndex(particleIndex)];
    for (int j = 0; j < m_numParticles; j++) {
	if (particleIndex == j) 
	    continue;
	Vector3f dist = pos - state[getParticlePosIndex(j)];
	if (dist.abs() > 0 && dist.abs() < 2*maxSep) {
	    align += state[getParticleVelIndex(j)];
	    count++;
	}
    }
    if (count > 0)
	align = align / count;
    limit(align, vel);
    return align;
}

Vector3f FlockSystem::cohesion(int particleIndex, vector<Vector3f> state)
{
    int count = 0;
    Vector3f cohesion;
    Vector3f pos = state[getParticlePosIndex(particleIndex)];
    Vector3f vel = state[getParticleVelIndex(particleIndex)];
    for (int j = 0; j < m_numParticles; j++) {
	if (particleIndex == j) 
	    continue;
	Vector3f dist = pos - state[getParticlePosIndex(j)];
	if (dist.abs() > 0 && dist.abs() < 2*maxSep) {
	    cohesion += state[getParticlePosIndex(j)];
	    count++;
	}
    }
    if (count > 0) {
	cohesion = cohesion / count;
	cohesion -= pos;
    }
    limit(cohesion, vel);
    return cohesion;
}

Vector3f FlockSystem::center(Vector3f pos, Vector3f vel)
{
    Vector3f center;
    if (pos.abs() > 4)
	center = -pos * pos.abs() * 0.01;
    limit(center, vel);
    return center;
}

Vector3f FlockSystem::hunger(Vector3f pos, Vector3f vel)
{
    float minDist = FLT_MAX;
    int targetIndex; 
    for (int i=0; i < food.size(); i++) {
	float dist = (pos - food[i]).abs();
	if (dist < minDist) {
	    targetIndex = i;
	    minDist = dist;
	}
    }
    if (minDist < eatDist)
	food.erase(food.begin() + targetIndex);
    Vector3f hunger = vel - (pos - food[targetIndex]);
    limit(hunger, vel);
    return hunger;
}

void FlockSystem::limit(Vector3f& desired, Vector3f vel)
{
    if (desired.abs() > 0) {
        desired.normalize();
	desired = desired * maxSpeed - vel;
	if (desired.abs() > maxForce)
	    desired *= (maxForce / desired.abs());
    }
}

// render the system (ie draw the particles)
void FlockSystem::draw()
{
	for (int i = 0; i < m_numParticles; i++) {
		Vector3f pos = getParticlePos(i);
		Vector3f vel = getParticleVel(i);
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		glDisable(GL_LIGHTING);
		float xyAngle = atan2(vel[1], vel[0]) * 180 / PI;
		glRotatef(xyAngle, 0, 0, 1);
		glScaled(0.2f,0.075f,0.075f);
		Vector3f color = depthColor(pos[2], flock[i].color);
		glColor3f(color[0], color[1], color[2]);
	        glutSolidSphere(1.0f,10.0f,10.0f);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
	for (Vector3f f : food) {
	    glDisable(GL_LIGHTING);
	    glPushMatrix();
	    glTranslatef(f[0], f[1], f[2] );
	    glColor3f(0.8f, 0.8f, 0.6f);
	    glutSolidSphere(0.075f,10.0f,10.0f);
	    glPopMatrix();
	    glEnable(GL_LIGHTING);
	}
}

Vector3f FlockSystem::depthColor(float z, Vector3f color)
{
    Vector3f diff = color - waterColor;
    diff = diff * z;
    return color + diff;
}

void FlockSystem::addFood(Vector3f loc)
{
    food.push_back(loc);
}
