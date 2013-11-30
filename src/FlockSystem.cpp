#include "FlockSystem.h"
#include <iostream>

FlockSystem::FlockSystem(int numParticles):ParticleSystem(numParticles)
{
	maxSep = 3;
	maxSpeed = .5;
	maxForce = .03;
	for (int i=0; i < numParticles; i++) {
		// Random location
		float x = 0.01 * (rand() % 400) - 2;
		float y = 0.01 * (rand() % 400) - 2;
		Vector3f pos = Vector3f(x, y, 0);

		// Random velocity
		int xSign = (rand() % 2) * 2 - 1;
		x = xSign * 0.01 * (rand() % 50) + 0.1;
		int ySign = (rand() % 2) * 2 - 1;
		y = ySign * 0.01 * (rand() % 50) + 0.1;
		Vector3f vel = Vector3f(x, y, 0);

		Foid foid = Foid(0.1, pos, vel);
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
	    f.push_back(vel);
	    
	    Vector3f a;
	    a += separation(i, state) * 1.5;
	    a += center(pos, vel);
	    a += alignment(i, state);
	    a += cohesion(i, state);

	    f.push_back(a / flock[i].getMass());
	}

	return f;
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
    if (pos.abs() > 6)
	center = -pos * pos.abs() * 0.01;
    limit(center, vel);
    return center;
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
		Vector3f pos = getParticlePos(i);//  position of particle i
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		//glutSolidSphere(0.075f,10.0f,10.0f);
		glDisable(GL_LIGHTING);
		Vector3f normal = Vector3f(0, 0, 1);
		Vector3f vel = getParticleVel(i).normalized() * -0.3;
		Vector3f cross = Vector3f::cross(normal, vel).normalized() * 0.1;
		glBegin(GL_TRIANGLES);
		glColor3f(0.7f, 0.4f, 0.0f);
		glNormal(normal);
		glVertex(Vector3f());
		glNormal(normal);
		glVertex(vel - cross);
		glNormal(normal);
		glVertex(vel + cross);	    
		glEnd();
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
}
