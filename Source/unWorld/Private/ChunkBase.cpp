// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkBase.h"


const int32 bTriangles[] = {2,1,0,0,3,2};
const FVector2D bUVs[] = {FVector2D(0.0,0.0),FVector2D(0.0,1.0) ,FVector2D(1.0,1.0) ,FVector2D(1.0,0.0) };

const FVector bNormals0[] = {FVector::UpVector,FVector::UpVector ,FVector::UpVector ,FVector::UpVector };
const FVector bNormals1[] = { FVector::DownVector,FVector::DownVector ,FVector::DownVector ,FVector::DownVector };
const FVector bNormals2[] = { FVector::RightVector,FVector::RightVector ,FVector::RightVector ,FVector::RightVector };
const FVector bNormals3[] = { FVector::LeftVector,FVector::LeftVector ,FVector::LeftVector ,FVector::LeftVector };
const FVector bNormals4[] = { FVector::ForwardVector,FVector::ForwardVector ,FVector::ForwardVector ,FVector::ForwardVector };
const FVector bNormals5[] = { FVector::BackwardVector,FVector::BackwardVector ,FVector::BackwardVector ,FVector::BackwardVector };

const FVector bMask[] = {FVector::UpVector,FVector::DownVector,FVector::RightVector,FVector::LeftVector,FVector::ForwardVector,FVector::BackwardVector};

// Sets default values
AChunkBase::AChunkBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AChunkBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AChunkBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AChunkBase::DisconnectNeighbors()
//{
//	for (int i = 0; i < 6; i++)
//	{
//		if (NeighborChunks.IsValidIndex(i))
//		{
//			//NeighborChunks[i].NeighborChunks[(int)(((AdjacentDirection)i).ChunkOpposite())] = NULL;
//			//NeighborChunks[i] = NULL;
//		}
//	}
//}
//
//EBlockType AChunkBase::GetBlockType(int x, int y, int z)
//{
//	return EBlockType();
//}

void AChunkBase::OnConstruction(const FTransform& Transform)
{
	chunkZElements = 80;
	chunkTotalElements = chunkElements * chunkElements * chunkZElements;
	chunkLineElementsP2 = chunkElements * chunkElements;
	voxelSizeHalf = voxelSize / 2;

	FString string = "Voxel_" + FString::FromInt(chunkXindex) + "_" + FString::FromInt(chunkYindex);
	FName name = FName(*string);
	proceduralComponent = NewObject<UProceduralMeshComponent>(this, name);
	proceduralComponent->RegisterComponent();

	RootComponent = proceduralComponent;
	RootComponent->SetWorldTransform(Transform);

	Super::OnConstruction(Transform);

	GenerateChunk();
	UpdateMesh();

}

void AChunkBase::GenerateChunk()
{
	chunkFields.SetNumUninitialized(chunkTotalElements);


	for (int32 x= 0;x<chunkElements;x++)
	{
		for (int32 y = 0; y < chunkElements; y++)
		{
			for (int32 z = 0;z < chunkZElements; z++)
			{
				int32 index = x + (y * chunkElements) +(z * chunkLineElementsP2);

				chunkFields[index] = (z < 30) ? 1 : 0;

			}
		}
	}

}

void AChunkBase::UpdateMesh()
{
	
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FProcMeshTangent> Tangents;
	TArray<FColor> VertexColor;

	int32 elementID = 0;

	for (int32 x = 0; x < chunkElements; x++)
	{
		for (int32 y = 0; y < chunkElements; y++)
		{
			for (int32 z = 0; z < chunkZElements; z++)
			{
				int32 index = x + (y * chunkElements) + (z * chunkLineElementsP2);
				int32 meshIndex = chunkFields[index];

				if (meshIndex > 0)
				{
					meshIndex--;
					
					// add faces, Verticies, UVS and Normals; ¹²6¸öÃæ
					int triangle_num = 0;
					for (int i = 0;i < 6 ; i++)
					{
						int newIndex = index + bMask[i].X +(bMask[i].Y * chunkElements) + (bMask[i].Z * chunkLineElementsP2);

						bool flag = false;
						if (meshIndex >= 20)
						{
							flag = true;
						}
						else if ((x + bMask[i].X < chunkElements) && (x + bMask[i].X >= 0) 
							&&( y + bMask[i].Y < chunkElements)&& ( y+bMask[i].Y >= 0 ) )
						{
							if (newIndex < chunkFields.Num() && newIndex >= 0)
							{
								if ( chunkFields[newIndex] < 1 )
								{
									flag = true;
								}
							}
						}
						else
						{
							flag = true;
						}

						if (flag)
						{
							Triangles.Add(bTriangles[0] + triangle_num + elementID);
							Triangles.Add(bTriangles[1] + triangle_num + elementID);
							Triangles.Add(bTriangles[2] + triangle_num + elementID);
							Triangles.Add(bTriangles[3] + triangle_num + elementID);
							Triangles.Add(bTriangles[4] + triangle_num + elementID);
							Triangles.Add(bTriangles[5] + triangle_num + elementID);

							triangle_num += 4;

							switch (i)
							{
								case 0: {
									Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));

									Normals.Append(bNormals0, ARRAY_COUNT(bNormals0));
									break;
								}
								case 1: {
									Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));

									Normals.Append(bNormals1, ARRAY_COUNT(bNormals1));
									break;
								}
								case 2: {
									Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));

									Normals.Append(bNormals2, ARRAY_COUNT(bNormals2));
									break;
								}
								case 3: {
									Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));

									Normals.Append(bNormals3, ARRAY_COUNT(bNormals3));
									break;
								}
								case 4: {
									Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));

									Normals.Append(bNormals4, ARRAY_COUNT(bNormals4));
									break;
								}
								case 5: {
									Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), -voxelSizeHalf + (z * voxelSize)));
									Vertices.Add(FVector(-voxelSizeHalf + (x * voxelSize), -voxelSizeHalf + (y * voxelSize), voxelSizeHalf + (z * voxelSize)));

									Normals.Append(bNormals5, ARRAY_COUNT(bNormals5));
									break;
								}
							}
							
							UVs.Append(bUVs, ARRAY_COUNT(bUVs));


							FColor color = FColor(255, 255, 255, i);
							VertexColor.Add(color);
							VertexColor.Add(color);
							VertexColor.Add(color);
							VertexColor.Add(color);
						}
					}
					elementID += triangle_num;
				}
			}
		}
	}

	proceduralComponent->ClearAllMeshSections();
	proceduralComponent->CreateMeshSection(0,Vertices,Triangles,Normals,UVs,VertexColor,Tangents,true);

}

//EBlockType AChunkBase::GenerateBlockType(FVector wPos)
//{
//	if (wPos.Y >= height)
//	{
//		return EBlockType::None;
//	}
//	
//	float genHeight = GenerateHeight(wPos);
//
//	if (wPos.Y > genHeight)
//	{
//		return EBlockType::None;
//	}
//
//	else if (wPos.Y == genHeight)
//	{
//		return EBlockType::Grass;
//	}
//
//	else if (wPos.Y < genHeight && wPos.Y > genHeight - 5)
//	{
//		return EBlockType::Dirt;
//	}
//
//	return EBlockType::Gravel;
//}
//
//int AChunkBase::GenerateHeight(FVector wPos)
//{
//	
//	float X = wPos.X * frequency;
//	float Y = wPos.Y * frequency;
//
//	//return USimplexNoiseBPLibrary::SimplexNoise2D(X, Y) * amplitude;
//	return 1;
//}