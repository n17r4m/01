all:
	g++ simulator.cpp -std=c++11 -o simulator

clean:
	rm simulator

run:
	#           M A  K   F    e      B  N    R      T S S ...
	./simulator B 50 400 4000 0.0007 50 5000 500000 5 1 2 3 4 5
	./simulator B 50 400 4000 0.0007 50 5000 500000 5 1 2 3 4 5
	./simulator B 50 400 4000 0.0007 50 5000 500000 5 1 2 3 4 5
	./simulator B 50 400 4000 0.0007 50 5000 500000 5 1 2 3 4 5
	