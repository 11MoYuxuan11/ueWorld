// Fill out your copyright notice in the Description page of Project Settings.


#include "OverworldGenerator.h"

// Sets default values
AOverworldGenerator::AOverworldGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOverworldGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOverworldGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOverworldGenerator::GenerateWorld()
{
	// 初始化
	//if (WorldManager != nullptr)
	//{
	//	WorldManager->OverworldCells.SetNumUninitialized(WorldManager->WorldElements* WorldManager->WorldElements);
	//	
	//	// 高度图
	//	TArray<float> heightMapLookup = GenerateHeightMapLookup(WorldManager->WorldElements, WorldManager->WorldElements);
	//	WorldManager->CreateHeightFromLookup(heightMapLookup);
	//}
}

TArray<float> AOverworldGenerator::GenerateHeightMapLookup(int width, int height)
{
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
			// 山
			float mountain = (float)FMath::Pow(GenerateNoiseHeight(FVector(x, y, 0), mountainWidth), 1);
			// 大陆
			float continent = GenerateNoiseHeight(FVector(x, y, 10), continentSize);
			// 爬坡道
			float hill = GenerateNoiseHeight(FVector(x, y, 20), hillSize) * 0.02f;
			// 小噪音(丘陵)
			float smallnoise = GenerateNoiseHeight(FVector(x, y, 100), smallNoiseSize) * 0.01f;
			// 悬崖
			float cliffs = GenerateNoiseHeight(FVector(x, y, 200), continentSize) + 0.5f;
			float h = FMath::Pow(FMath::Clamp((continent * mountain) + hill, 0.f, 1.f), 1);

			h += smallnoise;
			h += 0.4f;
			h = ((int)(h * invCliffHeight)) * cliffHeight;
			toReturn[x + y * height] = h;
		}
	}

	return toReturn;
}

float AOverworldGenerator::GenerateNoiseHeight_Implementation(FVector wPos, float frequency)
{
	return 0.0f;
}

