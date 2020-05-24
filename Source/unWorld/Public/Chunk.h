// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Chunk.generated.h"

UENUM(BlueprintType)
enum class EFaceType : uint8
{
	Up,
	Down,
	Right,
	Left,
	Forward,
	BackGround
};

UENUM(BlueprintType)
enum class EBlockType : uint8
{
	None = 0,
	Dirt = 1,
	Grass = 3,
	Gravel = 4,
};

UCLASS()
class UNWORLD_API AChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunk();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ChunkElements = 16;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 VoxelSize = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable)
	void BuildChunk();
	UFUNCTION(BlueprintCallable)
	void BuildBlock(FVector wPos);
	UFUNCTION(BlueprintCallable)
	void BuildFace(EFaceType facetype, FVector center, FVector up, FVector right, bool reversed);

};
