#pragma once

#include "Playground.h"

class PlaygroundBuilder
{
public:
	static const vector<vector<CellType>> lvl2;
	static const vector<vector<CellType>> lvl8;
	static const vector<vector<CellType>> lvl12;
	static const vector<vector<CellType>> lvl20;

	static Playground getLvl2() {
		Playground result;
		result.setField(lvl2);
		result.daggers = 0;
		result.player = { 1, 1, Direction::right };
		result.maxPathSize = 4;
		return result;
	}

	static Playground getLvl8() {
		Playground result;
		result.setField(lvl8);
		result.daggers = 0;
		result.player = { 1, 1, Direction::right };
		result.maxPathSize = 4;
		return result;
	}

	static Playground getLvl12() {
		Playground result;
		result.setField(lvl12);
		result.daggers = 0;
		result.player = { 3, 3, Direction::right };
		result.maxPathSize = 8;
		return result;
	}

	static Playground getLvl20() {
		Playground result;
		result.setField(lvl20);
		result.daggers = 8;
		result.player = { 4, 1, Direction::right };
		result.maxPathSize = 11;
		return result;
	}
};
