// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DonkeyKong_SIS457GameMode.generated.h"

class AObstaculo;
class APlataforma;
class ADonkeyKong_SIS457;
class ABarril;
class ACubo_Disparador;

UCLASS(minimalapi)
class ADonkeyKong_SIS457GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADonkeyKong_SIS457GameMode();
protected:
	virtual void BeginPlay() override;

public:
	AObstaculo* obstaculo01 = nullptr;
	ADonkeyKong_SIS457* player01 = nullptr;
	ABarril* barril01;

	TArray<APlataforma*> PlataformasPequenas;  // Renombrado para evitar conflictos
	TArray<APlataforma*> Plataformas;  // Cambiado de MapaPlataformas a TArray
	TMap<APlataforma*, TArray<APlataforma*>> MapaDePlataformas;  // Mantiene su función para el movimiento
	void GenerarCubosAleatoriamente(int MaxCubos = 5);
	TArray<APlataforma*> PlataformasConCubos; // <- Añadir esto

/*protected:
	TArray<TSubclassOf<class AMuro>> Muro;

	FTimerHandle Timer;

	void GenerarMurosAleatorios();

	int32 IndiceAleatorio;

	TSubclassOf<class AMuro> MurosAleatorios;*/
};



