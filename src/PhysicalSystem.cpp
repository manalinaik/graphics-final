#include "PhysicalSystem.h"

PhysicalSystem::PhysicalSystem(int numParticles):ParticleSystem(numParticles)
{
	g = Vector3f(0, -9.81, 0);
}

int PhysicalSystem::getParticlePosIndex(int particleIndex)
{
	return 2*particleIndex;
}

Vector3f PhysicalSystem::getParticlePos(int particleIndex)
{
	return m_vVecState[getParticlePosIndex(particleIndex)];
}

int PhysicalSystem::getParticleVelIndex(int particleIndex)
{
	return 2*particleIndex + 1;
}

Vector3f PhysicalSystem::getParticleVel(int particleIndex)
{
	return m_vVecState[getParticleVelIndex(particleIndex)];
}
