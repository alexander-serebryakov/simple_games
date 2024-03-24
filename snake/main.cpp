#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

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

        // Make a new fruit
        f.x = arc4random() % N; // new x-coordinate of the fruit
        f.y = arc4random() % M; // new y-coordinate of the fruit
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

int main() {

    // Prompt user to use standard game settings
    std:: cout << "Use standard settings? (Y/N)" << std::endl;
    char response;
    response = tolower(getchar());
    int N, M;
    bool speed;
    if (response == 'y'){
        N = 20;
        M = 20;
        speed = true; 
    }
    else {
        std:: cout << "Enter the window width and height in units." << std::endl;
        std:: cin >> N >> M;
        std:: cout << "Would you like the snake to speed up as it grows? (1/0)" << std::endl;
        std:: cin >> speed;
    }
    int size = 20;

    RenderWindow window(VideoMode(size * N, size * (M + 1)), "Snake Game");
    
    // Initialise the game variables
    Clock clock;
    float timer = 0;
    float baseDelay = 0.1; // Base delay

    // Initialise the fruit
    Fruit f;
    f.x = arc4random() % N;
    f.y = arc4random() % M;

    // Initialise the snake
    int num = 4; // Length of the snake
    std::vector<SnakeScale> snake; // Vector to store snake segments
    for (int i = 0; i < num; i++) {
        snake.push_back(SnakeScale(N / 2, M / 2));
    }
    
    // Initial direction of the snake
    Direction dir = Down;

    // Create a render texture for drawing the game board
    RenderTexture boardTexture;
    boardTexture.create(size * N, size * M);

    // Set up the board cell color
    Color cellColor;
    cellColor = Color(200, 200, 200); // Light grey

    // Load the font for displaying the game score
    Font font;
    font.loadFromFile("arial.ttf"); 
    
    // Create text object for displaying score
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(16);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, M * size);

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }
        
        // Check keyboard input for changing snake direction
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            dir = Left;
        };
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            dir = Right;
        };
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            dir = Up;
        };
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            dir = Down;
        };

        // Adjust snake movement delay based on length and speed toggle
        float delay = speed ? baseDelay - 0.001 * num : baseDelay;

        // Move the snake based on delay
        if (timer > delay) {
            timer = 0;
            Tick(snake, f, dir, N, M, num);
        }

        // Update score text
        scoreText.setString("SCORE: " + std::to_string(num));

        window.clear();

        // Draw the board
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // Create a rectangle shape representing the cell
                RectangleShape cell(Vector2f(size, size));
                cell.setPosition(i * size, j * size);
                cell.setFillColor(cellColor);

                // Draw black border around the cell
                cell.setOutlineThickness(1.0f);
                cell.setOutlineColor(Color::Black);

                // Draw the cell onto the render texture
                boardTexture.draw(cell);
            }
        }

        // Draw the snake
        for (const auto& segment : snake) {
            // Draw a snake segemnt
            RectangleShape snakeSegment(Vector2f(size, size));
            snakeSegment.setPosition(segment.x * size, segment.y * size);
            snakeSegment.setFillColor(Color::Green);

            // Draw black border around the snake segment
            snakeSegment.setOutlineThickness(1.0f);
            snakeSegment.setOutlineColor(Color::Black);

            // Draw the segment onto the render texture
            boardTexture.draw(snakeSegment);
        }

        // Draw the fruit
        CircleShape fruitShape(size / 2);
        fruitShape.setPosition(f.x * size, f.y * size);
        fruitShape.setFillColor(Color::Red);
        boardTexture.draw(fruitShape);

        // Display the rendered game board texture
        boardTexture.display();

        // Copy the rendered texture to a sprite for drawing
        Texture boardTextureCopy = boardTexture.getTexture();
        Sprite boardSprite(boardTextureCopy);
        window.draw(boardSprite);

        // Draw the score text
        window.draw(scoreText);

        // Update the display
        window.display();

    }

    return 0;
}