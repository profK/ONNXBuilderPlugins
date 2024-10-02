// Copyright Epic Games, Inc. All Rights Reserved.

#include "NNEInterfaceBPLibrary.h"
#include "NNEInterface.h"

UNNEInterfaceBPLibrary::UNNEInterfaceBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FNNEModel UNNEInterfaceBPLibrary::FromONNXFile(float InputSize)
{
	// Create the model from a neural network model data asset
	TObjectPtr<UNNEModelData> ModelData = LoadObject<UNNEModelData>(GetTransientPackage(), TEXT("/path/to/asset"));
	TWeakInterfacePtr<INNERuntimeCPU> Runtime = UE::NNE::GetRuntime<INNERuntimeCPU>(FString("NNERuntimeORTCpu"));
	TSharedPtr<UE::NNE::IModelInstanceCPU> ModelInstance = Runtime->CreateModelCPU(ModelData)->CreateModelInstanceCPU();

	// TODO: Setup input and output tensors and tensor bindings as well as corresponding input shapes

	// Prepare the model given a certain input size
	//return ModelInstance->SetInputTensorShapes(InputShapes);
	return FNNEModel(ModelInstance);

}

