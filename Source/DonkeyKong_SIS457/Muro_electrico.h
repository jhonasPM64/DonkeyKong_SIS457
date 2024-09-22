// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Muro.h"
#include "Muro_electrico.generated.h"

UCLASS()
class DONKEYKONG_SIS457_API AMuro_electrico : public AMuro
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMuro_electrico();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Valor de daño que el muro inflige al personaje
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Muro_electrico")
	float DamageValue;
};