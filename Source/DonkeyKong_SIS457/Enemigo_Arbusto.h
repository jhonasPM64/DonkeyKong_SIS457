// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "Enemigo_Arbusto.generated.h"

/**
 * 
 */
UCLASS()
class DONKEYKONG_SIS457_API AEnemigo_Arbusto : public AEnemigo
{
	GENERATED_BODY()

protected:
	int altura;
	int ancho;
	FVector posicionInicial;
	FVector posicionFinal;
public:
	void ocultar();
	void aparecer();
};
