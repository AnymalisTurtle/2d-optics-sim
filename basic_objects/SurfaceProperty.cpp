
#ifndef SURFACEPROPERTY

class SurfaceProperty{
    private:
        double (*reflect)(double);
        double (*refract)(double);

    public:
        static double stdRefract(double angle){return std::sin(angle);}
        static double stdReflect(double angle){return std::cos(angle);}
                    // static double stdRefract(double angle){
                    //     if (angle>PI/4){return 1;}
                    //     else {return 0;}
                    // }
                    // static double stdReflect(double angle){
                    //     if(angle>PI/2){return 1;}
                    //     else {return 0;}
                    // }
        static double returnOne(double angle){return 1;}
        static double returnZero(double angle){return 0;}
    //specify reflaction and refraction amount, absorption calculated to reach 100%
        SurfaceProperty(double  (*reflect)(double), double (*refract)(double)){
            this->reflect = reflect;
            this->refract = refract;
        }

        double get_reflection_perc(double angle){
            return this->reflect(angle);
        }
        
        double get_refraction_perc(double angle){
            return this->refract(angle);
        }
        double get_absoprtion_perc(double angle){
            double absorb = 1 - this->reflect(angle) - this->refract(angle);
            if (absorb<0){
                return 0;
            }else{
                return absorb;
            }
        }
};

#define SURFACEPROPERTY
#endif