// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldManagerBase.h"
#include "OverworldGenerator.generated.h"

UENUM(BlueprintType)
enum class EGenerationState : uint8
{
	NotStarted,
	Generating,
	Finished
};

UCLASS()
class UNWORLD_API AOverworldGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings")
	int NumCivilizations = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int NumRains = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int NumVolcanoes = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float RainfallScale = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int NumFaults = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float SeaLevel = 0.17f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings",Meta = (ExposeOnSpawn = true))
	float TemperatureScale = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	AWorldManagerBase* WorldManager;

	// Sets default values for this actor's properties
	AOverworldGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void GenerateWorld();

	UFUNCTION(BlueprintCallable, Category="Map")
	TArray<float> GenerateHeightMapLookup(int width,int height);

	UFUNCTION(BlueprintNativeEvent)
	float GenerateNoiseHeight(FVector wPos, float frequency);

	float GenerateNoiseHeight_Implementation(FVector wPos, float frequency);

};
