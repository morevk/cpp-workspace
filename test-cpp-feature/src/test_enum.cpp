#include <iostream>


enum TrafficLight {RED, GREEN, BLUE};
//enum Color {RED, GREEN, BLUE}; //Compile error: multiple definitions RED, GREEN, BLUE
enum class Color {RED, GREEN, BLUE}; 

void FillColor(Color c) {

    if(c == Color::RED) {
        std::cout << "RED fill" << std::endl;
    }
    else if (c == Color::GREEN) {
        std::cout << "GREEN fill" << std::endl;
    }
    else if(c == Color::BLUE) {
        std::cout << "BLUE fill" << std::endl;
    }
    else {
        std::cout << "Bad color" << std::endl;
    }

}

int test_enum_main() {

    //Color c = RED;      //compile error: cannot convert 'TrafficLight' to 'Color' in initialization
    //int x = Color::RED;   //compile error: cannot convert 'Color' to 'int' in initialization
    Color c = Color::RED;
    
    FillColor(Color::BLUE);
    FillColor(static_cast<Color>(2));   // int to enum conversion
    FillColor(static_cast<Color>(3));   // int to enum conversion
    FillColor(static_cast<Color>(BLUE)); // 'TrafficLight' to 'Color' conversion

    return 0;
}
