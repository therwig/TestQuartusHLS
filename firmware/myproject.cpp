#include <iostream>

#include "myproject.h"

//hls-fpga-machine-learning insert cpragmas
hls_component_ii(1)
component outputdat myproject(
    inputdat input_1
) {

    hls_init_on_powerup static const type_t w1[((NIN)*(NL1))] = {0.234676495194,
                                      -0.187852725387,
                                      0.033068928868,
                                      -0.048653922975,
                                      -0.374888777733,
                                      0.646579146385,
                                      0.050021182746,
                                      0.312999308109,
                                      0.338659077883,
                                      -0.119601063430,
                                      -0.104634605348,
                                      -0.004239426926,
                                      0.065622836351,
                                      0.195937886834,
                                      0.026970012113,
                                      0.259251356125,
                                      -0.039083551615,
                                      -0.108744531870,
                                      -0.310757696629,
                                      0.134187400341,
                                      0.314697116613,
                                      0.061356659979,
                                      -0.609105169773,
                                      0.213280841708,
                                      0.030744107440,
                                      0.111724905670,
                                      0.337700664997,
                                      -0.505674958229,
                                      0.460755765438,
                                      0.144929811358,
                                      0.590391814709,
                                      -0.139502108097,
                                      0.489353597164,
                                      0.928900778294,
                                      -0.075193911791,
                                      0.106781460345,
                                      0.174838140607,
                                      0.045111805201,
                                      -0.012011735700,
                                      0.267484903336,
                                      0.217413350940,
                                      -0.053802363575,
                                      0.521336734295,
                                      0.741704106331,
                                      0.204760104418,
                                      0.189866974950,
                                      0.694896399975,
                                      -0.047084681690,
                                      -0.061241794378,
                                      -0.344885140657,
    };
    hls_init_on_powerup static const type_t w2[((NOUT)*(NL1))] = {-1.130043148994,
                                       -0.614738821983,
                                       -0.818155288696,
                                       -0.154053628445,
                                       0.280428349972,
    };
    hls_init_on_powerup static const type_t b1[NL1] = {0.842707276344,
                            0.790710926056,
                            0.649383246899,
                            0.070417419076,
                            0.408660680056,
    };
    hls_init_on_powerup static const type_t b2[NOUT] = {0.098531961441}; 

    inputdat layer_1;

    #pragma unroll
    for(l1_ctr_t j=0;j<NL1;j++){
        hls_register type_t acc = b1[j];
        #pragma unroll
        for(in_ctr_t i=0;i<NIN;i++){
	    ind_w1_t ind = i+l1_ctr_t(NL1)*j;
            type_t mult = input_1.data[i] * w1[ind];
            acc += mult;
        }
        layer_1.data[j]=acc;
    }

    outputdat o;

    #pragma unroll
    for(out_ctr_t j=0;j<NOUT;j++){
        hls_register type_t acc = b2[j];
        #pragma unroll
        for(l1_ctr_t i=0;i<NL1;i++){
	    ind_w2_t ind = i+out_ctr_t(NOUT)*j;
            type_t mult = layer_1.data[i] * w2[ind];
            acc += mult;
        }
        o.data[j]=acc;
    }

    return o;
}
