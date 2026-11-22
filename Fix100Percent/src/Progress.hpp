#pragma once

#include <algorithm>
#include <cmath>
#include <optional>

namespace fix100 {
inline std::optional<float> positionPercent(double x, double length, bool completed) {
    if (completed) return 100.f;
    if (!std::isfinite(x) || !std::isfinite(length) || length <= 0.0)
        return std::nullopt;

    // GD's decimal display rounds to two places. Keep 100% for completion,
    // including when a teleport carries the player beyond the normal end.
    return static_cast<float>(std::clamp(x / length * 100.0, 0.0, 99.99));
}
}
