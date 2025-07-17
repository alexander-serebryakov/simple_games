#include "raylib.h"
#include "settings.h"
#include "game.h"

int main() {
    
    Settings settings; 
    settings.configureSettings();

    Game game(settings);

    while (!WindowShouldClose()) {
        game.update();
        game.render();
    }
    CloseWindow();

    return 0;
}