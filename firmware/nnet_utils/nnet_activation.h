//
//    rfnoc-hls-neuralnet: Vivado HLS code for neural-net building blocks
//
//    Copyright (C) 2017 EJ Kreinar
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef NNET_ACTIVATION_H_
#define NNET_ACTIVATION_H_

//#include <cmath>
#include "nnet_common.h"
#ifndef __INTELFPGA_COMPILER__
#include "ref/ac_int.h"
#include "ref/ac_fixed.h"
#include "ref/math.h"
#else
#include "HLS/ac_int.h"
#include "HLS/ac_fixed.h"
#include "HLS/math.h"
#endif

namespace nnet {

    struct activ_config
    {
        // IO size
        static const unsigned n_in = 10;

        // Internal info
        static const unsigned table_size = 512;

        // Resource reuse info
        static const unsigned io_type = io_parallel;
        static const unsigned reuse_factor = 1;

        // Internal data type definitions
        typedef ac_fixed<16,6> table_t;
        typedef ac_fixed<16,6> exp_table_t;
        typedef ac_fixed<16,6> sig_table_t;
    };

    // *************************************************
    //       RELU Activation
    // *************************************************
    template<class data_T, class res_T, typename CONFIG_T>
        void  relu(data_T data[CONFIG_T::n_in], res_T res[CONFIG_T::n_in])
    {
        #pragma unroll
        for (int ii=0; ii<CONFIG_T::n_in; ii++) {
            data_T datareg = data[ii];
            if (datareg > 0) res[ii] = datareg;
            else res[ii] = 0;
        }
    }

    // *************************************************
    //       Sigmoid Activation
    // *************************************************
    inline float sigmoid_fcn_float(float input) {
        return 1.0 / (1 + exp(-input));
    }

    template<typename CONFIG_T, int N_TABLE>
        void init_sigmoid_table(typename CONFIG_T::table_t table_out[N_TABLE])
    {
        // Default logistic sigmoid function:
        //   result = 1/(1+e^(-x))
        for (int ii = 0; ii < N_TABLE; ii++) {
            // First, convert from table index to X-value (signed 8-bit, range -8 to +8)
            float in_val = 2*8.0*(ii-float(N_TABLE)/2.0)/float(N_TABLE);
            // Next, compute lookup table function
            typename CONFIG_T::table_t real_val = sigmoid_fcn_float(in_val);
            //std::cout << "Lookup table In Value: " << in_val << " Result: " << real_val << std::endl;
            table_out[ii] = real_val;
        }
    }

    template<class data_T, class res_T, typename CONFIG_T>
        void  sigmoid(data_T data[CONFIG_T::n_in], res_T res[CONFIG_T::n_in])
    {
        // Index into the lookup table based on data
        hls_register ac_int<16> data_cache[CONFIG_T::n_in];
        New_loop:
        #pragma unroll
        for (int ii=0; ii<CONFIG_T::n_in; ii++) {
            data_cache[ii] = (data[ii] * 32).to_int();
            //16,6 (10 decimals) to 16,11 (0 decimals)
            //TODO cutting off some bits here!
        }
    
        #include "sigmoid_table.tb"

        NN_Outer:
        #pragma unroll
        for (int ii=0; ii<CONFIG_T::n_in; ii++) {
            ac_int<16> index = data_cache[ii];
            if (index < 0)   index = 0;
            if (index > CONFIG_T::table_size-1) index = CONFIG_T::table_size-1;
            res[ii] = (res_T) sigmoid_table[index];
        }
    }
}

#endif
