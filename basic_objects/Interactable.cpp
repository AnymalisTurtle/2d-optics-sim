#include "Vector.cpp"
#include "Line.cpp"

#ifndef INTERACTABLE
class Interactable{
    private:
    Line * lines = 0;
    int vertex_count;
    char* type;
    Interactable * last_element=0;

    public:
    // Interactable(int number_of_vertives, char* interact_type = "boundary"){
    //     this->lines = (Line*) malloc(sizeof(Line)*(number_of_vertives-1));
    //     this->vertex_count = number_of_vertives;
    //     this->type = interact_type;
    // };

    virtual Line *get_line(int index) = 0;
    virtual int get_linecount() = 0;
    virtual const char* get_type() = 0;
    virtual size_t get_size() = 0;
    virtual Interactable* get_last_element() = 0;

};
#define INTERACTABLE
#endif