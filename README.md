# A simple test of hls4ml with QuartusHLS

This repository contains a minimal example to produce FPGA firware to evaluate a 1-layer neural net, using Quartus HLS.
Adapted from hls4ml.

The test configuration is specified in `myproject_test.cpp` while the firmware implementation can be found in the `firmware` folder.  After seeing up the quartus tools, the project is compiled doing
```
make myproject-fpga
./myproject-fpga
```
The report subsequently generated can be found in the `myproject-fpga.prj/reports/` folder.
