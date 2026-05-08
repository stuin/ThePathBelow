#include "Skyrmion/tiling/LightMap.h"
#include "Skyrmion/tiling/RandomNoise.hpp"
#include "Skyrmion/input/InputHandler.h"
#include "Skyrmion/input/Settings.h"

#include "indexes.h"
#include "Player.hpp"

void initialize() {
	//Load settings file
	Settings::loadSettings("res/settings.json");
	//Load base tile maps
	GridMaker grid("res/full_map.txt");
	TileMap forest(TEXTURE_FOREST, 16, 16, new MapIndexer(&grid, displayIndex, 0), MAP);
	MapIndexer upperCollisionMap(&grid, upperCollisionIndex, 0, 16, 16);
	MapIndexer lowerCollisionMap(&grid, lowerCollisionIndex, 0, 16, 16);
	MapIndexer treetopMap(&grid, treetopIndex, -1);
	UpdateList::addNode(&forest);

	//Add overlapping bridges
	TileMap bridges(TEXTURE_BRIDGE, 16, 16, new MapIndexer(&grid, bridgeIndex, -1), BRIDGELAYER);
	UpdateList::addNode(&bridges);

	//Add overlapping tree middles
	TileMap treemid(TEXTURE_TREE_MID, 16, 16, &treetopMap, TREES);
	treemid.setPosition(0, -6);
	UpdateList::addNode(&treemid);

	//Add overlapping tree tops
	TileMap treetop(TEXTURE_TREE_TOP, 16, 16, &treetopMap, TREES);
	treetop.setPosition(0, -22);
	UpdateList::addNode(&treetop);

	//Setup Light maps
	int lightScale = Settings::getInt("/lighting_scale");
	MapIndexer lightMap(&grid, lightIndex, 0, lightScale, lightScale);
	LinearIndexer lightHalfMap(&lightMap, 0.4, 50, 0, 16, 16);
	LightMap staticLights(16, 16, 0.0f, 0.2f, &lightMap, LIGHTBUFFERS, true);
	LightMap movingLights(16, 16, 0, 0.2, &lightMap, LIGHTBUFFERS, false);
	UpdateList::addNode(&staticLights);
	UpdateList::addNode(&movingLights);

	//Light map combining
	LightMapCollection lighting(16, 16, &lightMap, LIGHT, LIGHTBUFFERS);
	lighting.addLightMap(&staticLights);
	lighting.addLightMap(&movingLights);
	UpdateList::addNode(&lighting);

	//Test tile display
	TileMap lightMapTexture(TEXTURE_LIGHT, 1, 1, &lightHalfMap, LIGHT);
	lightMapTexture.getRenderComponent(false)->setBlendMode(SK_BLEND_MULT);
	lightMapTexture.setHidden(true);
	UpdateList::addNode(&lightMapTexture);

	//Upper area player
	Player upperPlayer(true, upperCollisionMap);
	upperPlayer.setPosition(Vector2f(440, 312));
	upperPlayer.setTexture(TEXTURE_PLAYER_UPPER);
	upperPlayer.setupLighting(&movingLights, &lighting);
	UpdateList::addNode(&upperPlayer);

	//Lower area player
	Player lowerPlayer(false, lowerCollisionMap, &upperPlayer);
	lowerPlayer.setPosition(Vector2f(392, 312));
	lowerPlayer.setTexture(TEXTURE_PLAYER_LOWER);
	UpdateList::addNode(&lowerPlayer);

	//Place Treasure chests
	upperCollisionMap.mapGrid([](char c, Vector2f pos) {
		if(c == 'H' || c == 'h') {
			Node *t = new Node(TREASURE, RENDER_TEXTURE_SINGLE, Vector2i(10, 9));
			t->setTexture(TEXTURE_TREASURE);
			t->setPosition(pos + Vector2f(8, 8));
			UpdateList::addNode(t);
		}
	});

	//Finish engine setup
	UpdateList::globalLayer(MAP);
	UpdateList::globalLayer(TREES);
	UpdateList::globalLayer(INPUT);
	UpdateList::hideLayer(LIGHTBUFFERS);
	UpdateList::globalLayer(LIGHT);
	UpdateList::setCamera(&lowerPlayer, Vector2f(450, 250));

	UpdateList::startEngine();
}

std::string WINDOW_TITLE = "The Path Below";
std::string *windowTitle() {
	return &WINDOW_TITLE;
}

skColor backgroundColor() {
	return skColor(0,0,0);
}

std::vector<std::string> &textureFiles() {
	return TEXTURE_FILES;
}
std::vector<std::string> &layerNames() {
	return LAYER_NAMES;
}

void recieveNetworkString(std::string data, int code) {
	std::cout << "NETWORK: Received string " << data << "\n";
}