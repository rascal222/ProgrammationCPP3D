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
    std::string header;
    std::getline(input,header);
//    std::cout << header << std::endl;
//    if(header.compare("OFF")!=0)
//    {
//        std::cout << "Not Off Format File"<<std::endl;
//        exit(2);
//    }

    std::string values;
    std::getline(input,values);

    std::stringstream ss(values);

    std::string token;
    int pointNb,triangleNb,edgeNb=0;
    std::vector<std::string> tokens;
    while( std::getline(ss,token,' ')) {
        tokens.push_back(token);
    }

    pointNb = atoi(tokens.at(0).c_str());
    triangleNb = atoi(tokens.at(1).c_str());
    edgeNb = atoi(tokens.at(2).c_str());

    for(int i=0; i<pointNb;++i)
    {
        values.clear();
        tokens.clear();
        std::getline(input,values);

        //Tokenize in 3 double token
        unsigned pos;
        pos = values.find(' ');
        std::string first = values.substr(0, pos);
        std::string second = values.substr(pos + 1);
        pos = second.find(' ');
        std::string third = second.substr(pos+1);
        second = second.substr(0,pos);
        double val;
        tokens.push_back(first);
        tokens.push_back(second);
        tokens.push_back(third);
        std::vector<double> xyz;
        for(int k=0;k<3;++k)
        {
            std::stringstream ss2(tokens.at(k));
            if ( !( ss2 >> val ) )
            {
                std::cerr << "Not a double"<<std::endl;
                exit(3);
            }
            else
                xyz.push_back(val);
        }

        prog_3D::Point p(xyz.at(0),xyz.at(1),xyz.at(2));
        m.points.push_back(p);
    }

    for(int i=0;i<triangleNb;++i)
    {
        values.clear();
        ss.clear();
        tokens.clear();
        std::getline(input,values);
        unsigned pos;
        pos = values.find(' ');
        std::string first = values.substr(0, pos);
        std::string second = values.substr(pos + 1);
        pos = second.find(' ');
        std::string third = second.substr(pos+1);
        second = second.substr(0,pos);
        pos = third.find(' ');
        std::string four = third.substr(pos+1);
        third = third.substr(0,pos);
        double val;
        tokens.push_back(first);
        tokens.push_back(second);
        tokens.push_back(third);
        tokens.push_back(four);

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
    std::cout <<"end read"<<std::endl;
    return m;
}

void OffManipulator::write(std::string name,Mesh mesh)
{

}