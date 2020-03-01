// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkBase.h"
#include "Overworld.h"
#include "WorldManagerBase.generated.h"

UCLASS()
class UNWORLD_API AWorldManagerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldManagerBase();

	UPROPERTY(BlueprintReadOnly)
	TArray<bool> FaultMap;
	UPROPERTY(BlueprintReadOnly)
	TArray<int32> ElevationMap;

	UPROPERTY(BlueprintReadOnly)
	bool UseRandomSeed;

	UPROPERTY(BlueprintReadOnly)
	int32 ChunkSize;

	UPROPERTY(BlueprintReadOnly)
	int32 ChunkSizeHalf;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	int32 ChunkLineElement = 16;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	int32 VoxelSize = 100;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Setting")
	int32 renderRange = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	int32 WorldElements = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	int32 WorldChunkElements = 1024;

	int32 ChunkX;
	int32 ChunkY;
	int32 WorldSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AChunkBase> ChunkClass; 

	FString LoadingMessage = "";
	float LoadingProgress = 0.f;

	UPROPERTY(BlueprintReadOnly)
	TArray<FOverworldCell> OverworldCells;

	UPROPERTY(BlueprintReadOnly)
	//每个Chunk都包含16*16*256个block
	TArray<AChunkBase*> chunks;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void RandomFillMap();
	
	UFUNCTION(BlueprintCallable)
	int32 GetSurroundingWalls(int X,int Y);
	
	UFUNCTION(BlueprintCallable)
	void SmoothMap();

	UFUNCTION(BlueprintCallable)
	void AddChunk();

	UFUNCTION(BlueprintCallable)
	bool UpdatePostion();

	UFUNCTION(BlueprintCallable)
	void RemoveChunk();

	//计算降雨值
	void CalculateRain(int32 width,int32 height);

	UFUNCTION(BlueprintCallable)
	void CreateHeightFromLookup(TArray<float> lookup);

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	
	FVector characterPosition;

	TArray<FVector2D> chunkCords;
	

private:
	bool CheckRadius(float x,float y);

	//维诺图
	void Voronoi(int width,int height,int numVoronoiPoint);

	// 获取随机边缘点
	FVector2D GetEdgePoint(int width, int height);

};


//USTRUCT(BlueprintType)
//struct FVoronoiNode
//{
//	GENERATED_BODY()
//
//	UPROPERTY(BlueprintReadOnly)
//	FVector2D PointA;
//
//	UPROPERTY(BlueprintReadOnly)
//	FVector2D PointB;
//
//	UPROPERTY(BlueprintReadOnly)
//	float dist;
//
//	FVoronoiNode(FVector2D pointA, FVector2D pointB) {
//		PointA = pointA;
//		PointB = pointB;
//	}
//};
