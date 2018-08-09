A C++ library containing convenience methods for initializing UDP sockets and transmitting data.  
Can be compiled with both GCC (cmake) and Visual Studio Build Tools.

Also contains user programs for measuring the round-trip delay between two hosts.

The API documentation can be found [here](https://tbs-ualberta.github.io/data_transmission/classdata__transmission.html).

**Installation:**
- `data_transmission`-library (builds with both GCC and Visual Studio):
```
git clone https://github.com/tbs-ualberta/data_transmission.git  
cd data_transmission
chmod u+x ./install_data_transmission.sh && sudo ./install_data_transmission.sh
```
- `measure_delay` user program (only builds with GCC):
  - Dependencies:
    - https://github.com/tdl-tbslab/Timer  
    - https://github.com/funcman/fCSV  
  - 1. Install above dependencies
  - 2. `chmod u+x ./install_measure_delay.sh && sudo ./install_measure_delay.sh`
