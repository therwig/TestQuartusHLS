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

#ifndef NNET_DENSE_H_
#define NNET_DENSE_H_

#include "nnet_common.h"
#include "HLS/hls.h"
#include "HLS/math.h"

namespace nnet {

    struct dense_config
    {
        // Internal data type definitions
        typedef float bias_t;
        typedef float weight_t;
        typedef float accum_t;

        // Layer Sizes
        static const unsigned n_in = 10;
        static const unsigned n_out = 10;

        // Resource reuse info
        static const unsigned io_type = io_parallel;
        static const unsigned reuse_factor = 1;
        static const bool store_weights_in_bram = false;
        static const unsigned n_zeros = 0;
        // partitioning arrays cyclically to go with roll factors?
    };

    template<class data_T, class res_T, typename CONFIG_T>
        void dense(
                   data_T    data[CONFIG_T::n_in],
                   res_T     res[CONFIG_T::n_out],
                   const typename CONFIG_T::weight_t  weights[CONFIG_T::n_in*CONFIG_T::n_out],
                   const typename CONFIG_T::bias_t    biases[CONFIG_T::n_out]
                   )
    {
        Product1:
        #pragma unroll
        for(int jj = 0; jj < CONFIG_T::n_out; jj++) {
            hls_register typename CONFIG_T::accum_t acc = biases[jj];
            Product2:
            #pragma unroll
            for(int ii = 0; ii < CONFIG_T::n_in; ii++) {
                data_T cache = data[ii];
                typename CONFIG_T::accum_t mult = cache * weights[ii*CONFIG_T::n_out+jj];
                acc += mult;
            }
            res[jj] = acc;
        }
    }
}

#endif
