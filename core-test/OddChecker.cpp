#include "OddChecker.h"

bool OddChecker::OddChecker::even(int i) {
	return !odd(i);
}

bool OddChecker::OddChecker::odd(int i) {
	return (bool) (i & 1);
}
