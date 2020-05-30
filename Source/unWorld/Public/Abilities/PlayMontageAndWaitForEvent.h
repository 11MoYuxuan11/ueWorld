// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "unWorld.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "PlayMontageAndWaitForEvent.generated.h"

class URPGAbilitySystemComponent;

/** Delegate type used, EventTag and Payload may be empty if it came from the montage callbacks */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayMontageAndWaitForEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);

/**
 * This task combines PlayMontageAndWait and WaitForEvent into one task, so you can wait for multiple types of activations such as from a melee combo
 * Much of this code is copied from one of those two ability tasks
 * This is a good task to look at as an example when creating game-specific tasks
 * It is expected that each game will have a set of game-specific tasks to do what they want
 */
UCLASS()
class UNWORLD_API UPlayMontageAndWaitForEvent : public UAbilityTask
{
	GENERATED_BODY()

public:

	//Constructor and overrides
	UPlayMontageAndWaitForEvent(const FObjectInitializer& ObjectInitializer);
	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual FString GetDebugString() const override;
	virtual void OnDestroy(bool AbilityEnded) override;

	/** The montage completely finished playing */
	UPROPERTY(BlueprintAssignable)
		FPlayMontageAndWaitForEventDelegate OnCompleted;

	/** The montage started blending out */
	UPROPERTY(BlueprintAssignable)
		FPlayMontageAndWaitForEventDelegate OnBlendOut;

	/** The montage was interrupted */
	UPROPERTY(BlueprintAssignable)
		FPlayMontageAndWaitForEventDelegate OnInterrupted;

	/** The ability task was explicitly cancelled by another ability */
	UPROPERTY(BlueprintAssignable)
		FPlayMontageAndWaitForEventDelegate OnCancelled;

	/** One of the triggering gameplay events happened */
	UPROPERTY(BlueprintAssignable)
		FPlayMontageAndWaitForEventDelegate EventReceived;


	/**
	*播放蒙太奇并等待其结束。如果发生与EventTags匹配的游戏事件（或EventTags为空），则EventReceived委托将使用标签和事件数据触发。
	*如果StopWhenAbilityEnds为true，则如果该功能正常结束，则此剪辑画面将被中止。当该能力被明确取消时，它总是停止。
	*在正常执行时，蒙太奇混合时会调用OnBlendOut，完全播放时会调用OnCompleted
	*如果另一个蒙太奇覆盖了该对象，则调用OnInterrupted；如果取消该能力或任务，则调用OnCancelled
	*
	* @param TaskInstanceName设置为覆盖此任务的名称，以供以后查询
	* @param MontageToPlay在角色上播放的蒙太奇
	* @param EventTags与此标签匹配的任何游戏事件都会激活EventReceived回调。如果为空，所有事件将触发回调
	* @param Rate Change以更快或更慢地播放蒙太奇
	* @param bStopWhenAbilityEnds如果为true，则如果该功能正常结束，则此蒙太奇将被中止。当该能力被明确取消时，它总是停止
	* @param AnimRootMotionTranslationScale更改以修改根运动的大小或设置为0以完全阻止它
	*/
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UPlayMontageAndWaitForEvent* PlayMontageAndWaitForEvent(
		UGameplayAbility* OwningAbility,
		FName TaskInstanceName,
		UAnimMontage* MontageToPlay,
		FGameplayTagContainer EventTags,
		float Rate = 1.f,
		FName StartSection = NAME_None,
		bool bStopWhenAbilityEnds = true,
		float AnimRootMotionTranslationScale = 1.f);

private:
	/** Montage that is playing */
	UPROPERTY()
		UAnimMontage* MontageToPlay;

	/** List of tags to match against gameplay events */
	UPROPERTY()
		FGameplayTagContainer EventTags;

	/** Playback rate */
	UPROPERTY()
		float Rate;

	/** Section to start montage from */
	UPROPERTY()
		FName StartSection;

	/** Modifies how root motion movement to apply */
	UPROPERTY()
		float AnimRootMotionTranslationScale;

	/** Rather montage should be aborted if ability ends */
	UPROPERTY()
		bool bStopWhenAbilityEnds;

	/** Checks if the ability is playing a montage and stops that montage, returns true if a montage was stopped, false if not. */
	bool StopPlayingMontage();

	/** Returns our ability system component */
	URPGAbilitySystemComponent* GetTargetASC();

	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);
	void OnAbilityCancelled();
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;
	FDelegateHandle CancelledHandle;
	FDelegateHandle EventHandle;
};
