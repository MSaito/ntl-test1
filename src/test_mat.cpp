#include <NTL/mat_GF2.h>
#include <NTL/matrix.h>
#include <NTL/GF2.h>
#include <NTL/version.h>

using namespace NTL;
using namespace std;

int main(int argc, char * argv[])
{
    Mat<GF2> mat;
    mat.SetDims(2, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << "mat.put(i, j, 1)" << endl;
            mat.put(i, j, 1);
            cout << "mat.get(i, j) = " << mat.get(i, j) << endl;
            cout << "mat.put(i, j, 0)" << endl;
            mat.put(i, j, 0);
            cout << "mat.get(i, j) = " << mat.get(i, j) << endl;
        }
    }
    mat.put(0,0,1);
    mat.put(0,1,1);
    mat.put(1,0,1);
    mat.put(1,1,1);
    cout << mat << endl;
}
