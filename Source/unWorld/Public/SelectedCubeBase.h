// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "SelectedCubeBase.generated.h"

UCLASS()
class UNWORLD_API ASelectedCubeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelectedCubeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* Material;

	UPROPERTY()
	UProceduralMeshComponent* proceduralComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
