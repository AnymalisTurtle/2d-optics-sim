#include "Polygon.cpp"
#include "Vector.cpp"
#include "SurfaceProperty.cpp"


#ifndef LENS
class Lens{
    private:
        double x;
        double y;
        double h;
        double b;
        Polygon *poly = 0;
    public:
        Lens(int pointCount, double x, double y, double l, double b, Interactable * last, double reflect = 0, double refract=0.98, double phi=0, sf::Color color = sf::Color::Red){
            this->x = x;
            this->y = y;
            this->h = l;
            this->b = b;
            Vector * points = new Vector[pointCount];
            for(int i=0; i<(pointCount/2); i++){
                Vector p = Vector(x-pow(((double)i-pointCount)/pointCount,2)*b +b/2, y-l/2+(double)i/pointCount *l);
                std::cout<<p.x<<", "<<p.y<<std::endl;
                points[i] = p;
            }
            for(int i=pointCount/2; i<pointCount; i++){
                Vector p = Vector(x+pow(((double)i-pointCount)/pointCount,2)*b -b/2, y+l/2-(double)i/pointCount *l);
                std::cout<<p.x<<", "<<p.y<<std::endl;
                points[i] = p;
            }
            this->poly = new Polygon(points, pointCount, last, SurfaceProperty::stdReflect, SurfaceProperty::stdRefract, color);
            std::cout<<"created polygon"<< std::endl;
        };

        void draw(sf::RenderWindow &window){
            poly->draw(window);
        }

        Interactable *getPoly(){
            return this->poly;
        }

};
#define LENS
#endif