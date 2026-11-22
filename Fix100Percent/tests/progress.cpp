#include "../src/Progress.hpp"
#include <cassert>
#include <cmath>
#include <limits>
#include <iostream>

int main() {
    using fix100::positionPercent;
    assert(positionPercent(0, 1000, false) == 0.f);
    assert(positionPercent(250, 1000, false) == 25.f);
    assert(positionPercent(750, 1000, false) == 75.f);
    assert(positionPercent(-30, 1000, false) == 0.f);
    // End-portal approach, overshoot, and the completed run are distinct.
    assert(positionPercent(999.99, 1000, false).value() < 100.f);
    assert(positionPercent(1000, 1000, false).value() < 100.f);
    assert(positionPercent(1200, 1000, false).value() < 100.f);
    assert(positionPercent(1000, 1000, true) == 100.f);
    assert(!positionPercent(500, 0, false));
    assert(!positionPercent(500, -10, false));
    assert(!positionPercent(std::numeric_limits<double>::quiet_NaN(), 1000, false));
    assert(!positionPercent(500, std::numeric_limits<double>::infinity(), false));
    // Two-decimal formatting must not turn an unfinished run into 100.00%.
    assert(std::round(positionPercent(1000, 1000, false).value() * 100) < 10000);
    std::cout << "Position progress checks passed\n";
}
