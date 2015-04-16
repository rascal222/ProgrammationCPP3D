//
// Created by beugnon on 15/04/15.
//

#include <stack>
#include "Propagation.hpp"
#include <algorithm>
#include <map>
#include <functional>




int* Propagation::fullPropagation() {
    initPropagation();
    while(!passiveHull.empty())
        propagationStep();
}

void Propagation::propagationStep() {
    if(step==0)
    {
        initPropagation();
    }
    step++;
    if(passiveHull.empty())
        return;

    TopoEdge* edge = passiveHull.top();
    passiveHull.pop();
    std::function<void(int,int,TopoFace*)> recursive_coloration;

    recursive_coloration = [&](int oldColor,int newColor, TopoFace* tf)
    {
        if(oldColor==newColor)
            return;
        if(tf->getRegion() == oldColor)
        {
            tf->setRegion(newColor);
            std::vector<TopoFace*> neighs = tf->getNeighbours();
            for(unsigned long i=0;i<neighs.size();++i)
                if(neighs.at(i)->getRegion() == oldColor)
                    recursive_coloration(oldColor,newColor,neighs.at(i));
        }
    };
    if(edge->getFaces().size()>1) {
        int oldColor = edge->getFaces().at(1)->getRegion();
        int newColor = edge->getFaces().at(0)->getRegion();
        recursive_coloration(oldColor,newColor,edge->getFaces().at(1));
    }
    std::cout << "step "<<step<<" done"<<std::endl;
}


void Propagation::initPropagation() {
    std::cout << "init propagation"<<std::endl;
    for(int i=0;i<getTopoMesh()->getFaces().size();++i)
        getTopoMesh()->getFaces().at(i)->setRegion(i);

    for(int i=0;i<getTopoMesh()->getEdges().size();++i)
    {
        if(!getTopoMesh()->getEdges().at(i)->isActiveEdge(threshold,false))
        {
            passiveHull.push(getTopoMesh()->getEdges().at(i));
        }
    }
}
