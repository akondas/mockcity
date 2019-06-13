#include <SFML/Graphics.hpp>
#include <vector>

#include "animation_handler.hpp"

void AnimationHandler::update(const float dt) {
    if (currentAnim >= this->animations.size() || currentAnim < 0) return;

    float duration = this->animations[currentAnim].duration;

    if (int((time + dt) / duration) > int(time / duration)) {
        int frame = int((time + dt) / duration);

        frame %= this->animations[currentAnim].getLength();

        sf::IntRect rect = this->frameSize;
        rect.left = rect.width * frame;
        rect.top = rect.height * this->currentAnim;
        this->bounds = rect;
    }

    this->time += dt;

    if (this->time > duration * this->animations[currentAnim].getLength()) {
        this->time = 0.0f;
    }

    return;
}

void AnimationHandler::addAnim(Animation &anim) {
    this->animations.push_back(anim);

    return;
}

void AnimationHandler::changeAnim(unsigned int animID) {
    if (this->currentAnim == animID || animID >= this->animations.size() ||
        animID < 0)
        return;

    this->currentAnim = animID;
    sf::IntRect rect = this->frameSize;
    rect.top = rect.height * animID;
    this->bounds = rect;
    this->time = 0.0;

    return;
}