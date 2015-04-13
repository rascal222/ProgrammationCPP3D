//
// Created by beugnon on 13/04/15.
//

#include "FigureConverter.hpp"
#include <iostream>


Mesh FigureConverter::cylinderToMesh(prog_3D::Cylinder& cylinder)
{
    Mesh m;
    std::vector<std::vector<prog_3D::Point>> matrix = cylinder.compute();
    for(unsigned int i=0;i<matrix.size();++i)
        m.points.insert(m.points.end(),matrix.at(i).begin(),matrix.at(i).end());
    int offset = matrix.at(0).size();
    std::vector<int> idTri;
    for(int i=0;i< offset;++i)
    {
//
//            prog_3D::glPoint(m.points.at(i));
        idTri.push_back(i);
        if(idTri.size()==3)
        {
            prog_3D::IdTriangle tri(idTri.at(0),idTri.at(1),idTri.at(2));
            m.idTriangles.push_back(tri);
            idTri.erase(idTri.begin());//Remove first
        }
//            prog_3D::glPoint(m.points.at(offset+i));
        idTri.push_back(offset+i);
        if(idTri.size()==3)
        {
            prog_3D::IdTriangle tri(idTri.at(0),idTri.at(1),idTri.at(2));
            m.idTriangles.push_back(tri);
            idTri.erase(idTri.begin());//Remove first
        }
    }
//        prog_3D::glPoint(0);
    idTri.push_back(0);
    prog_3D::IdTriangle tri(idTri.at(0),idTri.at(1),idTri.at(2));
    m.idTriangles.push_back(tri);
    idTri.erase(idTri.begin());
//        prog_3D::glPoint(offset);
    idTri.push_back(offset);
    prog_3D::IdTriangle tri2(idTri.at(0),idTri.at(1),idTri.at(2));
    m.idTriangles.push_back(tri2);


    return m;
}


Mesh FigureConverter::sphereToMesh(prog_3D::Sphere& sphere)
{
    Mesh m;
    std::vector<std::vector<prog_3D::Point>> matrix = sphere.compute();

    for(unsigned int i=0;i<matrix.size();++i)
        m.points.insert(m.points.end(),matrix.at(i).begin(),matrix.at(i).end());

    std::vector<int> idTri;

    int max_parallels = matrix.size()-2;
    int max_meridians = matrix.at(1).size();


    //NORTH POLE
    idTri.push_back(0);
    for(int k=0;k<max_meridians;++k)
    {
        //parallel one //all meridians
        idTri.push_back(1+k);
        if(idTri.size()==3)
        {
            prog_3D::IdTriangle tri(idTri.at(0),idTri.at(1),idTri.at(2));
            m.idTriangles.push_back(tri);
            int id = idTri.back();
            idTri.pop_back();
            idTri.pop_back();
            idTri.push_back(id);
        }
    }
    {
        idTri.push_back(1);
        prog_3D::IdTriangle tri(idTri.at(0), idTri.at(1), idTri.at(2));
        m.idTriangles.push_back(tri);
    }
    idTri.clear();

    std::cout << "[DONE] NORTH POLE"<<std::endl;

    //SOUTH POLE
//    glPoint(matrix.at(matrix.size()-1).at(0));
    idTri.push_back(m.points.size()-1);
    for(int k=0;k<max_meridians;++k)
    {
//      glPoint(matrix.at(matrix.size()-2).at(k));
//        m.points.at(1+ (max_parallels + 1) * max_meridians + k);
        idTri.push_back(1 + (max_parallels-1) * max_meridians + k);
        if(idTri.size()==3)
        {
            prog_3D::IdTriangle tri(idTri.at(0),idTri.at(1),idTri.at(2));
            m.idTriangles.push_back(tri);
            int id = idTri.back();
            idTri.pop_back();
            idTri.pop_back();
            idTri.push_back(id);
        }

    }
    {
        idTri.push_back(1 + (max_parallels-1) * max_meridians );
        prog_3D::IdTriangle tri(idTri.at(0), idTri.at(1), idTri.at(2));
        m.idTriangles.push_back(tri);
    }
//    glPoint(matrix.at(matrix.size()-2).at(0));
//    glPoint(m.points.at(1+(max_parallels)*max_meridians));
    idTri.clear();
    std::cout << "[DONE] SOUTH POLE"<<std::endl;

    for(unsigned int i = 0;i < max_meridians; ++i)
    {
        for (unsigned int k = 0; k < max_parallels; ++k)
        {
//            glPoint(matrix.at(k).at(i)); m.points.at(1+k*(max_parallels*max_meridians)+i);
//            glPoint(matrix.at(k).at((i+1)));

            std::cout << "[DONE] INNER 0"<<std::endl;
            idTri.push_back( k *max_meridians + i + 1);
            std::cout << "[DONE] INNER 1"<<std::endl;

            if(idTri.size()==3)
            {
                prog_3D::IdTriangle tri(idTri.at(0),idTri.at(1),idTri.at(2));
                m.idTriangles.push_back(tri);
                idTri.erase(idTri.begin());//Remove first
            }

            std::cout << "[DONE] INNER 2"<<std::endl;
            idTri.push_back( k *max_meridians + i+2);


            std::cout << "[DONE] INNER 3"<<std::endl;
            if(idTri.size()==3)
            {
                prog_3D::IdTriangle tri(idTri.at(0),idTri.at(1),idTri.at(2));
                idTri.erase(idTri.begin());//Remove first
            }
        }
        idTri.clear();
    }
    std::cout << "[DONE] INNER"<<std::endl;
    idTri.clear();
    //TODO INVERSION DES FACES
    for(unsigned int i = 0;i < max_meridians; ++i)
    {
        for (unsigned int k = 0; k < max_parallels; ++k)
        {
            std::cout << "[DONE] INNER 0"<<std::endl;
            idTri.push_back( (k) *max_meridians + i + 1);

            std::cout << "[DONE] INNER 1"<<std::endl;

            if(idTri.size()==3)
            {
                prog_3D::IdTriangle tri(idTri.at(0),idTri.at(1),idTri.at(2));
                m.idTriangles.push_back(tri);
                idTri.erase(idTri.begin());//Remove first
            }

            std::cout << "[DONE] INNER 2"<<std::endl;
            idTri.push_back( (k+1) *max_meridians + i + 0);


            std::cout << "[DONE] INNER 3"<<std::endl;
            if(idTri.size()==3)
            {
                prog_3D::IdTriangle tri(idTri.at(0),idTri.at(1),idTri.at(2));
                idTri.erase(idTri.begin());//Remove first
            }
        }
        idTri.clear();
    }

    return m;
}