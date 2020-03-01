// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chunk.h"
#include "Overworld.generated.h"

UENUM(BlueprintType)
enum class EOverworldField : uint8
{
	// 侵蚀
	Erosion = 0 UMETA(DisplayName = "Erosion"),
	// 风化
	Weathering = 1 UMETA(DisplayName = "Weathering"),
	// 断层
	Faults = 2 UMETA(DisplayName = "Faults"),
	// 高度
	Height = 3 UMETA(DisplayName = "Height"),
	// 温度
	Temperature = 4 UMETA(DisplayName = "Temperature"),
	// 降雨量
	Rainfall = 5 UMETA(DisplayName = "Rainfall"),
	// 数值字段
	NumFields = 7 UMETA(DisplayName = "NumFields")
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
class UNWORLD_API AOverworld : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOverworld();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Settings")
	int32 VoxelSize = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 ChunkBlockElements = 16;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 WorldChunkElements = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 RenderRange = 3;

	UPROPERTY(BlueprintReadOnly)
	int32 ChunkSize;
	UPROPERTY(BlueprintReadOnly)
	int32 WorldBlockElements;

	UPROPERTY(BlueprintReadOnly)
	TArray<FOverworldCell> WorldCells;
	UPROPERTY(BlueprintReadOnly)
	FIntVector ChunkPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AChunk> ChunkClass;
	UPROPERTY(BlueprintReadOnly)
	TArray<FVector2D> ChunkCords;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable)
	void GeneratWorld();

	UFUNCTION(BlueprintCallable)
	void UpdatePosition();

	UFUNCTION(BlueprintCallable)
	void AddChunk();
	//UFUNCTION(BlueprintCallable)
	//TArray<FOverworldCell> AOverworld::GetChunkCells(FIntVector chunkPos);

private:
	FIntVector GetChunkLocation(FVector worldPos);
};
