
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
        mErrors = new int[KnotCount];
        for (int l = 0; l < LayerCount; l++)
        {
            mLayer[l].mKnot = new CKnot[KnotCount];

            for (int k = 0; k < KnotCount; k++)
            {
                mLayer[l].mKnot[k].mWeight = new float[KnotCount];
                mLayer[l].mKnot[k].mWeightNew = new float[KnotCount];
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
                mLayer[l+1].mKnot[k].mOut   = sigmoid(sum);
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
            mErrors[k] = mTargets[k] - mLayer[mLayerCount-1].mKnot[k].mValue;
            totalError += 0.5f * square(mErrors[k]);
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
        //for (int l = 0; l < mLayerCount-1; l++)
        for (int l = mLayerCount-2; l >= 0; l--)
        {
            for (int k = 0; k < mKnotCount; k++)
            {
                for (int w = 0; w < mKnotCount; w++)
                {              

                    float target_o1 = mTargets[k];
                    
                    if (l ==  mLayerCount-2)
                    {     
                        target_o1 = mTargets[k];
                        float wr = mLayer[l].mKnot[w].mWeight[k];
                        float out_o1    = mLayer[mLayerCount-1].mKnot[k].mValue;
                        float out_h1    = mLayer[l].mKnot[w].mValue;
                        float delta = -(target_o1 - out_o1) * out_o1 * (1.0f - out_o1) * out_h1;
                        float p2 = out_h1 * (1.0f - out_h1);
                        float wr_updated = wr - 0.5f * delta;
                        mLayer[l].mKnot[w].mWeight[k] = wr_updated;
                        
                        cout << "l=" << l << " w=" << n++ << " old=" << wr << " new=" << wr_updated 
                             << " p2=" << p2 << " layercount=" << mLayerCount << endl;
                    }
                    else
                    {
                        
                        
                        float wr = mLayer[l].mKnot[w].mWeight[k];
                        target_o1 = wr;
                        
                        float out_o1    = mLayer[l+1].mKnot[k].mValue;
                        float out_h1    = mLayer[l].mKnot[w].mValue;
                        float delta = -(target_o1 - out_o1) * out_o1 * (1.0f - out_o1) * out_h1;
                        float p2 = out_h1 * (1.0f - out_h1);
                        float wr_updated = wr - 0.5f * delta;
                        mLayer[l].mKnot[w].mWeightNew[k] = wr_updated;
                        
                        cout << "l=" << l << " w=" << n++ << " old=" << wr << " new=" << wr_updated 
                             << " p2=" << p2 << endl;
                        
                    }
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
                    mLayer[L].mKnot[k].mWeightNew[i] = mLayer[L].mKnot[k].mWeight[i] = weights[w++];
                    
                }
            }
        }
    }


} // end of namespace



