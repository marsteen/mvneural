//***************************************************************************
//
//
// @PROJECT  :	mvneural
// @VERSION  :	1.0
// @FILENAME :	main.cpp
// @DATE     :  22.02.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

//
// Backpropagation Example:
// https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/
//

#include <iostream>
#include <cmath>
#include <NNeural.h>

using namespace std;

int main(int argc, char* argv[])
{
    const float winit[] = 
    { 
        // Layer 0
        
        0.35f, // bias
        0.15f, // w1
        0.25f, // w2
        0.20f, // w3
        0.30f, // w4
        
        // Layer 1
        
        0.6f,  // bias         
        0.40f, // w5
        0.50f, // w6
        0.45f, // w7
        0.55f  // w8      
    };
    

    const float input[] = 
    {
        0.05f,
        0.1f
    };

    const float targets[] = 
    {
        0.01f,
        0.99f
    };

    NNeural::CNet* net = new NNeural::CNet;

    net->InitLayers(3, 2);
    net->InitWeights(winit);
    net->InitTargets(targets); 
    net->Learn(input);
    net->CalcTotalError();
    net->Backpropagate();
    return 0; 
}
