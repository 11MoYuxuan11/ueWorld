// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Texture.h"
#include "RTSCommanderBase.h"
#include "RTSHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class UNWORLD_API ARTSHUDBase : public AHUD
{
	GENERATED_BODY()
public:
    
    FVector2D ScreenRes;

    bool bShowOverlays;

    bool bMoveCamera;
    bool bIsDrawing;
    bool bConstaantSpeed;

    FVector2D CurrentLocation;
    FVector2D ClickLocation;

    UPROPERTY(BlueprintReadWrite,EditAnywhere)
    UTexture* Texture2Draw;

    ARTSCommanderBase* Commander;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float EdgeThickness = 20;

public:
    virtual void BeginPlay();

    UFUNCTION(BlueprintCallable)
    void DrawHitBox(FVector2D position,FVector2D Size,FName name, bool bConsumeInput,int32 Priority,bool bLocalShowOverlays, FLinearColor OverlayColor);

    void DrawHitAllHitboxes(int32 HitBoxID,FVector2D Location,FVector2D Size,bool bConsumeInput,int32 Priority,bool bShowOverlays, FLinearColor OverlayColor);

    void DrawAllEdgeHitboxes();

    void ResetEdgeVariables();

    virtual void ReceiveDrawHUD(int32 SizeX, int32 SizeY);
    virtual void HitBoxEndCursorOver(FName name);
    virtual void HitBoxBeginCursorOver(FName name);
};
