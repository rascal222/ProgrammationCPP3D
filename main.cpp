#include <iostream>

#include "src/core/Point.hpp"
#include "src/core/Vector.hpp"

using namespace std;

int main() {
    prog_3D::Vector zero(0,0,0);
    prog_3D::Vector x(1,0,0);
    prog_3D::Vector y(0,1,0);
    prog_3D::Vector z(0,0,1);

        cout << zero << endl;
    cout << x << endl;
    cout << y <<endl;
    cout << z << endl;



    prog_3D::Vector v(3,1,2);

    cout << "norme = " << v.norme() << endl;
    cout << "normalize"<<endl;v.normalize();
    cout << "norme = "<< v.norme() << endl;

    return 0;
}