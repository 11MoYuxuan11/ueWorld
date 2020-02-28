// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManagerBase.h"
#include "Runtime/Engine//Classes/Kismet/GameplayStatics.h"

// Sets default values
AWorldManagerBase::AWorldManagerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChunkSize = ChunkLineElement * VoxelSize;
	ChunkSizeHalf = ChunkSize / 2;
	WorldElements = WorldChunkElements * ChunkLineElement;
	WorldSize = VoxelSize * WorldElements;

	// �б��ʼ��
	ElevationMap.SetNumUninitialized(WorldElements* WorldElements);
	FaultMap.SetNumUninitialized(WorldElements * WorldElements);

	//chunkCords.SetNumUninitialized(WorldChunkElements*WorldChunkElements);
	//chunks.SetNumUninitialized(WorldChunkElements * WorldChunkElements);
}

// Called when the game starts or when spawned
void AWorldManagerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorldManagerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePostion();
	RemoveChunk();
	AddChunk();
}

void AWorldManagerBase::RandomFillMap()
{
	FaultMap.SetNumUninitialized(WorldElements * WorldElements);
	if (UseRandomSeed)
	{
		//SeedAllRandomStreams();
	}
	for (int i= 0;i< WorldElements;i++)
	{
		for (int j = 0; j < WorldElements; j++)
		{
			if (i == 0 || i == WorldElements - 1 || j == 0 || j == WorldElements - 1)
				FaultMap[i * WorldElements + j] = false;
			else
			{
				FaultMap[i * WorldElements + j] = FMath::RandBool();
			}
		}
	}
}

int32 AWorldManagerBase::GetSurroundingWalls(int X, int Y)
{
	int32 wallCount = 0;
	for (int i = X - 1; i <= X + 1; i++)
	{
		for (int j = Y - 1; j <= Y + 1; j++) {
			if (i >= 0 && i < WorldElements && j >= 0 && j < WorldElements) {
				if (i != X || j != Y)
					wallCount += FaultMap[i*WorldElements + j];
			}
			else {
				wallCount++;
			}
		}
	}
	return wallCount;
}

void AWorldManagerBase::SmoothMap()
{
	for (int i = 0; i < WorldElements; i++)
	{
		for (int j = 0; j < WorldElements; j++)
		{
			int surroundingTiles = GetSurroundingWalls(i, j);
			if (surroundingTiles > 4)
				FaultMap[i * WorldElements + j] = false;
			else if (surroundingTiles < 4)
				FaultMap[i * WorldElements + j] = true;
		}
	}
}

void AWorldManagerBase::CreateWorld()
{
	//�����ϲ� Fault
	RandomFillMap();
	for (int i = 0; i<4 ;i++)
	{
		SmoothMap();
	}

	//�����߶�ͼ����½����ɽ��ɽ��ͬ�����������Elevation

	GenerateElevation();

	//��ʴ����ˮ����Rainfall

	// �¶�ͼ���ܸ߶Ⱥ;�γ��Ӱ��Temperature

	//������ˮ���Drainage������Ӱ�쵱���ܷ��γɺ�����ʪ�غͺ�����ͬ��Ӱ���˵��ص����ʣ���һ��Ӱ��ֲ����

	//����Ⱥ�䣬�ܵ��߶ȡ���ˮ�����¶ȵ�����Ӱ��
	//Ŀǰ�ڼƻ��е�����Ⱥ������ݵء�ɳĮ��ɭ�֡����֡���Ҷ�֡�̦ԭ�͵���

	//��&���³�

	//��Ȼ�ر�

	//���� ϸ���Զ��� ������ѡ����ʵ�����Ⱥ�����
	//����֮�����Ϊ�ռ��ϵľ��롢�˴��Ļ���ͻ����ս����ó��

	//�˹��ر�
	//��������֮���������ں��ʵ�λ�ý�������ÿ��������ʼʱͨ����һ�����ǣ��������ݺ����ɴ���

	//ȷ����ҳ����� ������ҵ�����ѡ��һ���������
}

void AWorldManagerBase::AddChunk()
{
	for (int i=0;i<renderRange;i++)
	{
		for (int j = 0;j<renderRange; j++)
		{
			if (CheckRadius( (ChunkX + i)*ChunkSize +ChunkSizeHalf, 
				(ChunkY + j) * ChunkSize + ChunkSizeHalf))
			{
				if (!chunkCords.Contains(FVector2D(ChunkX + i, ChunkY + j)))
				{
					auto spawnTransform = FTransform();
					chunkCords.Add(FVector2D(ChunkX + i, ChunkY + j));
					auto deferredChunk = Cast<AChunkBase>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this,ChunkClass,spawnTransform));

					// ��ʼ������
					if (deferredChunk != nullptr)
					{
						deferredChunk->rabdinSeed = 0;
						deferredChunk->voxelSize = VoxelSize;
						deferredChunk->chunkElements = ChunkLineElement;
						deferredChunk->chunkXindex = i;
						deferredChunk->chunkYindex = j;

						UGameplayStatics::FinishSpawningActor(deferredChunk, spawnTransform);
					}

					// ��ӵ��б���
					chunks.Add(deferredChunk);

					//TODO �����ݴ��ݸ�Chunk��
				}
			}
		}
	}
}

bool AWorldManagerBase::CheckRadius(float x, float y)
{
	return (FVector(x,y,0) - characterPosition).Size() < ChunkSize * renderRange;
}

void AWorldManagerBase::GenerateElevation()
{
	ElevationMap.SetNumUninitialized(WorldElements * WorldElements);
	for (int32 i = 0; i < WorldElements; i++)
	{
		for (int32 j = 0; j < WorldElements; j++)
		{
			// ��ʱ����һ��ȡ�߶�����
			ElevationMap[i + j * WorldElements] = GenerateHeight(FVector(i,j,0), 0.025f, 1);
		}
	}
}

bool AWorldManagerBase::UpdatePostion()
{
	auto chaPosition = UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation();

	characterPosition = chaPosition * FVector(1,1,0);
	if ((ChunkX != characterPosition.X/ChunkSizeHalf)||(ChunkY != characterPosition.Y / ChunkSizeHalf))
	{
		ChunkX = characterPosition.X / ChunkSizeHalf;
		ChunkY = characterPosition.Y / ChunkSizeHalf;
		return true;
	}
	else
	{
		return false;
	}
}

int32 AWorldManagerBase::GenerateHeight_Implementation(FVector wPos, float frequency, float amplitude)
{
	return 0;
}

void AWorldManagerBase::RemoveChunk()
{
	for (int i = 0;i < chunkCords.Num();i++ )
	{
		if (!CheckRadius(ChunkSize * chunkCords[i].X + ChunkSizeHalf, ChunkSize * chunkCords[i].Y + ChunkSizeHalf))
		{
			// ɾ��Chunk���������
			chunks[i]->Destroy(false);
			chunkCords.RemoveAt(i);
			chunks.RemoveAt(i);
		}

		//TODO �ڸɵ�Chunk֮ǰ�������ݴ�������
	}
}
