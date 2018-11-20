#include <iostream>

using namespace std;

/**
    Given A1, A2, A3 points in R^3.

    a) Decide whether the points are collinear or not.
    b) If they are, write one of them as an affine combination
       of the other two.
*/

struct point_3d
{
    double x,y,z;

    bool operator ==(const point_3d &other)
    {
        return (this->x == other.x &&
                this->y == other.y &&
                this->z == other.z);
    }

    bool operator !=(const point_3d &other)
    {
        return !(*this==other);
    }
};

int main()
{
    point_3d A1,A2,A3;
    cin>>A1.x>>A1.y>>A1.z;
    cin>>A2.x>>A2.y>>A2.z;
    cin>>A3.x>>A3.y>>A3.z;

    ///Case 1: A1!=A2

    //A1, A2, A3 collinear <=> there is an a from R such that
    // A1A3 = a*A1A2
    if(A1!=A2)
    {
        double a;
        if(A1.x!=A2.y)
            a = (A3.x-A1.x)/(A2.x-A1.x);
        else
        {
            if(A1.y!=A2.y)
                a = (A3.y-A1.y)/(A2.y-A1.y);
            else
                a = (A3.z-A1.z)/(A2.z-A1.z);
        }

        if(A3.x-A1.x == a*(A2.x - A1.x) &&
           A3.y-A1.y == a*(A2.y - A1.y) &&
           A3.z-A1.z == a*(A2.z - A1.z)   )
        {
                cout<<"Yes, the points are collinear.\n";
                cout<<"A3 = "<<a<<"*A1"<<" + "<<1-a<<"*A2\n";
        }
        else
            cout<<"No, they are not collinear.\n";
        return 0;
    }
    if(A1==A2)///the points are collinear
    {
        cout<<"Yes, the points are collinear.\n";
        cout<<"A1 = 1*A2 + 0*A3\n";
    }
    return 0;
}
