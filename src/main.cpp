//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Skyrmion/LightMap.h"
#include "indexes.h"
#include "Player.hpp"

int main() {
	//Load base tile maps
	GridMaker grid("res/full_map.txt", 21, 11);
	TileMap forest("res/foresttiles.png", 16, 16, Indexer(&grid, displayIndex, 0), MAP);
	Indexer collisionMap(&grid, collisionIndex, WALL, 16, 16);
	Indexer treetopMap(&grid, treetopIndex, -1);
	UpdateList::addNode(&forest);

	//Add overlapping tree middles
	TileMap treemid("res/treemid.png", 16, 16, treetopMap, TREES);
	treemid.setPosition(0, -6);
	UpdateList::addNode(&treemid);

	//Add overlapping tree tops
	TileMap treetop("res/treetop.png", 16, 16, treetopMap, TREES);
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

	//Load the player textures
	std::string upperFile = "res/upperplayer.png";
	std::string lowerFile = "res/lowerplayer.png";
	sf::Texture upperTexture;
	sf::Texture lowerTexture;
	if(!upperTexture.loadFromFile(upperFile))
		throw std::invalid_argument("Player texture " + upperFile + " not found");
	if(!lowerTexture.loadFromFile(lowerFile))
		throw std::invalid_argument("Player texture " + lowerFile + " not found");

	//Upper area player
	Player upperPlayer(true, collisionMap);
	upperPlayer.setPosition(sf::Vector2f(200, 56));
	upperPlayer.setTexture(upperTexture);
	upperPlayer.setupLighting(&movingLights, &lighting);
	UpdateList::addNode(&upperPlayer);

	//Lower area player
	Player lowerPlayer(false, collisionMap);
	lowerPlayer.setPosition(sf::Vector2f(120, 56));
	lowerPlayer.setTexture(lowerTexture);
	UpdateList::addNode(&lowerPlayer);

	//Finish engine setup
	UpdateList::alwaysLoadLayer(MAP);
	UpdateList::alwaysLoadLayer(TREES);
	UpdateList::alwaysLoadLayer(INPUT);
	UpdateList::alwaysLoadLayer(LIGHT);
	UpdateList::setCamera(&lowerPlayer, sf::Vector2f(300, 200));

	UpdateList::startEngine("The Path Below", LIGHT);
	return 0;
}