# InternalEye

This is a fork of HardInfo - system monitor with GUI for Linux. HardInfo developed with GTK and C, and i want to port it to C++ and Qt5. 

At first, i will save all functionality of hardinfo, and after that will add some new features : thermal control, new benchmarks, new database of hardware, etc.

If you have any issues, pls tell me about that.

Thanks.

How to build:

1) Clone git : 

      git clone https://github.com/ZaMaZaN4iK/InternalEye.git
      
2) Create build directory :

      mkdir build
      
3) Change your directory to build :

      cd build
      
4) Run Cmake (Warning : If you have custom Qt SDK, please use : export CMAKE_PREFIX_PATH=/path/to/Qt/gcc_64/lib/cmake/ ) :

      cmake ..
      
5) If all is good, compile it (you can use make -jN, where N is number of your cores/threads + 1): 

      make
