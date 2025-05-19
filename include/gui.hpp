#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <stack>
#include <functional>
#include <iostream>
#include <cmath>
#include "windowprovider.hpp"

// What you have to do is :
// Give the Button class a callback function 
// Make the Menu class create the actual pages through the use of member functions, that will be passed to the buttons as callbacks

namespace GUI{
    class Element{
        protected:
        Element(){}

        public:
        Element(const Element&) = default;
        Element& operator=(const Element&) = default;
        virtual ~Element() = default;

        virtual void update(){}
        virtual void draw() const = 0;
    };

    class TextBox : public Element{
        public:
        TextBox(std::string, int, int, int, int);
        ~TextBox() = default;
        TextBox(const TextBox&) = default;
        TextBox& operator=(const TextBox&) = default;
    
        virtual void draw() const override;
    
        protected:
        sf::RectangleShape box;
        sf::Text text;
        sf::Font font;
    };

    class Button : public TextBox{
        public:
        Button(const std::string& distext, int x, int y, int width, int height, std::function<void()> callback) : 
            TextBox(distext, x, y, width, height), callback(callback){}
        ~Button() = default;
        Button(const Button&) = default;
        Button& operator=(const Button&) = default;

        void update() override;

        private:
        std::function<void()> callback;
    };

    class Page{
        public:
        explicit Page(const std::vector<Element*>& elements) : elements(elements) {}
        Page(const Page&) = default;
        Page& operator=(const Page&) = default;
        ~Page();

        void update();
        void draw();

        private:
        std::vector<Element*> elements;
    };

    
}
