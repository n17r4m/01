#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector> 
#include <stdlib.h>
#include <time.h>
#include <cmath>

using namespace std;

int    M; // the error model used: “I” (73) for Independent, “B” (66) for Burst. (in ascii)
int    A; // the feedback time, say, 50 bit time units.
int    K; // the number of blocks. Choose K such that F is a multiple of K. K = 0, 1, 2, 10, 40, 100, 400, 1000.
int    F; // the size of a frame, say, 4000 bits.
double E, e; // the starting probability of a bit in error. e = 0.0001, 0.0003, 0.0005, 0.0007, 0.001.
int    B; // burst length.  0 for the independent model.  For the burst model, set this to 50 and 500 bit times.
int    N; // non-burst length.  0 for the independent model.  For the burst model, set this to 5000 and 1000 bit times.
int    R; // the length of the simulation (in bit time units), say, 5,000,000 bit time units. R should be long enough for stable results.
int    T; // the number of trials (say, 5), followed by seeds for the trials.
vector<int> S; // the random seeds for reach trial.

void setArgs(int argc, char** argv);

// see if there is an error
bool get_error();

//temp function for indepdent trial
bool independent_error();

//temp function for burst trial
bool burst_error();

// standard deviation
double std_dev(vector<double> xi, double mean);

//temp function for get confidence intervel 
void print_ci(vector<double> xi, double mean);

//temp function for get average
double get_mean(vector<double> items);

//temp function for throughput
double get_throughput(int frames_ok);


int main (int argc, char** argv) {  
    setArgs(argc, argv);
    cout << "Hello Cmput 313 Assignment 1!\n";
    
    int frames_ok = 0;
    int frames_sent = 0;
    int average_ok = 0;
    
    vector<double> frame_transmission_averages;
    vector<double> throughputs;
    
    double mean_frame_transmissions = 0;
    double mean_throughputs = 0;
    
    for (int s : S) { // Will exec T times.
        srand(s);
        e = E;
        frames_ok = 0;
        frames_sent = 0;
        int bit_time_remaining = R;
        bool retransmit = false;
        int errors = 0;
        int FK = F/K;
        int r = (FK == 1 ? 2 : (FK >= 5 ? 4 : 3));
        
        while (bit_time_remaining > 0){
            bit_time_remaining -= F + A; // reduce time remaining by frame size.
            retransmit = false;
            
            // frame transmission
            for(int i = 0; i < K; i++){
                
                // block transmission
                errors = 0;
                for(int j = 0; j < (FK+r); j++){
                    if (get_error()){
                        ++errors;
                    }
                }
                
                // irrecoverable error in block.
                if(errors > 1){
                    retransmit = true;
                }
            }
            
            // frame sent correctly?
            if (retransmit == false){
                ++frames_ok;
            }
            
            // update total
            ++frames_sent;
            
            //update average ok frames
            average_ok = average_ok + frames_ok;
        }
        
        // trial finished.
        cout << frames_sent << " frames sent, " << frames_ok << " arrived ok." << endl;    
        
        // Get frames sent for this trial
        frame_transmission_averages.push_back(((double)frames_sent)/((double)frames_ok));
        
        // Get throughput for this trial
        throughputs.push_back(get_throughput(frames_ok));
        
        
        
    }
    
    double throughput_average = get_mean(throughputs);
    double frame_average_mean = get_mean(frame_transmission_averages);
    
    cout << frame_average_mean << " ";
    print_ci(frame_transmission_averages, frame_average_mean);
    cout << endl;
    
    cout << throughput_average << " ";
    print_ci(throughputs, throughput_average);
    cout << endl;
    
    
    
    
    return 0;
}




void setArgs(int argc, char** argv){
    cout << argc << endl;
    if (argc < 11) { 
        cout << "Requires at least 11 input arguments. M A K F e B N R T S S ..." << endl;
        exit(1);
    } else {
        M = (int)argv[1][0];
        A = stoi(argv[2]);
        K = stoi(argv[3]);
        F = stoi(argv[4]);
        E = stof(argv[5]);
        B = stoi(argv[6]);
        N = stoi(argv[7]);
        R = stoi(argv[8]);
        T = stoi(argv[9]);
        for (int i = 10; i < 10 + T; i++){
            if(i < argc){
                S.push_back(stoi(argv[i]));
            } else {
                S.push_back(S[0]);
            }
        }
    }
}

bool get_error(){
    //independent or burst
    switch(M){
        case 73: /* I */ return independent_error(); break;
        case 66: /* B */ 
        default : return burst_error(); break;
    }
}

//temp function for indepdent trial
bool independent_error(){
    
    //floating double between 0 and 1
    double bernoulli = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    
    if (bernoulli <= E){
        return true;
    }
    return false;
}


// for burst trial
int burst_period_counter = 0;
int bursting_errors = false;

bool burst_error(){
        ++burst_period_counter;
        
        if(bursting_errors && burst_period_counter > B){
            bursting_errors = false;
            burst_period_counter = 0;
        } else if (!bursting_errors && burst_period_counter > N){
            bursting_errors = true;
            burst_period_counter = 0;
        }
        
        if(bursting_errors){
        
            e = E * ((N + B) / B);
            
            //floating double between 0 and 1
            double bernoulli = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            
        
            if (bernoulli <= e){
                return true;
            }
        }
        
        return false;
}

double get_throughput(int frames_ok){
    //F * the total number of correctly recived frames / total time required to correctly recive frames
    return  (((double)F) * ((double)frames_ok)) / ((double)R);
}

double get_mean(vector<double> items){
    double sum = 0;
    for (double x : items) { 
        sum += x;
    }
    return sum / (double)items.size();
}

double std_dev(vector<double> xi, double mean){
    double square_sum = 0;
    for (double x : xi) { 
        square_sum += (x - mean) * (x - mean);   
    }
    return sqrt(square_sum / (T - 1));
}

void print_ci(vector<double> xi, double mean){
    // t-statistics from https://surfstat.anu.edu.au/surfstat-home/tables/t.php
    vector<double> t_val = {
        0, // undefined
        12.71, // df 1
        4.303,  // df 2
        3.181, // df 3
        2.776, // df 4
        2.571, // df 5
        2.447, // df 6
        2.365, // df 7
        2.306, // df 8
        2.262, // df 9
        2.228  // df 10
    };
    double s = std_dev(xi, mean);
    double ci = t_val[T-1] * s / sqrt((double)T);
    cout << "(" << mean - ci << ", " << mean + ci << ")";
}