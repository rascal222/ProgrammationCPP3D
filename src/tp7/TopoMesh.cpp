//
// Created by sbeugnon on 30/03/15.
//

#include "TopoMesh.h"


TopoMesh::TopoMesh(Mesh & mesh)
{
    for(int i=0;i<mesh.points.size();++i)
    {
        TopoPoint tp(mesh.points.at(i));
        this->points.push_back(tp);
    }

    for(int i=0;i<mesh.idTriangles.size();++i)
    {
        //Look for each face
        prog_3D::IdTriangle it = mesh.idTriangles.at(i);
        TopoPoint tp1 = points.at(it.getPointId(0));
        TopoPoint tp2 = points.at(it.getPointId(1));
        TopoPoint tp3 = points.at(it.getPointId(2));

        //Store index of edge if already have it
        int index = -1;
        TopoEdge te12;
        //Edge 1
        if((index=getEdge(tp1,tp2)) != -1)
            te12 = edges.at(index);
        else
        {
            //Add new Edge
            te12.getPoints()[0] = tp1;
            te12.getPoints()[1] = tp2;
            edges.push_back(te12);
        }
        //Edge 2
        TopoEdge te23;
        if((index=getEdge(tp2,tp3)) != -1)
            te23 = edges.at(index);
        else
        {
            //Add new Edge
            te23.getPoints()[0] = tp2;
            te23.getPoints()[1] = tp3;
            edges.push_back(te12);
        }
        //Edge 3
        TopoEdge te13;
        if((index=getEdge(tp1,tp3)) != -1)
            te13 = edges.at(index);
        else
        {
            //Add new Edge
            te13.getPoints()[0] = tp1;
            te13.getPoints()[1] = tp3;
            edges.push_back(te12);
        }
        //Face
        TopoFace tf(te12,te23,te13);
        te12.getFaces().push_back(tf);
        te13.getFaces().push_back(tf);
        te23.getFaces().push_back(tf);
        this->faces.push_back(tf);
    }
}

TopoMesh::~TopoMesh() {
}

bool TopoMesh::haveEdge(TopoPoint& p1,TopoPoint& p2)
{
    return getEdge(p1,p2)!=-1;
}

int TopoMesh::getEdge(TopoPoint& p1, TopoPoint& p2)
{
    int index = 0;
    while(index < edges.size()
            && !edges.at(index).havePointsIgnoreOrder(p1,p2))
        index++;
    if(index==edges.size())
        index=-1;
    return index;
}

std::vector<prog_3D::Point> TopoMesh::computeGaussianPointCloud()
{
    std::vector<prog_3D::Point> vect;

    for(unsigned int i=0;i<points.size();++i)
    {
        prog_3D::Vector v = points.at(i).getNormal();
        v.normalize();
        prog_3D::Point p(v.getX(),v.getY(),v.getZ());
        vect.push_back(p);
    }

    return vect;
}