//***************************************************************************
//
//
// @PROJECT  :	mvneural
// @VERSION  :	1.0
// @FILENAME :	NNeural.h
// @DATE     :  22.02.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef NNeural_H
#define NNeural_H

#include <cmath>

namespace NNeural
{
    //---------------------------------------------------------------------------
    //
    // Klasse:    CKnot
    //
    //---------------------------------------------------------------------------
    
    
	class CKnot
	{
        public:

            float  mValue;
            float* mWeight;
	  
	};  

    //---------------------------------------------------------------------------
    //
    // Klasse:    CLayer
    //
    //---------------------------------------------------------------------------
  
    class CLayer
    {
        public:

            CKnot* mKnot;
    };  

    //---------------------------------------------------------------------------
    //
    // Klasse:    CNet
    //
    //---------------------------------------------------------------------------
  
    class CNet
    {
        public:
      
            void InitLayers(int LayoutCount, int KnotCount);
            void Learn(const float* input);
            void InitWeights(const float* Weights);
      
 
        protected:

            CLayer* mLayer;
            int     mLayerCount;
            int     mKnotCount;
    
      
    };  
};

#endif
