// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeMetrics.h"

const FVector cubeVertex[] = {
	//上面四个顶点
	FVector(-0.5f,0.5f,0.5f),
	//右上
	FVector(0.5f,0.5f,0.5f),
	//右下
	FVector(0.5f,0.5f,-0.5f),
	//左下
	FVector(-0.5f,0.5f,-0.5f),
	//下面四个顶点
	//左上
	FVector(-0.5f,-0.5f,0.5f),
	//右上
	FVector(0.5f,-0.5f,0.5f),
	//右下
	FVector(0.5f,-0.5f,-0.5f),
	//左下
	FVector(-0.5f,-0.5f,-0.5f)
};



FVector UCubeMetrics::WorldPostion2CubePosition(FVector position,float CUBE_SIDE_LENGTH)
{
	FVector resut = FVector::ZeroVector;

	resut.X = position.X >= 0 ?
		(int)(position.X / CUBE_SIDE_LENGTH) * CUBE_SIDE_LENGTH + 0.5f * CUBE_SIDE_LENGTH :
		(int)(position.X / CUBE_SIDE_LENGTH) * CUBE_SIDE_LENGTH - 0.5f * CUBE_SIDE_LENGTH;
	resut.Y = position.Y >= 0 ?
		(int)(position.Y / CUBE_SIDE_LENGTH) * CUBE_SIDE_LENGTH + 0.5f * CUBE_SIDE_LENGTH :
		(int)(position.Y / CUBE_SIDE_LENGTH) * CUBE_SIDE_LENGTH - 0.5f * CUBE_SIDE_LENGTH;
	resut.Z = position.Z >= 0 ?
		(int)(position.Z / CUBE_SIDE_LENGTH) * CUBE_SIDE_LENGTH + 0.5f * CUBE_SIDE_LENGTH :
		(int)(position.Z / CUBE_SIDE_LENGTH) * CUBE_SIDE_LENGTH - 0.5f * CUBE_SIDE_LENGTH;

	return resut;
}

FVector UCubeMetrics::WorldPostion2ChunkPosition(FVector position, float CUBE_SIDE_LENGTH, int CHUNK_WIDTH)
{
	FVector resut = FVector::ZeroVector;

	resut.X = position.X >= 0 ?
		((int)(position.X / (CUBE_SIDE_LENGTH * CHUNK_WIDTH)) + 0.5f ) * CUBE_SIDE_LENGTH * CHUNK_WIDTH:
		((int)(position.X / (CUBE_SIDE_LENGTH * CHUNK_WIDTH)) - 0.5f ) * CUBE_SIDE_LENGTH * CHUNK_WIDTH;
	resut.Y = position.Y >= 0 ?
		((int)(position.Y / (CUBE_SIDE_LENGTH * CHUNK_WIDTH)) + 0.5f ) * CUBE_SIDE_LENGTH * CHUNK_WIDTH :
		((int)(position.Y / (CUBE_SIDE_LENGTH * CHUNK_WIDTH)) - 0.5f ) * CUBE_SIDE_LENGTH * CHUNK_WIDTH;
	resut.Z = position.Z >= 0 ?
		((int)(position.Z / (CUBE_SIDE_LENGTH * CHUNK_WIDTH)) + 0.5f ) * CUBE_SIDE_LENGTH * CHUNK_WIDTH :
		((int)(position.Z / (CUBE_SIDE_LENGTH * CHUNK_WIDTH)) - 0.5f ) * CUBE_SIDE_LENGTH * CHUNK_WIDTH;

	return resut;
}