
#ifndef SURFACEPROPERTY

class SurfaceProperty{
    private:
        double reflect;
        double refract;
        double absorb;

    public:
    //specify reflaction and refraction amount, absorption calculated to reach 100%
    SurfaceProperty(double reflect, double refract){
        this->reflect = reflect;
        this->refract = refract;
        this->absorb = 1 - reflect - refract;
        if (this->absorb<0) this->absorb = 0; 
    }

    double get_reflection_perc(){
        return this->reflect;
    }
    
    double get_refraction_perc(){
        return this->refract;
    }
    double get_absoprtion_perc(){
        return this->absorb;
    }
};

#define SURFACEPROPERTY
#endif