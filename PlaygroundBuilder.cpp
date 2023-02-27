#include "PlaygroundBuilder.h"

const vector<vector<CellType>> PlaygroundBuilder::lvl2 = {
	{wall,wall,wall,wall,wall},
	{wall,clear,clear,clear,wall},
	{wall,wall,clear,monster,wall},
	{wall,wall,wall,wall,wall}
};

const vector<vector<CellType>> PlaygroundBuilder::lvl8 = {
	{wall,wall,wall,wall,wall},
	{wall,clear,clear,monster,wall},
	{wall,clear,clear,clear,wall},
	{wall,monster,clear,monster,wall},
	{wall,wall,wall,wall,wall}
};

const vector<vector<CellType>> PlaygroundBuilder::lvl12 = {
	{wall,wall,wall,wall,wall,wall,wall},
	{wall,monster,clear,monster,wall,wall,wall},
	{wall,clear,clear,monster,wall,wall,wall},
	{wall,monster,monster,clear,monster,monster,wall},
	{wall,wall,wall,monster,clear,clear,wall},
	{wall,wall,wall,monster,clear,monster,wall},
	{wall,wall,wall,wall,wall,wall,wall},
};

const vector<vector<CellType>> PlaygroundBuilder::lvl15 = {
	{wall,wall,wall,wall,wall,wall,wall,wall,wall},
	{wall,wall,monster,wall,wall,wall,wall,wall,wall},
	{wall,wall,block,monster,monster,monster,block,monster,wall},
	{wall,wall,monster,monster,monster,monster,monster,wall,wall},
	{wall,wall,monster,monster,clear,monster,monster,wall,wall},
	{wall,wall,monster,monster,monster,monster,monster,wall,wall},
	{wall,monster,death,monster,monster,monster,block,wall,wall},
	{wall,wall,wall,wall,wall,wall,monster,wall,wall},
	{wall,wall,wall,wall,wall,wall,wall,wall,wall}
};

const vector<vector<CellType>> PlaygroundBuilder::lvl17 = {
	{wall,wall,wall,wall,wall,wall,wall},
	{wall,clear,monster,clear,monster,clear,wall},
	{wall,monster,clear,monster2,clear,monster,wall},
	{wall,clear,monster,clear,monster,clear,wall},
	{wall,wall,wall,wall,wall,wall,wall},
};

const vector<vector<CellType>> PlaygroundBuilder::lvl20 = {
	{wall,wall,wall,wall,wall,wall,wall,wall,wall},
	{wall,clear,death,clear,clear,clear,clear,monster,wall},
	{wall,clear,monster2,monster2,clear,clear,monster,clear,wall},
	{wall,death,clear,clear,clear,death,clear,monster,wall},
	{wall,wall,monster2,clear,death,clear,clear,clear,wall},
	{wall,monster,clear,clear,clear,monster2,death,clear,wall},
	{wall,clear,clear,clear,wall,clear,monster,clear,wall},
	{wall,wall,wall,wall,wall,wall,wall,wall,wall}
};
