noinst_bindir=./
order_test_files = combination.hpp calc_tvalue.hpp clac_tvalue_fp.hpp

noinst_bin_PROGRAMS = order_test order_test_I order_test_fp test_mat

order_test_SOURCES = order_test.cpp $(order_test_files)
order_test_I_SOURCES = order_test_I.cpp $(order_test_files)
order_test_fp_SOURCES = order_test_fp.cpp $(order_test_files)
test_mat_SOURCES = test_mat.cpp

AM_CXXFLAGS = -I../src -O3 -Wall -Wextra -D__STDC_CONSTANT_MACROS
