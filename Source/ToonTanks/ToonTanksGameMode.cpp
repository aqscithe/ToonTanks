// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		DestroyTank();
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;
		UE_LOG(LogTemp, Display, TEXT("Towers remaining: %d"), TargetTowers);

		if (TargetTowers <= 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
	
}

void AToonTanksGameMode::DestroyTank()
{
	Tank->HandleDestruction();
	if (ToonTanksPlayerController)
	{
		Tank->DisableInput(ToonTanksPlayerController);
		ToonTanksPlayerController->SetPlayerEnabledState(false);
	}
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	TargetTowers = GetTargetTowerCount();
	UE_LOG(LogTemp, Display, TEXT("Tower count: %d"), TargetTowers);

	StartGame();

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		// creating timer delegate b/c the callback functions needs to take in a parameter
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController, 
			&AToonTanksPlayerController::SetPlayerEnabledState, 
			true
		);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
	
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray< AActor* > OutTowers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), OutTowers);
	return OutTowers.Num();
}