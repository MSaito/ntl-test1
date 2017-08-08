#include <inttypes.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cerrno>
#include <NTL/lzz_p.h>
//#include <NTL/zz_p.h>
//#include <NTL/matrix.h>
#include <vector>
#include "calc_tvalue_fp.hpp"

using namespace std;
using namespace NTL;

//#define DEBUG

namespace {
    bool make_mat(Mat<zz_p>& mat, uint64_t num);
    size_t calc_order(Mat<zz_p>& mat, size_t max);
}

int main(int argc, char * argv[])
{

    if (argc < 5) {
        cout << argv[0] << " p s m max_tvalue" << endl;
        return -1;
    }
    errno = 0;
    int p = strtoul(argv[1], NULL, 10);
    int s = strtoul(argv[2], NULL, 10);
    int m = strtoul(argv[3], NULL, 10);
    int max_tvalue = strtoul(argv[4], NULL, 10);
    if (errno) {
        cout << "p, s, m and max_tvalue should be numbers" << endl;
        return -1;
    }
    cout << "# p = " << dec << p << endl;
    cout << "# s = " << dec << s << endl;
    cout << "# m = " << dec << m << endl;
    cout << "# max_tvalue = " << dec << max_tvalue << endl;
    zz_p::init(p);
#if defined(DEBUG)
    cout << "main step 0.1" << endl;
#endif
    int64_t max = pow(p, m * m);
    Mat<zz_p> mat;
    mat.SetDims(m, m);
    Mat<zz_p> array[s];
#if defined(DEBUG)
    cout << "main step 0.2" << endl;
#endif
    vector<vector<int> >to;
    to.resize(max_tvalue + 1);
#if defined(DEBUG)
    cout << "main step 1" << endl;
#endif
    for (int i = 0; i <= max_tvalue; i++) {
        to[i].resize(max);
        for (int64_t j = 0; j < max; j++) {
            to[i][j] = 0;
        }
    }
#if defined(DEBUG)
    cout << "main step 2" << endl;
#endif
    for (int64_t cnt = 1; cnt < max; cnt++) {
        if (!make_mat(mat, cnt)) {
            continue;
        }
        int order = calc_order(mat, max - 1);
        if (order < s) {
            continue;
        }
        array[0] = mat;
        for (int j = 1; j < s; j++) {
            array[j] = array[j - 1] * mat;
        }
        int tvalue = calc_tvalue(array, s, max_tvalue);
        if (tvalue > max_tvalue || tvalue < 0) {
            continue;
        }
        to[tvalue][order] += 1;
        if (tvalue == 0 && order == max -1) {
            cout << "found!" << endl;
            cout << "cnt = " << dec << cnt << endl;
            cout << "tvalue = " << dec << tvalue << endl;
            cout << "order = " << dec << order << endl;
            cout << mat;
        }
    }
    cout << "(tvalue, order) = cnt" << endl;
    for (int i = 0; i <= max_tvalue; i++) {
        for (int64_t j = 0; j < max; j++) {
            if (to[i][j] == 0) {
                continue;
            }
            cout << "(" << dec << i << ","
                 << j << ") = " << to[i][j] << endl;
        }
    }
    return 0;
}

namespace {
    bool make_mat(Mat<zz_p>& mat, uint64_t num)
    {
#if defined(DEBUG)
        cout << "start make_mat" << endl;
#endif
        //cout << "num = " << dec << num << endl;
        int p = zz_p::modulus();
        int m = mat.NumRows();
        //const uint64_t mask = ~UINT64_C(0) >> (64 - m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                zz_p z(num % p);
                num = num / p;
                mat.put(i, j, z);
            }
        }
        //cout << "make_mat 1:" << mat << endl;
        Mat<zz_p> w = mat;
        if (gauss(w) != m) {
#if defined(DEBUG)
            cout << "end make_mat" << endl;
#endif
            return false;
        }
        //cout << "make_mat 2:\n" << mat << endl;
#if defined(DEBUG)
        cout << "end make_mat" << endl;
#endif
        return true;
    }

    size_t calc_order(Mat<zz_p>& mat, size_t max)
    {
        Mat<zz_p> w = mat;
        for (size_t i = 1; i <= max; i++) {
            w = w * mat;
            if (w == mat) {
                return i;
            }
        }
        return max;
    }
}
