// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkBase.h"

// Sets default values
AChunkBase::AChunkBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	proceduralComponent = NewObject<UProceduralMeshComponent>(this, "Procedural");
	proceduralComponent->RegisterComponent();

	RootComponent = proceduralComponent;
}

// Called when the game starts or when spawned
void AChunkBase::BeginPlay()
{
	Super::BeginPlay();
	
	//AChunkBase::chunks.Add(this);
}

// Called every frame
void AChunkBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChunkBase::InitMap()
{



	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int z=0; z<width; z++)
			{
				//map.Add(FVector(x, y, z), GenerateBlockType(FVector(x, y, z)));
			}
		}
	}
}

EBlockType AChunkBase::GenerateBlockType(FVector wPos)
{
	if (wPos.Y >= height)
	{
		return EBlockType::None;
	}
	
	float genHeight = GenerateHeight(wPos);

	if (wPos.Y > genHeight)
	{
		return EBlockType::None;
	}

	else if (wPos.Y == genHeight)
	{
		return EBlockType::Grass;
	}

	else if (wPos.Y < genHeight && wPos.Y > genHeight - 5)
	{
		return EBlockType::Dirt;
	}

	return EBlockType::Gravel;
}

int AChunkBase::GenerateHeight(FVector wPos)
{
	
	float X = wPos.X * frequency;
	float Y = wPos.Y * frequency;

	//return USimplexNoiseBPLibrary::SimplexNoise2D(X, Y) * amplitude;
	return 1;
}

