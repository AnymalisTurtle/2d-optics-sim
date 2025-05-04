#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#ifndef VECTOR
class Vector{
    public:
    float x;
    float y;
    float z;
    bool is2d;

//Constructors
    Vector(float x_init, float y_init, float z_init){
        this->x = x_init;
        this->y = y_init;
        this->z = z_init;
        this->is2d = false;
    };
    //2d vector implementation
    Vector(float x_init, float y_init){
        this->x = x_init;
        this->y = y_init;
        this->is2d = true;
    };
    Vector(Vector start, Vector end){
        if (start.is2d && end.is2d){
            this->is2d = true;
        }else{
            this->is2d = false;
        }

        this->x = end.x - start.x;
        this->y = end.y - start.y;
        this->z = end.z - start.z;
    };
    Vector(){
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->is2d = true;
    };

//operators
    Vector operator+(Vector const& vec){
        Vector res;
        res.x = this->x + vec.x;
        res.y = this->y + vec.y;
        res.z = this->z + vec.z;
        return res;
    };
    Vector operator-(Vector const& vec){
        Vector res;
        res.x = this->x - vec.x;
        res.y = this->y - vec.y;
        res.z = this->z - vec.z;
        return res;
    };
    Vector operator*(float scalar){
        Vector res;
        res.x = this->x * scalar;
        res.y = this->y * scalar;
        res.z = this->z * scalar;
        return res;
    }

//methods and functions    
    float length(){
        return sqrt( pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) );
    };

    void unit(){
        float le = this->length();
        if (le != 0){
            this->x /= le;
            this->y /= le;
            this->z /= le;
        }else{
            std::cerr << "cannot unit zero-vector!";
        }
    };

    // vector-chains which define a body should always run ccw; normals should point outward
    // therefore the normal can be calculated for each segment of the vector chain individually
    // so far only working with 2d; z has to be zero
    Vector get_normal_2d(){
        if (this->is2d){
            std::cerr << "Function not implemented for 3d vectors";
        }
        Vector normal(-this->y, this->x, 0);
        normal.unit();
        return normal;
    }
};
#define VECTOR 1
#endif