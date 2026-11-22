#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "Progress.hpp"

using namespace geode::prelude;

class $modify(PositionProgress, PlayLayer) {
    float getCurrentPercent() {
        if (m_isPlatformer || !m_player1)
            return PlayLayer::getCurrentPercent();

        auto percent = fix100::positionPercent(
            m_player1->getPositionX(), m_levelLength, m_hasCompletedLevel);
        if (percent) return *percent;
        return PlayLayer::getCurrentPercent();
    }
};
