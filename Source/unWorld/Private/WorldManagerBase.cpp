// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManagerBase.h"

// Sets default values
AWorldManagerBase::AWorldManagerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChunkSize = ChunkLineElement * VoxelSize;
	ChunkSizeHalf = ChunkSize / 2;


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

void AWorldManagerBase::CreateWorld()
{
	//创建断层 Fault
	RandomFillMap();
	for (int i = 0; i<4 ;i++)
	{
		SmoothMap();
	}

	//创建高度图（大陆、高山和山丘不同起伏和噪声）Elevation

	


	//腐蚀（降水量）Rainfall

	// 温度图，受高度和经纬度影响Temperature

	//地质排水情况Drainage，可以影响当地能否形成湖泊、湿地和河流。同样影响了当地的土质（进一步影响植被）

	//生物群落，受到高度、降水量和温度等因素影响
	//目前在计划中的生物群落包括草地、沙漠、森林、丛林、针叶林、苔原和地狱

	//矿洞&地下城

	//自然地标

	//文明 细胞自动机 文明会选择合适的生物群落产生
	//文明之间会因为空间上的距离、彼此文化冲突引发战争和贸易

	//人工地标
	//有了文明之后，文明会在合适的位置建立城镇，每个文明开始时通常有一个主城，几个堡垒和若干村镇

	//确定玩家出生点 根据玩家的种族选择一个村镇出生
}

void AWorldManagerBase::AddChunk()
{
	for (int i=0;i<renderRange;i++)
	{
		for (int j = 0;j<renderRange; j++)
		{
			//if ()
			//{
			//	
			//}
		}
	}
}

int32 AWorldManagerBase::GenerateHeight_Implementation(FVector wPos)
{
	return 0;
}
