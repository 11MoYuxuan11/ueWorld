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

	//proceduralComponent = NewObject<UProceduralMeshComponent>(this, "proceduralComponent");
	//proceduralComponent->RegisterComponent();

	//TArray<FVector> Vertices;
	//TArray<int32> Triangles;
	//TArray<FVector> Normals;
	//TArray<FVector2D> UVs;
	//TArray<FProcMeshTangent> Tangents;
	//TArray<FColor> VertexColor;

	//int32 voxelSizeHalf = 50;
	//int32 voxelSize = voxelSizeHalf * 2;

	//int32 x = 1;
	//int32 y = 1;
	//int32 z = 1;

	//for (int i = 0; i < 6; i++)
	//{
	//		Triangles.Add(bTriangles[0]);
	//		Triangles.Add(bTriangles[1]);
	//		Triangles.Add(bTriangles[2]);
	//		Triangles.Add(bTriangles[3]);
	//		Triangles.Add(bTriangles[4]);
	//		Triangles.Add(bTriangles[5]);

	//		//triangle_num += 4;

	//		switch (i)
	//		{
	//		case 0: {
	//			Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));

	//			Normals.Append(bNormals0, ARRAY_COUNT(bNormals0));
	//			break;
	//		}
	//		case 1: {
	//			Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));

	//			Normals.Append(bNormals1, ARRAY_COUNT(bNormals1));
	//			break;
	//		}
	//		case 2: {
	//			Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));

	//			Normals.Append(bNormals2, ARRAY_COUNT(bNormals2));
	//			break;
	//		}
	//		case 3: {
	//			Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));

	//			Normals.Append(bNormals3, ARRAY_COUNT(bNormals3));
	//			break;
	//		}
	//		case 4: {
	//			Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));

	//			Normals.Append(bNormals4, ARRAY_COUNT(bNormals4));
	//			break;
	//		}
	//		case 5: {
	//			Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
	//			Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));

	//			Normals.Append(bNormals5, ARRAY_COUNT(bNormals5));
	//			break;
	//		}
	//		}

	//		UVs.Append(bUVs, ARRAY_COUNT(bUVs));


	//		FColor color = FColor(255, 255, 255, i);
	//		VertexColor.Add(color);
	//		VertexColor.Add(color);
	//		VertexColor.Add(color);
	//		VertexColor.Add(color);
	//}

	//proceduralComponent->ClearAllMeshSections();
	//proceduralComponent->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, VertexColor, Tangents, true);
	//proceduralComponent->SetMaterial(0,Material);
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

