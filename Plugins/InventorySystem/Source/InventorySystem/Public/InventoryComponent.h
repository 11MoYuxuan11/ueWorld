// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItemDataAsset;

/** Struct representing a slot for an item, shown in the UI */
//USTRUCT(BlueprintType)
//struct INVENTORYSYSTEM_API FItemSlot
//{
//	GENERATED_BODY()
//
//	/** Constructor, -1 means an invalid slot */
//	FItemSlot()
//		: SlotNumber(-1)
//	{}
//
//	FItemSlot(const FPrimaryAssetType& InItemType, int32 InSlotNumber)
//		: ItemType(InItemType)
//		, SlotNumber(InSlotNumber)
//	{}
//
//	/** The type of items that can go in this slot */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
//		FPrimaryAssetType ItemType;
//
//	/** The number of this slot, 0 indexed */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
//		int32 SlotNumber;
//
//	/** Equality operators */
//	bool operator==(const FItemSlot& Other) const
//	{
//		return ItemType == Other.ItemType && SlotNumber == Other.SlotNumber;
//	}
//	bool operator!=(const FItemSlot& Other) const
//	{
//		return !(*this == Other);
//	}
//
//	/** Implemented so it can be used in Maps/Sets */
//	friend inline uint32 GetTypeHash(const FItemSlot& Key)
//	{
//		uint32 Hash = 0;
//
//		Hash = HashCombine(Hash, GetTypeHash(Key.ItemType));
//		Hash = HashCombine(Hash, (uint32)Key.SlotNumber);
//		return Hash;
//	}
//
//	/** Returns true if slot is valid */
//	bool IsValid() const
//	{
//		return ItemType.IsValid() && SlotNumber >= 0;
//	}
//};
//
///** Extra information about a URPGItem that is in a player's inventory */
//USTRUCT(BlueprintType)
//struct INVENTORYSYSTEM_API FItemData
//{
//	GENERATED_BODY()
//
//	/** Constructor, default to count/level 1 so declaring them in blueprints gives you the expected behavior */
//	FItemData()
//		: ItemCount(1)
//		, ItemLevel(1)
//	{}
//
//	FItemData(int32 InItemCount, int32 InItemLevel)
//		: ItemCount(InItemCount)
//		, ItemLevel(InItemLevel)
//	{}
//
//	/** The number of instances of this item in the inventory, can never be below 1 */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
//		int32 ItemCount;
//
//	/** The level of this item. This level is shared for all instances, can never be below 1 */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
//		int32 ItemLevel;
//
//	/** Equality operators */
//	bool operator==(const FItemData& Other) const
//	{
//		return ItemCount == Other.ItemCount && ItemLevel == Other.ItemLevel;
//	}
//	bool operator!=(const FItemData& Other) const
//	{
//		return !(*this == Other);
//	}
//
//	/** Returns true if count is greater than 0 */
//	bool IsValid() const
//	{
//		return ItemCount > 0;
//	}
//
//	/** Append an item data, this adds the count and overrides everything else */
//	void UpdateItemData(const FItemData& Other, int32 MaxCount, int32 MaxLevel)
//	{
//		if (MaxCount <= 0)
//		{
//			MaxCount = MAX_int32;
//		}
//
//		if (MaxLevel <= 0)
//		{
//			MaxLevel = MAX_int32;
//		}
//
//		ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 1, MaxCount);
//		ItemLevel = FMath::Clamp(Other.ItemLevel, 1, MaxLevel);
//	}
//
//};

/** Delegate called when an inventory item changes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChanged, bool, bAdded, UItemDataAsset*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChangedNative, bool, UItemDataAsset*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	///** Map of all items owned by this player, from definition to data */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	//TMap<UItemDataAsset*, FItemData> InventoryData;

	///** Map of slot, from type/num to item, initialized from ItemSlotsPerType on RPGGameInstanceBase */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	//TMap<FItemSlot, UItemDataAsset*> SlottedItems;

	/** Delegate called when an inventory item has been added or removed */
	//UPROPERTY(BlueprintAssignable, Category = Inventory)
	//	FOnInventoryItemChanged OnInventoryItemChanged;

	/** Native version above, called before BP delegate */
	//FOnInventoryItemChangedNative OnInventoryItemChangedNative;

	//UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	//void InventoryItemChanged(bool bAdded,UItemDataAsset* item);

	///** Adds a new inventory item, will add it to an empty slot if possible. If the item supports count you can add more than one count. It will also update the level when adding if required */
	//UFUNCTION(BlueprintCallable, Category = Inventory)
	//bool AddInventoryItem(UItemDataAsset* NewItem, int32 ItemCount = 1, int32 ItemLevel = 1, bool bAutoSlot = true);

	///** Remove an inventory item, will also remove from slots. A remove count of <= 0 means to remove all copies */
	//UFUNCTION(BlueprintCallable, Category = Inventory)
	//bool RemoveInventoryItem(UItemDataAsset* RemovedItem, int32 RemoveCount = 1);

	///** Returns all inventory items of a given type. If none is passed as type it will return all */
	//UFUNCTION(BlueprintCallable, Category = Inventory)
	//void GetInventoryItems(TArray<UItemDataAsset*>& Items, FPrimaryAssetType ItemType);

	///** Returns number of instances of this item found in the inventory. This uses count from GetItemData */
	//UFUNCTION(BlueprintPure, Category = Inventory)
	//int32 GetInventoryItemCount(UItemDataAsset* Item) const;

	///** Returns the item data associated with an item. Returns false if none found */
	//UFUNCTION(BlueprintPure, Category = Inventory)
	//bool GetInventoryItemData(UItemDataAsset* Item, FItemData& ItemData) const;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//bool FillEmptySlotWithItem(UItemDataAsset* NewItem);

	///** Calls the inventory update callbacks */
	//void NotifyInventoryItemChanged(bool bAdded, UItemDataAsset* Item);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
