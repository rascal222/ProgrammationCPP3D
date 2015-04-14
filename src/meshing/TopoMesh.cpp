//
// Created by sbeugnon on 30/03/15.
//

#include <iostream>
#include "TopoMesh.h"
#include <algorithm>

TopoMesh::TopoMesh(Mesh & mesh)
{
    std::cout <<"--------------------------------------------" <<std::endl;
    std::cout <<"------ TOPOLOGIC MESH CONSTRUCTION ---------" <<std::endl;
    std::cout <<"--------------------------------------------" <<std::endl;
    std::cout <<"--------------------------------------------" <<std::endl;
    std::cout <<"-----          ADDING POINTS        --------" <<std::endl;
    for(unsigned long i=0;i<mesh.points.size();++i)
    {
        TopoPoint* tp = new TopoPoint(mesh.points.at(i));
        this->points.push_back(tp);
    }
    std::cout <<"[DONE] Copying "<< points.size() <<" points !" <<std::endl;
    std::cout <<"--------------------------------------------" <<std::endl;
    std::cout <<"--------------------------------------------" <<std::endl;
    std::cout <<"---- ADDING TOPOLOGIC TRIANGLES   ----------" <<std::endl;

    for(unsigned long i=0;i<mesh.idTriangles.size();++i)
    {
        //Look for each face
        std::cout <<"[START]" <<" Triangle number " << i <<"" << std::endl;
        std::cout <<"[START]" <<" Converting ID to TopoPoint " << std::endl;
        prog_3D::IdTriangle it = mesh.idTriangles.at(i);
        TopoPoint* tp1 = points.at(it.getPointId(0));
        TopoPoint* tp2 = points.at(it.getPointId(1));
        TopoPoint* tp3 = points.at(it.getPointId(2));
        std::cout <<"[DONE] Converting ID to TopoPoint" <<std::endl;

        std::cout <<"[START]" <<" Creating Edges for triangle "<<i << std::endl;
        //Store index of edge if already have it
        int index;
        TopoEdge* te12;
        //Edge 1
        std::cout <<"[START]" <<" First Edge : ["<< tp1<<";"<<tp2<<"]"<< std::endl;
        index = getEdge(tp1,tp2);

        if(index != -1)
        {
            te12 = edges.at(index);
            std::cout <<"[INFO]" <<" Already Created Edge : ["<< te12->getPoints().at(0)<<";"<<te12->getPoints().at(1)<<"]"<< std::endl;
        }
        else
        {
            //Add new Edge
            std::cout <<"[INFO]" <<" New Created Edge : ["<< tp1<<";"<<tp2<<"]"<< std::endl;
            te12 = new TopoEdge(tp1,tp2);
            edges.push_back(te12);
        }

        std::cout <<"[DONE]" <<" First Edge : ["<< te12->getPoints().at(0)<<";"<<te12->getPoints().at(1)<<"]"<< std::endl;
        std::cout << "[DEBUG]" << tp1 << "-> " << tp1->getEdges().size() << std::endl;
        std::cout << "[DEBUG]" << tp2 << "-> " << tp2->getEdges().size() << std::endl;
        std::cout << "[DEBUG]" << tp3 << "-> " << tp3->getEdges().size() << std::endl;

        //Edge 2
        TopoEdge* te23;
        std::cout <<"[START]" <<" Second Edge : ["<< tp2<<";"<<tp3<<"]"<< std::endl;
        if((index=getEdge(tp2,tp3)) != -1)
        {
            te23 = edges.at(index);
            std::cout <<"[INFO]" <<" Already Created Edge : ["<< te12->getPoints().at(0)<<";"<<te12->getPoints().at(1)<<"]"<< std::endl;

        }
        else
        {
            //Add new Edge
            std::cout <<"[INFO]" <<" New Created Edge : ["<< tp1<<";"<<tp2<<"]"<< std::endl;
            te23 = new TopoEdge(tp2,tp3);
            edges.push_back(te23);
        }
        std::cout <<"[DONE]" <<" Second Edge : ["<< te23->getPoints().at(0)<<";"<<te23->getPoints().at(1)<<"]"<< std::endl;
        std::cout << "[DEBUG]" << tp1 << "-> " << tp1->getEdges().size() << std::endl;
        std::cout << "[DEBUG]" << tp2 << "-> " << tp2->getEdges().size() << std::endl;
        std::cout << "[DEBUG]" << tp3 << "-> " << tp3->getEdges().size() << std::endl;

        //Edge 3
        TopoEdge* te13;
        std::cout <<"[START]" <<" Third Edge : ["<< tp1<<";"<<tp3<<"]"<< std::endl;

        if((index=getEdge(tp1,tp3)) != -1)
        {
            te13 = edges.at(index);
            std::cout <<"[INFO]" <<" Already Created Edge : ["<< te12->getPoints().at(0)<<";"<<te12->getPoints().at(1)<<"]"<< std::endl;
        }
        else
        {
            //Add new Edge
            std::cout <<"[INFO]" <<" New Created Edge : ["<< tp1<<";"<<tp2<<"]"<< std::endl;
            te13 = new TopoEdge(tp1,tp3);
            edges.push_back(te13);
        }
        std::cout <<"[DONE]" <<" Third Edge : ["<< te13->getPoints().at(0)<<";"<<te13->getPoints().at(1)<<"]"<< std::endl;
        std::cout << "[DEBUG]" << tp1 << "-> " << tp1->getEdges().size() << std::endl;
        std::cout << "[DEBUG]" << tp2 << "-> " << tp2->getEdges().size() << std::endl;
        std::cout << "[DEBUG]" << tp3 << "-> " << tp3->getEdges().size() << std::endl;
        std::cout <<"[DONE]" <<" Creating Edges for triangle "<<i << std::endl;
        //Face
        std::cout <<"[START]" <<" Creating Face for triangle "<<i << std::endl;
        prog_3D::Vector v1(*tp1,*tp2);
        prog_3D::Vector v2(*tp1,*tp3);
        prog_3D::Vector n = v1.cross(v2);
        TopoFace* tf = new TopoFace(te12,te23,te13,n);

        this->faces.push_back(tf);
        std::cout <<"[DONE]" <<" Creating Face for triangle "<<i << std::endl;
    }
}

TopoMesh::~TopoMesh() {
}

bool TopoMesh::haveEdge(TopoPoint* p1,TopoPoint* p2)
{
    return getEdge(p1,p2)!=-1;
}

int TopoMesh::getEdge(TopoPoint* p1, TopoPoint* p2)
{
    int index = 0;
    while(index < edges.size()
            && !edges.at(index)->havePointsIgnoreOrder(p1,p2))
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
        prog_3D::Vector v = points.at(i)->getNormal();
        v.normalize();
        prog_3D::Point p(v.getX(),v.getY(),v.getZ());
        vect.push_back(p);
    }

    return vect;
}

int *TopoMesh::giveNeighboringFaceTab() {
    int* tab = new int[faces.size()*3];
    for(unsigned int i=0;i<faces.size();++i)
    {
        for(unsigned int k=0;k<3;++k)
            tab[3 * i + k]=-1;


        std::vector<TopoFace*> neigh = faces.at(i)->getNeighbours();
        for(int k=0;k<neigh.size();++k)
        {
            if(k>2)
            {
                std::cerr<< "Face has "<< neigh.size() <<" neighbours !"<<std::endl;
                break;
            }
            auto index = std::find_if(faces.begin(), faces.end(), [neigh,k](TopoFace* n){return n == neigh.at(k);});
            if(index!= faces.end())
                tab[3 * i + k] = index - faces.begin();
        }
    }
    return tab;
}
