#include <iostream>
using namespace std;

class vector{
    public:
    int x;
    int y;
    int z;


    vector(int x_init, int y_init, int z_init){
        this->x = x_init;
        this->y = y_init;
        this->z = z_init;
    }
    
};


int main(int argc, char *argv[]){
    cout << "Entered " << argc
    << " argument(s):" << endl;

    for (int i = 0; i < argc; i++){
        cout << i+1 << ": " << argv[i] << endl;
    }
    cout << "\n\n\n";

    return 0;
}