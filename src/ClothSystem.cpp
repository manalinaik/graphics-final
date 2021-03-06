#include "ClothSystem.h"

ClothSystem::ClothSystem(int dimension)
{
	g = Vector3f(0, -2, 0);
	drawAllSprings = true;
	m_dimension = dimension; // number of particles per row or col
	m_numParticles = pow(m_dimension, 2);
	particleDist = 0.4; //distance between vertical/horizontal neighbors
	m = 0.5;
	dragConst = 0.5;
	
	// fill in code for initializing the state based on the number of particles
	for (int i = 0; i < m_dimension; i++) {
		for ( int j = 0; j < m_dimension; j++ ){
			// create particles across then down
			m_vVecState.push_back(Vector3f(j * particleDist, 0, i * particleDist));
			m_vVecState.push_back(Vector3f());
		}
	}
	setStructuralSprings();
	setShearSprings();
	setFlexSprings();
}

int ClothSystem::getIndex(int i, int j)
{
	return m_dimension * i + j;
}

int ClothSystem::getHorNeighborIndex(int i)
{
	return i + 1;
}

int ClothSystem::getVerNeighborIndex(int i)
{
	return i + m_dimension;
}

void ClothSystem::setStructuralSprings()
{
	for (int i = 0; i < m_dimension; i++) {
		for ( int j = 0; j < m_dimension; j++ ){
			if (j < m_dimension - 1) {
				// horizontal spring
				Spring hSpring;
				hSpring.p1 = getIndex(i, j);
				hSpring.p2 = getIndex(i, j) + 1;
				hSpring.k = 20;
				hSpring.restLength = particleDist;
				// prevent cloth from sinking down too far
				if (i == 0)
					hSpring.restLength = particleDist * 0.1;
				springs.push_back(hSpring);
			}
			if (i < m_dimension - 1) {
				// vertical spring
				Spring vSpring;
				vSpring.p1 = getIndex(i, j);
				vSpring.p2 = getIndex(i, j) + m_dimension;
				vSpring.k = 20;
				vSpring.restLength = particleDist;
				// prevent cloth from sinking down too far
				if (i == 0)
					vSpring.restLength = particleDist * 0.5;
				springs.push_back(vSpring);
			}
		}
	}
}

void ClothSystem::setShearSprings()
{
	for (int i = 0; i < m_dimension; i++) {
		for ( int j = 0; j < m_dimension; j++ ){
			if (j < m_dimension - 1 && i < m_dimension - 1) {
				// right-up diagonal spring
				Spring uSpring;
				uSpring.p1 = getIndex(i, j);
				uSpring.p2 = getIndex(i, j) + m_dimension + 1;
				uSpring.k = 1;
				uSpring.restLength = 2 * pow(particleDist, 2);
				springs.push_back(uSpring);
			}
			if (i < m_dimension - 1 && j > 0) {
				// right-down diagonal spring
				Spring dSpring;
				dSpring.p1 = getIndex(i, j);
				dSpring.p2 = getIndex(i, j) + m_dimension - 1;
				dSpring.k = 1;
				dSpring.restLength = 2 * pow(particleDist, 2);
				springs.push_back(dSpring);
			}
		}
	}
}

void ClothSystem::setFlexSprings()
{
	for (int i = 0; i < m_dimension; i++) {
		for ( int j = 0; j < m_dimension; j++ ){
			if (j < m_dimension - 2) {
				// horizontal flex spring
				Spring uSpring;
				uSpring.p1 = getIndex(i, j);
				uSpring.p2 = getIndex(i, j) + 2;
				uSpring.k = 5;
				uSpring.restLength = 2 * particleDist;
				springs.push_back(uSpring);
			}
			if (i < m_dimension - 2) {
				// vertical flex spring
				Spring dSpring;
				dSpring.p1 = getIndex(i, j);
				dSpring.p2 = getIndex(i, j) + 2*m_dimension;
				dSpring.k = 5;
				dSpring.restLength = 2 * particleDist;
				springs.push_back(dSpring);
			}
		}
	}
}


// for a given state, evaluate f(X,t)
vector<Vector3f> ClothSystem::evalF(vector<Vector3f> state)
{
	vector<Vector3f> f;

	// push velocities (and intermediate values of a) onto f
	// calculate acceleration caused by gravity and drag forces
	for ( int i = 0; i < m_numParticles; i++ )
	{
		f.push_back(state[getParticleVelIndex(i)]);
		Vector3f a = g;
		Vector3f drag = state[getParticleVelIndex(i)];
		drag = (-1 * dragConst) * drag;
		drag = drag / m;
		a += drag;
		f.push_back(a);
	}

	// calculate acceleration caused by spring forces
	
	for( Spring s : springs )
	{
		Vector3f d = state[getParticlePosIndex(s.p1)] - 
			     state[getParticlePosIndex(s.p2)];
		Vector3f F = (d / d.abs());
		F *= (-s.k * (d.abs() - s.restLength));
		Vector3f a = F / m;
		f[getParticleVelIndex(s.p1)] += a;
		f[getParticleVelIndex(s.p2)] += (-1 * a);
	}

	// make endpoints of first row of particles fixed
	f[0] = Vector3f();
	f[1] = Vector3f();
	int index = 2 * (m_dimension - 1);
	f[index] = Vector3f();
	f[index + 1] = Vector3f();

	return f;	
}

void ClothSystem::foward()
{
	// move top corners forward
	m_vVecState[0] += Vector3f(0, 0, 0.05);
	int index = 2 * (m_dimension - 1);
	m_vVecState[index] += Vector3f(0, 0, 0.05);
}

void ClothSystem::backward()
{
	// move top corners backward
	m_vVecState[0] -= Vector3f(0, 0, 0.05);
	int index = 2 * (m_dimension - 1);
	m_vVecState[index] -= Vector3f(0, 0, 0.05);
}

void ClothSystem::draw()
{
	for (int i = 0; i < m_numParticles; i++) {
		Vector3f pos = getParticlePos(i);//  position of particle i
		glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2] );
		glutSolidSphere(0.075f,10.0f,10.0f);
		glPopMatrix();
	}
	if (drawAllSprings)
		drawSprings();
}

void ClothSystem::drawSprings()
{
    glDisable(GL_LIGHTING);
    for( Spring s : springs) {
	    glLineWidth(3);
	    glColor3f(0.0, 0.7, 0.0);
	    glBegin(GL_LINES);
	    Vector3f v1 = getParticlePos(s.p1);
	    Vector3f v2 = getParticlePos(s.p2);
	    glVertex3f(v1[0], v1[1], v1[2]);
	    glVertex3f(v2[0], v2[1], v2[2]);
	    glEnd();
    }
    glEnable(GL_LIGHTING);
}

