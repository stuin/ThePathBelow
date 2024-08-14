#pragma once

#include "Skyrmion/GridMaker.h"

enum CollisionLayer {
	MAP,
	TREASURE,
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

static const std::map<char, int> upperCollisionIndex = {
	{'#', 0},
	{' ', 0},
	{'t', 0},
	{'T', 0},
	{'_', 0},
	{'\\',0},
	{'+', 0},
	{'|', 0},
	{',', 1},
	{'H', 1},
	{'!', 1},
	{']', 1},
	{'-', 1},
	{'.', 0},
	{'h', 0},
	{'=', 1},
	{'[', 1},
	{'@', 1}
};

static const std::map<char, int> lowerCollisionIndex = {
	{'#', 0},
	{' ', 0},
	{'t', 0},
	{'T', 0},
	{'_', 0},
	{'\\',0},
	{'+', 0},
	{'|', 0},
	{',', 0},
	{'H', 0},
	{'!', 0},
	{']', 0},
	{'-', 0},
	{'.', 1},
	{'h', 1},
	{'=', 1},
	{'[', 1},
	{'@', 1}
};

static const std::map<char, int> lightIndex = {
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