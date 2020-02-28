// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManagerBase.h"

// Sets default values
AWorldManagerBase::AWorldManagerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChunkSize = ChunkLineElement * VoxelSize;
	ChunkSizeHalf = ChunkSize / 2;


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
			//if ()
			//{
			//	
			//}
		}
	}
}

int32 AWorldManagerBase::GenerateHeight_Implementation(FVector wPos)
{
	return 0;
}
