#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <iostream>
#include <iomanip>

class Settings {
    int screenWidth;
    int screenHeight;
    bool speedup;
    int map_size;
    int fps {60};
    static constexpr int DEFAULT_GRID_SIZE = 20;

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
        std::cout << "#############################################################################################################" << std::endl;
        std::cout << std::setw(DEFAULT_GRID_SIZE) << "SETTINGS:" << std::endl;
        std::cout << "SCREEN WIDTH: " << screenWidth << std::endl;
        std::cout << "SCREEN HEIGHT: " << screenHeight << std::endl;
        std::cout << "SPEEDUP: " << speedup << std::endl;
        std::cout << "#############################################################################################################" << std::endl;
    }

    void set_width () {
        std::cout << "Enter new width:" << std::endl;
        int newWidth;
        std::cin >> newWidth;
        screenHeight = (newWidth > 0) ? newWidth : screenWidth;
    };

    void set_height () {
        std::cout << "Enter new height:" << std::endl;
        int newHeight;
        std::cin >> newHeight;
        screenHeight = (newHeight > 0) ? newHeight : screenHeight;
    };

    void set_speedup () {
        std::cout << "Do you want the snake to be speeding up? (1/0)\n";
        std::cin >> speedup;
    };

    void set_map_size () {
        std::cout << "Enter new map size:" << std::endl;
        int new_size {20};
        std::cin >> new_size;
        map_size = (new_size > 0) ? new_size : map_size;
    };
        
    void configureSettings() {
    std::cout << "Use standard settings? (Y/N)\n";
    char response;
    std::cin >> response;
    if (std::tolower(response) != 'y') {
        set_width();
        set_height();
        set_speedup();
        set_map_size();
        }    
    }

    Settings(int sWidth = 20, int sHeight = 20, bool speed = true, int size = 20) : 
    screenWidth(sWidth),
    screenHeight(sHeight),
    speedup(speed),
    map_size(size) {};
};

#endif