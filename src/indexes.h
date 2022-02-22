#pragma once

#include "Skyrmion/GridMaker.h"

enum CollisionType {
	WALL,
	SLOPE,
	LOWERAIR,
	BRIDGEAIR,
	UPPERAIR,
	TREASURE
};

enum CollisionLayer {
	MAP,
	LOWERPLAYER,
	BRIDGELAYER,
	UPPERPLAYER,
	INPUT,
	TREES,
	LIGHT,
	TITLE
};

static const std::map<char, int> displayIndex = {
	{' ', -1},
	{'\\',0},
	{'_', 1},
	{'-', 1},
	{'+', 2},
	{'#', 3},
	{',', 4},
	{'.', 5},
	{'=', 5},
	{'[', 5},
	{'|', 6},
	{']', 6},
	{'@', 7},
	{'H', 8},
	{'!', 9},
	{'T', 10},
	{'t', 11}
};

static const std::map<char, int> collisionIndex = {
	{'#', WALL},
	{' ', WALL},
	{'t', WALL},
	{'T', WALL},
	{',', UPPERAIR},
	{'!', UPPERAIR},
	{']', UPPERAIR},
	{'-', UPPERAIR},
	{'_', SLOPE},
	{'\\',SLOPE},
	{'+', SLOPE},
	{'|', SLOPE},
	{'.', LOWERAIR},
	{'=', BRIDGEAIR},
	{'[', BRIDGEAIR},
	{'@', BRIDGEAIR},
	{'H', TREASURE}
};

static const std::map<char, int> lightIndex = {
	{'#', -100},
	{' ', -100},
	{'@', -100},
	{'T', -80},
	{'t', 0},
	{'H', 0},
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

static const std::map<char, int> treetopIndex = {
	{' ', -1},
	{'#', -1},
	{'T', 0},
	{'t', 0}
};

static const std::map<char, int> bridgeIndex = {
	{' ', -1},
	{'#', -1},
	{'[', 0},
	{']', 1},
	{'=', 2},
	{'-', 3}
};