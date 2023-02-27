#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <boost/algorithm/string/join.hpp>
#include <boost/preprocessor.hpp>

#define MOVE_ENUM_MACRO(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10)\
	enum Movement { v1, v2, v3, v4, v5, v6, v7, v8, v9, v10 };\
	static const char* MovementStrings[] = { #v1, #v2, #v3, #v4, #v5, #v6, #v7, #v8, #v9, #v10 }; \
	constexpr const char* MovementToString(Movement value) { return MovementStrings[static_cast<int>(value)]; } \
	static const vector<Movement> allMovements = { v1, v2, v3, v4, v5, v6, v7, v8, v9, v10 };

/*#define MOVE_ENUM_MACRO(...)\
	enum Movement { __VA_ARGS__ };\
	const char *MovementStrings[] = { BOOST_PP_SEQ_FOR_EACH_I(PROCESS_ONE_ELEMENT, %%, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) };\
	const char *MovementToString(int value) { return MovementStrings[value]; }\
	static const auto allMovements = { __VA_ARGS__ };*/


using namespace std;

enum CellType {
	clear, wall, death, monster, monster2
};

enum Direction {
	top, right, down, left
};

MOVE_ENUM_MACRO(
	loop_start, dagger, rotate_right, rotate_left, attack, attack2, loop_end2, loop_end3, loop_end4, loop_finish
)

Direction operator++(Direction& d, int);
Direction operator--(Direction& d, int);

struct Player
{
	int x, y;
	Direction direction;
	bool alive = true;

	void rotate(Direction dir) {
		switch (dir) {
			case Direction::left: direction--; break;
			case Direction::right: direction++; break;
		}
	}

	void move() {
		switch (direction) {
			case Direction::top: y--; break;
			case Direction::left: x--; break;
			case Direction::down: y++; break;
			case Direction::right: x++; break;
		}
	}
};

class Playground
{
public:
	static bool keep_running;
	vector<vector<CellType>> field;
	Player player;
	int monsters = 0;
	int daggers = 0;
	int maxPathSize = 0;

	void addRow() {
		field.push_back({});
	}

	void addCell(CellType cell = CellType::clear) {
		field.back().push_back(cell);
		if (cell > 2) {
			monsters++;
		}
	}

	void setField(const vector<vector<CellType>>& field) {
		this->field = field;
		initMonstersCount();
	}

	void initMonstersCount() {
		for (auto& f : field) {
			for (auto& ff : f) {
				if (ff == monster || ff == monster2) monsters++;
			}
		}
	}

	void rotatePlayer(Direction dir) {
		player.rotate(dir);
	}

	void attack(int stepsize) {
		vector<CellType*> path;
		Player helper = player;
		for (int i = 0; i < stepsize; i++) {
			helper.move();
			if (field[helper.y][helper.x] == CellType::wall) break;
			path.push_back(&field[helper.y][helper.x]);
		}
		for (CellType* cell : path)
		{
			switch (*cell)
			{
				case CellType::clear: player.move(); break;
				case CellType::death: player.alive = false; return;
				case CellType::monster: *cell = CellType::clear; monsters--; player.move(); break;
				case CellType::monster2: *cell = CellType::monster; break;
			}
		}
	}

	void throwDagger() {
		if (daggers == 0) return;
		daggers--;

		vector<CellType*> path;
		Player helper = player;
		while (true) {
			helper.move();
			if (field[helper.y][helper.x] == CellType::wall) break;
			path.push_back(&field[helper.y][helper.x]);
		}
		for (CellType* cell : path)
		{
			switch (*cell)
			{
				case CellType::monster: *cell = CellType::clear; return;
				case CellType::monster2: *cell = CellType::monster; return;
			}
		}
	}

	void doMove(Movement& move) {
		switch (move)
		{
			case Movement::attack:
				attack(1);
				break;
			case Movement::attack2:
				attack(2);
				break;
			case Movement::rotate_right:
				rotatePlayer(Direction::right);
				break;
			case Movement::rotate_left:
				rotatePlayer(Direction::left);
				break;
			case Movement::dagger:
				throwDagger();
				break;
			default:
				break;
		}
	}


	int last_loop_start_offset = 0;
	int lastCheckedMove = 0;

	bool checkPath(vector<Movement> path) {
		for (auto it = path.begin() + lastCheckedMove; it != path.end(); it++) {
			lastCheckedMove = it - path.begin() + 1;
			switch (*it)
			{
				case Movement::loop_start:
					last_loop_start_offset = it - path.begin();
					continue;
				case Movement::loop_end2:
					*it = Movement::loop_finish;
					it = path.begin() + last_loop_start_offset;
					continue;
				case Movement::loop_end3:
					*it = Movement::loop_end2;
					it = path.begin() + last_loop_start_offset;
					continue;
				case Movement::loop_end4:
					*it = Movement::loop_end3;
					it = path.begin() + last_loop_start_offset;
					continue;
				case Movement::loop_finish:
					continue;
				default:
					doMove(*it);
			}
			if (!player.alive) return false;
		}
		if (monsters == 0) return true;
		if (monsters == 1) {
			cout << "1 monster!: ";
			printPath(path);
		}
		return false;
	}

	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	bool analyzePath(Playground helper, vector<Movement>& path, int num_daggers, int loop_starts) {
		bool pathCheck = helper.checkPath(path);
		if (!helper.player.alive) return false;
		if (path.size() == maxPathSize) {
			if (loop_starts > 0) return false;
			if (pathCheck) {
				cout << "!!!!!!!" << endl;
				printPath(path);
				keep_running = false;
				return true;
			}
			return false;
		}
		if (pathCheck) {
			cout << "!!!!!!!" << endl;
			printPath(path);
			return true;
		}

		int next_loop_starts = loop_starts;
		for (Movement move : allMovements) {
			if (!keep_running) return false;

			switch (move)
			{
				case Movement::loop_finish:
					continue;
				case Movement::loop_start:
					if (loop_starts > 0 || path.size() > (size_t)maxPathSize - 3) continue;
					next_loop_starts = loop_starts + 1;
					break;
				case Movement::loop_end2:
				case Movement::loop_end3:
				case Movement::loop_end4:
					if (loop_starts == 0 || path.back() == Movement::loop_start) continue;
					next_loop_starts = loop_starts - 1;
					break;
				case Movement::dagger:
					//if (num_daggers == 0) continue;
					num_daggers--;
					break;
			}
			path.emplace_back(move);
			if (path.size() == 4) {
				cout << chrono::duration_cast<std::chrono::milliseconds>(chrono::steady_clock::now() - begin).count() / 1000. << " | ";
				printPath(path);
			}

			if (analyzePath(helper, path, num_daggers, next_loop_starts)) {
				return true;
			}
			path.pop_back();
			next_loop_starts = loop_starts;
		}
		return false;
	}

	void analyzePathStart(vector<Movement>& path, int& num_daggers, int& loop_starts) {
		std::vector<std::thread> threads;

		for (Movement move : allMovements) {
			threads.push_back(std::thread(
				[&, move]()
				{
					if (!keep_running) return;

					int next_loop_starts = loop_starts;
					int next_num_daggers = num_daggers;

					switch (move)
					{
						case Movement::loop_finish:
							return;
						case Movement::loop_start:
							if (loop_starts > 0 || path.size() > (size_t)maxPathSize - 3) return;
							next_loop_starts = loop_starts + 1;
							break;
						case Movement::loop_end2:
						case Movement::loop_end3:
						case Movement::loop_end4:
							if (loop_starts == 0 || path.back() == Movement::loop_start) return;
							next_loop_starts = loop_starts - 1;
							break;
						case Movement::dagger:
							//if (num_daggers == 0) return;
							next_num_daggers--;
							break;
					}

					vector<Movement> next_path = path;

					next_path.emplace_back(move);

					analyzePath(*this, next_path, next_num_daggers, next_loop_starts);
				})
			);
		}

		for (auto& th : threads) {
			th.join();
		}
	}

	void printPath(vector<Movement> path) {
		vector<string> pathAsStrings;
		transform(path.begin(), path.end(), std::back_inserter(pathAsStrings), [](auto m) { return MovementToString(m); });
		string joinedString = boost::algorithm::join(pathAsStrings, ", ");
		cout << joinedString << endl;
	}

	vector<Movement> analyze() {
		vector<Movement> result;
		int loop_starts = 0;

		//analyzePathStart(result, daggers, loop_starts);
		analyzePath(*this, result, daggers, loop_starts);

		return result;
	}
};

