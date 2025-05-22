#include "gui.hpp"


GUI::TextBox::TextBox(std::string distext, int x, int y, int width, int height) : Element()
{

    font.loadFromFile("../resources/fonts/RobotoMono.ttf");
    text.setFont(font);
    box.setPosition(x, y);
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(sf::Color(30, 30, 30));
    text.setFillColor(sf::Color(240, 240, 240));

    
    text.setString(distext.substr(0,30));
    int charwidth = 0;
    do
    {
        charwidth += 1;
        text.setCharacterSize(charwidth);
    } while (text.getGlobalBounds().width + 6 < width);
    text.setCharacterSize(charwidth - 1);

    sf::FloatRect bounds = text.getLocalBounds();
    text.setPosition(
        x + std::round((width - bounds.width) / 2.0f - bounds.left),
        y + std::round((height - bounds.height) / 2.0f - bounds.top)
    );

    if(distext.size() > 30){
        text.setPosition(x + std::round((width - text.getGlobalBounds().width) / 2.0f), y);
        for(long unsigned int i = 30; i < distext.size(); i += 31){
            distext.insert(i, 1, '\n');
        }
        text.setString(distext);
        if(text.getGlobalBounds().height > height){
            throw std::runtime_error("The text box at (" + std::to_string(x) + ", " + std::to_string(y) + ") has surpassed the text height limit, remove text, increase height or kys");
        }
    }

}

void GUI::TextBox::draw() const
{
    auto& windowref = WindowProvider::instance().getWindow();

    windowref.draw(box);
    windowref.draw(text);
}

void GUI::Button::update(){
    auto& window = WindowProvider::instance().getWindow();

    sf::Vector2i mpos = sf::Mouse::getPosition(window);
    if(this->box.getGlobalBounds().contains(mpos.x, mpos.y)){
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            firstclick = true;
        }
        box.setFillColor(sf::Color(50, 50, 50));
        box.setOutlineThickness(2.f);
        box.setOutlineColor(sf::Color(50, 50, 50));
        text.setFillColor(sf::Color(255, 255, 255));
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && firstclick){
            box.setFillColor(sf::Color(20, 20, 20)); 
            box.setOutlineThickness(0.f);
            text.setFillColor(sf::Color(180, 180, 180));
            this->callback();
            firstclick = false;
        }
    }
    else{
        box.setFillColor(sf::Color(30, 30, 30));
        box.setOutlineThickness(0.f);
        text.setFillColor(sf::Color(240, 240, 240));
        firstclick = false;
    }
}

void GUI::Page::draw(){
    for(long unsigned int i = 0; i < elements.size(); i++){
        elements[i]->draw();
    }
}

void GUI::Page::update(){
    for(long unsigned int i = 0; i < elements.size(); i++){
        elements[i]->update();
    }
}

GUI::Page::~Page(){
    for(long unsigned int i = 0; i < this->elements.size(); i++){
        delete elements[i];
    }
}
