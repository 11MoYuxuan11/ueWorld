// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "AssetManagerBase.h"
#include "ItemDataAsset.generated.h"

/**
 * Item��������Դ����
 */
UCLASS(Abstract, BlueprintType)
class INVENTORYSYSTEM_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
    UItemDataAsset()
        : Price(0)
        , Stacked(0)
        , MaxCount(1)
        , MaxLevel(1)
        , AbilityLevel(1)
    {}

    // �������ͣ����Ը�����Ŀ��ͬ��ʹ�����Լ�����
    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Item)
    FPrimaryAssetType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    FText ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    FText ItemDescription;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    FSlateBrush ItemIcon; 

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    int32 Price;

    // �ѵ����������Ϊ0���ʾ�����ޣ�Ĭ��Ϊ1
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
    int32 Stacked;

    /** Maximum number of instances that can be in inventory at once, <= 0 means infinite */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Max)
    int32 MaxCount;

    /** Returns if the item is consumable (MaxCount <= 0)*/
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = Max)
    bool IsConsumable() const;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Max)
    int32 MaxLevel;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
    FName AbilityName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
    int32 AbilityLevel;

    /** Returns the logical name, equivalent to the primary asset id */
    UFUNCTION(BlueprintCallable, Category = Item)
    FString GetIdentifierString() const;

    /** Overridden to use saved type */
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
