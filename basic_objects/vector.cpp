#include <iostream>
#define PI 3.141592653589793238462643383279//50288419716939937510582097494459230781640628620899 
#include <cmath>
#include <SFML/Graphics.hpp>


#ifndef VECTOR
class Vector{
    public:
    double x;
    double y;
    double z;
    bool is2d;


//Constructors
    Vector(double x_init, double y_init, double z_init){
        this->x = x_init;
        this->y = y_init;
        this->z = z_init;
        this->is2d = false;
    };
    //2d vector implementation
    Vector(double x_init, double y_init){
        this->x = x_init;
        this->y = y_init;
        this->z = 0;
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
    Vector operator*(double scalar){
        Vector res;
        res.x = this->x * scalar;
        res.y = this->y * scalar;
        res.z = this->z * scalar;
        return res;
    };

//methods and functions    
    double length(){
        return sqrt( pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) );
    };

    void unit(){
        double le = this->length();
        if (le != 0){
            this->x /= le;
            this->y /= le;
            this->z /= le;
        }else{
            std::cerr << "cannot unit zero-vector!";
        }
    };

    void rotate(double angle){
        double xPrime = this->x*std::cos(angle) + this->y*std::sin(angle);
        double yPrime = -this->x*std::sin(angle) + this->y*std::cos(angle);
        Vector Prime(xPrime, yPrime);
        *this = Prime;
    }

    static Vector Vector_angle_length(double angle_rad, double length){
        Vector vec;
        while (angle_rad >= PI*2) {angle_rad -= PI*2;};
        while (angle_rad < 0) {angle_rad += PI*2;};
        // std::cout << "angle_length angle: "<<angle_rad/PI<<"PI"<<std::endl;
        if (angle_rad == 0){
            //+x
            // std::cout << "+x" << std::endl;
            vec = Vector(1, 0);
        } else
        if (0 < angle_rad && angle_rad < PI/2) {
            //first quadrant
            vec = Vector(1, -1* std::tan(angle_rad));
            // std::cout << "first quadrant" << std::endl;
        }else
        if(angle_rad == PI/2 ) {
            //-y
            vec = Vector(0, -1);
            // std::cout << "-y" << std::endl;
        } else
        if (PI/2 < angle_rad && angle_rad < PI) {
            //second quadrant
            vec = Vector( -1* std::tan(angle_rad-PI/2), -1);
            // std::cout << "second quadrant" << std::endl;
        } else
        if (angle_rad == PI) {
            //-x
            vec = Vector(-1, 0);
            // std::cout << "-x" << std::endl;
        } else
        if (PI < angle_rad && angle_rad < PI*3/2) {
            //third quadrant
            vec = Vector(-1, std::tan(angle_rad-PI));
            // std::cout << "thrid quadrant" << std::endl;
        } else
        if (angle_rad == PI*3/2) {
            //+y
            vec = Vector(0, 1);
            // std::cout << "+y" << std::endl;
        } else
        if (PI*3/2 < angle_rad && angle_rad < PI*2) {
            //fourth quadrant
            vec = Vector(std::tan(angle_rad-PI*3/2), 1);
            // std::cout << "fourth quadrant" << std::endl;
        }
        // std::cout << "From angle "<< angle_rad*360/(2*PI) << "°("<< angle_rad/PI <<"Pi) and length "<< length <<" Vector: (" << vec.x << ", " << vec.y << ")" << std::endl;
        vec.unit();
        Vector res = vec * length;
        // std::cout <<" Vector: (" << res.x << ", " << res.y << ")" << std::endl;
        return res;
    };

    // vector-chains which define a body should always run ccw; normals should point outward
    // therefore the normal can be calculated for each segment of the vector chain individually
    // so far only working with 2d; z has to be zero
    Vector get_normal_2d(){
        if (!(this->is2d)){
            // std::cerr << "Function not implemented for 3d vectors"<<std::endl;
        }
        double phi = this->get_angle_rad();
        // std::cout << "with x: " << x << " and y: " << y << " results the angle: " << phi*360/(2*PI) << "°" << std::endl;
        phi-=PI/2;
        if (phi >= 2*PI) phi -= 2*PI;
        else if (phi < 0) phi += 2*PI; 
        Vector normal = Vector_angle_length(phi, 1);
        return normal;
    };
    // returns the ccw angle from pos. x-axis to the vector (0...2Pi)
    double get_angle_rad(){
        double dx = abs(x);
        double dy = abs(y);
        double angle;
        if (x == 0){
            if (y == 0){
                //zero-vector
                return -1;
            } else if (y>0){
                //straight down
                angle = PI*3/2;
            } else {
                //straight up
                angle = PI/2;
            }
        } else {
            if (y<=0 && x>0){
                //first quadrant
                angle = (std::atan(dy/dx) + 0);
            } else if (y<0 && x<0){
                //second quadrant
                angle = (std::atan(dx/dy) + PI/2);
            } else if (y>=0 && x<0){
                //third quadrant
                angle = (std::atan(dy/dx) + PI);
            } else if (y>0 && x>0){
                //fourth quadrant
                angle = (std::atan(dx/dy) + PI*3/2);
            } else{
                //kaputt
                return -1;
            }
        }
        if (angle >= 2*PI) angle -= 2*PI;
        else if (angle < 0) angle += 2*PI; 
        return angle;
    };
};



#define VECTOR 
#endif