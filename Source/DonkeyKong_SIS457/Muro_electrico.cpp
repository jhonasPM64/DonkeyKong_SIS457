// Fill out your copyright notice in the Description page of Project Settings.


#include "Muro_electrico.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

class AMyCharacter :public ACharacter
{
public:
    float Health = 100.0f; // Valor inicial de salud
};

AMuro_electrico::AMuro_electrico()
{
    PrimaryActorTick.bCanEverTick = true;

    // Valor de daño del muro eléctrico
    DamageValue = 10.0f;

    // Asignar la colisión
    if (MeshMuro)
    {
        MeshMuro->OnComponentBeginOverlap.AddDynamic(this, &AMuro_electrico::OnOverlapBegin);
    }

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

void AMuro_electrico::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
    if (Character)
    {
        // Valor de salud antes de recibir daño
        float PreviousHealth = Character->Health;

        // Restar el daño a la salud del personaje
        Character->Health -= DamageValue;

        // Comprobar si el personaje perdió vida
        if (Character->Health < PreviousHealth)
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("El personaje ha perdido vida."));
            }
        }
        else
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("El personaje no ha perdido vida."));
            }
        }

        // Mostrar el valor de salud actual en la pantalla
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Salud del personaje: %f"), Character->Health));
        }

        // Si la salud llega a 0, destruir el personaje
        if (Character->Health <= 0.0f)
        {
            Character->Destroy();
        }
    }
}