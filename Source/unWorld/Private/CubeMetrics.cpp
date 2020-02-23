// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeMetrics.h"

FVector UCubeMetrics::WorldPostion2CubePosition(FVector position,float CUBE_SIDE_LENGTH,int CHUNK_WIDTH)
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

	//resut.X = position.X > 0 ? (int)position.X * 1.f + 0.5f : (int)position.X * 1.f - 0.5f;
	//resut.Y = position.Y > 0 ? (int)position.Y * 1.f + 0.5f : (int)position.Y * 1.f - 0.5f;
	//resut.Z = position.Z > 0 ? (int)position.Z * 1.f + 0.5f : (int)position.Z * 1.f - 0.5f;


	return resut;
}
