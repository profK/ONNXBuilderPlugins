// Copyright Epic Games, Inc. All Rights Reserved.

#include "NNEInterfaceBPLibrary.h"
#include "NNEInterface.h"
#include "NNETypes.h"

UNNEInterfaceBPLibrary::UNNEInterfaceBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

static TArray<uint32> ConvertToTArrayUint32(TArray<int32> inputShape)
{
	TArray<uint32> outputShape;
	for (int32 i = 0; i < inputShape.Num(); i++)
	{
		outputShape.Add(inputShape[i]);
	}
	return outputShape;
}

FNNEModel UNNEInterfaceBPLibrary::FromONNXFile(TArray<int32> inputShape)
{
	// Create the model from a neural network model data asset
	TObjectPtr<UNNEModelData> ModelData = LoadObject<UNNEModelData>(GetTransientPackage(), TEXT("/path/to/asset"));
	TWeakInterfacePtr<INNERuntimeCPU> Runtime = UE::NNE::GetRuntime<INNERuntimeCPU>(FString("NNERuntimeORTCpu"));
	TSharedPtr<UE::NNE::IModelInstanceCPU> ModelInstance = Runtime->CreateModelCPU(ModelData)->CreateModelInstanceCPU();

	

	// Prepare the model given a certain input size
	UE::NNE::FTensorShape tshape = UE::NNE::FTensorShape::Make(ConvertToTArrayUint32(inputShape));
	ModelInstance->SetInputTensorShapes({tshape});
	return FNNEModel(ModelInstance);

}

