#pragma once

#include "Playground.h"

class PlaygroundBuilder
{
public:
	static const vector<vector<CellType>> lvl2;
	static const vector<vector<CellType>> lvl8;
	static const vector<vector<CellType>> lvl12;
	static const vector<vector<CellType>> lvl15;
	static const vector<vector<CellType>> lvl17;
	static const vector<vector<CellType>> lvl20;
	static const vector<vector<CellType>> lvl36;

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

	static Playground getLvl15() {
		Playground result;
		result.setField(lvl15);
		result.daggers = 4;
		result.player = { 4, 4, Direction::right };
		result.maxPathSize = 11;
		return result;
	}

	static Playground getLvl17() {
		Playground result;
		result.setField(lvl17);
		result.daggers = 0;
		result.player = { 2, 2, Direction::right };
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

	static Playground getLvl36() {
		Playground result;
		result.setField(lvl36);
		result.daggers = 0;
		result.player = { 2, 1, Direction::right };
		result.maxPathSize = 11;
		return result;
	}
};
