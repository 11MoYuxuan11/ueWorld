// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCommanderBase.h"

// Sets default values
ARTSCommanderBase::ARTSCommanderBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RTSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RTSCameraComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARTSCommanderBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSCommanderBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARTSCommanderBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MouseX",this,&ARTSCommanderBase::Move_XAxis);
	PlayerInputComponent->BindAxis("MouseY",this,&ARTSCommanderBase::Move_YAxis);
	PlayerInputComponent->BindAxis("MoveForward",this,&ARTSCommanderBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ARTSCommanderBase::MoveRight);
}

void ARTSCommanderBase::Move_XAxis(float AxisValue)
{
	if (bRotateCamera)
	{
		
	}
}

void ARTSCommanderBase::Move_YAxis(float AxisValue)
{
}

void ARTSCommanderBase::MoveForward(float AxisValue) 
{
	
}

void ARTSCommanderBase::MoveRight(float AxisValue)
{
}
