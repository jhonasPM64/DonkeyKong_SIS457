// Fill out your copyright notice in the Description page of Project Settings.


#include "Muro_electrico.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h" // Importante para el personaje
#include "DonkeyKong_SIS457.h" // Asumiendo que tu clase de personaje es AMyCharacter
#include "DonkeyKong_SIS457Character.h"


AMuro_electrico::AMuro_electrico()
{
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UMaterial> Muro_electrico(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile_Pulse.M_Tech_Hex_Tile_Pulse'"));
    if (Muro_electrico.Succeeded()) {
        MeshMuro->SetMaterial(0, Muro_electrico.Object);
    }
    // Habilitar colisión
   // MeshMuro->OnComponentBeginOverlap.AddDynamic(this, &AMuro_electrico::OnOverlapBegin);
    // Aquí inicializas tu componente de malla, por ejemplo MeshMuro
    MeshMuro = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshMuro"));

    // Configurar las colisiones
    MeshMuro->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    MeshMuro->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    MeshMuro->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    // Asegurarse de que pueda generar eventos de superposición
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
    UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin se ha activado")); 

    if (OtherActor && (OtherActor != this))
    {
        UE_LOG(LogTemp, Warning, TEXT("Colisión detectada con: %s"), *OtherActor->GetName());

        // Verificar si el actor que colisionó es el personaje
        ADonkeyKong_SIS457Character* DonkeyKongCharacter = Cast<ADonkeyKong_SIS457Character>(OtherActor);
        if (DonkeyKongCharacter)
        {
            UE_LOG(LogTemp, Warning, TEXT("Aplicando daño al personaje"));

            // Si tienes un miembro de clase llamado Damage, usa this->Damage para referirte a él
            this->Damage = 10.0f; // Cantidad de daño que quieres aplicar
            DonkeyKongCharacter->TakeDamage(this->Damage, FDamageEvent(), nullptr, this);
        }
    }
}