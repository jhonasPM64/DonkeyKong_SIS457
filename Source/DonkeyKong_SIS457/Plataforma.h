// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plataforma.generated.h"

class UStaticMeshComponent;

UCLASS()
class DONKEYKONG_SIS457_API APlataforma : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlataforma();

	void MoverPlataforma(const FVector& NuevaPosicion);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UStaticMeshComponent* meshPlataforma;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Dirección de movimiento de la plataforma
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movimiento")
	FVector DireccionMovimiento;

	// Bandera para indicar si la plataforma se está moviendo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movimiento")
	bool bMoviendose;

private:
	UInputComponent* InputComponent;
	void SetupInputBindings();
	void CustomAction();

	FVector PosicionInicial;
	FVector PosicionFinal;
};