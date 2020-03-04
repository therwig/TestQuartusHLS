#ifndef MYPROJECT_H_
#define MYPROJECT_H_

#ifndef __INTELFPGA_COMPILER__
#include "ref/ac_int.h"
#include "ref/ac_fixed.h"
#else
#include "HLS/ac_int.h"
#include "HLS/ac_fixed.h"
#endif

#include "HLS/hls.h"

// use a single type for now
typedef ac_fixed<16,6> type_t;

#define NIN 10
#define NL1 5
#define NOUT 1
// counters with minimal bits
typedef uint4 in_ctr_t;
typedef uint3 l1_ctr_t;
typedef uint2 out_ctr_t;

typedef uint6 ind_w1_t; // NIN*NL1 50 -> 64
typedef uint3 ind_w2_t; // NL1*NOUT 5 -> 8



struct inputdat {
    type_t data[NIN];
};

struct outputdat {
    type_t data[NOUT];
};


// Prototype of top level function for C-synthesis
hls_component_ii(1)
component outputdat myproject(
    inputdat input_1
);

#endif
