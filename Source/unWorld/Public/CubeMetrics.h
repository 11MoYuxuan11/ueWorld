// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CubeMetrics.generated.h"

/**
 * 
 */
UCLASS()
class UNWORLD_API UCubeMetrics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	static FVector WorldPostion2CubePosition(FVector position, float CUBE_SIDE_LENGTH);

	UFUNCTION(BlueprintCallable)
	static FVector WorldPostion2ChunkPosition(FVector position, float CUBE_SIDE_LENGTH, int CHUNK_WIDTH);
};

enum class AdjacentDirection
{
	front,
	back,
	left,
	right,
	up,
	down
};
