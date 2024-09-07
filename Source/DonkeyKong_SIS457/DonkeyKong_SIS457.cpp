// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_SIS457.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, DonkeyKong_SIS457, "DonkeyKong_SIS457" );

ADonkeyKong_SIS457::ADonkeyKong_SIS457()
{
}

AObstaculo* ADonkeyKong_SIS457::GetObstaculo()
{
	return ObstaculoActual;
}

void ADonkeyKong_SIS457::SetObstaculo(AObstaculo* NuevoObstaculo)
{
	ObstaculoActual = NuevoObstaculo;
}
