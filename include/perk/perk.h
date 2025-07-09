#pragma once

#include <string>
#include <vector>
#include "perk/perk_effect.h"

enum class PerkTriggerType {
    Passive,
    Delayed,
    Recurring
};

struct Perk {
    std::string description;

    std::vector<PerkEffect> effects;

    float duration = -1.0f; // -1: vô thời hạn
    float elapsed = 0.0f;
    PerkTriggerType triggerType = PerkTriggerType::Passive;

    // Recurring & Delayed
    bool triggered = false;
    float interval = 0.0f;
    float timeSinceLastTrigger = 0.0f;

    Perk(const std::string& desc,
         const std::vector<PerkEffect>& effs,
         float dur = -1.0f,
         PerkTriggerType trigger = PerkTriggerType::Passive,
         float interval = 0.0f)
        : description(desc),
          effects(effs),
          duration(dur),
          triggerType(trigger),
          interval(interval)
    {}
};
