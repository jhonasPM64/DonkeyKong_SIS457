// Fill out your copyright notice in the Description page of Project Settings.


#include "Muro_electrico.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "DonkeyKong_SIS457Character.h"

class AMyCharacter :public ACharacter
{
};

AMuro_electrico::AMuro_electrico()
{
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FObjectFinder<UMaterial> Muro_electrico(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile_Pulse.M_Tech_Hex_Tile_Pulse'"));
    if (Muro_electrico.Succeeded()) {
        MeshMuro->SetMaterial(0, Muro_electrico.Object);
    }

    // Vincula el evento de colisión
    MeshMuro->OnComponentBeginOverlap.AddDynamic(this, &AMuro_electrico::OnOverlapBegin);
}

void AMuro_electrico::BeginPlay()
{
    Super::BeginPlay();

}

void AMuro_electrico::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMuro_electrico::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    // Verificar si el otro actor es el personaje
    if (OtherActor)
    {
        ADonkeyKong_SIS457Character* Character = Cast<ADonkeyKong_SIS457Character>(OtherActor);
        if (Character)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("¡El personaje ha tocado el muro eléctrico!"));

            // Infligir daño al personaje
            Character->TakeDamage(50.0f);
        }
    }
}