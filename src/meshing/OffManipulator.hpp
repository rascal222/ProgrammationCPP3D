//
// Created by sbeugnon on 23/03/15.
//

#ifndef _PROGRAMMATION3D_OFFMANIPULATOR_H_
#define _PROGRAMMATION3D_OFFMANIPULATOR_H_


#include <string>
#include <fstream>
#include <iostream>
#include "Mesh.hpp"

class OffManipulator
{
public:
    OffManipulator();
    ~OffManipulator();
    Mesh read(std::string name);
    void write(std::string name,Mesh mesh);
};


#endif //_PROGRAMMATION3D_OFFMANIPULATOR_H_
