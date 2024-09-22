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

	// Radio en el que el personaje comenzar� a reducir su velocidad
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Muro_Congelado")
	float RadioDeCongelacion;

	// Factor de reducci�n de velocidad
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Muro_Congelado")
	float FactorReduccionVelocidad;
protected:
	// Funci�n para aplicar la reducci�n de velocidad al personaje
	void AplicarEfectoCongelacion(ACharacter* Personaje, float Distancia);
};