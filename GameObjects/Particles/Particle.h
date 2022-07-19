#include "../GameObject.h"
#include "../Drawable.h"

namespace Valzuroid {
	using namespace Pinball;
	namespace Pinball {
		namespace GameObjects {
			namespace Particles {
				class ParticleEffect;

				class Particle: public GameObject, public Drawn
				{
				private:
					sf::Shape* particleShape;
					double angle = 0;
					double duration = 0;
					double rotationSpeed = 0; //Positive for clockwise
					Vector2D velocity = Vector2D::zero;
					bool _isActive = true;
					bool isAffectedByGravity = true;

					Vector2D position;
					friend class ParticleEffect;
				public:
					Vector2D relativePosition = Vector2D::zero;

					Particle(sf::Shape* particleShape);
					bool isActive() { return _isActive; }
					void start() override;
					void updateTick(double frameTime) override;
					void draw(Interface& interface) override;

					//setters
					void setDuration(double duration);
					void setRotationSpeed(double speed);
					void setVelocity(Vector2D velocity);
					void setAngle(double angle);
					void setGravityEffect(bool isAffected);
				};
			}
		}
	}
}