// Fill out your copyright notice in the Description page of Project Settings.


#include "Muro_Ladrillo.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

AMuro_Ladrillo::AMuro_Ladrillo()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> Muro_Ladrillo(TEXT("Material'/Game/StarterContent/Materials/M_Brick_Clay_New.M_Brick_Clay_New'"));
	if (Muro_Ladrillo.Succeeded()) {
		MeshMuro->SetMaterial(0, Muro_Ladrillo.Object);
	}
}

void AMuro_Ladrillo::BeginPlay()
{
}

void AMuro_Ladrillo::Tick(float DeltaTime)
{
}
