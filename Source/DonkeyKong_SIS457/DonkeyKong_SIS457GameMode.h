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
	/*APlataforma* cp02 = nullptr;
	APlataforma* cp03 = nullptr;
	APlataforma* cp04 = nullptr;
	APlataforma* cp05 = nullptr;
	APlataforma* cp06 = nullptr;*/
	ABarril* barril01;

	TArray<APlataforma*> PlataformasPequenas;  // Renombrado para evitar conflictos
	TMap<FVector, APlataforma*> MapaPlataformas;
	TMap<APlataforma*, TArray<APlataforma*>> MapaDePlataformas;
	void GenerarCubosAleatoriamente(int MaxCubos = 5);

};



