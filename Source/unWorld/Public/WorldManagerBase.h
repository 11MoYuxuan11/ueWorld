// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkBase.h"
#include "WorldManagerBase.generated.h"

UENUM(BlueprintType)
enum class EOverworldField : uint8
{
	// 侵蚀
	Erosion = 0 UMETA(DisplayName ="Erosion"),
	// 风化
	Weathering=1 UMETA(DisplayName = "Weathering"),
	// 断层
	Faults=2 UMETA(DisplayName = "Faults"),
	// 高度
	Height=3 UMETA(DisplayName = "Height"),
	// 温度
	Temperature=4 UMETA(DisplayName = "Temperature"),
	// 降雨量
	Rainfall=5 UMETA(DisplayName = "Rainfall"),
	// 数值字段
	NumFields=7 UMETA(DisplayName = "NumFields")
};

USTRUCT(BlueprintType)
struct FOverworldCell
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	uint8 Erosion;
	UPROPERTY(BlueprintReadOnly)
		uint8 Weathering;
	UPROPERTY(BlueprintReadOnly)
		uint8 Faults;
	UPROPERTY(BlueprintReadOnly)
		uint8 Height;
	UPROPERTY(BlueprintReadOnly)
		uint8 Temperature;
	UPROPERTY(BlueprintReadOnly)
		uint8 Rainfall;

	float GetValue(EOverworldField fieldType)
	{
		switch (fieldType)
		{
		case EOverworldField::Erosion:
			return Erosion / 255.f;
		case EOverworldField::Weathering:
			return Weathering / 255.f;
		case EOverworldField::Faults:
			return Faults / 255.f;
		case EOverworldField::Height:
			return Height / 255.f;
		case EOverworldField::Temperature:
			return Temperature / 255.f;
		case EOverworldField::Rainfall:
			return Rainfall / 255.f;
		}
	}

	void SetValue(EOverworldField fieldType, float Value) {
		uint8 _value = FMath::Min(FMath::Max(Value * 255.f, 0.f), 255.f);
		switch (fieldType)
		{
		case EOverworldField::Erosion:
			Erosion = _value;
			break;
		case EOverworldField::Weathering:
			Weathering = _value;
			break;
		case EOverworldField::Faults:
			Faults = _value;
			break;
		case EOverworldField::Height:
			Height = _value;
			break;
		case EOverworldField::Temperature:
			Temperature = _value;
			break;
		case EOverworldField::Rainfall:
			Rainfall = _value;
			break;
		}
	}
};

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
	int32 WorldElements;

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

	void CreateHeightFromLookup(TArray<float> lookup);

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	
	FVector characterPosition;

	TArray<FVector2D> chunkCords;

	//每个Chunk都包含16*16*256个block
	TArray<AChunkBase*> chunks;

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
