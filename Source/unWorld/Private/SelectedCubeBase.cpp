// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectedCubeBase.h"

const int32 bTriangles[] = { 2,1,0,0,3,2 };
const FVector2D bUVs[] = { FVector2D(0.0,0.0),FVector2D(0.0,1.0) ,FVector2D(1.0,1.0) ,FVector2D(1.0,0.0) };

const FVector bNormals0[] = { FVector::UpVector,FVector::UpVector ,FVector::UpVector ,FVector::UpVector };
const FVector bNormals1[] = { FVector::DownVector,FVector::DownVector ,FVector::DownVector ,FVector::DownVector };
const FVector bNormals2[] = { FVector::RightVector,FVector::RightVector ,FVector::RightVector ,FVector::RightVector };
const FVector bNormals3[] = { FVector::LeftVector,FVector::LeftVector ,FVector::LeftVector ,FVector::LeftVector };
const FVector bNormals4[] = { FVector::ForwardVector,FVector::ForwardVector ,FVector::ForwardVector ,FVector::ForwardVector };
const FVector bNormals5[] = { FVector::BackwardVector,FVector::BackwardVector ,FVector::BackwardVector ,FVector::BackwardVector };

const FVector bMask[] = { FVector::UpVector,FVector::DownVector,FVector::RightVector,FVector::LeftVector,FVector::ForwardVector,FVector::BackwardVector };

// Sets default values
ASelectedCubeBase::ASelectedCubeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//BuildBlock();
}

// Called when the game starts or when spawned
void ASelectedCubeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelectedCubeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASelectedCubeBase::OnConstruction(const FTransform& Transform)
{
	//mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("proceduralComponent"));
	mesh = NewObject<UProceduralMeshComponent>(this, "mesh");
	mesh->RegisterComponent();

	RootComponent = mesh;
	RootComponent->SetWorldTransform(Transform);

	Super::OnConstruction(Transform);

	BuildBlock();
}

void ASelectedCubeBase::BuildBlock()
{
	EBlockType blockType = EBlockType::Grass;

	BuildFace(blockType, EFaceType::Left, FVector(0, 0, 0), FVector::UpVector, FVector::ForwardVector, true);
	BuildFace(blockType, EFaceType::Right, FVector(0, 100, 0), FVector::UpVector, FVector::ForwardVector, false);
	BuildFace(blockType, EFaceType::Down, FVector(0, 0, 0), FVector::ForwardVector, FVector::RightVector, true);
	BuildFace(blockType, EFaceType::Up, FVector(0, 0, 100), FVector::ForwardVector, FVector::RightVector,false);
	BuildFace(blockType, EFaceType::BackGround, FVector(0, 0, 0), FVector::UpVector, FVector::RightVector,false);
	BuildFace(blockType, EFaceType::Forward, FVector(100, 0, 0), FVector::UpVector, FVector::RightVector,true);

	mesh->ClearAllMeshSections();
	mesh->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, VertexColor, Tangents, true);

	mesh->SetMaterial(0, Material);
}

void ASelectedCubeBase::BuildFace(EBlockType blocktype, EFaceType faceType, FVector wPos, FVector up, FVector right,bool reversed)
{
	int index = Vertices.Num();

	Vertices.Add(wPos + up * 100 + right * 100);
	Vertices.Add(wPos + right * 100);
	Vertices.Add(wPos);
	Vertices.Add(wPos + up * 100);

	//FVector2D uvWidth = FVector2D(0.25f, 0.25f);
	//FVector2D uvCorner = FVector2D(0.00f, 0.75f);

	//uvCorner.X += (float)((int)blocktype - 1) / 4;

	//UVs.Add(uvCorner);
	//UVs.Add(FVector2D(uvCorner.X, uvCorner.Y + uvWidth.Y));
	//UVs.Add(FVector2D(uvCorner.X + uvWidth.X, uvCorner.Y + uvWidth.Y));
	//UVs.Add(FVector2D(uvCorner.X + uvWidth.X, uvCorner.Y));

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

	switch (faceType) {
		case EFaceType::Up:
		{
			//Vertices.Add(wPos + FVector::UpVector * 50 + FVector::RightVector * 50 + FVector::BackwardVector * 50);
			//Vertices.Add(wPos + FVector::UpVector * 50 + FVector::LeftVector * 50 + FVector::BackwardVector * 50);
			//Vertices.Add(wPos + FVector::UpVector * 50 + FVector::LeftVector * 50 + FVector::ForwardVector * 50);
			//Vertices.Add(wPos + FVector::UpVector * 50 + FVector::RightVector * 50 + FVector::ForwardVector * 50);
			Normals.Append(bNormals0, ARRAY_COUNT(bNormals0));
			break;
		}
		case EFaceType::Down:
		{
			//Vertices.Add(wPos + FVector::DownVector * 50 + FVector::LeftVector * 50 + FVector::ForwardVector * 50);
			//Vertices.Add(wPos + FVector::DownVector * 50 + FVector::LeftVector * 50 + FVector::BackwardVector * 50);
			//Vertices.Add(wPos + FVector::DownVector * 50 + FVector::RightVector * 50 + FVector::BackwardVector * 50);
			//Vertices.Add(wPos + FVector::DownVector * 50 + FVector::RightVector * 50 + FVector::ForwardVector * 50);
			Normals.Append(bNormals1, ARRAY_COUNT(bNormals1));
			break;
		}
		case EFaceType::Right:
		{
			//Vertices.Add(wPos + FVector::RightVector * 50 + FVector::UpVector * 50 + FVector::ForwardVector * 50);
			//Vertices.Add(wPos + FVector::RightVector * 50 + FVector::DownVector * 50 + FVector::ForwardVector * 50);
			//Vertices.Add(wPos + FVector::RightVector * 50 + FVector::DownVector * 50 + FVector::BackwardVector * 50);
			//Vertices.Add(wPos + FVector::RightVector * 50 + FVector::UpVector * 50 + FVector::BackwardVector * 50);
			Normals.Append(bNormals3, ARRAY_COUNT(bNormals3));
			break;
		}
		case EFaceType::Left:
		{
			//Vertices.Add(wPos + FVector::LeftVector * 50 + FVector::UpVector * 50 + FVector::BackwardVector * 50);
			//Vertices.Add(wPos + FVector::LeftVector * 50 + FVector::DownVector * 50 + FVector::BackwardVector * 50);
			//Vertices.Add(wPos + FVector::LeftVector * 50 + FVector::DownVector * 50 + FVector::ForwardVector * 50);
			//Vertices.Add(wPos + FVector::LeftVector * 50 + FVector::UpVector * 50 + FVector::ForwardVector * 50);
			Normals.Append(bNormals2, ARRAY_COUNT(bNormals2));
			break;
		}
		case EFaceType::Forward:
		{
			//Vertices.Add(wPos + FVector::ForwardVector * 50 + FVector::LeftVector * 50 + FVector::UpVector * 50);
			//Vertices.Add(wPos + FVector::ForwardVector * 50 + FVector::LeftVector * 50 + FVector::DownVector * 50);
			//Vertices.Add(wPos + FVector::ForwardVector * 50 + FVector::RightVector * 50 + FVector::DownVector * 50);
			//Vertices.Add(wPos + FVector::ForwardVector * 50 + FVector::RightVector * 50 + FVector::UpVector * 50);
			Normals.Append(bNormals4, ARRAY_COUNT(bNormals4));
			break;
		}
		case EFaceType::BackGround:
		{
			//Vertices.Add(wPos + FVector::BackwardVector * 50 + FVector::RightVector * 50 + FVector::UpVector * 50);
			//Vertices.Add(wPos + FVector::BackwardVector * 50 + FVector::RightVector * 50 + FVector::DownVector * 50);
			//Vertices.Add(wPos + FVector::BackwardVector * 50 + FVector::LeftVector * 50 + FVector::DownVector * 50);
			//Vertices.Add(wPos + FVector::BackwardVector * 50 + FVector::LeftVector * 50 + FVector::UpVector * 50);
			Normals.Append(bNormals5, ARRAY_COUNT(bNormals5));
			break;
		}
	}

	UVs.Append(bUVs,ARRAY_COUNT(bUVs));

	FColor color = FColor(255, 255, 255, (int)faceType);
	VertexColor.Add(color);
	VertexColor.Add(color);
	VertexColor.Add(color);
	VertexColor.Add(color);
}

