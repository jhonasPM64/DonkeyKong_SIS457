// Fill out your copyright notice in the Description page of Project Settings.


#include "Muro_electrico.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

AMuro_electrico::AMuro_electrico()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> Muro_electrico(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile_Pulse.M_Tech_Hex_Tile_Pulse'"));
	if (Muro_electrico.Succeeded()) {
		MeshMuro->SetMaterial(0, Muro_electrico.Object);
	}
}

void AMuro_electrico::BeginPlay()
{
}

void AMuro_electrico::Tick(float DeltaTime)
{
}
