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

				chunkFields[index] = ((z < 30 + noise[x + y * chunkElements]) ? 1 : 0);

			}
		}
	}

}

void AChunkBase::UpdateMesh()
{
	
	//TArray<FVector> Vertices;
	//TArray<int32> Triangles;
	//TArray<FVector> Normals;
	//TArray<FVector2D> UVs;
	//TArray<FProcMeshTangent> Tangents;
	//TArray<FColor> VertexColor;

	int32 elementID = 0;

	for (int32 x = 0; x < chunkElements; x++)
	{
		for (int32 y = 0; y < chunkElements; y++)
		{
			for (int32 z = 0; z < chunkZElements; z++)
			{
				int32 index = x + (y * chunkElements) + (z * chunkLineElementsP2);
				int32 meshIndex = (int)chunkFields[index];

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
								if ( (int)chunkFields[newIndex] < 1 )
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

void AChunkBase::Initmap()
{
	// 初始化随机种子
	FMath::RandInit(RandSeed);
	offset0 = FVector(FMath::RandRange(0, 1000), FMath::RandRange(0, 1000), FMath::RandRange(0, 1000));
	offset1 = FVector(FMath::RandRange(0, 1000), FMath::RandRange(0, 1000), FMath::RandRange(0, 1000));
	offset2 = FVector(FMath::RandRange(0, 1000), FMath::RandRange(0, 1000), FMath::RandRange(0, 1000));

	//初始化Map
	chunkFields.SetNumUninitialized(chunkTotalElements);

	//遍历map，生成其中每个Block的信息
	for (int x = 0; x < chunkElements; x++)
	{
		for (int y = 0; y < chunkElements; y++)
		{
			for (int z = 0; z < chunkZElements; z++)
			{
				int32 index = x + (y * chunkElements) + (z * chunkLineElementsP2);
				auto wPos = FVector(x, y, z) + this->GetActorLocation();
				chunkFields[index] = (int)GenerateBlockType(wPos);
			}
		}
	}

	//根据生成的信息，Build出Chunk的网格
	BuildChunk();
}

void AChunkBase::BuildChunk()
{
	for (int x = 0;x< chunkElements;x++)
	{
		for (int y = 0; y < chunkElements; x++)
		{
			for (int z = 0;z < chunkZElements; z++)
			{
				BuildBlock(FVector(x,y,z));
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

void AChunkBase::BuildBlock(FVector wPos)
{
	if ((int)GetChunkFieldByVector(wPos) == 0) return;
	
	EBlockType blockType = GetBlockType(wPos.X,wPos.Y,wPos.Z);

	//Left
	if (CheckNeedBuildFace(FVector(wPos.X - 1, wPos.Y, wPos.Z)))
		BuildFace(blockType, EFaceType::Left, FVector(wPos.X, wPos.Y, wPos.Z), FVector::UpVector, FVector::ForwardVector, false);
	//Right
	if (CheckNeedBuildFace(FVector(wPos.X + 1, wPos.Y, wPos.Z)))
		BuildFace(blockType, EFaceType::Right, FVector(wPos.X + 1, wPos.Y, wPos.Z), FVector::UpVector, FVector::ForwardVector, true);
	//Bottom
	if (CheckNeedBuildFace(FVector(wPos.X, wPos.Y - 1, wPos.Z)))
		BuildFace(blockType, EFaceType::Down,FVector(wPos.X, wPos.Y, wPos.Z), FVector::ForwardVector, FVector::RightVector, false);
	//Top
	if (CheckNeedBuildFace(FVector(wPos.X, wPos.Y + 1, wPos.Z)))
		BuildFace(blockType, EFaceType::Up, FVector(wPos.X, wPos.Y + 1, wPos.Z), FVector::ForwardVector, FVector::RightVector, true);

	//Back
	if (CheckNeedBuildFace(FVector(wPos.X, wPos.Y, wPos.Z - 1)))
		BuildFace(blockType, EFaceType::BackGround, FVector(wPos.X, wPos.Y, wPos.Z), FVector::UpVector, FVector::RightVector, true);
	//Front
	if (CheckNeedBuildFace(FVector(wPos.X, wPos.Y, wPos.Z + 1)))
		BuildFace(blockType, EFaceType::Forward, FVector(wPos.X, wPos.Y, wPos.Z + 1), FVector::UpVector, FVector::RightVector, false);
}

bool AChunkBase::CheckNeedBuildFace(FVector wPos)
{
	if (wPos.Y < 0) return false;
	auto type = GetBlockType(wPos.X,wPos.Y,wPos.Z);

	switch (type)
	{
		case EBlockType::None:
			return true;
		default:
			return false;
	}
}

EBlockType AChunkBase::GetChunkFieldByVector(FVector wPos)
{
	return (EBlockType)chunkFields[wPos.X + wPos.Y * chunkElements + wPos.Z * chunkLineElementsP2];
}

EBlockType AChunkBase::GetBlockType(int x, int y, int z) {
	return (EBlockType)GetChunkFieldByVector(FVector(x,y,z));
}

EBlockType AChunkBase::GenerateBlockType(FVector wPos)
{
	//z坐标是否在Chunk内
	if (wPos.Z >= chunkZElements)
	{
		return EBlockType::None;
	}

	//获取当前位置方块随机生成的高度值
	float genHeight = generateHeight(wPos);

	//当前方块位置高于随机生成的高度值时，当前方块类型为空
	if (wPos.Y > genHeight)
	{
		return EBlockType::None;
	}
	//当前方块位置等于随机生成的高度值时，当前方块类型为草地
	else if (wPos.Y == genHeight)
	{
		return EBlockType::Grass;
	}
	//当前方块位置小于随机生成的高度值 且 大于 genHeight - 5时，当前方块类型为泥土
	else if (wPos.Y < genHeight && wPos.Y > genHeight - 5)
	{
		return EBlockType::Dirt;
	}
	//其他情况，当前方块类型为碎石
	return EBlockType::Gravel;
	return EBlockType::None;
}

//SCubeData AChunkBase::ToCubeData(Byte data)
//{
//	bool _active = (data & 1 << 0) != 0;
//	bool _isTransparent = (data & 1 <<1) != 0;
//
//	EBlockType _type = (EBlockType)((data & 15<<4) >>4);
//	return SCubeData(_active,_isTransparent,_type);
//}
//
//Byte AChunkBase::ToByte(SCubeData sdata)
//{
//	Byte data = Byte.MinValue;
//	
//	data = sdata.active ?(byte)(data | 1<<0):data;
//	data = sdata.isTransparent ? (byte)(data | 1 << 0) : data;
//	data |= (byte)((int)sdata.blockType << 4)
//
//	return data;
//}

void AChunkBase::BuildFace(EBlockType blocktype, EFaceType faceType, FVector corner, FVector up, FVector right, bool reversed) 
{
	int index = Vertices.Num();

	Vertices.Add(corner);
	Vertices.Add(corner + up);
	Vertices.Add(corner + up + right);
	Vertices.Add(corner + right);

	FVector2D uvWidth = FVector2D(0.25f, 0.25f);
	FVector2D uvCorner = FVector2D(0.00f, 0.75f);

	uvCorner.X += (float)((int)blocktype - 1) / 4;
	UVs.Add(uvCorner);
	UVs.Add(FVector2D(uvCorner.X, uvCorner.Y + uvWidth.Y));
	UVs.Add(FVector2D(uvCorner.X + uvWidth.X, uvCorner.Y + uvWidth.Y));
	UVs.Add(FVector2D(uvCorner.X + uvWidth.X, uvCorner.Y));

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
		case EFaceType::Up : 
		{
			Normals.Append(bNormals0, ARRAY_COUNT(bNormals0));
			break;
		}
		case EFaceType::Down :
		{
			Normals.Append(bNormals1, ARRAY_COUNT(bNormals1));
			break;
		}
		case EFaceType::Left:
		{
			Normals.Append(bNormals2, ARRAY_COUNT(bNormals2));
			break;
		}
		case EFaceType::Right:
		{
			Normals.Append(bNormals3, ARRAY_COUNT(bNormals3));
			break;
		}
		case EFaceType::Forward :
		{
			Normals.Append(bNormals4, ARRAY_COUNT(bNormals4));
			break;
		}
		case EFaceType::BackGround :
		{
			Normals.Append(bNormals5, ARRAY_COUNT(bNormals5));
			break;
		}
	}

	FColor color = FColor(255, 255, 255, (int)faceType);
	VertexColor.Add(color);
	VertexColor.Add(color);
	VertexColor.Add(color);
	VertexColor.Add(color);
}

TArray<int32> AChunkBase::calculateNosie_Implementation()
{
	TArray<int32> aa;
	aa.SetNum(chunkLineElementsP2);
	return aa;
}

int AChunkBase::generateHeight_Implementation(FVector wPos)
{
	return 0;
}
