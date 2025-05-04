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
    cout << "\n\n";

    // constructing an example vector
    vector vec(1,2,3);
    cout << "vector coord: " << "("<< vec.x <<", "<< vec.y <<", "<< vec.z <<")"<<endl;

    return 0;
}