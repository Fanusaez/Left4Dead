#ifndef __WORM_H__
#define __WORM_H__

#include <SDL2pp/SDL2pp.hh>
#include "Animation.h"
#include <utility>

class Player {
	Animation an;
	bool facingLeft;
	std::pair<int, int> position;
	std::pair<int, int> speed;

public:
    Player(SDL2pp::Texture &texture);
    ~Player();
    void update(float dt);
    void render(SDL2pp::Renderer &renderer);
    void moveRigth();
    void moveLeft();
    void moveUp();
    void moveDown();
    void stopMoving();

private:
	bool isMoving() const;
};

#endif // __WORM_H__