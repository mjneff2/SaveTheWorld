// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MapGridUtils.generated.h"

/**
 * 
 */
UCLASS()
class SAVETHEWORLD_API UMapGridUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	/** Generate array with path */
	UFUNCTION(BlueprintCallable)
	static TArray<int32> GenerateGrid(int32 size);
};
