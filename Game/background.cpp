#include "background.h"



void Background::Add(const std::filesystem::path& texture_path, double speed) {
	backgrounds.push_back(ParallaxLayer{ texture_path, speed });
}

void Background::Unload()
{
	backgrounds.clear(); //clear all elements withing vector
}

void Background::Draw(const CS230::Camera& camera) {

    for (auto& a : backgrounds) {
        Math::vec2 cposition = Math::vec2{ 0 - camera.GetPosition().x * a.speed, 0 - camera.GetPosition().y * a.speed };
        Math::TranslationMatrix matrix(cposition);
        a.texture.Draw(matrix);
    }

}

Math::ivec2 Background::GetSize() {
    return backgrounds[backgrounds.size() - 1].texture.GetSize();
}