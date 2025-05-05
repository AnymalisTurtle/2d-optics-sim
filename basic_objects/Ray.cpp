#include <iostream>
#include <SFML/Graphics.hpp>

#include "Vector.cpp"
#include "Line.cpp"
#include "Interactable.cpp"

class Ray{
    private:
    Vector u;
    Vector v;
    Vector end;
    Ray *child = 0;
    Ray *parent = 0;
    int recursion_depth;
    sf::Color c1;
    sf::Color c2;

    public:
    Ray(Vector origin, Vector direction, int recursion_depth = 0, Ray *parent = 0, sf::Color col1 = sf::Color(256, 256, 256), sf::Color col2 = sf::Color(236, 226, 226)){
        this->u = origin;
        this->v = direction;
        this->recursion_depth = recursion_depth;
        // std::cout << "constructing with recursion_depth: " << this->recursion_depth <<std::endl;
        this->parent = parent;
    };
    Ray(){
        u=Vector(0,0);
        v=Vector(1,1);
    }

    bool trace(Interactable *coll_obj){
        Interactable *pass_on_col_obj = coll_obj;
        bool is_incoming; //true if the ray is outside the obj. false if it is inside
        int y_hit = -1;
        Interactable *hit = 0;
        Line *hit_line = 0;
        while (coll_obj != 0){
            for (int i=0; i<coll_obj->get_linecount(); i++){
                Line *l = coll_obj->get_line(i);
                Vector a = l->get_a();
                Vector b = l->get_b();
                //a+x*b = u+y*v
                double y = (u.x - a.x - (b.x/b.y) * (u.y - a.y)) / (v.y * (b.x/b.y) - v.x);
                if (y>0){
                    double x = (u.y - a.y + y * v.y) / b.y;
                    if (x>0 && x<1){
                        //intersection!
                        //only store this if it is closer (=x smaller then previous hits)
                        if (y_hit < 0 || y<y_hit){
                            y_hit = y;
                            hit = coll_obj;
                            hit_line = l;
                        }
                    }

                }//ray cannot travel backwards
            }
            coll_obj = coll_obj->get_last_element();
        }
        if (y_hit < 0){
            end = u + v * 1000;
            return false; //no hit
        }else{
            end = u + v * y_hit;
            // std::cout<<"endpoint calculated"<<std::endl;

            if (recursion_depth >= 10){
                // std::cout << "stopped recursion" <<std::endl;
                return 0;
            }else{
                // std::cout << "recursion depth: " << recursion_depth <<std::endl;
                //determine if the ray is inside or outside of the interactable
                //IDEA: normals always point outward; find the intersection of the normal (from the midpoint) and a line parallel to the hit_line through the ray origin
                //      if this intersection occurs for a positive multiple of the normal vector, the ray originates on the outside of the interactable
                //a - ray origin; b - line direction; u - line midpoint; v - normal vector;; a+xb=u+yv
                Vector a = this->u;
                Vector b = hit_line->get_b();
                Vector u = hit_line->get_a() + hit_line->get_b()* (double)(1/2);
                Vector v = hit_line->get_normal().get_b();
                double y = (u.x - a.x - (b.x/b.y) * (u.y - a.y)) / (v.y * (b.x/b.y) - v.x);

                if (y>0){
                    is_incoming = true;
                }else{
                    is_incoming = false;
                }

                //process *hit type
                if (! hit == 0) {
                    // std::cout << "hit_type of "<< hit <<" : " << hit->get_type() << std::endl;
                    if (hit->get_type() == "absorb");
                    else if (hit->get_type() == "reflect"){
                        double incidence = v.get_angle_rad() - (this->v * -1).get_angle_rad();
                        Vector outsidence = v.Vector_angle_length((this->v * -1).get_angle_rad() + 2*incidence, 1);
                        // std::cout << "with incidence " << incidence/PI << "PI and vector (" << outsidence.x << ", " << outsidence.y << ") creating new ray." << std::endl;
                        this->child = (Ray*)malloc(sizeof(Ray));
                        *child = Ray(this->end, outsidence, (this->recursion_depth)+1, this, c2, sf::Color(c2.r-30, c2.g-40, c2.b-40));
                        child->trace(pass_on_col_obj);
                    }else if (hit->get_type() == "refract"){

                    }
                }
                return true;
            }
        }
    };

    void draw(sf::RenderWindow &window){
        if (child != 0){
            child->draw(window);
        }
        std::array line = line_from_vec(u, end);
        line[0].color = c1;
        line[1].color = c2;
        window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);

    };
};