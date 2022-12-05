// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"


ATower::ATower()
{

}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
	
}

void ATower::CheckFireCondition()
{
	if (InFireRange())
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());
		return (Distance <= FireRange);
	}

	return false;
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}
