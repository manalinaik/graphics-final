#include "FlockSystem.h"

FlockSystem::FlockSystem(int numParticles):ParticleSystem(numParticles)
{
	maxSep = 0.2;
	for (int i=0; i < numParticles; i++) {
		// Random location
		float x = 0.01 * (rand() % 400) - 2;
		float y = 0.01 * (rand() % 400) - 2;
		Vector3f pos = Vector3f(x, y, 0);

		// Random velocity
		int xSign = (rand() % 2) * 2 - 1;
		x = xSign * 0.01 * (rand() % 100) + 0.1;
		int ySign = (rand() % 2) * 2 - 1;
		y = ySign * 0.01 * (rand() % 100) + 0.1;
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
	    int count = 0;
	    Vector3f sep;
	    Vector3f center;
	    Vector3f a;
	    for (int j=0; j < m_numParticles; j++) {
		if (i == j) 
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
	    if (sep.abs() > 0)
	        sep -= vel;
	    a += sep;
	    center = -pos * pos.absSquared() * 0.5;
	    a += center;
	    f.push_back(a / flock[i].getMass());
	}

	return f;
}

// render the system (ie draw the particles)
void FlockSystem::draw()
{
	for (int i = 0; i < m_numParticles; i++) {
		Vector3f pos = getParticlePos(i);//  position of particle i
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}
}
