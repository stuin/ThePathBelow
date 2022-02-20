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
	Player *otherPlayer;

	//End screen stuff
	sf::Texture endTexture;
	Node endNode;

	//Dynamic Lighting
	LightMap *lightMap = NULL;
	LightMapCollection *lightCollection = NULL;
	

public:
	int treasure = 0;
	bool endShown = false;

	Player(bool _upper, Indexer _collisionMap, Player *_otherPlayer=NULL) : 
		Node(_upper ? UPPERPLAYER : LOWERPLAYER), input(controlLayouts[_upper ? 1 : 2], INPUT, this), 
		collisionMap(_collisionMap), endNode(TITLE, sf::Vector2i(64, 32), false, this) {

		upper = _upper;
		otherPlayer = _otherPlayer;
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
		if(!endShown) {
			if(targetType == (upper ? UPPERAIR : LOWERAIR) || targetType == BRIDGEAIR) {
				sf::Vector2f light = scalePosition(target);
				if(lightMap != NULL && light != scalePosition(getGPosition())) {
					lightMap->moveSource(0, light);
					lightMap->reload();
				}

				setPosition(target);
			}

			//Check for win condition
			if(getPosition().y < 30 && otherPlayer != NULL && otherPlayer->getPosition().y < 30) {
				//Load the end texture
				std::string endFile = "res/endscreen.png";
				if(!endTexture.loadFromFile(endFile))
					throw std::invalid_argument("Player texture " + endFile + " not found");
				endNode.setTexture(endTexture);
				endNode.setPosition(0, -48);
				UpdateList::addNode(&endNode);

				std::cout << "YOU WIN!!\n";
				//std::cout << treasure + otherPlayer->treasure << " Treasure chests collected!\n";
				
				endShown = true;
				otherPlayer->endShown = true;
			}
		}
	}

	sf::Vector2f scalePosition(sf::Vector2f pos) {
		return sf::Vector2f((int)(pos.x / 8) + 1, (int)(pos.y / 8) + 1);
	}
};