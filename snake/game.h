#ifndef _GAME_H_
#define _GAME_H_

#include "settings.h"
#include "snake.h"
#include "raylib.h"

class Game {
private:
    Settings settings;
    Snake snake;
    Position fruit;
    Direction direction {Direction::Down};
    int score {0};
    float timer {0};
    static constexpr float BASE_DELAY = 0.1f;
public:
    Game(Settings s) : settings(s), snake(s.get_width() / 2, s.get_height() / 2), fruit(GetRandomValue(0, s.get_width() - 1), GetRandomValue(0, s.get_height() - 1)) {
            SetRandomSeed(time(NULL));
            SetTraceLogLevel(LOG_NONE);
            InitWindow(settings.get_width() * settings.get_map_size(), 
            (settings.get_height() + 1) * settings.get_map_size(), "Snake Game");
            SetTargetFPS(settings.get_fps());
    };
    void update();
    void render();
};

#endif