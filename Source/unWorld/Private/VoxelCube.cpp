// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelCube.h"

// Sets default values
AVoxelCube::AVoxelCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVoxelCube::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVoxelCube::OnConstruction(const FTransform& Transform)
{
	ProduralMesh = NewObject<UProceduralMeshComponent>(this,"ProduralMesh");
	ProduralMesh->RegisterComponent();

	RootComponent = ProduralMesh;
	ProduralMesh->SetWorldTransform(Transform);
	
	BuildCube();
}

// Called every frame
void AVoxelCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVoxelCube::BuildCube()
{
	BuildFace(EFaceType::Up,FVector(0,0,100),FVector::ForwardVector,FVector::RightVector,false);
	BuildFace(EFaceType::Down, FVector(0, 0, 0), FVector::ForwardVector, FVector::RightVector, true);
	BuildFace(EFaceType::Forward, FVector(100, 0, 0), FVector::UpVector, FVector::RightVector, true);
	BuildFace(EFaceType::BackGround, FVector(0, 0, 0), FVector::UpVector, FVector::RightVector, false);
	BuildFace(EFaceType::Right, FVector(0, 100, 0), FVector::UpVector, FVector::ForwardVector, false);
	BuildFace(EFaceType::Left, FVector(0, 0, 0), FVector::UpVector, FVector::ForwardVector, true);

	ProduralMesh->ClearAllMeshSections();
	ProduralMesh->CreateMeshSection_LinearColor(0,Vertices,Triangles,Normals,UV0,VertexColors,Tangents,true);

	ProduralMesh->SetMaterial(0,Material);
}

void AVoxelCube::BuildFace(EFaceType facetype, FVector center, FVector up, FVector right, bool reversed)
{
	int index = Vertices.Num();
	
	Vertices.Add(center+up * 100 +right * 100);
	Vertices.Add(center+right * 100);
	Vertices.Add(center);
	Vertices.Add(center + up * 100);

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
	UV0.Append(bUVs,ARRAY_COUNT(bUVs));

	FColor color = FColor(255,255,255,(int)facetype);
	VertexColors.Add(color);
	VertexColors.Add(color);
	VertexColors.Add(color);
	VertexColors.Add(color);

}

