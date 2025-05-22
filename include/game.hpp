#pragma once
#include <unordered_map>
#include <functional>
#include "windowprovider.hpp"
#include "board.hpp"
#include "gui.hpp"

class Game{
    private:
    class State{
        public:
        enum class Type{
            NoneType,
            Tetris,
            Menu
        };

        public:
        virtual ~State() = default;
        State& operator=(const State&) = default;
        State(const State&) = default;

        public:
        virtual bool run() = 0;

        protected:
        State(std::function<void(Type)> callback) : callback(callback){}

        protected:
        std::function<void(Type)> callback;
    };

    class Menu : public State{
        public:
        explicit Menu(std::function<void(Type)> callback);
        ~Menu() override ;
        Menu(const Menu&) = delete;
        Menu& operator=(const Menu&) = delete;

        void addOptionPage();

        bool run() override;

        private:
        std::stack<GUI::Page*> pages;
        bool delpage;
    };

    
    class Tetris : public State{
        public:
        explicit Tetris(std::function<void(Type)> callback) : State(callback), firstpress(true), board(){}
        ~Tetris() override = default;
        Tetris(const Tetris&) = delete;
        Tetris& operator=(const Tetris&) = delete;

        bool run() override;
 
        private:
        bool firstpress;
        Board board;
        sf::Clock moveTimer;
    };

    public:
    Game();
    ~Game();
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

    bool run();

    private:
    void changeState(State::Type newState);

    private:
    State* state;
    State::Type nstate;
};