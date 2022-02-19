#include "Skyrmion/InputHandler.hpp"
#include "Skyrmion/TileMap.hpp"

class Player : public Node {
	bool upper;
	InputHandler input;
	Indexer *collisionMap;

public:
	Player(bool _upper, Indexer *_collisionMap) : Node(_upper ? UPPER : LOWER), input(INPUT, 2, this), collisionMap(_collisionMap) {

	}

	void update(double time) {
		sf::Vector2f target = input.getMovement(this, time * 24);
		int targetType = collisionMap->getTile(target);

		if(targetType == AIR)
			setPosition(target);
	}
};