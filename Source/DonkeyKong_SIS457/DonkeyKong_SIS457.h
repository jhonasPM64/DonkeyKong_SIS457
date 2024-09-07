// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"  // Asegúrate de incluir el módulo que contiene la clase AActor
#include "Obstaculo.h"
#include "DonkeyKong_SIS457.generated.h"

UCLASS()
class DONKEYKONG_SIS457_API ADonkeyKong_SIS457 : public AActor  // La clase hereda de AActor, puedes cambiar esto si hereda de otra clase
{
    GENERATED_BODY()

public:
    // Constructor de la clase
    ADonkeyKong_SIS457();
    AObstaculo* GetObstaculo();
    // Aquí puedes declarar las funciones y propiedades de la clase

public:
    void SetObstaculo(AObstaculo* NuevoObstaculo);

private:
    AObstaculo* ObstaculoActual;

};
