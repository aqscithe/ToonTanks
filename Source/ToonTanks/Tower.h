// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	ATower();

	void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRange = 500.f;

	class ATank* Tank;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireRate = 2.f;

	FTimerHandle FireRateTimerHandle;
	void CheckFireCondition();

	bool InFireRange();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
