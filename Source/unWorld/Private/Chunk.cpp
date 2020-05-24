// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"

// Sets default values
AChunk::AChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChunk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChunk::OnConstruction(const FTransform& Transform) 
{
	ProduralMesh = NewObject<UProceduralMeshComponent>(this, "ProduralMesh");
	ProduralMesh->RegisterComponent();

	RootComponent = ProduralMesh;
	ProduralMesh->SetWorldTransform(Transform);

	BuildChunk();
}

void AChunk::BuildChunk() {
	
	for (int i = 0; i < ChunkElements; i++)
	{
		for (int j = 0; j < ChunkElements; j++)
		{
			BuildBlock(FVector(i * VoxelSize,j * VoxelSize,0));
		}
	}

	// ¸üÐÂProduralMesh
	ProduralMesh->ClearAllMeshSections();
	ProduralMesh->CreateMeshSection_LinearColor(0,Vertices,Triangles,Normals,UV0,VertexColors,Tangents,true);

	ProduralMesh->SetMaterial(0, Material);
}


void AChunk::BuildBlock(FVector wPos)
{
	BuildFace(EFaceType::Up, wPos + FVector(0, 0, VoxelSize), FVector::ForwardVector, FVector::RightVector, false);
	BuildFace(EFaceType::Down, wPos + FVector(0, 0, 0), FVector::ForwardVector, FVector::RightVector, true);
	BuildFace(EFaceType::Forward, wPos + FVector(VoxelSize, 0, 0), FVector::UpVector, FVector::RightVector, true);
	BuildFace(EFaceType::BackGround, wPos + FVector(0, 0, 0), FVector::UpVector, FVector::RightVector, false);
	BuildFace(EFaceType::Right, wPos + FVector(0, VoxelSize, 0), FVector::UpVector, FVector::ForwardVector, false);
	BuildFace(EFaceType::Left, wPos + FVector(0, 0, 0), FVector::UpVector, FVector::ForwardVector, true);
}

void AChunk::BuildFace(EFaceType facetype, FVector center, FVector up, FVector right, bool reversed)
{
	int index = Vertices.Num();

	Vertices.Add(center + up * VoxelSize + right * VoxelSize);
	Vertices.Add(center + right * VoxelSize);
	Vertices.Add(center);
	Vertices.Add(center + up * VoxelSize);

	if (reversed)
	{
		Triangles.Add(index + 0);
		Triangles.Add(index + 1);
		Triangles.Add(index + 2);
		Triangles.Add(index + 2);
		Triangles.Add(index + 3);
		Triangles.Add(index + 0);
	}
	else
	{
		Triangles.Add(index + 1);
		Triangles.Add(index + 0);
		Triangles.Add(index + 2);
		Triangles.Add(index + 3);
		Triangles.Add(index + 2);
		Triangles.Add(index + 0);
	}

	const FVector2D bUVs[] = { FVector2D(0.0,0.0),FVector2D(0.0,1.0) ,FVector2D(1.0,1.0) ,FVector2D(1.0,0.0) };
	UV0.Append(bUVs, ARRAY_COUNT(bUVs));

	FColor color = FColor(255, 255, 255, (int)facetype);
	VertexColors.Add(color);
	VertexColors.Add(color);
	VertexColors.Add(color);
	VertexColors.Add(color);

}