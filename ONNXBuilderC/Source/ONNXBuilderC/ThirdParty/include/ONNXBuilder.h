#pragma once

extern "C" {
// this is a super structure to hide the details of the model struct
    
    typedef struct OpaqueModel
    {
    
    } OpaqueModel;
    
    extern  OpaqueModel& MakeMLP(int input_layer,int hidden_layer,int hidden_layer_count,int output_layer,
                float bias);
    extern int  GetWeightCount(OpaqueModel* model);
    extern float* ExtractWeights(OpaqueModel* model);
    extern uint8_t* GetByteArray(OpaqueModel* model);
    extern void  SetWeights(OpaqueModel* model, float* weights);
    extern int GetByteArraySize(OpaqueModel* model);
    extern void WriteToFile(OpaqueModel* model);
    //extern std::string GetByteString(OpaqueModel* model);
    
}
