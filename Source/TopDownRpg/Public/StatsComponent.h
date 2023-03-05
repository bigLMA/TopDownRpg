// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

	UFUNCTION(BlueprintCallable, Category = "Max Health")
	void SetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetHealth(int32 ValueToChange);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ResetHealth();

	UFUNCTION(BlueprintCallable, Category = "Max Energy")
	void SetMaxEnergy();

	UFUNCTION(BlueprintCallable, Category = "Energy")
	void SetEnergy(int32 ValueToChange);

	UFUNCTION(BlueprintCallable, Category = "Energy")
	void ResetEnergy();

	UFUNCTION(BlueprintCallable, Category = "Armour")
	void SetArmour();

	UFUNCTION(BlueprintCallable, Category = "Magres")
	void SetMagres();

	UFUNCTION(BlueprintCallable, Category = "Strength")
	void SetStrength(int32 ValueToChange);

	UFUNCTION(BlueprintCallable, Category = "Agility")
	void SetAgility(int32 ValueToChange);

	UFUNCTION(BlueprintCallable, Category = "Constitution")
	void SetConstitution(int32 ValueToChange);

	UFUNCTION(BlueprintCallable, Category = "Intelligence")
	void SetIntelligence(int32 ValueToChange);

	UFUNCTION(BlueprintCallable, Category = "Modifier|Max Health")
	void SetMaxHealthModifier(int32 ValueToChange);

	UFUNCTION(BlueprintCallable, Category = "Modifier|Max Energy")
	void SetMaxEnergyModifier(int32 ValueToChange);

	UFUNCTION(BlueprintCallable, Category = "Modifier|Armour")
	void SetArmourModifier(int32 ValueToChange);

	UFUNCTION(BlueprintCallable, Category = "Modifier|Magres")
	void SetMagresModifier(int32 ValueToChange);

	UFUNCTION(BlueprintCallable, Category = "Initialization")
	void InitializeStats();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Max Health|Base Value")
	int32 BaseMaxHealth = 13;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Max Health")
	int32 MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Max Energy|Base Value")
	int32 BaseMaxEnergy = 7;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Max Energy")
	int32 MaxEnergy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Energy")
	int32 Energy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Strength")
	int32 Strength = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Agility")
	int32 Agility = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constitution")
	int32 Constitution = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Intelligence")
	int32 Intelligence = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Armour|Base Value")
	int32 BaseArmour = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Armour")
	int32 Armour;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Magres|Base Value")
	int32 BaseMagres = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magres")
	int32 Magres;

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
};
