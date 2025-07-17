#include "snake.h"
#include "raylib.h"

void Snake::move(Direction dir){
    Position head (segments.front().x, segments.front().y);
    switch (dir) {
        case Direction::Up:    head.y--; break;
        case Direction::Down:  head.y++; break;
        case Direction::Left:  head.x--; break;
        case Direction::Right: head.x++; break;
    }

    segments.push_front(head);
    segments.pop_back(); // Remove the tail to maintain length
}

void Snake::checkCollision(int N, int M, int &score) {

    // If the snale goes overboard, it comes out from the oppposite side  
    if (segments[0].x < 0) {
        segments[0].x += N;
    }
    if (segments[0].x >= N) {
        segments[0].x %= N;
    }
    if (segments[0].y < 0) {
        segments[0].y += M;
    }
    if (segments[0].y >= M) {
        segments[0].y %= M;
    }

    // Check if the snake bites itself
    for (int i = 1; i < segments.size(); i++) {
        if (segments[0].x == segments[i].x && segments[0].y == segments[i].y) {
            // Reduce the snake length to the bite point
            while (segments.size() > i) {
                segments.pop_back();
                if (score != 0) {
                    --score;
                }
            }
            // No need to continue the loop once a bite is found
            break;
        }
    }
};

void Snake::grow() {
    // Add a new snake segment
    segments.push_back(segments.back());
};

const std::deque<Position> &Snake::get_segments() const {
    return segments;
};

