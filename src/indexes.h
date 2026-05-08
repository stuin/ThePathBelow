#pragma once

#include "Skyrmion/tiling/GridMaker.h"
#include "Skyrmion/input/MovementEnums.h"

#define LAYER_FOREACH(E) \
    E(MAP) \
    E(TREASURE) \
    E(LOWERPLAYER) \
    E(BRIDGELAYER) \
    E(UPPERPLAYER) \
	E(TREES) \
	E(INPUT) \
	E(GRIDEDITOR) \
	E(LIGHTBUFFERS) \
	E(LIGHT) \
	E(TITLE) \

NAMED_ENUM(LAYER)

enum TEXTURES {
	TEXTURE_INVALID,
	TEXTURE_FOREST,
	TEXTURE_BRIDGE,
	TEXTURE_TREE_MID,
	TEXTURE_TREE_TOP,
	TEXTURE_TREASURE,
	TEXTURE_PLAYER_UPPER,
	TEXTURE_PLAYER_LOWER,
	TEXTURE_LIGHT,
	TEXTURE_END,
	TEXTURE_FONT
};
static std::vector<std::string> TEXTURE_FILES = {
	"#INVALID",
	"res/foresttiles.png",
	"res/bridge.png",
	"res/treemid.png",
	"res/treetop.png",
	"res/treasure.png",
	"res/upperplayer.png",
	"res/lowerplayer.png",
	"res/debug/heatmapG.png",
	"res/endscreen.png",
	"res/small_pixel.ttf"
};

static const std::map<int, int> displayIndex = {
	{' ', -1},
	{'\\',0},
	{'_', 1},
	{'-', 1},
	{'+', 2},
	{'#', 3},
	{',', 4},
	{'H', 4},
	{'.', 5},
	{'h', 5},
	{'=', 5},
	{'[', 5},
	{'|', 6},
	{']', 6},
	{'@', 7},
	{'!', 8},
	{'T', 9},
	{'t', 10}
};

static const std::map<int, int> upperCollisionIndex = {
	{'#', FULL},
	{' ', FULL},
	{'t', FULL},
	{'T', FULL},
	{'_', FULL},
	{'\\',FULL},
	{'+', FULL},
	{'|', FULL},
	{',', EMPTY},
	{'H', EMPTY},
	{'!', EMPTY},
	{']', EMPTY},
	{'-', EMPTY},
	{'.', FULL},
	{'h', FULL},
	{'=', EMPTY},
	{'[', EMPTY},
	{'@', EMPTY}
};

static const std::map<int, int> lowerCollisionIndex = {
	{'#', FULL},
	{' ', FULL},
	{'t', FULL},
	{'T', FULL},
	{'_', FULL},
	{'\\',FULL},
	{'+', FULL},
	{'|', FULL},
	{',', FULL},
	{'H', FULL},
	{'!', FULL},
	{']', FULL},
	{'-', FULL},
	{'.', EMPTY},
	{'h', EMPTY},
	{'=', EMPTY},
	{'[', EMPTY},
	{'@', EMPTY}
};

static const std::map<int, int> lightIndex = {
	{'#', -100},
	{' ', -100},
	{'@', -100},
	{'T', -50},
	{'t', 0},
	{'H', 0},
	{'h', 0},
	{',', 0},
	{'.', 0},
	{']', 0},
	{'[', 0},
	{'=', 0},
	{'_', 0},
	{'-', 0},
	{'\\',0},
	{'+', 0},
	{'|', 0},
	{'!', 100}
};

static const std::map<int, int> treetopIndex = {
	{' ', -1},
	{'#', -1},
	{'T', 0},
	{'t', 0}
};

static const std::map<int, int> bridgeIndex = {
	{' ', -1},
	{'#', -1},
	{'[', 0},
	{']', 1},
	{'=', 2},
	{'-', 3}
};