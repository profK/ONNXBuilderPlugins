// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ONNXBuilder.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"



class FONNXBuilderCModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	static OpaqueModel* MakeMLPModel(int input_layer,int hidden_layer,int hidden_layer_count,int output_layer,
					float bias) {
		return &MakeMLP(input_layer,hidden_layer,hidden_layer_count,output_layer,bias);
	}
	static int GetMLPWeightCount(OpaqueModel* model)
	{
		return GetWeightCount(model);
	}
	static float* ExtractMLPWeights(OpaqueModel* model)
	{
		return ExtractWeights(model);
	}
	static uint8_t* GetMLPByteArray(OpaqueModel* model)
	{
		return GetByteArray(model);
	}
	static void  SetMLPWeights(OpaqueModel* model, float* weights)
	{
		SetWeights(model, weights);
	}
	static int GetMLPByteArraySize(OpaqueModel* model)
	{
		return GetByteArraySize(model);
	}
	static void WriteMLPFile(OpaqueModel* model)
	{
		WriteToFile(model);
	}

	//static std::string GetMLPByteString(OpaqueModel* model)
	//{
	//	return GetByteString(model);
	//}

};
