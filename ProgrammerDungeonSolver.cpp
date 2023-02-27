// ProgrammerDungeonSolver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include "PlaygroundBuilder.h"

int main()
{
	Playground playground = PlaygroundBuilder::getLvl20();

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	playground.analyze();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000. << "[s]" << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
}
