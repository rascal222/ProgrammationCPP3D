#include "../core/Vector.hpp"
#include "../core/Point.hpp"
#include <iostream>

using namespace prog_3D;

int main()
{
    Point A(2,1,0);
    Point B(4,1,0);
    Point C(3.5,3.5,0);



    Point C2 =C.projectOnLine(A,B);

<<<<<<< HEAD
    std::cout << C2 << std::endl;
    Vector v2(1,0,0);
    Vector t = Vector::UP * 3.0;
    std::cout << t << std::endl;
    t*=2;
    std::cout << t << std::endl;

    Point O(0,0,0);
    Vector n(0,1,0);
    Point M(1,1,1);
=======

    Point O(0,0,0);
    Vector n(0,1,0);
    Point M(1,-1,1);
>>>>>>> 6b2255602677cec1483f7c52bc496c591eafafee

    Point M2 = M.projectOnPlan(O, n);
    std::cout << M2 << std::endl;



}