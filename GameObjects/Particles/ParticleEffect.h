#include "../GameObject.h"
#include "../Drawable.h"
#include "Particle.h"
#include "../../Utility/Factory.h"

namespace Valzuroid {
	namespace Pinball {
		using namespace Utility;
		namespace GameObjects {
			namespace Particles {
				class ParticleEffect: public GameObject, public Drawn, public Factory<Particle>
				{
				public:
					bool isActive = true;
					Vector2D position = Vector2D::zero;

					void start() final;
					void updateTick(double frameTime) final;
					void draw(Interface& interface) final;
				};
			}
		}
	}
}