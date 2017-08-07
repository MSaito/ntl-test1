noinst_bindir=./
order_test_files = combination.hpp calc_tvalue.hpp

noinst_bin_PROGRAMS = order_test test_mat

order_test_SOURCES = order_test.cpp $(order_test_files)
test_mat_SOURCES = test_mat.cpp

AM_CXXFLAGS = -I../src -O3 -Wall -Wextra -D__STDC_CONSTANT_MACROS
