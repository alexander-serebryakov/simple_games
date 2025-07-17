#include "game.h"
#include "raylib.h"

void Game::update() {
    timer += GetFrameTime();
    // Check keyboard input
    if (IsKeyPressed(KEY_LEFT) && direction != Direction::Right) direction = Direction::Left;
    if (IsKeyPressed(KEY_RIGHT) && direction != Direction::Left) direction = Direction::Right;
    if (IsKeyPressed(KEY_UP) && direction != Direction::Down) direction = Direction::Up;
    if (IsKeyPressed(KEY_DOWN) && direction != Direction::Up) direction = Direction::Down;
    
    float delay = settings.get_speedup() ? BASE_DELAY - 0.001f * score : BASE_DELAY;

    if (timer >= delay) {
        timer -= delay;

        snake.move(direction);
        
        // Handle collisions with boarders and itself
        snake.checkCollision(settings.get_width(), settings.get_height(), score);

        // Check if the snake eats the fruit
        if ((snake.get_segments().front().x == fruit.x) && (snake.get_segments().front().y == fruit.y)){
            snake.grow();
            score++;
            
            // Make a new fruit
            fruit.x = GetRandomValue(0, settings.get_width() - 1); // new x-coordinate of the fruit
            fruit.y = GetRandomValue(0, settings.get_height() - 1); // new y-coordinate of the fruit
        }
    }
}

void Game::render() {
    BeginDrawing();

    // Clear the screen
    ClearBackground(BLACK);

    // Draw the board
    for (int i = 0; i < settings.get_width(); i++) {
        for (int j = 0; j < settings.get_height(); j++) {
            DrawRectangle(i * settings.get_map_size(), j * settings.get_map_size(),
                          settings.get_map_size(), settings.get_map_size(), GRAY);
            DrawRectangleLines(i * settings.get_map_size(), j * settings.get_map_size(),
                               settings.get_map_size(), settings.get_map_size(), BLACK);
        }
    }

    // Draw the snake
    for (const auto& segment : snake.get_segments()) {
        DrawRectangle(segment.x * settings.get_map_size(), segment.y * settings.get_map_size(),
                      settings.get_map_size(), settings.get_map_size(), GREEN);
    }
    
    // Draw the fruit
    DrawCircle(fruit.x * settings.get_map_size() + settings.get_map_size() / 2,
               fruit.y * settings.get_map_size() + settings.get_map_size() / 2,
               settings.get_map_size() / 2, RED);
    
    // Draw the game score
    DrawText(("SCORE: " + std::to_string(score)).c_str(), 10, settings.get_height() * settings.get_map_size(), 16, WHITE);
    
    EndDrawing();
}