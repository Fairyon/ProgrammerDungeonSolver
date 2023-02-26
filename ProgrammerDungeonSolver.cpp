// ProgrammerDungeonSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "PlaygroundBuilder.h"

int main()
{
	Playground playground = PlaygroundBuilder::getLvl12();
	playground.analyze();
}
