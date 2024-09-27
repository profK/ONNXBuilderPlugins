// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ONNXBuilder.h"
#include "ONNXBuilderC.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ONNXBlueprintBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
USTRUCT(BlueprintType)
struct FONNXModel
{
	GENERATED_BODY()


	OpaqueModel* Model;

	FONNXModel(){}
	FONNXModel(OpaqueModel *model):Model(model){}
};

UCLASS()
class UONNXBlueprintBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "ONNXBlueprint sample test testing"), Category = "ONNXBlueprintTesting")
	static float ONNXBlueprintSampleFunction(float Param);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "MakeMLP", Keywords = "ONNXBlueprint NNI MLP"), Category = "ONNXBlueprint")
	static FONNXModel MakeMLP(int input_layer,int hidden_layer,int hidden_layer_count,int output_layer,
					float bias, FString& Report);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetWeightCount", Keywords = "Get Weight Count ONNXBlueprint NNI MLP"), Category = "ONNXBlueprint")
	static int GetWeightCount(FONNXModel model, FString& Report);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ExtractWeights", Keywords = "Extract Weight ONNXBlueprint NNI MLP"), Category = "ONNXBlueprint")
	static TArray<float> ExtractWeights(FONNXModel model, FString& Report);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetWeights", Keywords = "Set Weight ONNXBlueprint NNI MLP"), Category = "ONNXBlueprint")
	static FONNXModel SetWeights(FONNXModel model, TArray<float> weights, FString& Report);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetByteArray", Keywords = "Get Byte Array ONNXBlueprint NNI MLP"), Category = "ONNXBlueprint")
	static TArray<uint8> GetByteArray(FONNXModel model, FString& Report);

	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Compare Bytes", Keywords = "Compare Bytes ONNXBlueprint NNI MLP"), Category = "ONNXBlueprint")
	//static void CompareBytes(TArray<uint8> fileByte, TArray<uint8> arrayByte, FString& Report);

};
