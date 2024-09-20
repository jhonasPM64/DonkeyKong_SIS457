// Fill out your copyright notice in the Description page of Project Settings.


#include "Muro_Congelado.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h" 

AMuro_Congelado::AMuro_Congelado()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> Muro_Congelado(TEXT("Material'/Game/StarterContent/Materials/M_Water_Lake.M_Water_Lake'"));
	if (Muro_Congelado.Succeeded()) {
		MeshMuro->SetMaterial(0, Muro_Congelado.Object);
	}
}

void AMuro_Congelado::BeginPlay()
{
}

void AMuro_Congelado::Tick(float DeltaTime)
{
}
