Point* hermiteCubicCurve(const Point& p0, const Point& p1, const Vector& v0, const Vector& v1,long nbU)
{
    Point* tab1 = new Point[nbU];
    for(long i=0;i<nbU;i++)
    {
        double u = ((double) i) *1.0 /(double)(nbU-1);

        double f1 = 2 * pow(u,3) - 3 * pow(u,2) + 1;
        double f2 = -2 * pow(u,3) + 3 * pow(u,2);
        double f3 = pow(u,3) - 2 * pow(u,2) + u;
        double f4 = pow(u,3) - pow(u,2);

        double x = f1*p0.getX() + f2*p1.getX() + f3*v0.getX() + f4*v1.getX();
        double y = f1*p0.getY() + f2*p1.getY() + f3*v0.getY() + f4*v1.getY();
        double z = f1*p0.getZ() + f2*p1.getZ() + f3*v0.getZ() + f4*v1.getZ();
        tab1[i].setX(x);
        tab1[i].setY(y);
        tab1[i].setZ(z);
    }

    return tab1;
}
