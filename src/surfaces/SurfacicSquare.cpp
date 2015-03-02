#include "SurfacicSquare.hpp"
#include "../curves/DeCasteljauBezierCurve.hpp"
#include "../core/GlCoreRendering.hpp"
#include <iostream>
namespace prog_3D {
    SurfacicSquare::SurfacicSquare(int nbU, int nbV) : Surface(nbU,nbV){}

    SurfacicSquare::~SurfacicSquare()
    {

    }


    std::vector<DeCasteljauBezierCurve>& SurfacicSquare::getControlCurves()
    {
        return this->curves;
    }



    std::vector<std::vector<Point>> SurfacicSquare::compute()
    {
        std::vector<std::vector<Point>> matrice;
        for(int i=0;i< getControlCurves().size();++i)
        {
            std::vector<Point> line;
            for(int u=0; u< getPointNumberForU();++u)
            {

                double u2 = (double) u / (double) (getPointNumberForU() - 1.0);
                Point p = getControlCurves().at(i).compute(u2);
                line.push_back(p);
            }
            matrice.push_back(line);
        }

        std::vector<std::vector<Point>> generated;

        for (int u = 0; u < getPointNumberForU(); ++u)
        {
            std::vector<Point> line;
            for(int i=0;i<getControlCurves().size();++i)
            {
                line.push_back(matrice.at(i).at(u));
            }
            DeCasteljauBezierCurve curve(line, getPointNumberForV());
            curve.setPointsNumber(getPointNumberForV());
            generated.push_back(curve.compute());
        }





        return generated;
    }

    std::vector<DeCasteljauBezierCurve> SurfacicSquare::compute2()
    {
        std::vector<std::vector<Point>> matrice;
        for(int i=0;i< getControlCurves().size();++i)
        {
            std::vector<Point> line;
            for(int u=0; u< getPointNumberForU();++u)
            {
                double u2 = (double) u / (double) (getPointNumberForU() - 1.0);
                Point p = getControlCurves().at(i).compute(u2);
                line.push_back(p);
            }
            matrice.push_back(line);
        }


        std::vector<DeCasteljauBezierCurve> generated;
        for(int u=0;u< getPointNumberForU();++u)
        {
            std::vector<Point> line;
            for(int i=0;i<getControlCurves().size();++i)
                line.push_back(matrice.at(i).at(u));
            DeCasteljauBezierCurve curve(line, getPointNumberForV());
            generated.push_back(curve);
        }
        return generated;
    }


    Point SurfacicSquare::compute(double u, double v)
    {

        std::vector<std::vector<Point>> points;
        for(int i=0;i< getControlCurves().size();++i)
            points.push_back(getControlCurves().at(i).getControlPoint());

        return recursive(points,u,v);
    }

    Point SurfacicSquare::recursive(std::vector<std::vector<Point>> poins2,double u, double v)
    {
        if(poins2.size()==1 && poins2.at(0).size()==1)
            return poins2.at(0).at(0);


        std::vector<std::vector<Point>> points;
        for(int i=0; i< poins2.size()-1;++i)
        {
            std::vector<Point> line;
            for(int j=0; j< poins2.at(i).size()-1;++j)
            {
                //Compute A
                Point A;
                A.setX( (1.0-u) * poins2.at(i).at(j+1).getX() + u * poins2.at(i+1).at(j+1).getX());
                A.setY( (1.0-u) * poins2.at(i).at(j+1).getY() + u * poins2.at(i+1).at(j+1).getY());
                A.setZ( (1.0-u) * poins2.at(i).at(j+1).getZ() + u * poins2.at(i+1).at(j+1).getZ());

                //Compute B
                Point B;
                B.setX( (1.0-u) * poins2.at(i).at(j).getX() + u * poins2.at(i+1).at(j).getX());
                B.setY( (1.0-u) * poins2.at(i).at(j).getY() + u * poins2.at(i+1).at(j).getY());
                B.setZ( (1.0-u) * poins2.at(i).at(j).getZ() + u * poins2.at(i+1).at(j).getZ());


                Point F;
                F.setX( (1.0-v) * B.getX() + v * A.getX());
                F.setY( (1.0-v) * B.getY() + v * A.getY());
                F.setZ( (1.0-v) * B.getZ() + v * A.getZ());
                line.push_back(F);
            }
            points.push_back(line);
        }

        return recursive(points,u,v);
    }

    void SurfacicSquare::draw(bool showPoints)
    {
        std::vector<std::vector<Point>> others= compute();
        /*
        for(int i=0;i<others.size()-1;++i)
        {
            for (int j = 0; j < others.at(0).size()-1; ++j)
            {
                Point pi = others.at(i).at(j);
                Point pi1 = others.at(i+1).at(j);
                Point pi2 = others.at(i).at(j+1);
                Point pi3 = others.at(i+1).at(j+1);
                if(showPoints) {
                    drawPoint(pi);
                    drawPoint(pi2);
                    drawPoint(pi1);
                    drawPoint(pi3);
                }
                drawLine(pi, pi1);
                drawLine(pi,pi2);
                drawLine(pi2,pi3);
                drawLine(pi1,pi3);
            }
        }*/



        drawSurface(others, showPoints);


        if(showPoints)
        drawIntermediate(showPoints);

    }


    void SurfacicSquare::drawIntermediate(bool showPoints)
    {
        std::vector<std::vector<Point>> points;
        for(int i=0;i< getControlCurves().size();++i)
        {
            points.push_back(getControlCurves().at(i).getControlPoint());
        }



        for(int u=0;u< getPointNumberForU();++u)
        {
            double u2 = (double) u / ((double)getPointNumberForU()-1.0);
            for(int v=0;v< getPointNumberForV();++v)
            {
                double v2 = (double) v / ((double)getPointNumberForV()-1.0);
                drawIntermediateRecursive(0,points,v2,u2,showPoints);
            }
        }

    }

    void SurfacicSquare::drawIntermediateRecursive(int step,std::vector<std::vector<Point>>& poins2,

            double u,double v, bool showPoints)
    {
        if(poins2.size()==1 && poins2.at(0).size()==1)
        {
            glColor3f(1.0f,1.0f,1.0f);
            //BAD POINT AT THIS TIME

            drawPoint(poins2.at(0).at(0));
            return ;
        }
        else if(poins2.size()==2 &&  poins2.at(0).size()==1)
        {

            Point F;
            F.setX( (1.0-v) * poins2.at(0).at(0).getX() + v * poins2.at(1).at(0).getX());
            F.setY( (1.0-v) * poins2.at(0).at(0).getY() + v * poins2.at(1).at(0).getY());
            F.setZ( (1.0-v) * poins2.at(0).at(0).getZ() + v * poins2.at(1).at(0).getZ());
            drawPoint(F);
            return ;
        }
        else  if(poins2.size()==1 &&  poins2.at(0).size()==2)
        {
            Point F;
            F.setX( (1.0-v) * poins2.at(0).at(0).getX() + v * poins2.at(0).at(1).getX());
            F.setY( (1.0-v) * poins2.at(0).at(0).getY() + v * poins2.at(0).at(1).getY());
            F.setZ( (1.0-v) * poins2.at(0).at(0).getZ() + v * poins2.at(0).at(1).getZ());
            drawPoint(F);
            return;
        }

        if(step==0)
            glColor3f(1.0f,.0f,.0f);
        else if(step==1)
            glColor3f(.0f,1.0f,.0f);
        else if(step==2)
            glColor3f(.0f,.0f,1.0f);
        else if(step==3)
            glColor3f(1.0f,1.0f,.0f);
        else if(step==4)
            glColor3f(1.0f,.0f,1.0f);
        else if(step==5)
            glColor3f(.0f,1.0f,1.0f);
        else if(step==6)
            glColor3f(1.0f,.0f,.50f);

        std::vector<std::vector<Point>> points;
        for(int i=0; i< poins2.size()-1;++i)
        {
            std::vector<Point> line;
            for(int j=0; j< poins2.at(i).size()-1;++j)
            {
                //Compute A
                Point A;
                A.setX( (1.0-u) * poins2.at(i).at(j+1).getX() + u * poins2.at(i+1).at(j+1).getX());
                A.setY( (1.0-u) * poins2.at(i).at(j+1).getY() + u * poins2.at(i+1).at(j+1).getY());
                A.setZ( (1.0-u) * poins2.at(i).at(j+1).getZ() + u * poins2.at(i+1).at(j+1).getZ());


                //Compute B
                Point B;
                B.setX( (1.0-u) * poins2.at(i).at(j).getX() + u * poins2.at(i+1).at(j).getX());
                B.setY( (1.0-u) * poins2.at(i).at(j).getY() + u * poins2.at(i+1).at(j).getY());
                B.setZ( (1.0-u) * poins2.at(i).at(j).getZ() + u * poins2.at(i+1).at(j).getZ());


                Point F;
                F.setX( (1.0-v) * B.getX() + v * A.getX());
                F.setY( (1.0-v) * B.getY() + v * A.getY());
                F.setZ( (1.0-v) * B.getZ() + v * A.getZ());
                line.push_back(F);

            }
            points.push_back(line);
        }

        drawSurface(points, showPoints);
        drawIntermediateRecursive(step+1,points,u,v,showPoints);
    }



    void SurfacicSquare::draw()
    {
        draw(false);
    }

}