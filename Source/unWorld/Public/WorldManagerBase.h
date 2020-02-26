// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldManagerBase.generated.h"

UCLASS()
class UNWORLD_API AWorldManagerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldManagerBase();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 WorldElements = 1024*1024;

	UPROPERTY(BlueprintReadOnly)
	TArray<bool> FaultMap;

	UPROPERTY(BlueprintReadOnly)
	bool UseRandomSeed;

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
};
