// Copyright Epic Games, Inc. All Rights Reserved.

#include "NNInterfaceBPLibrary.h"
#include "NNInterface.h"
#include <NeuralNetworkInference\Public\NeuralNetwork.h>

class NEURALNETWORKINFERENCE_API UNeuralNetwork;

UNNInterfaceBPLibrary::UNNInterfaceBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UNNInterfaceBPLibrary::NNInterfaceSampleFunction(float Param)
{
	return -1;
}

void UNNInterfaceBPLibrary::LoadFromFile(FString SaveDirectory, FString FileName, FString& Report)
{
	UNeuralNetwork* Network = NewObject<UNeuralNetwork>((UObject*)GetTransientPackage(), UNeuralNetwork::StaticClass());
	
	SaveDirectory += FileName;

	const FString ONNXModelFilePath = SaveDirectory;

	if (Network->Load(ONNXModelFilePath))
	{
		if (Network->IsGPUSupported())
			Network->SetDeviceType(ENeuralDeviceType::GPU);
		Network->SetDeviceType(ENeuralDeviceType::CPU);

		TArray<float> InArray;
		Network->SetInputFromArrayCopy(InArray);
		Network->Run();
		const FNeuralTensor& OutputTensor = Network->GetOutputTensor();

		Report = FString::Printf(TEXT("UNeuralNetwork was successfully loaded from file %s. Output tensor: %s."), *ONNXModelFilePath, *OutputTensor.ToString());
	}
	// Check that the network was successfully loaded
	else
	{
		Report = FString::Printf(TEXT("UNeuralNetwork was not loaded from %s."), *ONNXModelFilePath);
	}
}

TArray<uint8> UNNInterfaceBPLibrary::ReadONNXfile(FString SaveDirectory, FString FileName)
{
	SaveDirectory += FileName;
	const FString InModelFilePath = SaveDirectory;

	FString ModelFullFilePath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*InModelFilePath);
	TArray<uint8> ModelReadFromFileInBytes;
	FFileHelper::LoadFileToArray(ModelReadFromFileInBytes, *ModelFullFilePath);

	return ModelReadFromFileInBytes;
}

void UNNInterfaceBPLibrary::LoadFromBytes(TArray<uint8>InModelReadFromFileInBytes, FString& Report)
{
	UNeuralNetwork* Network = NewObject<UNeuralNetwork>((UObject*)GetTransientPackage(), UNeuralNetwork::StaticClass());

	if (Network->Load(InModelReadFromFileInBytes))
	{
		if (Network->IsGPUSupported())
			Network->SetDeviceType(ENeuralDeviceType::GPU);
		Network->SetDeviceType(ENeuralDeviceType::CPU);

		TArray<float> InArray;
		Network->SetInputFromArrayCopy(InArray);
		Network->Run();
		const FNeuralTensor& OutputTensor = Network->GetOutputTensor();

		Report = FString::Printf(TEXT("UNeuralNetwork was successfully loaded from input bytes. Output tensor: %s."), *OutputTensor.ToString());
	}
	// Check that the network was successfully loaded
	else
	{
		Report = FString::Printf(TEXT("UNeuralNetwork was not loaded from bytes."));
	}
}



