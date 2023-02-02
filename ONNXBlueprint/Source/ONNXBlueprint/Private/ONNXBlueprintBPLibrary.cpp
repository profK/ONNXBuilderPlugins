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
	return TWeights;
}

void UONNXBlueprintBPLibrary::SetWeights(FONNXModel model, TArray<float> weights, FString& Report)
{
	FONNXBuilderCModule::SetMLPWeights(model.Model, weights.GetData());
}


TArray<uint8> UONNXBlueprintBPLibrary::GetByteArray(FONNXModel model, FString SaveDirectory, FString& Report)
{
	uint8_t* bArray = FONNXBuilderCModule::GetMLPByteArray(model.Model);
	TArray<uint8> TBytes;

	int onnxSize = FONNXBuilderCModule::GetMLPByteArraySize(model.Model);
	TBytes.Append(bArray, onnxSize);

	return TBytes;

	//FString fileByteString((char*)bArray);
	//FString temp_file = FPaths::CreateTempFilename(TEXT(""), TEXT(""), nullptr);
	//FFileHelper::SaveStringToFile(fileByteString, *temp_file);

	//TArray<uint8> model_array;
	//FFileHelper::LoadFileToArray(model_array, *temp_file);
	//IFileManager::Get().Delete(*temp_file);

	//FONNXBuilderCModule::WriteMLPFile(model.Model);

	//SaveDirectory += "mlp1.onnx";
	//const FString InModelFilePath = SaveDirectory;

	//FString ModelFullFilePath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*InModelFilePath);
	//TArray<uint8> ModelReadFromFileInBytes;
	//if (FFileHelper::LoadFileToArray(ModelReadFromFileInBytes, *ModelFullFilePath))
	//{
	//	Report = FString::Printf(TEXT("Read bytes from file %s"), *InModelFilePath);
	//}
	//else
	//{
	//	Report = FString::Printf(TEXT("file not read!"));
	//}

	//FString fileByteString((char*)ModelReadFromFileInBytes.GetData());

	//Report = FString::Printf(TEXT("Read bytes from file %s"), *fileByteString);

	//return model_array;

	// return model_array;
}

void UONNXBlueprintBPLibrary::CompareBytes(TArray<uint8> fileByte, TArray<uint8> arrayByte, FString& Report)
{
	// Passing
	FString fileByteString((char*)fileByte.GetData());
	FString arrayByteString((char*)arrayByte.GetData());

	//FString fileByteString((char*)bArray);
	FString temp_file = FPaths::CreateTempFilename(TEXT(""), TEXT(""), nullptr);
	FFileHelper::SaveStringToFile(fileByteString, *temp_file);

	TArray<uint8> model_array;
	FFileHelper::LoadFileToArray(model_array, *temp_file);
	IFileManager::Get().Delete(*temp_file);

	Report = FString::Printf(TEXT("Compare Bytes %s"), model_array == fileByte, fileByteString == arrayByteString);

	
	//uint8* file = fileByte.GetData();
	//uint8* arr = arrayByte.GetData();

	//FString wrongs = "";

	//for (int i = 0; i < fileByte.Num(); i++)
	//{
	//	if (fileByte[i] != arrayByte[i])
	//	{
	//		wrongs = wrongs + (FString)i + " ";
	//	}
	//}

	//int onnxSize = 874;
	//TArray<uint8> TBytes2;
	//TBytes2.Append(arrayByte.GetData(), onnxSize);

	// Report = FString::Printf(TEXT("FString Model %s"), *arrayByteString);

	//TArray<TCHAR> model_char_array;
	//fileByteString.GetCharArray(model_char_array);
	//TArray<uint8> model_uint8_array;
	//model_uint8_array.SetNumUninitialized(model_char_array.Num());
	//FMemory::Memcpy(model_uint8_array.GetData(), model_char_array.GetData(), model_char_array.Num());
	
	//TArray<uint8> model_data;
	//int32 ModelStringLength = fileByteString.Len();
	//model_data.SetNumUninitialized(ModelStringLength);
	//FMemory::Memcpy(model_data.GetData(), TCHAR_TO_UTF8(*fileByteString), ModelStringLength);

	// FONNXBuilderCModule::WriteMLPFile(model.Model);
}

