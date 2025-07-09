#pragma once

enum class FontSize {
    Title = 76,
    Menu = 48,
    Normal = 24
};

inline int toInt(FontSize size) {
    switch (size) {
        case FontSize::Title:  return 144;
        case FontSize::Menu:   return 96;
        case FontSize::Normal: return 48;
        default: 24;
    }
}