// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ItemDataAsset.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

//bool UInventoryComponent::AddInventoryItem(UItemDataAsset* NewItem, int32 ItemCount, int32 ItemLevel, bool bAutoSlot)
//{
//	bool bChanged = false;
//	if (!NewItem) {
//		// 报错，直接返回
//		//UE_LOG(LogInventory, Warning, TEXT("AddInventoryItem: Failed trying to add null item!"));
//		return false;
//	}
//
//	if (true)
//	{
//		//UE_LOG(LogInventory, Warning, TEXT("AddInventoryItem: Failed trying to add item %s with negative count or level!"), *NewItem->GetName());
//		return false;
//	}
//
//	FItemData OldData;
//	GetInventoryItemData(NewItem, OldData);
//
//	// Find modified data
//	FItemData NewData = OldData;
//	NewData.UpdateItemData(FItemData(ItemCount,ItemLevel), NewItem->MaxCount,NewItem->MaxLevel);
//
//	if (OldData != NewData)
//	{
//		// If data changed, need to update storage and call callback
//		InventoryData.Add(NewItem, NewData);
//		NotifyInventoryItemChanged(true, NewItem);
//		bChanged = true;
//	}
//
//	if (bAutoSlot)
//	{
//		// Slot item if required
//		bChanged |= FillEmptySlotWithItem(NewItem);
//	}
//
//	if (bChanged)
//	{
//		// If anything changed, write to save game
//		//SaveInventory();
//		return true;
//	}
//
//	return false;
//}
//
//bool UInventoryComponent::FillEmptySlotWithItem(UItemDataAsset* NewItem)
//{
//	// Look for an empty item slot to fill with this item
//	FPrimaryAssetType NewItemType = NewItem->GetPrimaryAssetId().PrimaryAssetType;
//	FItemSlot EmptySlot;
//	for (TPair<FItemSlot, UItemDataAsset*>& Pair : SlottedItems)
//	{
//		if (Pair.Key.ItemType == NewItemType)
//		{
//			if (Pair.Value == NewItem)
//			{
//				// Item is already slotted
//				return false;
//			}
//			else if (Pair.Value == nullptr && (!EmptySlot.IsValid() || EmptySlot.SlotNumber > Pair.Key.SlotNumber))
//			{
//				// We found an empty slot worth filling
//				EmptySlot = Pair.Key;
//			}
//		}
//	}
//
//	if (EmptySlot.IsValid())
//	{
//		SlottedItems[EmptySlot] = NewItem;
//		//NotifySlottedItemChanged(EmptySlot, NewItem);
//		return true;
//	}
//
//	return false;
//}

//void UInventoryComponent::NotifyInventoryItemChanged(bool bAdded, UItemDataAsset* Item)
//{
//	// Notify native before blueprint
//	OnInventoryItemChangedNative.Broadcast(bAdded, Item);
//	//OnInventoryItemChanged.Broadcast(bAdded, Item);
//
//	// Call BP update event
//	InventoryItemChanged(bAdded, Item);
//}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}