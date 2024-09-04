// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemigo.generated.h"

UCLASS()
class DONKEYKONG_SIS457_API AEnemigo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemigo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
    // Atributos comunes a todos los enemigos
    FString Nombre;
    int Vida;
    int Ataque;
    int Defensa;
    float Velocidad;

public:
    void atacar();
    void AtaqueMagia();
    void RecibidoDano();
    void RecibirVida();

public:
    // Métodos de acceso (Getters)
    FORCEINLINE int GetVida() const { return Vida; }
    FORCEINLINE int GetAtaque() const { return Ataque; }
    FORCEINLINE int GetDefensa() const { return Defensa; }
    FORCEINLINE float GetVelocidad() const { return Velocidad; }
    FORCEINLINE FString GetNombre() const { return Nombre; }

    // Métodos de modificación (Setters)
    FORCEINLINE void SetVida(int NuevaVida) { Vida = NuevaVida; }
    FORCEINLINE void SetAtaque(int NuevoAtaque) { Ataque = NuevoAtaque; }
    FORCEINLINE void SetDefensa(int NuevaDefensa) { Defensa = NuevaDefensa; }
    FORCEINLINE void SetVelocidad(float NuevaVelocidad) { Velocidad = NuevaVelocidad; }
    FORCEINLINE void SetNombre(FString NuevoNombre) { Nombre = NuevoNombre; }

};
