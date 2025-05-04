#include <iostream>
#include <cmath>
using namespace std;

class vector{
    public:
    float x;
    float y;
    float z;
    bool is2d;


    vector(float x_init, float y_init, float z_init){
        this->x = x_init;
        this->y = y_init;
        this->z = z_init;
        this->is2d = false;
    }
    //2d vector implementation
    vector(float x_init, float y_init){
        this->x = x_init;
        this->y = y_init;
        this->is2d = true;
    }
    vector(vector start, vector end){
        if (start.is2d && end.is2d){
            this->is2d = true;
        }else{
            this->is2d = false;
        }

        this->x = end.x - start.x;
        this->y = end.y - start.y;
        this->z = end.z - start.z;
    }
    
    float length(){
        return sqrt( pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) );
    }

    void unit(){
        float le = this->length();
        if (le != 0){
            this->x /= le;
            this->y /= le;
            this->z /= le;
        }else{
            cerr << "cannot unit zero-vector!";
        }
    }

    // vector-chains which define a body should always run ccw; normals should point outward
    // therefore the normal can be calculated for each segment of the vector chain individually
    // so far only working with 2d; z has to be zero
    vector get_normal_2d(){
        if (this->is2d){
            cerr << "Function not implemented for 3d vectors";
        }
        vector normal(this->y, -this->x, 0);
        normal.unit();
        return normal;
    }
};