#include <SFML/Graphics.hpp>
#include "Vector.cpp"


#ifndef UTIL
//contains some utility functions
// #creates a drawable line from vector objects for start and end points
std::array<sf::Vertex, 2> line_from_vec(Vector p1, Vector p2){
    std::array line = 
    {
        sf::Vertex{sf::Vector2f(p1.x, p1.y)},
        sf::Vertex{sf::Vector2f(p2.x, p2.y)} 
    };
    return line;
};
template<typename T>
T* pointer_increment(T* pointer){
    int ptr = reinterpret_cast<std::uintptr_t> (pointer);
    std::cout<<"ptr "<<ptr<<" incr "<<sizeof(*pointer)<<std::endl;
    ptr += sizeof(*pointer);
    return reinterpret_cast<T*> (ptr);
}
#define UTIL
#endif