#include "GlCoreRendering.hpp"
namespace prog_3D {
/// \brief génère un point opengl
    void glPoint(const Point &p) {
        glVertex3d(p.getX(), p.getY(), p.getZ());
    }

/// \brief dessine une instance de classe Point
    void drawPoint(const Point &p) {
        glPointSize(5);
        glBegin(GL_POINTS);
        glPoint(p);
        glEnd();
    }

    void drawPoint(Point &p, float r, float g, float b) {
        glColor3f(r, g, b);
        glBegin(GL_POINTS);
        glPoint(p);
        glEnd();
    }

    void drawPoint(Point &p, float r, float g, float b, float alpha) {
        glColor4f(r, g, b, alpha);
        glBegin(GL_POINTS);
        glPoint(p);
        glEnd();
    }

/// \brief

    void drawLine(const Point &p, const Vector &v) {
        glBegin(GL_LINES);
        glPoint(p);
        Point p2 = p.translate(v);
        glPoint(p2);
        glEnd();
    }

    void drawLine(Point &p, Point &p2) {
        glBegin(GL_LINES);
        glPoint(p);
        glPoint(p2);
        glEnd();
    }

    void drawCurve(std::vector<Point> tabPointsOfCurve, bool showPoint) {
        for (int i = 0; i < tabPointsOfCurve.size() - 1; ++i) {
            drawLine(tabPointsOfCurve.at(i), tabPointsOfCurve.at(i + 1));
            if (showPoint) {
                drawPoint(tabPointsOfCurve[i]);
                drawPoint(tabPointsOfCurve[i + 1]);
            }
        }
    }

    void drawSurface(std::vector<std::vector<Point>> vector,bool showPoint)
    {
        for(int i=0;i< vector.size()-1;++i)
        {
            for(int j=0;j<vector.at(i).size()-1;++j)
            {
                Point pij = vector.at(i).at(j);
                Point pi1j = vector.at(i+1).at(j);
                Point pij1 = vector.at(i).at(j+1);
                Point pi1j1 = vector.at(i+1).at(j+1);

                drawLine(pij, pi1j);
                drawLine(pij, pij1);

                drawLine(pij1,pi1j1);
                drawLine(pi1j, pi1j1);
                if(showPoint)
                {
                    drawPoint(pij);
                    drawPoint(pi1j);
                    drawPoint(pij1);
                    drawPoint(pi1j1);
                }

            }
        }
    }
}