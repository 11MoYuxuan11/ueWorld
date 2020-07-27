// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "RTSCommanderBase.generated.h"

UCLASS()
class UNWORLD_API ARTSCommanderBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARTSCommanderBase();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Setting")
	float EdgeRightAxis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	float EdgeForwardAxis;

	bool bRotateCamera;
	float RotateSpeed = 2.0;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float MovementSpeed = 10.0;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* RTSCameraComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
};
