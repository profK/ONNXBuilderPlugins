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
					float bias, FString& Report)
{
	OpaqueModel *model = FONNXBuilderCModule::MakeMLPModel(input_layer,hidden_layer,hidden_layer_count,output_layer, bias);
	FONNXModel fmdl(model);

	Report = FString::Printf(TEXT("Make MLP execution successful."));
	return fmdl;
}

int UONNXBlueprintBPLibrary::GetWeightCount(FONNXModel model, FString& Report)
{
	int weight_count = FONNXBuilderCModule::GetMLPWeightCount(model.Model);
	Report = FString::Printf(TEXT("Make MLP execution successful. Weight count %d"), weight_count);
	return weight_count;
}

TArray<float> UONNXBlueprintBPLibrary::ExtractWeights(FONNXModel model, FString& Report)
{
	float* weights = FONNXBuilderCModule::ExtractMLPWeights(model.Model);
	TArray<float> TWeights;

	TWeights.Append(weights, FONNXBuilderCModule::GetMLPWeightCount(model.Model));

	// Demo
	//FString ArrayString;
	//for (float Value : TWeights)
	//{
	//	ArrayString += FString::SanitizeFloat(Value) + TEXT(", ");
	//}
	//ArrayString = ArrayString.LeftChop(2);
	//UE_LOG(LogTemp, Log, TEXT("MyArray: %s"), *ArrayString);

	return TWeights;
}

FONNXModel UONNXBlueprintBPLibrary::SetWeights(FONNXModel model, TArray<float> weights, FString& Report)
{
	FONNXBuilderCModule::SetMLPWeights(model.Model, weights.GetData());
	return model;
}


TArray<uint8> UONNXBlueprintBPLibrary::GetByteArray(FONNXModel model, FString& Report)
{
	uint8_t* bArray = FONNXBuilderCModule::GetMLPByteArray(model.Model);
	TArray<uint8> TBytes;

	int onnxSize = FONNXBuilderCModule::GetMLPByteArraySize(model.Model);
	TBytes.Append(bArray, onnxSize);

	return TBytes;
}

