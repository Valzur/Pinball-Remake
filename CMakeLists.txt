cmake_minimum_required(VERSION 3.15)
project(Pinball)

set(CMAKE_CXX_STANDARD 14)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "Libs/SFML-2.5.1/lib/cmake/SFML")
set(FREETYPE_DIR "Libs/freetype-2.12.1/include")
set(Ogg_DIR "Libs/libogg-1.3.5/cmake")

find_package(SFML 2.5.1 REQUIRED COMPONENTS audio graphics window system)
find_package(FreeType 2.12.1 )
find_package(Ogg 1.3.5)

include_directories(Libs/libogg-1.3.5/include libs/libogg-1.3.4/)
include_directories(Libs/flac-1.3.4/include)
include_directories(Libs/liboggz-1.1.1/include)
include_directories(Libs/freetype-2.12.1/include)
include_directories(Libs/SFML-2.5.1/include libs/SFML-2.5.1/lib libs/SFML-2.5.1/bin)

add_executable(Pinball main.cpp  GameObjects/GameObject.h Game.cpp Game.h Interface.cpp Interface.h
        GameObjects/Drawable.h GameObjects/Ball.cpp GameObjects/Ball.h GameObjects/Collidable.h
        Defs.h GameObjects/Obstacles/Obstacle.h
        GameObjects/Flipper.cpp GameObjects/Flipper.h GameObjects/Obstacles/SpriteWalls.cpp
        GameObjects/Obstacles/SpriteWalls.h GameObjects/Obstacles/Bumper.cpp GameObjects/Obstacles/Bumper.h
        Utility/PixelPerfectCollision.cpp Utility/PixelPerfectCollision.h GameObjects/GameManager.cpp
        GameObjects/GameManager.h Utility/AudioManager.cpp Utility/AudioManager.h Defs.cpp Utility/PreGame.cpp
        Utility/PreGame.h Utility/Configurable.cpp Utility/Configurable.h GameObjects/Obstacles/PopBumper.cpp
        GameObjects/Obstacles/PopBumper.h Utility/PostProcessing.cpp Utility/PostProcessing.h GameObjects/Obstacles/Portal.cpp
        GameObjects/Obstacles/Portal.h Utility/CollisionDetection.cpp Utility/CollisionDetection.h GameObjects/Obstacles/Magnet.cpp
        GameObjects/Obstacles/Magnet.h GameObjects/Obstacles/Gate.cpp GameObjects/Obstacles/Wall.cpp
        GameObjects/Obstacles/Ramp.cpp GameObjects/Obstacles/Kicker.cpp
        GameObjects/Obstacles/Collectable.cpp GameObjects/Obstacles/Collectable.h GameObjects/Obstacles/SpeedBooster.cpp
        GameObjects/Obstacles/SpeedBooster.h GameObjects/Obstacles/ThrustBumper.cpp GameObjects/Obstacles/ThrustBumper.h
        GameObjects/Obstacles/VibraniumBumper.cpp GameObjects/Obstacles/VibraniumBumper.h GameObjects/Obstacles/ScoreMultiplier.cpp
        GameObjects/Obstacles/ScoreMultiplier.h GameObjects/Obstacles/Switch.cpp GameObjects/Obstacles/Switch.h GameObjects/Obstacles/Lane.cpp 
        GameObjects/Obstacles/Lane.h GameObjects/Obstacles/Bullseye.cpp GameObjects/Obstacles/Bullseye.h UI/Button.h UI/Button.cpp 
        "UI/UIElement.h"  UI/UIManager.h UI/UIManager.cpp   "Utility/Factory.h" "UI/MainMenuUI.h" "UI/MainMenuUI.cpp" "UI/Text.h" "UI/Text.cpp" "UI/AllUIIncludes.h" "UI/EventReceiver.h" "UI/EventSource.h" "GameObjects/Particles/ParticleEffectsManager.h" "GameObjects/Particles/ParticleEffect.cpp" "GameObjects/Particles/Particle.h" "GameObjects/Particles/Particle.cpp" "GameObjects/Particles/HitFX.h")

target_link_libraries(Pinball OpenAL Vorbis)

target_link_libraries(Pinball sfml-audio sfml-graphics sfml-window sfml-system)