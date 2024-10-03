// Copyright Epic Games, Inc. All Rights Reserved.

#include "NNEInterfaceBPLibrary.h"
#include "NNEInterface.h"
#include "NNETypes.h"

//Utilities
static TArray<uint32> ConvertToTArrayUint32(TArray<int32> inputShape)
{
	TArray<uint32> outputShape;
	for (int32 i = 0; i < inputShape.Num(); i++)
	{
		outputShape.Add(inputShape[i]);
	}
	return outputShape;
}

//Blueprint Library

UNNEInterfaceBPLibrary::UNNEInterfaceBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FNNEModel::FNNEModel()
{
	TWeakInterfacePtr<INNERuntimeCPU> Runtime = UE::NNE::GetRuntime<INNERuntimeCPU>(FString("NNERuntimeORTCpu"));
	if (Runtime.IsValid())
	{
		UNNEModelData* ModelData = NewObject<UNNEModelData>();
		TSharedPtr<UE::NNE::IModelCPU> Model = Runtime->CreateModelCPU(ModelData);
		ModelInstance = Model->CreateModelInstanceCPU();
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Runtime is not valid"));
	}
}



FNNEModel UNNEInterfaceBPLibrary::FromONNXFile(TArray<int32> inputShape)
{
	FNNEModel model;
	model.ModelInstance->SetInputTensorShapes({UE::NNE::FTensorShape::Make(ConvertToTArrayUint32(inputShape))});
	return model;
}

FNNEModel UNNEInterfaceBPLibrary::SetInputShape(FNNEModel model, TArray<int32> inputShape)
{
	model.ModelInstance->SetInputTensorShapes({UE::NNE::FTensorShape::Make(ConvertToTArrayUint32(inputShape))});
	return model;
}

TArray<int32> ConvertToArrayInt32(TConstArrayView<uint32> Shape)
{
	TArray<int32> outputShape;
	for (int32 i = 0; i < Shape.Num(); i++)
	{
		outputShape.Add(Shape[i]);
	}
	return outputShape;
}

TArray<int32> UNNEInterfaceBPLibrary::GetInputShape(FNNEModel model)
{
	TConstArrayView<UE::NNE::FTensorShape> shapes = model.ModelInstance->GetInputTensorShapes();
	TConstArrayView<uint32> shape =shapes[0].GetData();
	return ConvertToArrayInt32(shape);
}

