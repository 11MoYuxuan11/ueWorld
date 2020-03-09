// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/CoreAttributeSet.h"
#include "Abilities/RPGAbilitySystemComponent.h"
#include "unWorldCharacter.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UCoreAttributeSet::UCoreAttributeSet():
	Health(1.f),
	MaxHealth(1.f)
{
}

void UCoreAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(UCoreAttributeSet, Health);
	//DOREPLIFETIME(UCoreAttributeSet, MaxHealth);
}

void UCoreAttributeSet::OnRep_Health() {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCoreAttributeSet,Health);
}

void UCoreAttributeSet::OnRep_MaxHealth() {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCoreAttributeSet, MaxHealth);
}

void UCoreAttributeSet::AdjustAttributeFormMaxChange(FGameplayAttributeData& AffectedAttribute, \
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue, 
	const FGameplayAttribute& AffectedAttributeProperty) 
{
	UAbilitySystemComponent* AbilityComponent = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();

	if (!FMath::IsNearlyEqual(CurrentMaxValue,NewMaxValue) && AbilityComponent )
	{
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) : NewMaxValue;

		AbilityComponent->ApplyModToAttributeUnsafe(AffectedAttributeProperty,EGameplayModOp::Additive,NewDelta);
	}

}

void UCoreAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) 
{
	Super::PreAttributeChange(Attribute,NewValue);

	// ������ֵ�ı�ǰ���ж��Ƿ��ں���Χ��
	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeFormMaxChange(Health,MaxHealth,NewValue,GetHealthAttribute());
	}
}

void UCoreAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) 
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// If this was additive, store the raw delta value to be passed along later
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	AunWorldCharacter* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetCharacter = Cast<AunWorldCharacter>(Data.Target.AbilityActorInfo->AvatarActor.Get());
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0.f,GetMaxHealth()));

		if (TargetCharacter)
		{
			//TargetCharacter->HandleHealthChanged(DeltaValue,SourceTags);
			//TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
		}
	}
}