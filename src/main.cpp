//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Skyrmion/LightMap.h"
#include "Skyrmion/InputHandler.h"
#include "indexes.h"
#include "Player.hpp"

int main() {
	//Load settings file
	Settings::loadSettings("res/settings.json");

	//Load tilemap textures
	sf::Texture forestTexture;
	sf::Texture bridgeTexture;
	sf::Texture treemidTexture;
	sf::Texture treetopTexture;
	UpdateList::loadTexture(&forestTexture, "res/foresttiles.png");
	UpdateList::loadTexture(&bridgeTexture, "res/bridge.png");
	UpdateList::loadTexture(&treemidTexture, "res/treemid.png");
	UpdateList::loadTexture(&treetopTexture, "res/treetop.png");

	//Load base tile maps
	GridMaker grid("res/full_map.txt");
	TileMap forest(&forestTexture, 16, 16, new Indexer(&grid, displayIndex, 0), MAP);
	Indexer upperCollisionMap(&grid, upperCollisionIndex, 0, 16, 16);
	Indexer lowerCollisionMap(&grid, lowerCollisionIndex, 0, 16, 16);
	Indexer treetopMap(&grid, treetopIndex, -1);
	UpdateList::addNode(&forest);

	//Add overlapping bridges
	TileMap bridges(&bridgeTexture, 16, 16, new Indexer(&grid, bridgeIndex, -1), BRIDGELAYER);
	UpdateList::addNode(&bridges);

	//Add overlapping tree middles
	TileMap treemid(&treemidTexture, 16, 16, &treetopMap, TREES);
	treemid.setPosition(0, -6);
	UpdateList::addNode(&treemid);

	//Add overlapping tree tops
	TileMap treetop(&treetopTexture, 16, 16, &treetopMap, TREES);
	treetop.setPosition(0, -22);
	UpdateList::addNode(&treetop);

	//Setup Light maps
	Indexer lightMap(&grid, lightIndex, 0, 2, 2);
	LightMapCollection lighting(8, 8, lightMap, LIGHT);
	LightMap staticLights(8, 8, 0, 0.1, lightMap, LIGHT, true);
	LightMap movingLights(8, 8, 0, 0.1, lightMap, LIGHT, false);
	lighting.addLightMap(&staticLights);
	lighting.addLightMap(&movingLights);
	UpdateList::addNode(&lighting);

	//Load node textures
	sf::Texture upperTexture;
	sf::Texture lowerTexture;
	sf::Texture treasureTexture;
	UpdateList::loadTexture(&upperTexture, "res/upperplayer.png");
	UpdateList::loadTexture(&lowerTexture, "res/lowerplayer.png");
	UpdateList::loadTexture(&treasureTexture, "res/treasure.png");

	//Upper area player
	Player upperPlayer(true, upperCollisionMap);
	upperPlayer.setPosition(sf::Vector2f(440, 312));
	upperPlayer.setTexture(upperTexture);
	upperPlayer.setupLighting(&movingLights, &lighting);
	UpdateList::addNode(&upperPlayer);

	//Lower area player
	Player lowerPlayer(false, lowerCollisionMap, &upperPlayer);
	lowerPlayer.setPosition(sf::Vector2f(392, 312));
	lowerPlayer.setTexture(lowerTexture);
	UpdateList::addNode(&lowerPlayer);

	//Place Treasure chests
	upperCollisionMap.mapGrid([&treasureTexture](char c, sf::Vector2f pos) {
		if(c == 'H' || c == 'h') {
			Node *t = new Node(TREASURE, sf::Vector2i(10, 9));
			t->setTexture(treasureTexture);
			t->setPosition(pos + sf::Vector2f(8, 8));
			UpdateList::addNode(t);
		}
	});

	//Finish engine setup
	UpdateList::staticLayer(MAP);
	UpdateList::staticLayer(TREES);
	UpdateList::staticLayer(INPUT);
	UpdateList::staticLayer(LIGHT);
	UpdateList::setCamera(&lowerPlayer, sf::Vector2f(450, 250));

	UpdateList::startEngine("The Path Below");
	return 0;
}