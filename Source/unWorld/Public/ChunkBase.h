// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "GridBase.h"
#include "ChunkBase.generated.h"

UCLASS()
class UNWORLD_API AChunkBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunkBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UMaterialInterface*> Materials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		int32 rabdinSeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		int32 voxelSize = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		int32 chunkElements = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		int32 chunkXindex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		int32 chunkYindex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float xMult = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float yMult = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float zMult = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float weight = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float freq = 1;
	
	UPROPERTY(BlueprintReadOnly)
	FVector offset0;
	UPROPERTY(BlueprintReadOnly)
	FVector offset1;
	UPROPERTY(BlueprintReadOnly)
	FVector offset2;


	UPROPERTY()
		int32 chunkTotalElements;
	UPROPERTY()
		int32 chunkZElements;
	UPROPERTY()
		int32 chunkLineElementsP2;
	UPROPERTY()
		int32 voxelSizeHalf;

	UPROPERTY()
	TArray<int32> chunkFields;

	UPROPERTY()
		UProceduralMeshComponent* proceduralComponent;

	UFUNCTION(BlueprintNativeEvent)
	TArray<int32> calculateNosie();

	UFUNCTION(BlueprintNativeEvent)
	int generateHeight();

	virtual TArray<int32> calculateNosie_Implementation();

	virtual int generateHeight_Implementation();

	void Initmap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	void GenerateChunk();

	void UpdateMesh();

	void BuildChunk();

private:

	//EBlockType GenerateBlockType(FVector wPos);
	//int GenerateHeight(FVector wPos);
	void BuildBlock(int x, int y, int z, TArray<FVector> verts, TArray<FVector2D> uvs, TArray<int> tris);
	void BuildFace(EBlockType blocktype, FVector corner, FVector up, FVector right,
		bool reversed, TArray<FVector> verts, TArray<FVector2D> uvs, TArray<int> tris);

	bool CheckNeedBuildFace(int x,int y,int z);
	int32 GetChunkFieldByVector(int x, int y, int z);

	EBlockType GetBlockType(int x, int y, int z);

	EBlockType GenerateBlockType(int x, int y ,int z);

	int GenerateHeight(int x, int y ,int z);
};

UENUM(BlueprintType)
enum class EBlockType:uint8
{
	None,
	Dirt,
	Grass,
	Gravel,
};

