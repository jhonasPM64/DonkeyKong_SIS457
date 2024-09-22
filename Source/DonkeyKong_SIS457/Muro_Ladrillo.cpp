// Fill out your copyright notice in the Description page of Project Settings.


#include "Muro_Ladrillo.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"

AMuro_Ladrillo::AMuro_Ladrillo()
{
    // Crear el componente de malla estática
    MuroMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MuroMesh"));
    RootComponent = MuroMesh;

    // Cargar la malla estática para el muro (puedes cambiar esto por la malla que prefieras)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MuroMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
    if (MuroMeshAsset.Succeeded())
    {
        MuroMesh->SetStaticMesh(MuroMeshAsset.Object);
    }

    // Cargar y aplicar el material
    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Brick_Clay_Old.M_Brick_Clay_Old'"));
    if (MaterialAsset.Succeeded())
    {
        MuroMesh->SetMaterial(0, MaterialAsset.Object);
    }
}

void AMuro_Ladrillo::BeginPlay()
{
    Super::BeginPlay();
}

void AMuro_Ladrillo::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
