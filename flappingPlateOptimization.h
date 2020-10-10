#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//Importing
#include <cmath> 

using namespace std;

//Definitions And Calculations
void terms(vector<float> &x, vector<float> &y, 
            vector<float> X, vector<float> Y, vector<float> amplitude, vector<float> phase, 
            int length, float y_0, float freq, float time, float beta_k);

vector<float> psi(float beta_k, vector<float> X);
float findC(vector<float> psi);
vector<float> sum(float sumterm, vector<float> psi);
vector<float> matrixv_product(vector<float> m1, vector<float> m2);
vector<float> product(vector<float> v, float f);
vector<float> vector_sum(vector<float> v1, vector<float> v2);
float vmax(vector<float> v);