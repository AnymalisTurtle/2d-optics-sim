#include <functional>
#include "Polygon.cpp"
#include "Vector.cpp"
#include "SurfaceProperty.cpp"


#ifndef LENS
typedef std::function<double(double)> shapeFct;
typedef std::function<shapeFct(double,double)> shapeFctFct;

class Lens{
    private:
        double xCenter;
        double yCenter;
        double l;
        double b;
        double phi;
        Polygon *poly = 0;
        shapeFct *xFct = new shapeFct;
    public:
        static shapeFct convexParabolic(double b, double l) {
            shapeFct x = [b, l](double y) {return b/pow(l,2) * pow(y,2) - b;};
            return x;
        }
        static shapeFct concaveParabolic(double b, double l){
            shapeFct x = [b, l](double y) {return -b/pow(l,2) * pow(y,2) - b/10;};
            return x;
        }

        static double lensRefract(double angleToNormal){
            if (angleToNormal>PI/2 * 0.9){return 0.8;}
            else {return 1;}
        }
        static double lensReflect(double angleToNormal){
            if (angleToNormal>PI/2 * 0.9){return 0.15;}
            else {return 0;}
        }

        Lens(int pointCount, double xCenter, double yCenter, double l, double b, Interactable * last, double phi=0, shapeFctFct funcGen = Lens::convexParabolic, double (*reflect)(double) = &Lens::lensReflect, double (*refract)(double) = &Lens::lensRefract, sf::Color color = sf::Color::Red){
            this->xCenter = xCenter;
            this->yCenter = yCenter;
            this->l = l;
            this->b = b;
            this->phi = phi;
            *this->xFct = funcGen(b, l);
            while (pointCount%4 != 0) pointCount++; //ensure divisibility by 4

            Vector * points = new Vector[pointCount];
            Vector pCenter = Vector(xCenter, yCenter);
            double *y = new double;
            for(int i=0; i<(pointCount/2); i++){
                *y = l*4 * ((double)i/pointCount- (double)1/4);
                Vector p = Vector((*xFct)(*y), *y);
                p.rotate(phi);
                p = p + pCenter;
                // std::cout<<p.x<<", "<<p.y<<std::endl;
                points[i] = p;
            }
            // std::cout<<"finished first loop in lenscreating"<<std::endl;
            for(int i=0; i<pointCount/2; i++){
                *y = l*4 * ((double)1/4-(double)i/pointCount);
                Vector p = Vector(-(*xFct)(*y), *y);
                p.rotate(phi);
                p = p + pCenter;
                // std::cout<<p.x<<", "<<p.y<<std::endl;
                points[i+pointCount/2] = p;
            }
            delete y;
            this->poly = new Polygon(points, pointCount, last, reflect, refract, color);
            // std::cout<<"created polygon"<< std::endl;
        };

        ~Lens(){
            delete this->poly;
            delete this->xFct;
        }

        void draw(sf::RenderWindow &window){
            poly->draw(window);
        }

        Interactable *getPoly(){
            return this->poly;
        }

};
#define LENS
#endif