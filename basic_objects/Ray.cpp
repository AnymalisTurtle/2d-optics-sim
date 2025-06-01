#include <iostream>
#include <SFML/Graphics.hpp>

#include "Vector.cpp"
#include "Line.cpp"
#include "Interactable.cpp"


#ifndef RAY
class Ray{
    private:
    Vector u;
    Vector v;
    Vector end;
    Ray *child_reflected = 0;
    Ray *child_refracted = 0;
    Ray *parent = 0;
    int recursion_depth;
    sf::Color c1;
    sf::Color c2;

    public:
    Ray(Vector origin, Vector direction, int recursion_depth = 0, Ray *parent = 0, sf::Color col1 = sf::Color(255, 255, 255), sf::Color col2 = sf::Color(237, 235, 235)){
        this->u = origin;
        this->v = direction;
        this->recursion_depth = recursion_depth;
        // std::cout << "constructing with recursion_depth: " << this->recursion_depth <<std::endl;
        this->parent = parent;
        this->c1 = col1;
        this->c2 = col2;
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
            // std::cout<<"tracing with coll_obj: "<<coll_obj<<std::endl;
            for (int i=0; i<coll_obj->get_linecount(); i++){
                Line *l = coll_obj->get_line(i);
                Vector a = l->get_a();
                Vector b = l->get_b();
                //a+x*b = u+y*v
                double y; double x;
                if (b.y==0){
                    if(v.y==0) continue;
                    y = (a.y - u.y) / v.y;
                }else{
                    y = (u.x - a.x - (b.x/b.y) * (u.y - a.y)) / (v.y * (b.x/b.y) - v.x);
                }
                if (y>0){
                    if(b.y==0){
                        x = (u.x - a.x + y * v.x) / b.x;
                    }else{
                        x = (u.y - a.y + y * v.y) / b.y;
                    }
                    if (x>0 && x<1){
                        //intersection!
                        //only store this if it is closer (=x smaller then previous hits) but the hit is also suff. away (avoid hitting same obstacle multiple times)
                        if ((y_hit < 0 || y<y_hit) && (this->v*y).length()>2){
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

                double surfaceIncidence = abs(v.get_angle_rad() - this->v.get_angle_rad()); //angle between ray and wall normal : 0...2PI
                if (surfaceIncidence > PI){surfaceIncidence-=PI;}
                surfaceIncidence = (double)PI/2 - abs(PI/2-surfaceIncidence);

                if (y>0){
                    is_incoming = true;
                }else{
                    is_incoming = false;
                }

                //process *hit type
                if (! hit == 0) {
                    SurfaceProperty *sp = hit->get_SurfaceProperty();
                    if (sp->get_absoprtion_perc(surfaceIncidence) == 1);
                        // do nothing
                    else 
                    {   
                        double r = c2.r * sp->get_reflection_perc(surfaceIncidence);//std::sqrt(std::pow((double) c2.r, 2)*sp->get_reflection_perc());
                        double g = c2.g * sp->get_reflection_perc(surfaceIncidence);//std::sqrt(std::pow((double) c2.g, 2)*sp->get_reflection_perc());
                        double b = c2.b * sp->get_reflection_perc(surfaceIncidence);//std::sqrt(std::pow((double) c2.b, 2)*sp->get_reflection_perc());
                        sf::Color refl_col = sf::Color(r, g, b);
                        if(! (refl_col.r<10 && refl_col.g<10 && refl_col.b<10)){
                            if (sp->get_reflection_perc(surfaceIncidence) > 0){
                                double incidence = v.get_angle_rad() - (this->v * -1).get_angle_rad();
                                Vector outsidence = v.Vector_angle_length((this->v * -1).get_angle_rad() + 2*incidence, 1);
                                // std::cout << "with incidence " << incidence/PI << "PI and vector (" << outsidence.x << ", " << outsidence.y << ") creating new ray." << std::endl;
                                this->child_reflected = (Ray*)malloc(sizeof(Ray));
                                *child_reflected = Ray(this->end, outsidence, (this->recursion_depth)+1, this, refl_col, refl_col);
                                child_reflected->trace(pass_on_col_obj);
                            }
                        }
                        
                        r = c2.r * sp->get_refraction_perc(surfaceIncidence);//std::sqrt(std::pow((double) c2.r, 2)*sp->get_refraction_perc());
                        g = c2.g * sp->get_refraction_perc(surfaceIncidence);//std::sqrt(std::pow((double) c2.g, 2)*sp->get_refraction_perc());
                        b = c2.b * sp->get_refraction_perc(surfaceIncidence);// std::sqrt(std::pow((double) c2.b, 2)*sp->get_refraction_perc());
                        sf::Color refr_col = sf::Color(r, g, b);
                        if (!(refr_col.r<10 && refr_col.g<10 && refr_col.b<10)){
                            if (sp->get_refraction_perc(surfaceIncidence) > 0){
                                if (is_incoming){
                                    double incidence = PI + v.get_angle_rad() - this->v.get_angle_rad();
                                    double k = std::max((double)-0.999999, std::min((double)0.999999, 1/hit->get_refraction_index() * std::sin(incidence)));
                                    double outsidence = std::asin(k);
                                    // std::cout << "incidence: "<<incidence<<"    outsidence: "<<outsidence<<std::endl;
                                    Vector refracd = end.Vector_angle_length(PI + v.get_angle_rad() - outsidence, 1);
                                    this->child_refracted = (Ray*)malloc(sizeof(Ray));
                                    *child_refracted = Ray(this->end, refracd, (this->recursion_depth)+1, this, refr_col, refr_col);
                                    child_refracted->trace(pass_on_col_obj);

                                } else {
                                    double incidence = (v).get_angle_rad() - this->v.get_angle_rad();
                                    double k = std::max((double)-0.999999, std::min((double)0.999999, hit->get_refraction_index() * std::sin(incidence)));
                                    double outsidence =  std::asin(k);
                                    // std::cout << "incidence: "<<incidence/PI<<"Pi    outsidence: "<<outsidence/PI<<"PI    normal angle: "<<v.get_angle_rad()/PI<<"PI"<<std::endl;
                                    Vector refracd = end.Vector_angle_length(v.get_angle_rad() - outsidence, 1);
                                    // std::cout << "refracd: ("<<refracd.x<<", "<<refracd.y<<")   end: ("<<end.x<<", "<<end.y<<")"<<std::endl;
                                    this->child_refracted = (Ray*)malloc(sizeof(Ray));
                                    *child_refracted = Ray(this->end, refracd, (this->recursion_depth)+1, this, refr_col, refr_col);
                                    child_refracted->trace(pass_on_col_obj);
                                }
                            }
                        }
                    }
                }
                return true;
            }
        }
    };

    void draw(sf::RenderWindow &window){
        if (child_reflected != 0){
            child_reflected->draw(window);
        }
        if (child_refracted != 0){
            child_refracted->draw(window);
        }
        std::array line = line_from_vec(u, end);
        line[0].color = c1;
        line[1].color = c2;
        window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);

    };
};
#define RAY
#endif