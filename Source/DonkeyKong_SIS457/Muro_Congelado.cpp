// Fill out your copyright notice in the Description page of Project Settings.


#include "Muro_Congelado.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h" 
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"


AMuro_Congelado::AMuro_Congelado()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> Muro_Congelado(TEXT("Material'/Game/StarterContent/Materials/M_Water_Lake.M_Water_Lake'"));
	if (Muro_Congelado.Succeeded()) {
		MeshMuro->SetMaterial(0, Muro_Congelado.Object);
	}
	// Definir valores por defecto
	RadioDeCongelacion = 500.0f;
	FactorReduccionVelocidad = 0.5f;
}

void AMuro_Congelado::BeginPlay()
{
	Super::BeginPlay();
}

void AMuro_Congelado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // Obtener el personaje principal
    ACharacter* Personaje = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (Personaje)
    {
        // Calcular la distancia entre el muro y el personaje
        float Distancia = FVector::Dist(GetActorLocation(), Personaje->GetActorLocation());

        // Si el personaje está dentro del radio de congelación, reducir la velocidad
        if (Distancia <= RadioDeCongelacion)
        {
            AplicarEfectoCongelacion(Personaje, Distancia);
        }
    }
}

void AMuro_Congelado::AplicarEfectoCongelacion(ACharacter* Personaje, float Distancia)
{
    // Calcular el porcentaje de congelación basado en la distancia
    float ProporciónCongelación = FMath::Clamp(1.0f - (Distancia / RadioDeCongelacion), 0.0f, 1.0f);

    // Obtener la velocidad actual del personaje
    float VelocidadActual = Personaje->GetCharacterMovement()->MaxWalkSpeed;

    // Aplicar la reducción de velocidad
    Personaje->GetCharacterMovement()->MaxWalkSpeed = FMath::Lerp(VelocidadActual, 0.0f, ProporciónCongelación);

}
