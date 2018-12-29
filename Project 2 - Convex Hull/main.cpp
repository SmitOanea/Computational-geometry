#include <bits/stdc++.h>

using namespace std;

/**
    Given 4 distinct 2d points( A1, A2, A3,A4).
    Find subsets I,J such as:
      I U J = {A1, A2, A3, A4}
      I intersect J = empty set
      convex_hull(I) intersect convex_hull(J) != empty set
*/

const double epsilon=0.00000001;

struct point_2d
{
    double x,y;

    bool operator ==(point_2d &other)
    {
        return (x==other.x && y==other.y);
    }

    friend istream &operator>>(istream &in,point_2d &Point);
    friend ostream &operator<<(ostream &out,point_2d &Point);
};

istream &operator>>(istream &in, point_2d &Point)
{
    in>>Point.x>>Point.y;
    return in;
}

ostream &operator<<(ostream &out,point_2d &Point)
{
    out<<Point.x<<" "<<Point.y;
    return out;
}

double Determinant(point_2d P, point_2d Q, point_2d R)
{
    return  Q.x*R.y + P.x*Q.y + R.x*P.y
         -( Q.x*P.y + P.x*R.y + R.x*Q.y);
}

bool Between(point_2d A,point_2d B, point_2d C)
{
    ///says if B is between A and C, knowing that A,B,C are collinear
    double dist1,dist2,dist3;
    dist1 = sqrt((A.x - B.x)*(A.x - B.x) +
           (A.y - B.y)*(A.y - B.y));
    dist2 = sqrt((C.x - B.x)*(C.x - B.x) +
           (C.y - B.y)*(C.y - B.y));
    dist3 = sqrt((C.x - A.x)*(C.x - A.x) +
           (C.y - A.y)*(C.y - A.y));
    if(abs(dist1 + dist2 - dist3) < epsilon)
        return true;
    return false;
}

void JarvisMarch(point_2d A[],point_2d res[],int &indres)
{
    int i;
    double xmax=A[1].x,ymax=A[1].y;
    int poz=1;
    for(i=1;i<=4;++i)
        if(A[i].x > xmax)
        {
            xmax = A[i].x;
            poz=i;
        }
        //else
            //if(A[i].x==xmax && A[i].y>A)
    swap(A[1],A[poz]);

    point_2d current,next_point,P;
    current = A[1];
    next_point = A[2];
    indres = 0;
    while(!(next_point==A[1]))
    {
        next_point = A[1];
        if(next_point == current)
            next_point == A[2];
        for(i=1;i<=4;++i)
        {
            P = A[i];
            double det = Determinant(current,next_point,P);
            if(det < 0)///P is to the right
                next_point = P;
            if(abs(det) < epsilon)///they are collinear
                if(Between(current, next_point, P))
                    next_point = P;
        }
        res[++indres] = next_point;
        current = next_point;
    }
}

int main()
{
    int i,j;
    point_2d A[5], res[5];
    int indres=0;
    ifstream fin("date.in");
    for(i=1;i<=4;++i)
        fin>>A[i];
    fin.close();

    JarvisMarch(A,res,indres);
    if(indres==4)
    {
        cout<<"I={"<<res[1]<<", "<<res[3]<<"}\n";
        cout<<"I={"<<res[2]<<", "<<res[4]<<"}\n";
    }

    point_2d P;
    if(indres==3)
    {
        for(i=1;i<=4;++i)
        {
            P = A[i];
            bool ok=true;
            for(j=1;j<=3;++j)
                if(res[j]==P)
                    ok=false;
            if(ok)
            {
                cout<<"I={"<<P<<"}\n";
                cout<<"J={"<<res[1]<<", "<<res[2]<<", "<<res[3]<<"}\n";
            }
        }
    }
    if(indres==2)
    {
        cout<<"I={"<<res[1]<<", "<<res[2]<<"}\n";
        cout<<"J={";
        for(i=1;i<=4;++i)///search foar a point that is not on the convex hull
        {
            P = A[i];
            bool ok=true;
            for(j=1;j<=2;++j)
                if(res[j]==P)
                    ok=false;
            if(ok)
            {
                cout<<P<<", ";
            }
        }
        cout<<"}\n";
    }
    return 0;
}
