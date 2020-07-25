// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHUDBase.h"
#include "RTSPlayerControllerBase.h"
#include "Kismet/KismetMathLibrary.h"

void ARTSHUDBase::BeginPlay()
{
	//Commander = Cast<ARTSCommanderBase>(GetOwningPawn());
}

void ARTSHUDBase::DrawHitBox(FVector2D position, FVector2D Size, FName name,
	bool bConsumeInput, int32 Priority, bool bLocalShowOverlays, FLinearColor OverlayColor) {
	AddHitBox(position,Size,name,bConsumeInput,Priority);
	if (bShowOverlays)
	{
		DrawRect(OverlayColor,position.X,position.Y,Size.X,Size.Y);
	}
}

void ARTSHUDBase::DrawHitAllHitboxes(int32 HitBoxID, FVector2D Location, FVector2D Size, bool bConsumeInput, int32 Priority, bool bLocalShowOverlays, FLinearColor OverlayColor)
{
	
	for (int32 i = 0; i < 4; i++)
	{
		
		FName name = FName(*("EdgeBox" + FString::FromInt(HitBoxID) + "." + FString::FromInt(i)));
		FVector2D position;
		FVector2D size;
		switch (i)
		{
		//Top
		case 0:
		position = Location;
		size = FVector2D(Size.X-EdgeThickness,EdgeThickness);
		//Right
		case 1:
		position = FVector2D(Location.X + Size.X - EdgeThickness,Location.Y+EdgeThickness);
		size = FVector2D(EdgeThickness, Size.Y - EdgeThickness);
		//Botton
		case 2:
		position = FVector2D(Location.X + EdgeThickness , Location.X + Size.X - EdgeThickness);
		size = FVector2D(Size.X - EdgeThickness, EdgeThickness);
		//Left
	    case 3:
		position = FVector2D(Location.X,Location.Y + EdgeThickness);
		size = FVector2D(EdgeThickness, Size.Y - EdgeThickness);
		default:
			break;
		}
		DrawHitBox(position,size,name,bConsumeInput,Priority,bLocalShowOverlays,OverlayColor);
	}
}

void ARTSHUDBase::DrawAllEdgeHitboxes()
{
	DrawHitAllHitboxes(0, FVector2D(0, 0), ScreenRes, false, 0, bShowOverlays, FLinearColor(1.0, 0.051264, 0.9601917, 0.5));
	if (bMoveCamera)
	{
		FVector2D mousePosition;
		if (GetOwningPlayerController()->GetMousePosition(mousePosition.X,mousePosition.Y))
		{
			FVector direction = UKismetMathLibrary::GetDirectionUnitVector(FVector(ScreenRes.X / 2, ScreenRes.Y / 2, 0),FVector(mousePosition.X, mousePosition.Y, 0));
			
			auto x = UKismetMathLibrary::Clamp(UKismetMathLibrary::NormalizeToRange(FMath::Abs(ScreenRes.X / 2 - mousePosition.X), ScreenRes.X / 2 - EdgeThickness, ScreenRes.X / 2),0,1) + 1;
			x = x^2-1;
			if (bConstaantSpeed)
			{
				x = 1;
			}
			auto y = UKismetMathLibrary::Clamp(UKismetMathLibrary::NormalizeToRange(FMath::Abs(ScreenRes.Y / 2 - mousePosition.Y), ScreenRes.Y / 2 - EdgeThickness, ScreenRes.Y / 2), 0, 1)+ 1;
			y= y^2-1;
			if (bConstaantSpeed)
			{
				y = 1;
			}
			
			Commander->EdgeForwardAxis = direction.Y * -1 * y;
			Commander->EdgeRightAxis = direction.X * x;
		}
	}
}

void ARTSHUDBase::ResetEdgeVariables()
{
	Commander->EdgeForwardAxis = 0;
	Commander->EdgeRightAxis = 0;
}

void ARTSHUDBase::ReceiveDrawHUD(int32 SizeX, int32 SizeY)
{
	ScreenRes = FVector2D(SizeX,SizeY);
	DrawAllEdgeHitboxes();
	if (bIsDrawing)
	{
		CurrentLocation = FVector2D();
		auto controller = GetOwningPlayerController();
		FVector2D MousePostion;
		controller->GetMousePosition(MousePostion.X,MousePostion.Y);
		CurrentLocation = MousePostion;
		DrawTexture(Texture2Draw, ClickLocation.X,ClickLocation.Y,(ClickLocation-CurrentLocation).X, (ClickLocation - CurrentLocation).Y,
			0,0,0,0,FLinearColor(1,1,1,0.5),BLEND_Translucent,1.f,false,0.f,FVector2D(0,0));

	}
}

void ARTSHUDBase::HitBoxEndCursorOver(FName name)
{
	
}

void ARTSHUDBase::HitBoxBeginCursorOver(FName name)
{
}
