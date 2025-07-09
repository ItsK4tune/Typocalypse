#include "perk/perk_system.h"
#include <iostream>
#include <algorithm>

void PerkSystem::addPerk(const Perk& perk) {
    activePerks.push_back(perk);
}

void PerkSystem::update(float deltaTime) {
    for (auto& perk : activePerks) {
        if (perk.duration > 0.0f) {
            perk.elapsed += deltaTime;
            if (perk.elapsed >= perk.duration)
                continue; // đã hết thời gian
        }

        switch (perk.triggerType) {
            case PerkTriggerType::Delayed:
                if (!perk.triggered && perk.elapsed >= perk.interval) {
                    applyTriggeredPerk(perk);
                    perk.triggered = true;
                }
                break;

            case PerkTriggerType::Recurring:
                perk.timeSinceLastTrigger += deltaTime;
                if (perk.timeSinceLastTrigger >= perk.interval) {
                    perk.timeSinceLastTrigger = 0.0f;
                    applyRecurringPerk(perk);
                }
                break;

            default:
                break;
        }
    }

    // Xóa những perk đã hết thời gian (nếu có thời hạn)
    activePerks.erase(std::remove_if(activePerks.begin(), activePerks.end(),
        [](const Perk& p) {
            return p.duration > 0.0f && p.elapsed >= p.duration;
        }), activePerks.end());
}

void PerkSystem::applyTriggeredPerk(const Perk& perk) {
    for (const auto& effect : perk.effects) {
        switch (effect.type) {
            case PerkEffectType::ExplodeEnemies:
                std::cout << "[Perk Triggered] BOOM! All enemies exploded.\n";
                break;
            default:
                break;
        }
    }
}

void PerkSystem::applyRecurringPerk(Perk& perk) {
    for (const auto& effect : perk.effects) {
        switch (effect.type) {
            case PerkEffectType::FreezeEnemies:
                std::cout << "[Perk Recurring] Freeze all enemies this round.\n";
                break;
            default:
                break;
        }
    }
}

float PerkSystem::getTotalFireRateMultiplier() const {
    float result = 1.0f;
    for (const auto& perk : activePerks) {
        for (const auto& effect : perk.effects) {
            if (effect.type == PerkEffectType::PlayerFireRateMultiplier)
                result *= effect.value;
        }
    }
    return result;
}

float PerkSystem::getEnemyHealthMultiplier() const {
    float result = 1.0f;
    for (const auto& perk : activePerks) {
        for (const auto& effect : perk.effects) {
            if (effect.type == PerkEffectType::EnemyHealthMultiplier)
                result *= effect.value;
        }
    }
    return result;
}

float PerkSystem::getEnemySpeedMultiplier() const {
    float result = 1.0f;
    for (const auto& perk : activePerks) {
        for (const auto& effect : perk.effects) {
            if (effect.type == PerkEffectType::EnemySpeedMultiplier)
                result *= effect.value;
        }
    }
    return result;
}

const std::vector<Perk>& PerkSystem::getActivePerks() const {
    return activePerks;
}

void PerkSystem::clear() {
    activePerks.clear();
}
