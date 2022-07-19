#include "../../Utility/Factory.h"
#include "HitFX.h"

namespace Valzuroid {
	namespace Pinball {
		namespace GameObjects {
			namespace Particles {
				class ParticleEffectsManager : Factory<ParticleEffect>, GameObject, Drawn
				{
				public:
					void AddHitVFX(Vector2D position){ AddObject(new HitFX(position)); }

					void start() override
					{
						ParticleEffect** vfx = GetAllObjects();
						for (int i = 0; i < Count(); i++)
						{
							vfx[i]->start();
						}
					}

					void updateTick(double frameTime)
					{
						ParticleEffect** vfx = GetAllObjects();
						for (int i = 0; i < Count(); i++)
						{
							if(!vfx[i]->isActive){ RemoveObject(vfx[i]); continue; }
							vfx[i]->updateTick(frameTime);
						}
					}

					void draw(Interface& interface)
					{
						ParticleEffect** vfx = GetAllObjects();
						for (int i = 0; i < Count(); i++)
						{
							vfx[i]->draw(interface);
						}
					}
				};
			}
		}
	}
}