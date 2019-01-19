main: main.o 
	g++ -std=c++11 -o main main.o -lGLEW -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

run: main 
    ./main
