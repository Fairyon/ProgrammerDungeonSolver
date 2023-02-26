#include "Playground.h"

Direction operator++(Direction& d, int) {
	if (d == Direction::left)
		d = Direction::top;
	else
		d = Direction(d + 1);
	return d;
}

Direction operator--(Direction& d, int) {
	if (d == Direction::top)
		d = Direction::left;
	else
		d = Direction(d - 1);
	return d;
}