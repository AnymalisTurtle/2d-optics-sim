#include "Vector.cpp"
#include "Line.cpp"

#ifndef INTERACTABLE
class Interactable{
    private:
    Line * lines = 0;
    int vertex_count;
    char* type;

    public:
    // Interactable(int number_of_vertives, char* interact_type = "boundary"){
    //     this->lines = (Line*) malloc(sizeof(Line)*(number_of_vertives-1));
    //     this->vertex_count = number_of_vertives;
    //     this->type = interact_type;
    // };

    virtual Line *get_line(int index) = 0;
    virtual int get_linecount() = 0;
    char* get_type(){
        return type;
    };
    virtual size_t get_size() = 0;

};
#define INTERACTABLE
#endif