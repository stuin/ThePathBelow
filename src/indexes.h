#pragma once

#include "Skyrmion/GridMaker.h"

enum CollisionType {
	WALL,
	SLOPE,
	AIR
};

enum CollisionLayer {
	MAP,
	LOWER,
	BRIDGE,
	UPPER,
	INPUT,
	TREES,
	LIGHT
};

static const std::map<char, int> displayIndex = {
	{'~', -1},
	{' ', -1},
	{'#', 0},
	{'\\', 1},
	{'/', 2},
	{'@', 3},
	{'.', 4},
	{'>', 5},
	{'<', 5},
	{',', 5},
	{'t', 6},
	{'T', 6},
	{'!', 7}
};

static const std::map<char, int> collisionIndex = {
	{'#', WALL},
	{' ', WALL},
	{'t', WALL},
	{'T', WALL},
	{'.', AIR},
	{',', AIR},
	{'@', AIR},
	{'!', AIR}
};

static const std::map<char, int> lightIndex = {
	{'#', -100},
	{' ', -100},
	{'@', -100},
	{'T', -80},
	{'t', 0},
	{'\\', 0},
	{'/', 0},
	{'.', 0},
	{',', 0},
	{'!', 100}
};

static const std::map<char, int> treetopIndex = {
	{' ', -1},
	{'#', -1},
	{'T', 0},
	{'t', 0}
};