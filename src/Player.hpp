#include "Skyrmion/tiling/TileMap.hpp"
#include "Skyrmion/input/MovementSystems.h"

class Player : public Node {
	bool upper;
	DirectionHandler input;
	MapIndexer collisionMap;
	Player *otherPlayer;
	Node endNode;

	//Dynamic Lighting
	LightMap *lightMap = NULL;
	LightMapCollection *lightCollection = NULL;

public:
	int treasure = 0;
	bool endShown = false;

	Player(bool _upper, MapIndexer _collisionMap, Player *_otherPlayer=NULL) :
		Node(_upper ? UPPERPLAYER : LOWERPLAYER),
		input(_upper ? "/upper" : "/lower", INPUT),
		collisionMap(_collisionMap), endNode(TITLE, RENDER_TEXTURE_SINGLE, Vector2i(64, 32), this) {

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
		Vector2f prevPosition = getPosition();
		setPosition(topDownMovement(this, input.getDirection(), &collisionMap, time * 32));

		//Move player
		if(!endShown) {
			if(lightMap != NULL) {
				Vector2f light = getPosition();
				//lightMap->setPosition(remainderPosition(target));
				if(light != prevPosition) {
					lightMap->moveSource(0, light);
					lightMap->reload();
				}
			}

			//Check for win condition
			if(getPosition().y < 30 && otherPlayer != NULL && otherPlayer->getPosition().y < 30) {
				endNode.setTexture(TEXTURE_END);
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

	Vector2f remainderPosition(Vector2f pos) {
		return Vector2f((int)(pos.x) % 8, (int)(pos.y) % 8);
	}
};