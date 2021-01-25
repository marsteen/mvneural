
//***************************************************************************
//
//
// @PROJECT  :	mvneural
// @VERSION  :	1.0
// @FILENAME :	NNeural.cpp
// @DATE     :  22.02.2021
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#include <NNeural.h>
#include <iostream>

using namespace std;

namespace NNeural
{
    
    //---------------------------------------------------------------------------
    //
    // Klasse:    CNet
    // Methode:   InitLayers
    //
    //---------------------------------------------------------------------------
    
    void CNet::InitLayers(int LayerCount, int KnotCount)
    {
        mKnotCount  = KnotCount;
        mLayerCount = LayerCount;
        mLayer = new CLayer[LayerCount];
        for (int l = 0; l < LayerCount; l++)
        {
            mLayer[l].mKnot = new CKnot[KnotCount];

            for (int k = 0; k < KnotCount; k++)
            {
                mLayer[l].mKnot[k].mWeight = new float[KnotCount];
            }      
        }
    }


    //---------------------------------------------------------------------------
    //
    // Klasse:    static
    // Methode:   sigmoid
    //
    //---------------------------------------------------------------------------

    static inline float sigmoid(float x)
    {
        return 1.0f / (1.0f + exp(-x));
    }
    
    static inline float square(float x)
    {
        return x * x;        
    }

    //---------------------------------------------------------------------------
    //
    // Klasse:    CNet
    // Methode:   Learn
    //
    //---------------------------------------------------------------------------

    void CNet::Learn(const float* input)
    {
        // 1. Schicht des neuronalen Netzes mit Daten fuellen
        for (int k = 0; k < mKnotCount; k++)
        {
            mLayer[0].mKnot[k].mValue = input[k];
        }

        // Berechnen
        for (int l = 0; l < mLayerCount-1; l++)
        {
            for (int k = 0; k < mKnotCount; k++)
            {
                float sum = 0.0f;  
                for (int w = 0; w < mKnotCount; w++)
                {        
                    float vr = mLayer[l].mKnot[w].mValue;
                    float wr = mLayer[l].mKnot[w].mWeight[k];
                    cout << "vr=" << vr << " wr=" << wr << endl;
                    sum += vr * wr;
                }
                cout << "sum=" << sum << " bias=" <<  + mLayer[l+1].mBias <<  endl;
                mLayer[l+1].mKnot[k].mValue = sigmoid(sum + mLayer[l+1].mBias);
                //mLayer[l+1].mKnot[k].mValue = sum;
            }
        }

        // Ausgabe:

        for (int k = 0; k < mKnotCount; k++)
        {
            cout <<  "output " << k << ": " << mLayer[mLayerCount-1].mKnot[k].mValue << endl;
        }

    }

    //---------------------------------------------------------------------------
    //
    // Klasse:    CNet
    // Methode:   CalcTotalError
    //
    //---------------------------------------------------------------------------

    float CNet::CalcTotalError() const
    {
        float totalError = 0.0f;
        for (int k = 0; k < mKnotCount; k++)
        {
            totalError += 0.5f * square(mTargets[k] - mLayer[mLayerCount-1].mKnot[k].mValue);
        }
        cout << "totalError=" << totalError << endl;
        
        return totalError;
    }    

    //---------------------------------------------------------------------------
    //
    // Klasse:    CNet
    // Methode:   Backpropagate
    //
    //---------------------------------------------------------------------------

    void CNet::Backpropagate()
    {
        int n = 0;
        float totalError = CalcTotalError();
        for (int l = 0; l < mLayerCount-1; l++)
        {
            for (int k = 0; k < mKnotCount; k++)
            {
                float sum = 0.0f;
                for (int w = 0; w < mKnotCount; w++)
                {                            
                    float wr = mLayer[l].mKnot[w].mWeight[k];
                    float wr_updated = wr - 0.5f * (totalError / wr);
                    mLayer[l].mKnot[w].mWeight[k] = wr_updated;
                    
                    cout << "w=" << n++ << " old=" << wr << " new=" << wr_updated << endl;
                    
                }
            }
        }        
    }
    
    
    //---------------------------------------------------------------------------
    //
    // Klasse:    CNet
    // Methode:   InitTargets
    //
    //---------------------------------------------------------------------------

    void CNet::InitTargets(const float* targets)
    {
        mTargets = targets;
    }
    
    //---------------------------------------------------------------------------
    //
    // Klasse:    CNet
    // Methode:   InitWeights
    //
    //---------------------------------------------------------------------------

    void CNet::InitWeights(const float* weights)
    {
        int w = 0;
        
        for (int L = 0; L < mLayerCount-1; L++)
        {        
            mLayer[L+1].mBias = weights[w++];
            for (int k = 0; k < mKnotCount; k++)
            {
                for (int i = 0; i < mKnotCount; i++)
                {        
                    mLayer[L].mKnot[k].mWeight[i] = weights[w++];
                }
            }
        }
    }


} // end of namespace



