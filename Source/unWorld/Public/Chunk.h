// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Overworld.h"
#include "Chunk.generated.h"

UCLASS()
class UNWORLD_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();

	UPROPERTY(BlueprintReadOnly)
	TArray<FOverworldCell> ChunkCells;
	UPROPERTY(BlueprintReadOnly)
	AOverworld* OverWorld;
	UPROPERTY(BlueprintReadOnly)
	FIntVector ChunkPosition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
