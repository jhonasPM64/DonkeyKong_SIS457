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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Muro_electrico")
	UTexture2D* TextureElectrico;
};
