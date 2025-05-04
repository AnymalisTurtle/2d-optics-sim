#include <iostream>
#include "basic_objects\vector.cpp"
using namespace std;


int main(int argc, char *argv[]){
    // parsing commandline arguments
    cout << "Entered " << argc
    << " argument(s):" << endl;

    for (int i = 0; i < argc; i++){
        cout << i+1 << ": " << argv[i] << endl;
    }
    cout << "\n####################\n" <<endl;

    // constructing an example vector
    vector vec1(1,2,3);
    cout << "vector coord: " << "("<< vec1.x <<", "<< vec1.y <<", "<< vec1.z <<")"<<endl;

    vector a(1,3,0);
    vector b = a.get_normal_2d();
    vector c(a,b);
    cout << "vector a: (" << a.x <<", "<< a.y <<", "<< a.z <<")\n"
    << "vector b: (" << b.x <<", "<< b.y <<", "<< b.z <<")\n"
    << "vector c: (" << c.x <<", "<< c.y <<", "<< c.z <<")" << endl;

    return 0;
}