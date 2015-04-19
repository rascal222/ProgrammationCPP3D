//
// Created by sbeugnon on 30/03/15.
//

#include <iostream>
#include "TopoMesh.h"
#include "../core/Axis.hpp"
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

float *TopoMesh::getPointNormals() {
    float* norms = new float[3*getPoints().size()];
    for(int i=0;i<getPoints().size();++i)
    {
        prog_3D::Vector n = getPoints().at(i)->getNormal();
        norms[i+0] =n.getX();
        norms[i+1] =n.getY();
        norms[i+2] =n.getZ();
    }
    return norms;
}

void TopoMesh::mergePoint(TopoPoint *p1, TopoPoint *p2) {
    std::vector<TopoPoint*> s = p1->getNeighbours();

    auto f = std::find(s.begin(),s.end(),p2);
    if(f==s.end())
        return;

    std::vector<TopoFace*> face1 = p1->getFaces();
    std::vector<TopoFace*> face2 = p2->getFaces();
    face1.insert(face1.end(),face2.begin(),face2.end());
    std::sort(face1.begin(),face1.end());
    face1.erase(std::unique(face1.begin(),face1.end()),face1.end());

    //Can be merge
    std::vector<TopoEdge*> edge1 = p1->getEdges();
    std::vector<TopoEdge*> edge2 = p2->getEdges();
    //TODO GET EDGE WITH P1/P2 AND RETRIEVE ONE OR TWO FACES

    TopoEdge* commonEdge=nullptr;
    for(TopoEdge* te : edge1)
    {
        if(te->havePointsIgnoreOrder(p1,p2)){ commonEdge = te; break;}
    }

    if(commonEdge==nullptr)
        return;

    //Unregister common edge of edge list
    std::remove_if(edges.begin(),edges.end(),[commonEdge](TopoEdge* te){return te==commonEdge;});
    //Unregister side face(s) of face list
    for(TopoFace* tf : commonEdge->getFaces())
        std::remove_if(faces.begin(),faces.end(), [tf](TopoFace *tf2) { return tf2 == tf; });
    //Unregister p1 and p2 of point list
    std::remove_if(points.begin(),points.end(),[p1,p2](TopoPoint* tp){return tp==p1||tp==p2;});


    std::vector<TopoPoint*> otherTwo;
    TopoPoint* tp = commonEdge->getFaces().at(0)->getThirdPoint(p1,p2);
    if(tp!= nullptr)
        otherTwo.push_back(tp);
    if(commonEdge->getFaces().size()==2)
    {
        tp = commonEdge->getFaces().at(1)->getThirdPoint(p1,p2);
        if(tp!= nullptr)
            otherTwo.push_back(tp);
    }


    //Creation of new Point
    prog_3D::Vector v1(*p1,*p2);
    prog_3D::Axis axis(*p1,v1);
    prog_3D::Point mid = axis.compute(0.5);
    TopoPoint* nPoint = new TopoPoint(mid);

    //Redirect all edge from p1 to new point (except p1,p2)
    for(TopoEdge* te: edge1) {
        if(te!=commonEdge) {
            te->replace(p1,nPoint);
        }
    }
    //Redirect all edge from p2 to new point (except p1,p2)
    for(TopoEdge* te: edge2) {
        if(te!=commonEdge) {
            te->replace(p2,nPoint);
        }
    }

    std::vector<TopoFace*> facesToRemoves;
    for(TopoFace* tf : commonEdge->getFaces()) {
        facesToRemoves.push_back(tf);
        for (TopoEdge *te : tf->getEdges()) {
            te->removeFace(tf);
        }
    }

    for(TopoPoint* tp : otherTwo) {
        std::vector<TopoEdge*> edges_of_point = tp->getEdges();
        std::remove_if(edges_of_point.begin(), edges_of_point.end(),[edges_of_point,nPoint,tp](TopoEdge* te){return ! (te->havePointsIgnoreOrder(nPoint,tp));});
        if(edges_of_point.size()==2) {
            if(edges_of_point.at(1)->getFaces().size()>0)
                edges_of_point.at(0)->addFace(edges_of_point.at(1)->getFaces().at(0));
            TopoEdge* toRemove = edges_of_point.at(1);
            //REMOVE EDGE
            tp->removeEdge(toRemove);
            //Unregister edge of edge list
            std::remove_if(edges.begin(),edges.end(),[toRemove](TopoEdge* te){return toRemove==te;});
        }
    }

    //Register new point in point list
    points.push_back(nPoint);
    while(!facesToRemoves.empty()) {
        TopoFace* tf = facesToRemoves.back();
        facesToRemoves.pop_back();
        delete tf;
    }

    p1->removeEdge(commonEdge);
    p2->removeEdge(commonEdge);

    //CLEANUP
    delete commonEdge;
    delete p1;
    delete p2;

    //TODO RECOMPUTE NORMALES FOR ALL TRIANGLES
    for(TopoFace* tf : faces) {
        prog_3D::Vector att = tf->getNormal();
        prog_3D::Vector newV = tf->computeNormal();
        att.normalize();
        newV.normalize();
        double b = att.getAngle(newV);
        if(! (b== 0 || b==M_PI)) {
            if(b/M_PI*180 >= 90) {
                newV*=-1;
                tf->setNormal(newV);
            }
            else
                tf->setNormal(newV);
        }

    }

    //TODO MERGE FACES
    std::vector<TopoFace*> toRemove;
    for(unsigned int i=0;i<faces.size();++i) {
        for (unsigned int j = i + 1; j < faces.size(); ++j) {

            std::vector<TopoPoint *> vectorOfF1 = faces.at(i)->getVertices();

            std::vector<TopoPoint *> vectorOfF2 = faces.at(j)->getVertices();

            int cpt = 0;
            for (TopoPoint *tp4 : vectorOfF2) {
                if (std::find(vectorOfF1.begin(), vectorOfF1.end(), tp4) != vectorOfF1.cend())
                    cpt++;
            }
            if(cpt==3) {
                //same face
                //remove one
                if(std::find(toRemove.begin(),toRemove.end(),faces.at(j))!=toRemove.end())
                    toRemove.push_back(faces.at(j));
            }

        }

    }

    while(!toRemove.empty()) {
        std::cout << "found one"<<std::endl;
        TopoFace* s2 = toRemove.back();
        toRemove.pop_back();
        for(TopoEdge* topoEdge : s2->getEdges()) {
            topoEdge->removeFace(s2);
        }
        std::remove_if(faces.begin(),faces.end(),[s2](TopoFace* tf){return tf==s2;});
        delete s2;
    }


}

