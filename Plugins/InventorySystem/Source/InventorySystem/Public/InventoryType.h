// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryType.generated.h"

/** Struct representing a slot for an item, shown in the UI */
USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FItemSlot
{
	GENERATED_BODY()

	/** Constructor, -1 means an invalid slot */
	FItemSlot()
		: SlotNumber(-1)
	{}

	FItemSlot(const FPrimaryAssetType& InItemType, int32 InSlotNumber)
		: ItemType(InItemType)
		, SlotNumber(InSlotNumber)
	{}

	/** The type of items that can go in this slot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		FPrimaryAssetType ItemType;

	/** The number of this slot, 0 indexed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		int32 SlotNumber;

	/** Equality operators */
	bool operator==(const FItemSlot& Other) const
	{
		return ItemType == Other.ItemType && SlotNumber == Other.SlotNumber;
	}
	bool operator!=(const FItemSlot& Other) const
	{
		return !(*this == Other);
	}

	/** Implemented so it can be used in Maps/Sets */
	friend inline uint32 GetTypeHash(const FItemSlot& Key)
	{
		uint32 Hash = 0;

		Hash = HashCombine(Hash, GetTypeHash(Key.ItemType));
		Hash = HashCombine(Hash, (uint32)Key.SlotNumber);
		return Hash;
	}

	/** Returns true if slot is valid */
	bool IsValid() const
	{
		return ItemType.IsValid() && SlotNumber >= 0;
	}
};

///** Extra information about a URPGItem that is in a player's inventory */
USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FItemData
{
	GENERATED_BODY()

	/** Constructor, default to count/level 1 so declaring them in blueprints gives you the expected behavior */
	FItemData()
		: ItemCount(1)
		, ItemLevel(1)
	{}

	FItemData(int32 InItemCount, int32 InItemLevel)
		: ItemCount(InItemCount)
		, ItemLevel(InItemLevel)
	{}

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	//UItemDataAsset* ItemAsset;

	/** The number of instances of this item in the inventory, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		int32 ItemCount;

	/** The level of this item. This level is shared for all instances, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		int32 ItemLevel;

	/** Equality operators */
	bool operator==(const FItemData& Other) const
	{
		return ItemCount == Other.ItemCount && ItemLevel == Other.ItemLevel;
	}
	bool operator!=(const FItemData& Other) const
	{
		return !(*this == Other);
	}

	/** Returns true if count is greater than 0 */
	bool IsValid() const
	{
		return ItemCount > 0;
	}

	/** Append an item data, this adds the count and overrides everything else */
	void UpdateItemData(const FItemData& Other, int32 MaxCount, int32 MaxLevel)
	{
		if (MaxCount <= 0)
		{
			MaxCount = MAX_int32;
		}

		if (MaxLevel <= 0)
		{
			MaxLevel = MAX_int32;
		}

		ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 1, MaxCount);
		ItemLevel = FMath::Clamp(Other.ItemLevel, 1, MaxLevel);
	}

};

USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FInventoryItem 
{
	GENERATED_BODY()

	//FInventoryItem(FName ID	, UTexture2D* Icon, FName Name,FText Des,int32 Quality
	//		,int32 ItemType,int32 MaxStackSize, bool IsDroppable)
	//	: ID(ID)
	//	, Icon(Icon)
	//	, Name(Name)
	//	, Description(Description)
	//	, Quality(Quality)
	//	, ItemType(ItemType)
	//	, MaxStackSize(MaxStackSize)
	//	, IsDroppable(IsDroppable)
	//{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FName ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 Quality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 MaxStackSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	bool IsDroppable;

	void UpdateItemData(const FInventoryItem& Other, int32 MaxCount, int32 MaxLevel = 1)
	{
		if (MaxCount <= 0)
		{
			MaxCount = MAX_int32;
		}

		if (MaxLevel <= 0)
		{
			MaxLevel = MAX_int32;
		}

		Amount = FMath::Clamp(Amount + Other.Amount, 1, MaxCount);

	}
};


/** Delegate called when an inventory item changes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChanged, bool, bAdded, UItemDataAsset*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChangedNative, bool, UItemDataAsset*);

/** Delegate called when the contents of an inventory slot change */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChanged, FItemSlot, ItemSlot, UItemDataAsset*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChangedNative, FItemSlot, UItemDataAsset*);
