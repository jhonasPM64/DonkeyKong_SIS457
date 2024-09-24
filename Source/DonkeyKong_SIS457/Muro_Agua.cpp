// Fill out your copyright notice in the Description page of Project Settings.


#include "Muro_Agua.h"

AMuro_Agua::AMuro_Agua()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> AguaMaterial(TEXT("Material'/Game/StarterContent/Materials/M_Water_Ocean.M_Water_Ocean'"));
	if (AguaMaterial.Succeeded()) {
		MeshMuro->SetMaterial(0, AguaMaterial.Object);
	}

	FVector NewScale(2.0f, 0.25f, 2.0f);
	SetActorScale3D(NewScale);
}

void AMuro_Agua::BeginPlay()
{
	Super::BeginPlay();
}

void AMuro_Agua::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
