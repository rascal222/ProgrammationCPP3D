//
// Created by sbeugnon on 23/03/15.
//

#include "OffManipulator.hpp"
#include <sstream>

OffManipulator::OffManipulator(){}

OffManipulator::~OffManipulator(){}

Mesh OffManipulator::read(std::string name)
{
    Mesh m;

    std::ifstream input;
    input.open(name,std::ios::in);
    if(!input.is_open())
    {
        std::cout << "File not found" <<std::endl;
        exit(0);
    }
    std::cout << "IS OPEN" <<std::endl;
    std::string header;
    std::getline(input,header);
    if(header.compare("OFF")!=0)
    {
        std::cout << "Not Off Format File"<<std::endl;
        exit(2);
    }
    std::cout << "Recognized files" << std::endl;

    std::string values;
    std::getline(input,values);
    std::cout << "values : "<<values<<std::endl;

    std::stringstream ss(values);

    std::string token;
    int pointNb,triangleNb,edgeNb=0;
    std::vector<std::string> tokens;
    while( std::getline(ss,token,' ')) {
        tokens.push_back(token);
    }
    if(tokens.size()>3)
        std::cout << "More than 3 tokens"<<std::endl;

    pointNb = atoi(tokens.at(0).c_str());
    triangleNb = atoi(tokens.at(1).c_str());
    edgeNb = atoi(tokens.at(2).c_str());

    for(int i=0; i<pointNb;++i)
    {
        values.clear();
        ss.clear();
        tokens.clear();
        std::getline(input,values);
        ss << values;
        while( std::getline(ss,token,' '))
        {
            tokens.push_back(token);
        }
        if(tokens.size() == 3)
        {
            std::vector<double> xyz;
            for(int k=0;k<3;++k)
            {
                std::stringstream ss2(tokens.at(k));
                double val;
                if ( !( ss2 >> val ) )
                {
                    std::cerr << "Not a double"<<std::endl;
                    exit(3);
                }
                else
                {
                    xyz.push_back(val);
                }

            }
            prog_3D::Point p(xyz.at(0),xyz.at(1),xyz.at(2));
            m.points.push_back(p);
        }

    }

    for(int i=0;i<triangleNb-1;++i)
    {
        values.clear();
        ss.clear();
        tokens.clear();
        std::getline(input,values);
        //3 8 3758 9 //nb points
        ss << values;
        std::cout << values<<std::endl;
        while( std::getline(ss,token,' '))
        {
            tokens.push_back(token);
        }
        int n=atoi(tokens.at(0).c_str());

        if(n==3)//Triangle
        {
            std::array<int,3> tab;
            tab[0] = atoi(tokens.at(1).c_str());
            tab[1] = atoi(tokens.at(2).c_str());
            tab[2] = atoi(tokens.at(3).c_str());
            prog_3D::IdTriangle tri(tab);
            m.idTriangles.push_back(tri);
        }
    }
    return m;
}

void OffManipulator::write(std::string name,Mesh mesh)
{

}