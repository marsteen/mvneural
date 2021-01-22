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

#include <iostream>
#include <cmath>
#include <NNeural.h>

using namespace std;

int main(int argc, char* argv[])
{
    const float winit[] = 
    { 
        0.9f, 
        0.2f,
        0.3f,
        0.8f
    };

    const float input[] = 
    {
        1.0f,
        0.5
    };

    NNeural::CNet* net = new NNeural::CNet;

    net->InitLayers(2, 2);
    net->InitWeights(winit);
    net->Learn(input);  
    return 0; 
}
