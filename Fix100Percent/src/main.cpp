#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJGameLevel.hpp>
#include "Progress.hpp"

using namespace geode::prelude;

class $modify(PositionProgress, PlayLayer) {
    struct Fields {
        std::optional<float> deathPercent;
    };

public:
    std::optional<float> deathPercent() {
        if (m_isPlatformer || m_hasCompletedLevel || m_levelEndAnimationStarted)
            return std::nullopt;
        return m_fields->deathPercent;
    }

    float getCurrentPercent() {
        if (m_isPlatformer || !m_player1)
            return PlayLayer::getCurrentPercent();
        if (auto percent = deathPercent()) return *percent;

        auto percent = fix100::positionPercent(
            m_player1->getPositionX(), m_levelLength, m_hasCompletedLevel);
        if (percent) return *percent;
        return PlayLayer::getCurrentPercent();
    }

    void destroyPlayer(PlayerObject* player, GameObject* object) {
        auto previous = m_fields->deathPercent;
        if (!m_isPlatformer && m_player1 && !previous)
            m_fields->deathPercent = fix100::positionPercent(
                m_player1->getPositionX(), m_levelLength, m_hasCompletedLevel);

        PlayLayer::destroyPlayer(player, object);

        // Noclip and the game's ignored collision checks can return without
        // a death. Do not freeze a live run's progress in those cases.
        if (!m_playerDied && (!m_player1 || !m_player1->m_isDead))
            m_fields->deathPercent = previous;
    }

    void resetLevel() {
        m_fields->deathPercent.reset();
        PlayLayer::resetLevel();
    }

    void showNewBest(bool newReward, int orbs, int diamonds, bool demonKey, bool noRetry, bool noTitle) {
        if (auto percent = deathPercent())
            m_lastAttemptPercent = static_cast<int>(*percent);
        PlayLayer::showNewBest(newReward, orbs, diamonds, demonKey, noRetry, noTitle);
    }
};

class $modify(PositionProgressSave, GJGameLevel) {
    void savePercentage(int percent, bool practice, int clicks, int attempts, bool checkpointValid) {
        auto* play = PlayLayer::get();
        if (play && play->m_level == this) {
            if (auto death = static_cast<PositionProgress*>(play)->deathPercent())
                percent = static_cast<int>(*death);
        }
        GJGameLevel::savePercentage(percent, practice, clicks, attempts, checkpointValid);
    }
};
