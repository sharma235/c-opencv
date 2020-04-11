# c-opencv
opencv project using c++

This is c++ program made with opencv. To install opencv in ubuntu run following commands-
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install libopencv-dev

After than compile the main.cpp file using following command-
g++ main.cpp -o main `pkg-config --cflags --libs opencv`
Then execute binary file using- 
./main
