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



    Point O(0,0,0);
    Vector n(0,1,0);
    Point M(1,-1,1);

    Point M2 = M.projectOnPlan(O, n);
    std::cout << M2 << std::endl;



}