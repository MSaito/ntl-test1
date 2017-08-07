#pragma once
#ifndef CALC_TVALUE_HPP
#define CALC_TVALUE_HPP

#include <NTL/matrix.h>
#include <NTL/GF2.h>
#include "combination.hpp"

int calc_tvalue(NTL::Mat<NTL::GF2> array[], int dim, int max_tvalue)
{
    using namespace std;
    using namespace NTL;

    uint32_t s = dim;
    uint32_t m = array[0].NumRows();
    Combination index(s);
    int t = 0;
    for (; t <= max_tvalue; t++) {
        index.reset(m - t);
#if defined(DEBUG)
        cout << "t = " << dec << t << endl;
#endif
        //vector<uint32_t> v;
        bool pass = true;
        for (;;) {
            Mat<GF2> v;
            v.SetDims(m - t, m);
#if defined(DEBUG)
            index.print(cout);
#endif
            int vrow = 0;
            for (uint32_t i = 0; i < s; ++i) {
                for (int j = 0; j < index[i]; ++j) {
                    v[vrow++] = array[i][j];
                }
            }
            if (gauss(v) != m-t) {
                pass = false;
                break;
            }
            bool hasNext = index.next();
            if (!hasNext) {
                break;
            }
        }
        if (pass) {
            return t;
        }
    }
    return -1;
}

#endif // CALC_TVALUE_HPP
