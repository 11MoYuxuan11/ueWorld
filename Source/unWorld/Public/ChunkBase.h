// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
//#include "SimplexNoiseBPLibrary.h"
#include "ChunkBase.generated.h"

UCLASS()
class UNWORLD_API AChunkBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunkBase();

	//static TArray<AChunkBase*> chunks;

	static const int width = 30;
	static const int height = 30;

	float baseHeight = 10.f;

	float frequency = 0.025f;

	float amplitude = 1.f;

	TMap<FVector,EBlockType*>  map;

	UPROPERTY()
		UProceduralMeshComponent* proceduralComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitMap();

private:

	EBlockType GenerateBlockType(FVector wPos);
	int GenerateHeight(FVector wPos);
};

UENUM(BlueprintType)
enum class EBlockType:uint8
{
	None,
	Dirt,
	Grass,
	Gravel,
};
