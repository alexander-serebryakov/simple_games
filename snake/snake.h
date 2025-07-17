#ifndef _SNAKE_H_
#define _SNAKE_H_
#include <deque>

enum class Direction { Down, Left, Right, Up };

struct Position {
    int x, y;
    Position(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

class Snake {
private:
    std::deque<Position> segments;
    static constexpr int INITIAL_LENGTH = 4;
public:
    Snake(int startX = 0, int startY = 0) {
        for (int i = 0; i < INITIAL_LENGTH; i++){
            segments.push_back(Position(startX, startY));
        };
    }
    
    void move(Direction dir);
    void checkCollision(int N, int M, int &score);
    const std::deque<Position> &get_segments() const;
    void grow();
};

#endif