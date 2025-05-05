#include <iostream>

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

    public:
    Ray(Vector origin, Vector direction){
        this->u = origin;
        this->v = direction;
        // std::cout<<"constructed ray"<<std::endl;
    };
    Ray(){
        u=Vector(0,0);
        v=Vector(1,1);
    }

    bool trace(Interactable *coll_obj, int obj_count){
        int n = 0;
        int y_hit = -1;
        Interactable *hit = 0;
        while (n < obj_count){
            // std::cout<<"enter while with n="<<n<<std::endl;
            for (int i=0; i<coll_obj->get_linecount(); i++){
                // std::cout<<"enter for with i="<<i<<std::endl;
                Line *l = coll_obj->get_line(i);
                // std::cout<<"line gotten: "<<l<<std::endl;
                Vector a = l->get_a();
                Vector b = l->get_b();
                //a+x*b = u+y*v
                // std::cout<<"solving linear sys"<<std::endl;
                double y = (u.x - a.x - (b.x/b.y) * (u.y - a.y)) / (v.y * (b.x/b.y) - v.x);
                if (y>0){
                    double x = (u.y - a.y + y * v.y) / b.y;
                    if (x>0 && x<1){
                        //intersection!
                        // std::cout<<"hit! at x="<<u.x+v.x*y<<" and y="<<u.y+v.y*y<<std::endl;
                        //only store this if it is closer (=x smaller then previous hits)
                        if (y_hit < 0 || y<y_hit){
                            y_hit = y;
                            hit = coll_obj;
                        }
                    }

                }//ray cannot travel backwards
            }
            coll_obj += coll_obj->get_size(); //advance pointer by object size
            // std::cout<<"pointer advanced"<<std::endl;
            n++;    //n presents overrunning memory limits
        }
        if (y_hit < 0){
            end = u + v * 1000;
            return false; //no hit
        }else{
            end = u + v * y_hit;
            // std::cout<<"endpoint calculated"<<std::endl;
            return true;
            //process *hit type
        }
    };

    void draw(sf::RenderWindow &window){
        if (child != 0){
            child->draw(window);
        }
        std::array line = line_from_vec(u, end);
        line[0].color = sf::Color::White;
        line[1].color = sf::Color::White;
        window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
    };
};