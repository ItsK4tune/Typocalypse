#pragma once

#include <vector>
#include "perk/perk.h"

class PerkSystem {
public:
    void addPerk(const Perk& perk);
    void update(float deltaTime);
    void clear();

    float getTotalFireRateMultiplier() const;
    float getEnemyHealthMultiplier() const;
    float getEnemySpeedMultiplier() const;

    const std::vector<Perk>& getActivePerks() const;

private:
    std::vector<Perk> activePerks;

    void applyTriggeredPerk(const Perk& perk);
    void applyRecurringPerk(Perk& perk);
};
