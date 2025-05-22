#include "game.hpp"

#include <iostream>

Game::Game(){
    state = new Menu([this](State::Type s) { changeState(s); });
    nstate = State::Type::NoneType;
}

bool Game::run()
{
    switch (nstate)
    {
    case State::Type::Menu:
        delete state;
        state = new Menu([this](State::Type s) { changeState(s); });
        nstate = State::Type::NoneType;
        break;
    case State::Type::Tetris:
        delete state;
        state = new Tetris([this](State::Type s) { changeState(s); });
        nstate = State::Type::NoneType;
    break;
    
    default:
        break;
    }
    return this->state->run();
}

void Game::changeState(State::Type newState) {
    nstate = newState;
}

Game::~Game(){
    delete this->state;
}

bool Game::Tetris::run(){
    auto& window = WindowProvider::instance().getWindow();

    sf::Event e{};
    while (window.pollEvent(e))
    {
        switch (e.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            switch (e.key.code)
            {
            case sf::Keyboard::Left:
                if (firstpress)
                {
                    board.moveLeft();
                    firstpress = false;
                }

                break;
            case sf::Keyboard::Right:
                if (firstpress)
                {
                    board.moveRight();
                    firstpress = false;
                }
                break;

            case sf::Keyboard::Up:
                if(firstpress){
                    board.rotate();
                    firstpress = false;
                }
            break;
            default:
                break;
            }
            break;

        case sf::Event::KeyReleased:
            switch (e.key.code)
            {
            case sf::Keyboard::Left:
            case sf::Keyboard::Right:
            case sf::Keyboard::Up:
                firstpress = true;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    board.update();

    window.clear(sf::Color(30, 30, 30));
    board.draw();
    window.display();

    return window.isOpen();
}

Game::Menu::Menu(std::function<void(Type)> callback) : State(callback), delpage(false){
    GUI::Page* newp = new GUI::Page({
        new GUI::TextBox("Simplicity is the key to clarity; when we remove the unnecessary, the essential shines with unmistakable purpose.", 250, 50, 300, 80),
        new GUI::Button(" Play ", 300, 180, 200, 60, [this](){
            this->callback(Type::Tetris);
        }),
        new GUI::Button("Options", 300, 270, 200, 60, [this](){
            this->addOptionPage();
        }),
        new GUI::Button(" Exit ", 300, 360, 200, 60, [](){
            std::exit(0);
        })
    });
    
    pages.push(newp);
}

void Game::Menu::addOptionPage() {
    GUI::Page* optionsPage = new GUI::Page({
        new GUI::TextBox("Options", 300, 50, 200, 60),
        
        new GUI::Button(" Toggle Sound ", 300, 150, 200, 50, [](){
            // Sound toggle logic
        }),
        
        new GUI::Button(" Change Difficulty ", 300, 220, 200, 50, [](){
            // Difficulty toggle logic
        }),
        
        new GUI::Button(" Controls ", 300, 290, 200, 50, [](){
            // Show control scheme
        }),
        
        new GUI::Button(" Back ", 300, 400, 200, 50, [this]() {
            // Go back to previous page
            this->delpage = true;
        })
    });

    pages.push(optionsPage);
}


bool Game::Menu::run(){
    auto& window = WindowProvider::instance().getWindow();

    sf::Event e{};
    while (window.pollEvent(e))
    {
        switch (e.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
        break;
        }
    }

    pages.top()->update();
    if(delpage){
        if (!pages.empty()) {
            delete pages.top();
            pages.pop();
        }
        delpage = false;
    }

    window.clear(sf::Color(20, 20, 20));
    pages.top()->draw();
    window.display();

    return window.isOpen();
}

Game::Menu::~Menu(){
    while(!pages.empty()){
        delete pages.top();
        pages.pop();
    }
}