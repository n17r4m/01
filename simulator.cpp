#include <iostream>

using namespace std;

char   M; // the error model used: “I” for Independent, “B” for Burst.
int    A; // the feedback time, say, 50 bit time units.
int    K; // the number of blocks. Choose K such that F is a multiple of K. K = 0, 1, 2, 10, 40, 100, 400, 1000.
int    F; // the size of a frame, say, 4000 bits.
double e; // the probability of a bit in error. e = 0.0001, 0.0003, 0.0005, 0.0007, 0.001.
int    B; // burst length.  0 for the independent model.  For the burst model, set this to 50 and 500 bit times.
int    N; // non-burst length.  0 for the independent model.  For the burst model, set this to 5000 and 1000 bit times.
int    R; // the length of the simulation (in bit time units), say, 5,000,000 bit time units. R should be long enough for stable results.
int    T; // the number of trials (say, 5), followed by seeds for the trials.

void setArgs(int argc, char** argv){
    if (argc != 9) {
        cout << "Requires 9 input arguments. M A K F e B N R T" << endl;
        // explode and exit here
    } else {
        cout << argv[2] << endl;
        //M = argv[2];
    }
}

int main (int argc, char** argv) {  
    setArgs(argc, argv);
    cout << "Hello Cmput 313 Assignment 1!\n";
    return 0;
}