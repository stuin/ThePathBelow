#include "Skyrmion/TileMap.hpp"

class Player : public Node {
	bool upper;
	DirectionHandler input;
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
		Node(_upper ? UPPERPLAYER : LOWERPLAYER), 
		input(_upper ? "/upper" : "/lower", INPUT, this), 
		collisionMap(_collisionMap), endNode(TITLE, sf::Vector2i(64, 32), false, this) {

		upper = _upper;
		otherPlayer = _otherPlayer;

		collideWith(TREASURE);
	}

	void setupLighting(LightMap *_lightMap, LightMapCollection *_lightCollection) {
		lightMap = _lightMap;
		lightCollection = _lightCollection;
		lightMap->addSource(getGPosition(), 1);
		lightMap->reload();
	}

	void update(double time) {
		sf::Vector2f prevPosition = getPosition();
		sf::Vector2f target = move(input.getDirection(), &collisionMap, time * 32);

		//Move player
		if(!endShown) {
			if(lightMap != NULL) {
				sf::Vector2f light = target;
				//lightMap->setPosition(remainderPosition(target));
				if(light != prevPosition) {
					lightMap->moveSource(0, light);
					lightMap->reload();
				}
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
				std::cout << treasure + otherPlayer->treasure << " Treasure chests collected!\n";
				
				endShown = true;
				otherPlayer->endShown = true;
			}
		}
	}

	void collide(Node *object) {
		treasure++;
		object->setDelete();
	}

	sf::Vector2f remainderPosition(sf::Vector2f pos) {
		return sf::Vector2f((int)(pos.x) % 8, (int)(pos.y) % 8);
	}
};