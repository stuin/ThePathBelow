//SFML headers
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "indexes.h"
#include "Player.hpp"

int main() {
	//Load base tile maps
	GridMaker grid("res/rooms/spawn.txt", 11, 5);
	TileMap forest("res/forestmap.png", 16, 16, Indexer(&grid, displayIndex, 0), MAP);
	Indexer *collisionMap = new Indexer(&grid, collisionIndex, AIR, 16, 16);

	UpdateList::addNode(&forest);
	UpdateList::alwaysLoadLayer(MAP);
	UpdateList::alwaysLoadLayer(INPUT);

	//Load the upper player texture
	std::string file = "res/upperplayer.png";
	sf::Texture upperPlayerTexture;
	if(!upperPlayerTexture.loadFromFile(file))
		throw std::invalid_argument("Player texture " + file + " not found");

	//Upper area player
	Player upperPlayer(true, collisionMap);
	upperPlayer.setPosition(sf::Vector2f(120, 56));
	upperPlayer.setTexture(upperPlayerTexture);
	UpdateList::setCamera(&upperPlayer, sf::Vector2f(300, 200));
	UpdateList::addNode(&upperPlayer);

	UpdateList::startEngine("The Path Below", TREE);
	return 0;
}