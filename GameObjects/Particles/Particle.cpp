#include "Particle.h"
using namespace Valzuroid::Pinball::GameObjects::Particles;

Particle::Particle(sf::Shape* particleShape)
{
	this->particleShape = particleShape;
}

void Particle::start()
{
	
}

void Particle::updateTick(double frameTime)
{
	if (!_isActive) return;
	position += velocity * frameTime;
	particleShape->rotate(rotationSpeed * frameTime);
	if (isAffectedByGravity) velocity += Vector2D{0, -400} * frameTime;
	duration -= frameTime;
	if (duration <= 0) _isActive = false;
}

void Particle::draw(Interface& interface)
{
	if (particleShape) interface.GetWindow().draw(*particleShape);
}

void Particle::setDuration(double duration) { this->duration = duration; }
void Particle::setRotationSpeed(double speed) { this->rotationSpeed = speed; }
void Particle::setVelocity(Vector2D velocity) { this->velocity = velocity; }
void Particle::setAngle(double angle) { this->angle = angle; }
void Particle::setGravityEffect(bool isAffected) { this->isAffectedByGravity = isAffected; }