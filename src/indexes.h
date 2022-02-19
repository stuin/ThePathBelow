#pragma once

#include "Skyrmion/GridMaker.h"

enum TileType {
	WALL,
	SLOPE,
	AIR,
	WATER
};

enum CollisionLayer {
	MAP,
	LOWER,
	BRIDGE,
	UPPER,
	INPUT,
	TREE
};

static const std::map<char, int> displayIndex = {
	{'#', 0},
	{' ', -1},
	{'t', 6},
	{'>', 5},
	{'<', 5},
	{'\\', 1},
	{'/', 2},
	{'.', 4},
	{',', 5},
	{'@', 3},
	{'~', -1}
};

static const std::map<char, int> collisionIndex = {
	{'#', WALL},
	{' ', WALL},
	{'t', WALL},
	{'>', WALL},
	{'<', WALL},
	{'\\', SLOPE},
	{'/', SLOPE},
	{'.', AIR},
	{',', AIR},
	{'@', AIR},
	{'~', WATER}
};