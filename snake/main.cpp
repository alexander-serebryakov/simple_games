#include "raylib.h"
#include <time.h>
#include <iostream>
#include <iomanip>

enum Direction { Down, Left, Right, Up };

struct SnakeScale {
    int x,y;
    SnakeScale(int _x, int _y) : x(_x), y(_y) {}
};

struct Fruit {
    int x,y;
};

void Tick(std::vector<SnakeScale>& snake, Fruit& f, Direction dir, int N, int M, int& num) {
    
    // Move each snake segment one cell forward
    for (int i = snake.size() - 1; i > 0; i--) {
        snake[i] = snake[i-1];
    }

    switch (dir) {
        case Up:    snake[0].y -= 1; break;
        case Down:  snake[0].y += 1; break;
        case Left:  snake[0].x -= 1; break;
        case Right: snake[0].x += 1; break;
    }

    // If the snale goes overboard, it comes out from the oppposite side  
    if (snake[0].x < 0) {
        snake[0].x += N;
    }
    if (snake[0].x >= N) {
        snake[0].x %= N;
    }
    if (snake[0].y < 0) {
        snake[0].y += M;
    }
    if (snake[0].y >= M) {
        snake[0].y %= M;
    }

    // If the snake eats the fruit, its length increases by one and a new fruit is generated
    if ((snake[0].x == f.x) && (snake[0].y == f.y)) {
        // Add a new scale
        snake.push_back(snake.back()); 
        
        // Increment the snake length
        num++;

        // Make a new frui
        f.x = GetRandomValue(0, N - 1); // new x-coordinate of the fruit
        f.y = GetRandomValue(0, M - 1); // new y-coordinate of the fruit
    }

    // Check if the snake bites itself
    for (int i = 1; i < num; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            // Reduce the snake length to the bite point
            num = i;

            // Remove excess snake segments
            while (snake.size() > num) {
                snake.pop_back();
            }

            // No need to continue the loop once a bite is found
            break; 
        }
    }
}


class Settings {
    int screenWidth {30};
    int screenHeight {45};
    bool speedup {true};
    int map_size {20};
    int fps {60};

public:
    
    int get_width () const {
        return screenWidth;
    }
    
    int get_height () const {
        return screenHeight;
    }
    
    bool get_speedup () const {
            return speedup;
    }
    
    int get_fps () const {
        return fps;
    }

    int get_map_size () const {
        return map_size;
    }
    
    void display_settings () {
        std::cout << "#############################################################################################################\n";
        std::cout << std::setw(20) << "SETTINGS:\n";
        std::cout << "SCREEN WIDTH: " << screenWidth << std::endl;
        std::cout << "SCREEN HEIGHT: " << screenHeight << std::endl;
        std::cout << "SPEEDUP: " << speedup << std::endl;
        std::cout << "#############################################################################################################\n";
    }

    void set_width () {
        std::cout << "Enter new width:\n";
        std::cin >> screenWidth;
    };

    void set_height () {
        std::cout << "Enter new height:\n";
        std::cin >> screenHeight;
    };

    void set_speedup () {
        std::cout << "Do you want the snake to be speeding up? (1/0)\n";
        std::cin >> speedup;
    };

    void set_map_size () {
        std::cout << "Enter new map size:\n";
        std::cin >> map_size;
    };
    
};

// 

int main() {
    SetRandomSeed(time(NULL));
    SetTraceLogLevel(LOG_NONE); // Suppress all logs

    Settings settings;
    settings.display_settings();

    // Prompt user to use standard game settings
    std:: cout << "Use standard settings? (Y/N)" << std::endl;
    char response;
    std::cin >> response;
    response = std::tolower(response);

    if (response != 'y') {
        settings.display_settings();
        settings.set_width();
        settings.set_height();
        settings.set_speedup();
        settings.set_map_size();
    }

    // Initialise a window
    InitWindow(settings.get_width() * settings.get_map_size(), (settings.get_height() + 1) * settings.get_map_size(), "Snake Game");

    // Set frames-per-second
    SetTargetFPS(settings.get_fps()); 
    
    // Initialise the game variables
    float timer = 0;
    float baseDelay = 0.1; // Base delay

    // Initialise the fruit
    Fruit f;
    f.x = GetRandomValue(0, settings.get_width() - 1);
    f.y = GetRandomValue(0, settings.get_height() - 1);

    // Initialise the snake
    int num = 4; // Length of the snake
    std::vector<SnakeScale> snake; // Vector to store snake segments
    for (int i = 0; i < num; i++) {
        snake.push_back(SnakeScale(settings.get_width() / 2, settings.get_height() / 2));
    }
    
    // Initial direction of the snake
    Direction dir = Down;

    while (!WindowShouldClose()) {

        float time = GetFrameTime();
        timer += time;

        if (WindowShouldClose()) {
            CloseWindow();
            return 0;
        }

        // Check keyboard input for changing snake direction
        if (IsKeyPressed(KEY_LEFT)) dir = Left;
        if (IsKeyPressed(KEY_RIGHT)) dir = Right;
        if (IsKeyPressed(KEY_UP)) dir = Up;
        if (IsKeyPressed(KEY_DOWN)) dir = Down;

        // Adjust snake movement delay based on length and speed toggle
        float delay = settings.get_speedup() ? baseDelay - 0.001 * num : baseDelay;

        // Move the snake based on delay
        if (timer > delay) {
            timer = 0;
            Tick(snake, f, dir, settings.get_width(), settings.get_height(), num);
        }
        
        BeginDrawing();

        // Draw the board
        ClearBackground(BLACK); // Clear the screen
        for (int i = 0; i < settings.get_width(); i++) {
            for (int j = 0; j < settings.get_height(); j++) {
                DrawRectangle(i * settings.get_map_size(), j * settings.get_map_size(), settings.get_map_size(), settings.get_map_size(), GRAY); // Background cells
                DrawRectangleLines(i * settings.get_map_size(), j * settings.get_map_size(), settings.get_map_size(), settings.get_map_size(), BLACK); // Cell borders
            }
        }

        // Draw the snake
        for (const auto& segment : snake) {
            DrawRectangle(segment.x * settings.get_map_size(), segment.y * settings.get_map_size(), settings.get_map_size(), settings.get_map_size(), GREEN);
            DrawRectangleLines(segment.x * settings.get_map_size(), segment.y * settings.get_map_size(), settings.get_map_size(), settings.get_map_size(), BLACK);
        }
        
        // Draw the fruit
        DrawCircle(f.x * settings.get_map_size() + settings.get_map_size() / 2, f.y * settings.get_map_size() + settings.get_map_size() / 2, settings.get_map_size() / 2, RED);

        // Draw the score text
        DrawText(("SCORE: " + std::to_string(num)).c_str(), 10, settings.get_height() * settings.get_map_size(), 16, WHITE);

        EndDrawing();
    }
    CloseWindow();
    
    return 0;
}