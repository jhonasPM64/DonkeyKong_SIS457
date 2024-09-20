// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Muro.h"
#include "Muro_Congelado.generated.h"

UCLASS()
class DONKEYKONG_SIS457_API AMuro_Congelado : public AMuro
{
	GENERATED_BODY()  
	
public:
	// Sets default values for this actor's properties
	AMuro_Congelado();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Muro_Congelado")
	UTexture2D* TextureCongeladot;
};
