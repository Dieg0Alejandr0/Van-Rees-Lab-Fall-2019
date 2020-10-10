#include "flappingPlateOptimization.h"


/*Note: The I = (0, 1) is not defined here but is considered by our 
        definitions of any terms interacting with it solely in the 
        vertical dimension. */

//We Define How To Find The Main Three Main Physical Terms (Plunging, Rotating, And Deforming Motion)
void terms(vector<float> &x, vector<float> &y, 
            vector<float> X, vector<float> Y, vector<float> amplitude, vector<float> phase, 
            int length, float y_0, float freq, float time, float beta_k) {


    float sumterm = amplitude[1]*sin(freq*time + phase[1]); //Used Later For The Summation
    float theta = amplitude[0]*sin (freq*time + phase[0]); //Defined Theta


    float xrotation; //First Row Of Rotation Matrix
    float yrotation; //Second Row Of Rotation Matrix

    xrotation = cos(theta);
    yrotation = sin(theta);

    //Summation Term
    vector<float> Psi;
    vector<float> deform_sum;

    Psi = psi(beta_k, X);
    deform_sum = sum(sumterm, Psi);

    //Transformation Terms
    float Plunging;
    vector<float> XRotating, YRotating, DeformingX, DeformingY;

    Plunging = y_0*sin(freq*time);
    XRotating = product(X, xrotation);
    YRotating = product(X, yrotation);
    DeformingX = product(deform_sum, -yrotation);
    DeformingY = product(deform_sum, xrotation);

    //Applies transformations to each nodes
    x.assign(X.size(),0.0);
    y.assign(X.size(),0.0);
    for (int i = 0; i < X.size(); i++) {
            x[i] = XRotating[i] + DeformingX[i];
            y[i] = Plunging + YRotating[i] + DeformingY[i];

    }

    return;
}


//We Define Our Psi From The Betas We Found As Detailed In Equation 5.28
vector<float> psi(float beta_k, vector<float> X) { 
        
        vector<float> Psi;
        Psi.assign(X.size(), 0);
        
        for(int k = 0; k < X.size(); k++){

            if (X[k] == 0.0) {
                Psi[k] = 0.0;
            }

            else {

                float numerator = cosh(beta_k*X[k]) + cos(beta_k*X[k]); //Part Of A Term In Psi
                float denominator = sinh(beta_k*X[k]) + sin(beta_k*X[k]); //Part Of A Term In Psi

                float factor = sin(beta_k*X[k]) - sinh(beta_k*X[k]); //Multiplicative Factor Of Fraction
                float additive = cosh(beta_k*X[k]) - cos(beta_k*X[k]); //Term Outside Of Product

                Psi[k] = additive + (factor)*(numerator/denominator);
            }

        }
        return Psi;

    };

//We Follow The Definition The Normalizing Coefficient As Detailed At The End Of Page 82
float findC(vector<float> psi) { 
        float max = vmax(psi);
        float C_k = 1.0;
        
        if (max != 1.0) {
            C_k = 1.0/max;
            psi = product(psi,C_k);
        }

        return C_k ;//Normalizing Coefficient
    };

//A Function Used To Calculate The Summation In 5.26
vector<float> sum(float sumterm, vector<float> psi) {
        vector<float> summation;
        float nk = psi.size();
        summation.assign(nk, 0);

        for (int n = 0; n < nk; n++) {

            summation[n] = sumterm*psi[n];

        }

        return summation;
    };

//The Following Defines The Product Between A Scalar And A Vecto
vector<float> product(vector<float> v, float f) {
        
        vector<float> prod;
        prod.assign(v.size(), 0);

        for (int n = 0; n < v.size(); n++) {

            prod[n] = v[n]*f;

        }

        return prod;
    };

//The Following Defines The Product Between Particular Parts Of Matrices
vector<float> matrixv_product(vector<float> m1, vector<float> m2) {

    int i = 0;
    vector<float> product;
    product.assign(m1.size(), 0);

    if (m1.size() == m2.size()) {

        for (int i = 0; i < m1.size(); i++) {

            product[i] = m1[i] * m2[i];
        }

    }
    return product;
};

//The Following Produces A Vector From The Element-Wise Sums Of Other Vectors
vector<float> vector_sum(vector<float> v1, vector<float> v2) {
    int i = 0;
    vector<float> sum;
    sum.assign((v1.size()), 0);
    if (v1.size() == v2.size()) {

        for (int i = 0; i < v1.size(); i++) {

            sum[i] = v1[i] + v2[i];

        }

    }

    return sum;

};

//We Define A Way To Find The Maximum Of A Vector
float vmax(vector<float> v) {
        float maximum;
        maximum = v[0];

        for (int n = 0; n < v.size(); n++) {

            if (v[n] > maximum){
                maximum = v[n];
            }

        }

        return maximum;
    };

//Something To Note, I Would Like To Add Code To Generalize The Finding Of The Beta Coefficient