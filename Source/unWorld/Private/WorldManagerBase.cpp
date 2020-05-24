// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManagerBase.h"
#include "Runtime/Engine//Classes/Kismet/GameplayStatics.h"

// Sets default values
AWorldManagerBase::AWorldManagerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldManagerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorldManagerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UpdatePostion();
	//RemoveChunk();
	//AddChunk();
}

void AWorldManagerBase::RandomFillMap()
{
	FaultMap.SetNumUninitialized(WorldElements * WorldElements);
	if (UseRandomSeed)
	{
		//SeedAllRandomStreams();
	}
	for (int i= 0;i< WorldElements;i++)
	{
		for (int j = 0; j < WorldElements; j++)
		{
			if (i == 0 || i == WorldElements - 1 || j == 0 || j == WorldElements - 1)
				FaultMap[i * WorldElements + j] = false;
			else
			{
				FaultMap[i * WorldElements + j] = FMath::RandBool();
			}
		}
	}
}

int32 AWorldManagerBase::GetSurroundingWalls(int X, int Y)
{
	int32 wallCount = 0;
	for (int i = X - 1; i <= X + 1; i++)
	{
		for (int j = Y - 1; j <= Y + 1; j++) {
			if (i >= 0 && i < WorldElements && j >= 0 && j < WorldElements) {
				if (i != X || j != Y)
					wallCount += FaultMap[i*WorldElements + j];
			}
			else {
				wallCount++;
			}
		}
	}
	return wallCount;
}

void AWorldManagerBase::SmoothMap()
{
	for (int i = 0; i < WorldElements; i++)
	{
		for (int j = 0; j < WorldElements; j++)
		{
			int surroundingTiles = GetSurroundingWalls(i, j);
			if (surroundingTiles > 4)
				FaultMap[i * WorldElements + j] = false;
			else if (surroundingTiles < 4)
				FaultMap[i * WorldElements + j] = true;
		}
	}
}

void AWorldManagerBase::AddChunk()
{
	for (int i=0;i<renderRange;i++)
	{
		for (int j = 0;j<renderRange; j++)
		{
			if (CheckRadius( (ChunkX + i)*ChunkSize +ChunkSizeHalf, 
				(ChunkY + j) * ChunkSize + ChunkSizeHalf))
			{
				if (!chunkCords.Contains(FVector2D(ChunkX + i, ChunkY + j)))
				{
					auto spawnTransform = FTransform();
					chunkCords.Add(FVector2D(ChunkX + i, ChunkY + j));
					auto deferredChunk = Cast<AChunkBase>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this,ChunkClass,spawnTransform));

					// 初始化传参
					if (deferredChunk != nullptr)
					{
						deferredChunk->rabdinSeed = 0;
						deferredChunk->voxelSize = VoxelSize;
						deferredChunk->chunkElements = ChunkLineElement;
						deferredChunk->chunkXindex = i;
						deferredChunk->chunkYindex = j;

						UGameplayStatics::FinishSpawningActor(deferredChunk, spawnTransform);
					}

					// 添加到列表中
					chunks.Add(deferredChunk);

					//TODO 将数据传递给Chunk；
				}
			}
		}
	}
}

bool AWorldManagerBase::CheckRadius(float x, float y)
{
	return (FVector(x,y,0) - characterPosition).Size() < ChunkSize * renderRange;
}

FVector2D AWorldManagerBase::GetEdgePoint(int width, int height)
{
	return FVector2D(FMath::RandRange(0,width),FMath::RandRange(0,height));
}

void AWorldManagerBase::Voronoi(int width, int height, int numVoronoiPoint)
{
	TArray<TArray<FVector2D>> vPoints;
	TArray<float> rands;

	for (int i = 0; i < numVoronoiPoint; i++)
	{
		FVector2D v = GetEdgePoint(width, height);

		for (int j = 0; j < 4; j++)
		{
			TArray<FVector2D> line;
			rands.Add(1.0f);

			line.Add(v);

			//v += FVector2D(FMath::Rand() - 0.5f, FMath::Rand() - 0.5f) * Overworld.Width * 0.5f;
			line.Add(v);
			vPoints.Add(line);
		}

	}

	//TArray<FVoronoiNode> nodes;
	//for each(TArray<FVoronoiNode> pts in vPoints)
	//{
	//	for (int j = 0; j < pts.Num() - 1; j++)
	//	{
	//		//FVoronoiNode node = FVoronoiNode(pts[j],pts[j + 1]);
	//		//nodes.Add(node);
	//	}
	//}

	//for (int x = 0; x < width; x++)
	//	for (int y = 0; y < height; y++)
	//		Overworld.Map.Map[x, y].Faults = GetVoronoiValue(nodes, x, y);

	//ScaleMap(Overworld.Map.Map, width, height, OverworldField.Faults);
	//OverworldImageOperations.Distort(Overworld.Map.Map, width, height, 20, 0.01f, OverworldField.Faults);




}
//
//void AWorldManagerBase::GenerateElevation()
//{
//	ElevationMap.SetNumUninitialized(WorldElements * WorldElements);
//	for (int32 i = 0; i < WorldElements; i++)
//	{
//		for (int32 j = 0; j < WorldElements; j++)
//		{
//			// 暂时进行一次取高度运算
//			ElevationMap[i + j * WorldElements] = GenerateNoiseHeight(FVector(i,j,1), 0.025f);
//		}
//	}
//}

bool AWorldManagerBase::UpdatePostion()
{
	auto chaPosition = UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation();

	characterPosition = chaPosition * FVector(1,1,0);
	if ((ChunkX != characterPosition.X/ChunkSizeHalf)||(ChunkY != characterPosition.Y / ChunkSizeHalf))
	{
		ChunkX = characterPosition.X / ChunkSizeHalf;
		ChunkY = characterPosition.Y / ChunkSizeHalf;
		return true;
	}
	else
	{
		return false;
	}
}

void AWorldManagerBase::RemoveChunk()
{
	for (int i = 0;i < chunkCords.Num();i++ )
	{
		if (!CheckRadius(ChunkSize * chunkCords[i].X + ChunkSizeHalf, ChunkSize * chunkCords[i].Y + ChunkSizeHalf))
		{
			// 删除Chunk和相关引用
			chunks[i]->Destroy(false);
			chunkCords.RemoveAt(i);
			chunks.RemoveAt(i);
		}

		//TODO 在干掉Chunk之前，将数据储存起来
	}
}

void AWorldManagerBase::CreateHeightFromLookup(TArray<float> lookup)
{
	OverworldCells.SetNumUninitialized(WorldElements* WorldElements);
	for (int i = 0; i < WorldElements; i++)
	{
		for (int j = 0; j<WorldElements; j++)
		{
			OverworldCells[i + j * WorldElements].SetValue(EOverworldField::Height, FMath::Clamp(lookup[i + j * WorldElements], 0.f, 1.f));
		}
	}
}

void AWorldManagerBase::OnConstruction(const FTransform& Transform)
{
	ChunkSize = ChunkLineElement * VoxelSize;
	ChunkSizeHalf = ChunkSize / 2;
	WorldElements = WorldChunkElements * ChunkLineElement;
	WorldSize = VoxelSize * WorldElements;

	// 列表初始化
	//ElevationMap.SetNumUninitialized(WorldElements* WorldElements);
	//FaultMap.SetNumUninitialized(WorldElements * WorldElements);

	//chunkCords.SetNumUninitialized(WorldChunkElements*WorldChunkElements);
	//chunks.SetNumUninitialized(WorldChunkElements * WorldChunkElements);
}

