// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"
#include "StatusEffectComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	StatusEffectComponent = GetOwner()->FindComponentByClass<UStatusEffectComponent>();

	if (StatusEffectComponent)
	{
		StatusEffectComponent->OnEffectFire.AddDynamic(this, &UStatsComponent::ApplyEffect);
	}
}


// 
void UStatsComponent::SetMaxHealth()
{
	float DivideValue = float(Health) / float(MaxHealth);
	MaxHealth = Constitution * CostitutionPerUnitToMaxHealth + MaxHealtModifier +BaseMaxHealth;

	AdjustHealthToMax(DivideValue);
}


// Helper function called when Max Health is chnged
void UStatsComponent::AdjustHealthToMax(float DivideValue)
{
	auto NewHealth = float(MaxHealth) * DivideValue;
	Health = NewHealth;
}


//
void UStatsComponent::SetHealth(int32 ValueToChange)
{
	Health += ValueToChange;
	Health = FMath::Clamp(Health, 0, MaxHealth);
}


//
void UStatsComponent::ResetHealth()
{
	Health = MaxHealth;
}


//
void UStatsComponent::SetMaxEnergy()
{
	float DivideValue = float(Energy) / float(MaxEnergy);
	MaxEnergy = Strength * StrengthPerUnitToMaxEnergy + MaxEnergyModifier + BaseMaxEnergy;

	AdjustEnergyToMax(DivideValue);
}


// Helper function called when Max Energy is chnged
void UStatsComponent::AdjustEnergyToMax(float DivideValue)
{
	auto NewEnergy = float(MaxEnergy) * DivideValue;
	Energy = NewEnergy;
}


//
void UStatsComponent::SetEnergy(int32 ValueToChange)
{
	Energy += ValueToChange;
	Energy = FMath::Clamp(Energy, 0, MaxEnergy);
}



void UStatsComponent::ResetEnergy()
{
	Energy = MaxEnergy;
}


//
void UStatsComponent::SetArmour()
{
	auto NewArmour = float(Agility) / AgilityToArmourDivider + ArmourModifier + BaseArmour;
	Armour = NewArmour;
}


//
void UStatsComponent::SetMagres()
{
	auto NewMagres = float(Intelligence) / IntelligenceToMagresDivider + MagresModifier + BaseMagres;
	Magres = NewMagres;
}


//
void UStatsComponent::SetStrength(int32 ValueToChange)
{
	Strength += ValueToChange;
	Strength = FMath::Clamp(Strength, 0, 9999);
	SetMaxEnergy();
}


//
void UStatsComponent::SetAgility(int32 ValueToChange)
{
	Agility += ValueToChange;
	Agility = FMath::Clamp(Agility, 0, 9999);
	SetArmour();
}


//
void UStatsComponent::SetConstitution(int32 ValueToChange)
{
	Constitution += ValueToChange;
	Constitution = FMath::Clamp(Constitution, 0, 9999);
	SetMaxHealth();
}


//
void UStatsComponent::SetIntelligence(int32 ValueToChange)
{
	Intelligence += ValueToChange;
	Intelligence = FMath::Clamp(Intelligence, 0, 9999);
	SetMagres();
}


//
void UStatsComponent::SetMaxHealthModifier(int32 ValueToChange)
{
	MaxHealtModifier += ValueToChange;
	SetMaxHealth();
}


//
void UStatsComponent::SetMaxEnergyModifier(int32 ValueToChange)
{
	MaxEnergyModifier += ValueToChange;
	SetMaxEnergy();
}


//
void UStatsComponent::SetArmourModifier(int32 ValueToChange)
{
	ArmourModifier += ValueToChange;
	SetArmour();
}


//
void UStatsComponent::SetMagresModifier(int32 ValueToChange)
{
	MagresModifier += ValueToChange;
	SetMagres();
}


//
void UStatsComponent::InitializeStats()
{
	SetMaxEnergy();
	SetMaxHealth();
	SetMagres();
	SetArmour();
	ResetHealth();
	ResetEnergy();
}


//
void UStatsComponent::ApplyEffect(FGameplayTag GameplayTag, int32 EffectValue)
{
	FGameplayTag StateTag = FGameplayTag::RequestGameplayTag("State");

	if (GameplayTag.MatchesTag(StateTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("StateTag"))
	}
	else if(GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Strength")))
	{
		SetStrength(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Agility")))
	{
		SetAgility(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Constitution")))
	{
		SetConstitution(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Intelligence")))
	{
		SetIntelligence(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.MaxHealth")))
	{
		SetMaxHealthModifier(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.MaxEnergy")))
	{
		SetMaxEnergyModifier(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Armour")))
	{
		SetArmourModifier(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Magres")))
	{
		SetMagresModifier(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Energy")))
	{
		SetEnergy(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Health")))
	{
		SetHealth(EffectValue);
	}
}
