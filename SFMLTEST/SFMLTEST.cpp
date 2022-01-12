#include <iostream>
#include <SFML/Graphics.hpp>
#include "SortingAlgorithms.h"
#include <cstdlib>

template <typename T>
float r_num()
{
    float r_num = static_cast<T> (rand()) / static_cast<T> (RAND_MAX / 5);
    return r_num;
}

class ProgramManager 
{
public:
    sf::Color* color;
    sf::Event* event;
    sf::RenderWindow* window;
    sf::RectangleShape* m_rects = nullptr;
    float m_largestNumber = 0;
    int m_length = 0;                                                                               // Random debug number
    float* m_array = nullptr;                                                                       // Initalise later in functions

    ProgramManager(sf::RenderWindow* w, sf::Color* c, sf::Event* e)
    {
        window = w;
        color = c;
        event = e;
    }

    void init_array(int size) 
    {
        float* array = new float[size];

        for (int i = 0; i < size; i++) 
        {                                                                                           // Initalise each value in array to a random number
            array[i] = r_num<float>();
            if (array[i] > m_largestNumber) 
            {
                m_largestNumber = array[i];
            }
        }
        m_array = array;
        m_length = size;
    }

    void init_rects() 
    {
        sf::RectangleShape* rects = new sf::RectangleShape[m_length];                               // Array of rectangle entities
        float w_sizex = window->getSize().x;                                                        // Used to scale the height of each bar by setting the max height of the window to the biggest bar.
        float multiplier = window->getSize().y / m_largestNumber;

        for (int i = 0; i < m_length; i++) 
        {
            rects[i].setSize(sf::Vector2f((w_sizex / (m_length - 1)), (m_array[i] * multiplier)));
            rects[i].setPosition((rects[i].getSize().x * i), (window->getSize().y - rects[i].getSize().y));
            color->r = m_array[i] * (255 / 5);
            rects[i].setFillColor(*color);
        }
        m_rects = rects;
    }

    void visual_sort() {
        for (int a = 0; a < m_length - 1; a++) {
            while (window->pollEvent(*event)) {                                                     // Ensures program doesn't freeze
                if (event->type == sf::Event::Closed) { window->close(); }
            }
            for (int i = 0; i < m_length - 1; i++) {
                if (m_array[i] > m_array[i + 1]) {
                    float t = m_array[i];
                    m_array[i] = m_array[i + 1];
                    m_array[i + 1] = t;
                }
            }
            delete[] m_rects;
            init_rects();
            window->clear(sf::Color::Black);
            for (int i = 0; i < m_length - 1; i++)
            {
                window->draw(m_rects[i]);
            }
            window->display();
        }
    }
};



int main(){
    sf::RenderWindow window(sf::VideoMode(1200, 600), "Sorting Ting");                                  // Variable definitions
    sf::Color Test(255, 30, 30);                                                                        // Make entity of class color called gray and give it some sick ass colors
    sf::Event event;

    std::cout << "Press K to generate a new set of bars" << std::endl;
    std::cout << "Press L to visually sort the array" << std::endl;
    std::cout << "Press S to non-vissualy sort the array" << std::endl;
    ProgramManager Manager(&window, &Test, &event);
    int array_size;

    std::cout << "Input amount of bars: " << std::endl;
    std::cin >> array_size;

    Manager.init_array(array_size);
    Manager.init_rects();

    while (window.isOpen()){                                                                        // Main game loop
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){window.close();}

            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::K){
                    Manager.init_array(array_size);
                    Manager.init_rects();
                }
                if (event.key.code == sf::Keyboard::S) {
                    BubbleSort(Manager.m_array, Manager.m_length);
                    Manager.init_rects();
                }
                if (event.key.code == sf::Keyboard::L){
                    Manager.visual_sort();
                }
            }
        }
        window.clear(sf::Color::Black);
        for (int i = 0; i < Manager.m_length-1; i++){
            window.draw(Manager.m_rects[i]);
        }
        window.display();
    }
    delete[] Manager.m_rects;
}