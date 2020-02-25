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

TArray<int32> AChunkBase::calculateNosie_Implementation()
{
	TArray<int32> aa;
	aa.SetNum(chunkLineElementsP2);
	return aa;
}

int AChunkBase::generateHeight_Implementation()
{
	return 0;
}

void AChunkBase::Initmap()
{
	//offset0 = FVector(Random.value * 1000, Random.value * 1000, Random.value * 1000);
	//offset1 = FVector(Random.value * 1000, Random.value * 1000, Random.value * 1000);
	//offset2 = FVector(Random.value * 1000, Random.value * 1000, Random.value * 1000);

	//初始化Map
	//map = new BlockType[width, height, width];

	//遍历map，生成其中每个Block的信息
	for (int x = 0; x < chunkElements; x++)
	{
		for (int y = 0; y < chunkElements; y++)
		{
			for (int z = 0; z < chunkZElements; z++)
			{
				int32 index = x + (y * chunkElements) + (z * chunkLineElementsP2);
				auto wPos = FVector(x, y, z) + this->GetActorLocation();
				chunkFields[index] = (int)GenerateBlockType(wPos.X, wPos.Y,wPos.Z);
			}
		}
	}

	//根据生成的信息，Build出Chunk的网格
	BuildChunk();
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

	//GenerateChunk();
	//UpdateMesh();
	Initmap();
}

void AChunkBase::GenerateChunk()
{
	chunkFields.SetNumUninitialized(chunkTotalElements);

	TArray<int32> noise = calculateNosie();

	for (int32 x= 0;x<chunkElements;x++)
	{
		for (int32 y = 0; y < chunkElements; y++)
		{
			for (int32 z = 0;z < chunkZElements; z++)
			{
				int32 index = x + (y * chunkElements) +(z * chunkLineElementsP2);

				chunkFields[index] = (z < 30 + noise[x + y * chunkElements]) ? 1 : 0;

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
					
					// add faces, Verticies, UVS and Normals; 共6个面
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

	int s = 0;
	while (s < Materials.Num())
	{
		proceduralComponent->SetMaterial(s, Materials[s]);
		s++;
	}

}

void AChunkBase::BuildChunk()
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FProcMeshTangent> Tangents;
	TArray<FColor> VertexColor;

	for (int x = 0;x< chunkElements;x++)
	{
		for (int y = 0; y < chunkElements; x++)
		{
			for (int z = 0;z < chunkZElements; z++)
			{
				BuildBlock(x,y,z, Vertices ,UVs , Triangles);
			}
		}
	}

	proceduralComponent->ClearAllMeshSections();
	proceduralComponent->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, VertexColor, Tangents, true);

	int s = 0;
	while (s < Materials.Num())
	{
		proceduralComponent->SetMaterial(s, Materials[s]);
		s++;
	}

}

void AChunkBase::BuildBlock(int x, int y, int z, TArray<FVector> verts, TArray<FVector2D> uvs, TArray<int> tris)
{
	if (GetChunkFieldByVector(x, y, z) == 0) return;
	
	EBlockType blockType = GetBlockType(x,y,z);

	//Left
	if (CheckNeedBuildFace(x - 1, y, z))
		BuildFace(blockType, FVector(x, y, z), FVector::UpVector, FVector::ForwardVector, false, verts, uvs, tris);
	//Right
	if (CheckNeedBuildFace(x + 1, y, z))
		BuildFace(blockType, FVector(x + 1, y, z), FVector::UpVector, FVector::ForwardVector, true, verts, uvs, tris);

	//Bottom
	if (CheckNeedBuildFace(x, y - 1, z))
		BuildFace(blockType, FVector(x, y, z), FVector::ForwardVector, FVector::RightVector, false, verts, uvs, tris);
	//Top
	if (CheckNeedBuildFace(x, y + 1, z))
		BuildFace(blockType, FVector(x, y + 1, z), FVector::ForwardVector, FVector::RightVector, true, verts, uvs, tris);

	//Back
	if (CheckNeedBuildFace(x, y, z - 1))
		BuildFace(blockType, FVector(x, y, z), FVector::UpVector, FVector::RightVector, true, verts, uvs, tris);
	//Front
	if (CheckNeedBuildFace(x, y, z + 1))
		BuildFace(blockType, FVector(x, y, z + 1), FVector::UpVector, FVector::RightVector, false, verts, uvs, tris);
}

bool AChunkBase::CheckNeedBuildFace(int x, int y, int z)
{
	if (y < 0) return false;
	auto type = GetBlockType(x,y,z);

	switch (type)
	{
		case EBlockType::None:
			return true;
		default:
			return false;
	}
}

int32 AChunkBase::GetChunkFieldByVector(int x, int y, int z)
{
	return chunkFields[x + y * chunkElements + z * chunkLineElementsP2];
}

EBlockType AChunkBase::GetBlockType(int x, int y, int z) {
	return (EBlockType)GetChunkFieldByVector(x,y,z);
}

EBlockType AChunkBase::GenerateBlockType(int x, int y, int z)
{
	////z坐标是否在Chunk内
	//if (z >= chunkZElements)
	//{
	//	return EBlockType::None;
	//}

	////获取当前位置方块随机生成的高度值
	////float genHeight = GenerateHeight(wPos);

	////当前方块位置高于随机生成的高度值时，当前方块类型为空
	//if (y > genHeight)
	//{
	//	return EBlockType::None;
	//}
	////当前方块位置等于随机生成的高度值时，当前方块类型为草地
	//else if (y == genHeight)
	//{
	//	return EBlockType::Grass;
	//}
	////当前方块位置小于随机生成的高度值 且 大于 genHeight - 5时，当前方块类型为泥土
	//else if (y < genHeight && y > genHeight - 5)
	//{
	//	return EBlockType::Dirt;
	//}
	////其他情况，当前方块类型为碎石
	//return EBlockType::Gravel;
	return EBlockType::None;
}

int AChunkBase::GenerateHeight(int x, int y, int z)
{
	//让随机种子，振幅，频率，应用于我们的噪音采样结果
	//float x0 = (x + offset0.x) * frequency;
	//float y0 = (y + offset0.y) * frequency;
	//float z0 = (z + offset0.z) * frequency;

	//float x1 = (x + offset1.x) * frequency * 2;
	//float y1 = (y + offset1.y) * frequency * 2;
	//float z1 = (z + offset1.z) * frequency * 2;

	//float x2 = (x + offset2.x) * frequency / 4;
	//float y2 = (y + offset2.y) * frequency / 4;
	//float z2 = (z + offset2.z) * frequency / 4;

	//float noise0 = Noise.Generate(x0, y0, z0) * amplitude;
	//float noise1 = Noise.Generate(x1, y1, z1) * amplitude / 2;
	//float noise2 = Noise.Generate(x2, y2, z2) * amplitude / 4;

	////在采样结果上，叠加上baseHeight，限制随机生成的高度下限
	//return FMathf.Floor(noise0 + noise1 + noise2 + baseHeight);
	return 0;
}

void AChunkBase::BuildFace(EBlockType blocktype, FVector corner, FVector up, FVector right, 
		bool reversed, TArray<FVector> verts, TArray<FVector2D> uvs, TArray<int> tris) {
	int index = verts.Num();

	verts.Add(corner);
	verts.Add(corner + up);
	verts.Add(corner + up + right);
	verts.Add(corner + right);

	FVector2D uvWidth = FVector2D(0.25f, 0.25f);
	FVector2D uvCorner = FVector2D(0.00f, 0.75f);

	uvCorner.X += (float)((int)blocktype - 1) / 4;
	uvs.Add(uvCorner);
	uvs.Add(FVector2D(uvCorner.X, uvCorner.Y + uvWidth.Y));
	uvs.Add(FVector2D(uvCorner.X + uvWidth.X, uvCorner.Y + uvWidth.Y));
	uvs.Add(FVector2D(uvCorner.X + uvWidth.X, uvCorner.Y));

	if (reversed)
	{
		tris.Add(index + 0);
		tris.Add(index + 1);
		tris.Add(index + 2);
		tris.Add(index + 2);
		tris.Add(index + 3);
		tris.Add(index + 0);
	}
	else
	{
		tris.Add(index + 1);
		tris.Add(index + 0);
		tris.Add(index + 2);
		tris.Add(index + 3);
		tris.Add(index + 2);
		tris.Add(index + 0);
	}
}