#pragma once
#include <SFML/Graphics.hpp>

class WindowProvider {
public:
    static WindowProvider& instance() {
        static WindowProvider instance;
        return instance;
    }

    inline sf::RenderWindow& getWindow() {
        return window;
    }

private:
    WindowProvider() : window(sf::VideoMode(800, 600), "Tetris?", sf::Style::Close) {window.setVerticalSyncEnabled(true);}
    ~WindowProvider() = default;

    WindowProvider(const WindowProvider&) = delete;
    WindowProvider& operator=(const WindowProvider&) = delete;

    sf::RenderWindow window;
};
