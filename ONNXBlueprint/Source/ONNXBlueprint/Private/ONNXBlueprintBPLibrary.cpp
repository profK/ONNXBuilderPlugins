// Copyright Epic Games, Inc. All Rights Reserved.


#include "ONNXBlueprintBPLibrary.h"
#include "ONNXBlueprint.h"


UONNXBlueprintBPLibrary::UONNXBlueprintBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UONNXBlueprintBPLibrary::ONNXBlueprintSampleFunction(float Param)
{
	return -1;
}

FONNXModel UONNXBlueprintBPLibrary::MakeMLP(int input_layer,int hidden_layer,int hidden_layer_count,int output_layer,
					float bias)
{
	OpaqueModel *model = FONNXBuilderCModule::MakeMLPModel(input_layer,hidden_layer,hidden_layer_count,output_layer, bias);
	FONNXModel fmdl(model);
	return fmdl;
}

