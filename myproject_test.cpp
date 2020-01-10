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
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "firmware/myproject.h"

#define NTEST 10

int main(int argc, char **argv)
{
  // insert test data
  hls_register inputdat input_1[NTEST];
  hls_register outputdat output_1[NTEST];

  for (int i = 0; i < NTEST; ++i) {
    for(int j = 0; j < NIN; ++j) {
      // junk test data for now
      input_1[i].data[j] = 0.3;
    }
    // run once for each test iteration
    ihc_hls_enqueue(&output_1[i], myproject, input_1[i]);
  }
  ihc_hls_component_run_all(myproject);


  // check output
  for (int i = 0; i < NTEST; ++i) {
    std::cout << "Input: ";
    for(int j = 0; j < NIN; j++) {
      std::cout << input_1[i].data[j] << " ";
    }
    std::cout << ";";
    std::cout << "Output: ";
    for(int j = 0; j < NOUT; j++) {
      std::cout << output_1[i].data[j] << " ";
    }
    std::cout << ";";
    std::cout << std::endl;
  }

  return 0;
}
