// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkBase.h"
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
	int32 WorldElements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	int32 WorldChunkElements = 1024;

	int32 ChunkX;
	int32 ChunkY;
	int32 WorldSize;

	TSubclassOf<class AChunkBase> ChunkClass; 

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
	void CreateWorld();

	UFUNCTION(BlueprintCallable)
	void AddChunk();

	void GenerateElevation();

	UFUNCTION(BlueprintCallable)
	bool UpdatePostion();

	UFUNCTION(BlueprintNativeEvent)
	int32 GenerateHeight(FVector wPos, float frequency, float amplitude);

	int32 GenerateHeight_Implementation(FVector wPos, float frequency, float amplitude);

	UFUNCTION(BlueprintCallable)
	void RemoveChunk();

private:
	
	FVector characterPosition;

	TArray<FVector2D> chunkCords;

	//每个Chunk都包含16*16*256个block
	TArray<AChunkBase*> chunks;

private:
	bool CheckRadius(float x,float y);
};
