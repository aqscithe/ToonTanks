// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);

	virtual void BeginPlay() override;

private:
	void HandleGameStart();
	void DestroyTank();

	UPROPERTY(EditAnywhere, Category = "Options")
	float StartDelay = 3.f;

	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

};
