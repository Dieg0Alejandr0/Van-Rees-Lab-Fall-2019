#include "flappingPlateOptimization.h"
#include <fstream>


int main(int argc, char * argv[]) {

    //We Populate The Float Variables
	
	//We Define Our Langrangian Coordinates
    vector<float> X = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    vector<float> Y;
    Y.assign(X.size(), 0.0);
    
    float y_0 = 0.5; //Heave amplitude
	vector<float> amplitude = {0.5, 0.5}; //a_{n}
	vector<float> phase = {-0.5*M_PI, M_PI}; //pi for phi_{n}

	int nk = 1; //Number Of Terms Of Summation
	int length = 1; //Length Of Foil We Are Modeling

	float beta_k = 1.875; //"beta_k is the kth solution of 'cosh(beta_kL)cos(beta_kL) + 1 = 0'"

	float time = 0.0;
	float freq = 2*M_PI; //Frequency

	
    //We Define And Calculate The Deformed Shape
	vector<float> x;
    vector<float> y;
    terms(x, y, X, Y, amplitude, phase, length, y_0, freq, time,  beta_k);

    
   //We Create A txt File To Place Our Eulerian Coordinates For Python Plotting
   ofstream outfile("FlappingPlateOptimization.txt"); 
  
   //We Check If The File Was Indeed Created 
   if(!outfile) 
   { 
       cout<<"File not created";
   } 

	for (int i = 0; i < x.size(); i++) {

        outfile << to_string(x[i]) << " " << to_string(y[i]) << endl;
		cout << x[i] << " " << y[i] << endl;

    }
   
   outfile.close(); 

}