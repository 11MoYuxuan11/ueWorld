// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Chunk.h"
#include "VoxelCube.generated.h"

UCLASS()
class UNWORLD_API AVoxelCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVoxelCube();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UMaterialInterface* Material;

	UPROPERTY(BlueprintReadOnly)
	UProceduralMeshComponent* ProduralMesh;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FLinearColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void BuildCube();

	void BuildFace(EFaceType facetype,FVector center, FVector up,FVector right,bool reversed);
};
