// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "StatsComponent.generated.h"

class UStatusEffectComponent;

UCLASS( ClassGroup=(Stats), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

	// Sets max health based on modifier and other stats
	UFUNCTION(BlueprintCallable, Category = "Max Health")
	void SetMaxHealth();

	// Changes current health
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetHealth(int32 ValueToChange);

	// Reset health to max health
	UFUNCTION(BlueprintCallable, Category = "Health")
	void ResetHealth();

	// Sets max energy based on modifier and other stats
	UFUNCTION(BlueprintCallable, Category = "Max Energy")
	void SetMaxEnergy();

	// Changes current energy
	UFUNCTION(BlueprintCallable, Category = "Energy")
	void SetEnergy(int32 ValueToChange);

	// Reset energy to max energy
	UFUNCTION(BlueprintCallable, Category = "Energy")
	void ResetEnergy();

	// Sets armour based modifier and other stats
	UFUNCTION(BlueprintCallable, Category = "Armour")
	void SetArmour();

	// Sets magres based modifier and other stats
	UFUNCTION(BlueprintCallable, Category = "Magres")
	void SetMagres();

	// Changes current strength
	UFUNCTION(BlueprintCallable, Category = "Strength")
	void SetStrength(int32 ValueToChange);

	// Changes current agility
	UFUNCTION(BlueprintCallable, Category = "Agility")
	void SetAgility(int32 ValueToChange);

	// Changes current constitution
	UFUNCTION(BlueprintCallable, Category = "Constitution")
	void SetConstitution(int32 ValueToChange);

	// Changes current intelligence
	UFUNCTION(BlueprintCallable, Category = "Intelligence")
	void SetIntelligence(int32 ValueToChange);

	// Changes modifier value of max health
	UFUNCTION(BlueprintCallable, Category = "Modifier|Max Health")
	void SetMaxHealthModifier(int32 ValueToChange);

	// Changes modifier value of max energy
	UFUNCTION(BlueprintCallable, Category = "Modifier|Max Energy")
	void SetMaxEnergyModifier(int32 ValueToChange);

	// Changes modifier value of armour
	UFUNCTION(BlueprintCallable, Category = "Modifier|Armour")
	void SetArmourModifier(int32 ValueToChange);

	// Changes modifier value of magres
	UFUNCTION(BlueprintCallable, Category = "Modifier|Magres")
	void SetMagresModifier(int32 ValueToChange);

	// Initializes all stats
	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void InitializeStats();

	// Change stats based on effect
	UFUNCTION()
	void ApplyEffect(FGameplayTag& GameplayTag, int32 EffectValue);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Max Health|Base Value", meta=(ClampMin=1, UIMin = 1, ClampMax = 9999, UIMax = 9999))
	int32 BaseMaxHealth = 13;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Max Health")
	int32 MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Max Energy|Base Value", meta = (ClampMin = 1, UIMin = 1, ClampMax = 9999, UIMax = 9999))
	int32 BaseMaxEnergy = 7;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Max Energy")
	int32 MaxEnergy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Energy")
	int32 Energy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Strength", meta = (ClampMin = 1, UIMin = 1, ClampMax = 9999, UIMax = 9999))
	int32 Strength = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Agility", meta = (ClampMin = 1, UIMin = 1, ClampMax = 9999, UIMax = 9999))
	int32 Agility = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constitution", meta = (ClampMin = 1, UIMin = 1, ClampMax = 9999, UIMax = 9999))
	int32 Constitution = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Intelligence", meta = (ClampMin = 1, UIMin = 1, ClampMax = 9999, UIMax = 9999))
	int32 Intelligence = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armour|Base Value", meta = (ClampMin = 1, UIMin = 1, ClampMax = 9999, UIMax = 9999))
	int32 BaseArmour = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Armour")
	int32 Armour;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Magres|Base Value", meta = (ClampMin = 1, UIMin = 1, ClampMax = 9999, UIMax = 9999))
	int32 BaseMagres = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magres")
	int32 Magres;

	// TODO new stats (skills and defences)

private:
	float CostitutionPerUnitToMaxHealth = 8;

	float StrengthPerUnitToMaxEnergy = 5;

	float AgilityToArmourDivider = 3;

	float IntelligenceToMagresDivider = 4;

	int32 MaxHealtModifier;

	int32 MaxEnergyModifier;

	int32 ArmourModifier;

	int32 MagresModifier;

	// Helper function called when Max Health is chnged
	void AdjustHealthToMax(float DivideValue);

	// Helper function called when Max Energy is chnged
	void AdjustEnergyToMax(float DivideValue);

	UStatusEffectComponent* StatusEffectComponent;
};
