#include "ParticleEffect.h"

namespace Valzuroid {
	namespace Pinball {
		namespace GameObjects {
			namespace Particles {
				class HitFX: public ParticleEffect
				{
					public:
						HitFX(Vector2D position)
						{
							this->position = position;

							//1st Particle
							sf::CircleShape* shape1 = new sf::CircleShape(20);
							shape1->setFillColor(sf::Color::Green);
							shape1->setOrigin({ 10, 10 });
							Particle* particle1 = new Particle(shape1);
							particle1->setVelocity({1, 1}); // Right up
							particle1->setDuration(0.5);
							particle1->setRotationSpeed(1);
							AddObject(particle1);

							//2nd Particle
							sf::CircleShape* shape2 = new sf::CircleShape(20);
							shape2->setFillColor(sf::Color::Green);
							shape2->setOrigin({ 10, 10 });
							Particle* particle2 = new Particle(shape2);
							particle2->setVelocity({ 1, -1 }); // Right down
							particle2->setDuration(0.5);
							particle2->setRotationSpeed(1);
							AddObject(particle2);

							//3rd Particle
							sf::CircleShape* shape3 = new sf::CircleShape(20);
							shape3->setFillColor(sf::Color::Green);
							shape3->setOrigin({ 10, 10 });
							Particle* particle3 = new Particle(shape3);
							particle3->setVelocity({ -1, 1 }); // Left up
							particle3->setDuration(0.5);
							particle3->setRotationSpeed(1);
							AddObject(particle3);

							//4th Particle
							sf::CircleShape* shape4 = new sf::CircleShape(20);
							shape4->setFillColor(sf::Color::Green);
							shape4->setOrigin({ 10, 10 });
							Particle* particle4 = new Particle(shape4);
							particle4->setVelocity({ -1, -1 }); // Left down
							particle4->setDuration(0.5);
							particle4->setRotationSpeed(1);
							AddObject(particle4);
						}
				};
			}
		}
	}
}