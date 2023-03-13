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
		StatusEffectComponent->FinishEffect.AddDynamic(this, &UStatsComponent::ApplyEffect);
	}
}


// Sets max health based on modifier and other stats
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


// Changes health
void UStatsComponent::SetHealth(int32 ValueToChange)
{
	Health += ValueToChange;
	Health = FMath::Clamp(Health, 0, MaxHealth);
}


// Reset health to max health
void UStatsComponent::ResetHealth()
{
	Health = MaxHealth;
}


// Sets max energy based on modifier and other stats
void UStatsComponent::SetMaxEnergy()
{
	float DivideValue = float(Energy) / float(MaxEnergy);
	MaxEnergy = Strength * StrengthPerUnitToMaxEnergy + MaxEnergyModifier + BaseMaxEnergy;

	AdjustEnergyToMax(DivideValue);
}


// Helper function called when Max Energy is changed
void UStatsComponent::AdjustEnergyToMax(float DivideValue)
{
	auto NewEnergy = float(MaxEnergy) * DivideValue;
	Energy = NewEnergy;
}


// Changes current energy
void UStatsComponent::SetEnergy(int32 ValueToChange)
{
	Energy += ValueToChange;
	Energy = FMath::Clamp(Energy, 0, MaxEnergy);
}


// Reset energy to max energy
void UStatsComponent::ResetEnergy()
{
	Energy = MaxEnergy;
}


// Sets armour based modifier and other stats
void UStatsComponent::SetArmour()
{
	auto NewArmour = float(Agility) / AgilityToArmourDivider + ArmourModifier + BaseArmour;
	Armour = NewArmour;
}


// Sets magres based modifier and other stats
void UStatsComponent::SetMagres()
{
	auto NewMagres = float(Intelligence) / IntelligenceToMagresDivider + MagresModifier + BaseMagres;
	Magres = NewMagres;
}


// Changes current strength
void UStatsComponent::SetStrength(int32 ValueToChange)
{
	Strength += ValueToChange;
	Strength = FMath::Clamp(Strength, 0, 9999);
	SetMaxEnergy();
}


// Changes current agility
void UStatsComponent::SetAgility(int32 ValueToChange)
{
	Agility += ValueToChange;
	Agility = FMath::Clamp(Agility, 0, 9999);
	SetArmour();
}


// Changes current constitution
void UStatsComponent::SetConstitution(int32 ValueToChange)
{
	Constitution += ValueToChange;
	Constitution = FMath::Clamp(Constitution, 0, 9999);
	SetMaxHealth();
}

// Changes current intelligence
void UStatsComponent::SetIntelligence(int32 ValueToChange)
{
	Intelligence += ValueToChange;
	Intelligence = FMath::Clamp(Intelligence, 0, 9999);
	SetMagres();
}


// Changes modifier value of max health
void UStatsComponent::SetMaxHealthModifier(int32 ValueToChange)
{
	MaxHealtModifier += ValueToChange;
	SetMaxHealth();
}


// Changes modifier value of max energy
void UStatsComponent::SetMaxEnergyModifier(int32 ValueToChange)
{
	MaxEnergyModifier += ValueToChange;
	SetMaxEnergy();
}


// Changes modifier value of armour
void UStatsComponent::SetArmourModifier(int32 ValueToChange)
{
	ArmourModifier += ValueToChange;
	SetArmour();
}


// Changes modifier value of magres
void UStatsComponent::SetMagresModifier(int32 ValueToChange)
{
	MagresModifier += ValueToChange;
	SetMagres();
}


// Changes melee skill value
void UStatsComponent::SetMelee(int32 ValueToSet)
{
	Melee += ValueToSet;
}


//Changes ranged skill value
void UStatsComponent::SetRanged(int32 ValueToSet)
{
	Ranged += ValueToSet;
}


//Changes arcane skill value
void UStatsComponent::SetArcane(int32 ValueToSet)
{
	Arcane += ValueToSet;
}


//Changes social skill value
void UStatsComponent::SetSocial(int32 ValueToSet)
{
	Social += ValueToSet;
}


//Changes blocking skill value
void UStatsComponent::SetBlocking(int32 ValueToSet)
{
	Blocking += ValueToSet;
}


//Changes evading skill value
void UStatsComponent::SetEvading(int32 ValueToSet)
{
	Evading += ValueToSet;
}


//Changes tenacity skill value
void UStatsComponent::SetTenacity(int32 ValueToSet)
{
	Tenacity += ValueToSet;
}


// Initializes all stats
void UStatsComponent::InitializeStats()
{
	SetMaxEnergy();
	SetMaxHealth();
	SetMagres();
	SetArmour();
	ResetHealth();
	ResetEnergy();
}

// Change stats based on gameplay tag
void UStatsComponent::ApplyEffect(FGameplayTag& GameplayTag, int32 EffectValue)
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
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Skills.Arcane")))
	{
		SetArcane(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Skills.Melee")))
	{
		SetMelee(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Skills.Ranged")))
	{
		SetRanged(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Skills.Social")))
	{
		SetSocial(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.DefensiveSkills.Blocking")))
	{
		SetBlocking(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.DefensiveSkills.Evading")))
	{
		SetEvading(EffectValue);
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.DefensiveSkills.Tenacity")))
	{
		SetTenacity(EffectValue);
	}
}


// Getter for stats
int32 UStatsComponent::GetStatByTag(FGameplayTag& GameplayTag) const
{
	if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Strength")))
	{
		return Strength;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Agility")))
	{
		return Agility;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Constitution")))
	{
		return Constitution;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Intelligence")))
	{
		return Intelligence;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.MaxHealth")))
	{
		return MaxHealth;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.MaxEnergy")))
	{
		return MaxHealth;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Armour")))
	{
		return Armour;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Magres")))
	{
		return Magres;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Energy")))
	{
		return Energy;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Health")))
	{
		return Health;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Skills.Arcane")))
	{
		return Arcane;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Skills.Melee")))
	{
		return Melee;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Skills.Ranged")))
	{
		return Ranged;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.Skills.Social")))
	{
		return Social;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.DefensiveSkills.Blocking")))
	{
		return Blocking;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.DefensiveSkills.Evading")))
	{
		return Evading;
	}
	else if (GameplayTag.MatchesTag(FGameplayTag::RequestGameplayTag("Stats.DefensiveSkills.Tenacity")))
	{
		return Tenacity;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR! Please use right tag to get stats!"))
		return -1;
	}
}
