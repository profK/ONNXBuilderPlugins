#pragma once

extern "C" {
// this is a super structure to hide the details of the model struct
    
     struct OpaqueModel
    {
    
    };
    
    extern  OpaqueModel& MakeMLP(int input_layer,int hidden_layer,int hidden_layer_count,int output_layer,
                float bias);
    extern int  GetWeightCount(OpaqueModel& model);
    extern float* ExtractWeights(OpaqueModel& model);
    extern void  SetWeights(OpaqueModel& model, float* weights);
    
}
