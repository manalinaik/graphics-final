#include "TimeStepper.h"

//Explicit Euler time integrator
void ForwardEuler::takeStep(ParticleSystem* particleSystem, float stepSize)
{
	vector<Vector3f> newState;
	vector<Vector3f> currState = particleSystem->getState();
	vector<Vector3f> vels = particleSystem->evalF(currState);
	for( int i = 0; i < currState.size(); i++ )
	{
		//currState[i].print();
		//vels[i].print();
		Vector3f offset = stepSize * vels[i];
		newState.push_back(currState[i] + offset);
	}
	particleSystem->setState(newState);
}

//Trapzoidal rule
void Trapzoidal::takeStep(ParticleSystem* particleSystem, float stepSize)
{
	vector<Vector3f> newState;
	vector<Vector3f> currState = particleSystem->getState();
	vector<Vector3f> f0 = particleSystem->evalF(currState);

	vector<Vector3f> approxState;
	for( int i = 0; i < currState.size(); i++ )
	{
		approxState.push_back(currState[i] + stepSize * f0[i]);
	}
	vector<Vector3f> f1 = particleSystem->evalF(approxState);

	for( int i = 0; i < currState.size(); i++ )
	{
		Vector3f offset = (stepSize / 2) * (f0[i] + f1[i]);
		newState.push_back(currState[i] + offset);
	}
	particleSystem->setState(newState);
}
