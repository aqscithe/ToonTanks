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

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	void HandleGameStart();
	void DestroyTank();

	UPROPERTY(EditAnywhere, Category = "Options")
	float StartDelay = 3.f;

	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();

};
