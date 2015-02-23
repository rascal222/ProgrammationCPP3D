#ifndef PROG_3D_POLAR_POINT_HPP
#define PROG_3D_POLAR_POINT_HPP

namespace prog_3D
{
    class PolarPoint
    {
    private :
        Point local;
        float angleTau;
        float anglePhi;
        float rayon;

    public:
        PolarPoint();
        PolarPoint(Point& local,float angleTau,float anglePhi,float rayon);
        virtual ~PolarPoint();

        Point& getLocal();
        float getAnglePhi();
        float getAngleTau();

        virtual Point toCartesian();
    };

}

#endif