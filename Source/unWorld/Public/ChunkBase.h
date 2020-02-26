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
	int32 RandSeed;

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

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FColor> VertexColor;
	TArray<FProcMeshTangent> Tangents;

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

	UFUNCTION(BlueprintNativeEvent)
	TArray<int32> calculateNosie();

	UFUNCTION(BlueprintNativeEvent)
	int generateHeight(FVector wPos);

	virtual TArray<int32> calculateNosie_Implementation();

	virtual int generateHeight_Implementation(FVector wPos);

	void Initmap();

private:

	//EBlockType GenerateBlockType(FVector wPos);
	//int GenerateHeight(FVector wPos);
	void BuildBlock(FVector wPos);
	void BuildFace(EBlockType blocktype, EFaceType faceType, FVector corner, FVector up, FVector right,bool reversed);

	bool CheckNeedBuildFace(FVector wPos);
	EBlockType GetChunkFieldByVector(FVector wPos);

	EBlockType GetBlockType(int x, int y, int z);
	EBlockType GenerateBlockType(FVector wPos);

	//SCubeData ToCubeData(Byte data);
	//Byte ToByte(SCubeData sdata);
};


UENUM(BlueprintType)
enum class EBlockType : uint8
{
	None,
	Dirt,
	Grass,
	Gravel,
};

UENUM(BlueprintType)
enum class EFaceType : uint8
{
	Up,
	Down,
	Forward,
	BackGround,
	Right,
	Left
};

USTRUCT(BlueprintType)
struct FCubeData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		bool active;
	UPROPERTY(BlueprintReadOnly)
		bool isTransparent;
	UPROPERTY(BlueprintReadOnly)
		EBlockType blockType;

	FCubeData(bool _active, bool _isTransparent, EBlockType _blockType) {
		active = _active;
		isTransparent = _isTransparent;
		blockType = _blockType;
	}

	FCubeData(){
		active = false;
		isTransparent = false;
		blockType = EBlockType::None;
	}
};
