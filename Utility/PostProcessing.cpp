#include "PostProcessing.h"

using namespace Valzuroid::Pinball::Utility;

void PostProcessing::SetPreTexture(sf::Texture *preTexture) {
    PreTexture=preTexture;
}

sf::Texture *PostProcessing::GetPostTexture() {
    return &PostTexture;
}
