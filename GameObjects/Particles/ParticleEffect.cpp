#include "ParticleEffect.h"
using namespace Valzuroid::Pinball::GameObjects::Particles;

void ParticleEffect::start()
{
	Particle** particles = GetAllObjects();
	for (int i = 0; i < Count(); i++)
	{
		particles[i]->position = this->position + particles[i]->relativePosition;
		particles[i]->start();
	}
}

void ParticleEffect::updateTick(double frameTime)
{
	if (Count() == 0) isActive = false;
	Particle** particles = GetAllObjects();
	for (int i = 0; i < Count(); i++)
	{
		if (!particles[i]->isActive()) { RemoveObject(particles[i]); continue; }
		particles[i]->updateTick(frameTime);
	}
}

void ParticleEffect::draw(Interface& interface)
{
	Particle** particles = GetAllObjects();
	for (int i = 0; i < Count(); i++)
	{
		particles[i]->draw(interface);
	}
}
