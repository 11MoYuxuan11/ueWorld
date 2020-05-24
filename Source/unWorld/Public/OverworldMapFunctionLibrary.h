// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OverworldMapFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UNWORLD_API UOverworldMapFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static TArray<float> GenerateHeightMapLookup(int32 width, int32 height) {
		TArray<float> toReturn;
		toReturn.SetNumUninitialized(width * height);

		const float mountainWidth = 0.04f;
		const float continentSize = 0.03f;
		const float hillSize = 0.1f;
		const float smallNoiseSize = 0.15f;
		const float cliffHeight = 0.1f;
		const float invCliffHeight = 1.0f / cliffHeight;
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				//float mountain = (float)FMath::Pow(OverworldImageOperations.noise(heightNoise, x, y, 0, mountainWidth), 1);
				//float continent = OverworldImageOperations.noise(heightNoise, x, y, 10, continentSize);
				//float hill = OverworldImageOperations.noise(heightNoise, x, y, 20, hillSize) * 0.02f;
				//float smallnoise = OverworldImageOperations.noise(heightNoise, x, y, 100, smallNoiseSize) * 0.01f;
				//float cliffs = OverworldImageOperations.noise(heightNoise, x, y, 200, continentSize) + 0.5f;
				//float h = OverworldImageOperations.pow(OverworldImageOperations.clamp((continent * mountain) + hill, 0, 1), 1);
				//h += smallnoise;
				//h += 0.4f;
				//h = ((int)(h * invCliffHeight)) * cliffHeight;

				// TODO 高度图随机生成算法
				toReturn[x + y * height] = 0;
			}
		}

		return toReturn;
	}
};
