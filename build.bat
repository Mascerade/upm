@ECHO OFF
cd C:\Users\Jason\Documents\UPM\build
g++ -std=c++11 -c ../src/token.cpp ../src/combination.cpp ../src/common.cpp ../src/product.cpp ../src/main.cpp -I ../include/
g++ --std=c++11 -o ../bin/main.exe ./token.o ./combination.o ./common.o ./product.o ./main.o
ECHO Finished compiling and creating executable with no error
