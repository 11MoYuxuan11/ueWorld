// Fill out your copyright notice in the Description page of Project Settings.


#include "Overworld.h"
#include "Runtime/Engine//Classes/Kismet/GameplayStatics.h"

// Sets default values
AOverworld::AOverworld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOverworld::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AOverworld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOverworld::OnConstruction(const FTransform& Transform)
{
	ChunkSize = ChunkBlockElements * VoxelSize;
	WorldBlockElements = WorldChunkElements * ChunkBlockElements;
}

void AOverworld::GeneratWorld()
{
	WorldCells.SetNumUninitialized(WorldBlockElements * WorldBlockElements);
	for (int i = 0; i < WorldBlockElements; i++)
	{
		for (int j = 0; j < WorldBlockElements; j++)
		{
			// TODO 通过noise随机生成高度
			WorldCells[i + j * WorldBlockElements].SetValue(EOverworldField::Height,0);
		}
	}
}

void AOverworld::UpdatePosition()
{
	auto chaPos = UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation();

	if ( ChunkPosition != GetChunkLocation(chaPos) )
	{
		ChunkPosition.X = GetChunkLocation(chaPos).X;
		ChunkPosition.Y = GetChunkLocation(chaPos).Y;
	}
}

void AOverworld::AddChunk()
{
	for (int i = -RenderRange; i <= RenderRange; i++)
	{
		for (int j = -RenderRange; j <= RenderRange; j++)
		{
			// 边界判断
			if ((i > 0 && j > 0 && i < WorldChunkElements && j < WorldChunkElements))
			{
				if (ChunkClass == nullptr) return;
				if (!ChunkCords.Contains(FVector2D(ChunkPosition.X + i, ChunkPosition.Y + j)))
				{
					AChunk* chunk = Cast<AChunk>(UGameplayStatics::BeginSpawningActorFromClass(GetWorld(), ChunkClass, FTransform()));

					if (chunk)
					{
						chunk->OverWorld = this;
						chunk->ChunkPosition = FIntVector(ChunkPosition.X + i, ChunkPosition.Y + j,0);
						chunk->FinishSpawning((FTransform)FVector((ChunkPosition.X + i) * VoxelSize, (ChunkPosition.Y + j) * VoxelSize, 0));
					}
					ChunkCords.Add(FVector2D(ChunkPosition.X + i, ChunkPosition.Y + j));
				}
			}
		}
	}
}

FIntVector AOverworld::GetChunkLocation(FVector worldPos)
{
	return FIntVector(worldPos.X/ChunkSize, worldPos.Y / ChunkSize,0);
}

//TArray<FOverworldCell> AOverworld::GetChunkCells(FIntVector chunkPos)
//{
//	TArray<FOverworldCell> toReturn;
//	toReturn.SetNumUninitialized(ChunkBlockElements * ChunkBlockElements);
//	for (int i = chunkPos.X * ChunkBlockElements; i < ChunkBlockElements; i++)
//	{
//		for (int j = chunkPos.Y * ChunkBlockElements; j < ChunkBlockElements; j++)
//		{
//			toReturn[i + j * ChunkBlockElements] = WorldCells[i + j * WorldBlockElements];
//		}
//	}
//	return toReturn;
//}