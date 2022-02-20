#include "Skyrmion/InputHandler.hpp"
#include "Skyrmion/TileMap.hpp"

sf::Keyboard::Key controlLayouts[3][4] = {
	{sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D},
	{sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right},
	{sf::Keyboard::W, sf::Keyboard::R, sf::Keyboard::A, sf::Keyboard::S}
};

class Player : public Node {
	bool upper;
	InputHandler input;
	Indexer collisionMap;

	//Dynamic Lighting
	LightMap *lightMap = NULL;
	LightMapCollection *lightCollection = NULL;
	

public:
	Player(bool _upper, Indexer _collisionMap) : 
		Node(_upper ? UPPER : LOWER), input(controlLayouts[_upper ? 1 : 2], INPUT, this), collisionMap(_collisionMap) {

		upper = _upper;
	}

	void setupLighting(LightMap *_lightMap, LightMapCollection *_lightCollection) {
		lightMap = _lightMap;
		lightCollection = _lightCollection;
		lightMap->addSource(scalePosition(getGPosition()), 1);
		lightMap->reload();
	}

	void update(double time) {
		sf::Vector2f target = input.getMovement(this, time * 32);
		int targetType = collisionMap.getTile(target);

		//Move player
		if(targetType == AIR) {
			sf::Vector2f light = scalePosition(target);
			if(lightMap != NULL && light != scalePosition(getGPosition())) {
				lightMap->moveSource(0, light);
				lightMap->reload();
			}

			setPosition(target);
		}
	}

	sf::Vector2f scalePosition(sf::Vector2f pos) {
		return sf::Vector2f((int)(pos.x / 8) + 1, (int)(pos.y / 8) + 1);
	}
};