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
    RadioDeCongelacion = 1000.0f;
    FactorReduccionVelocidad = 0.5f;
    ProgresoCongelacion = 0.0f;  // Inicialmente no congelado
    VelocidadCongelacion = 0.1f; // A qué ritmo el personaje se congela por tick
}

void AMuro_Congelado::BeginPlay()
{
	Super::BeginPlay();
}

void AMuro_Congelado::Tick(float DeltaTime)
{
    ACharacter* Personaje = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (Personaje)
    {
        float Distancia = FVector::Dist(GetActorLocation(), Personaje->GetActorLocation());

        // Si el personaje está dentro del rango de congelación
        if (Distancia <= RadioDeCongelacion)
        {
            AplicarEfectoCongelacion(Personaje, Distancia, DeltaTime);
        }
        else
        {
            // Si el personaje sale del rango, reduce el progreso del congelamiento gradualmente
            if (ProgresoCongelacion > 0.0f)
            {
                ProgresoCongelacion -= VelocidadCongelacion * DeltaTime;
                ProgresoCongelacion = FMath::Clamp(ProgresoCongelacion, 0.0f, 1.0f);
            }
        }
    }
}

void AMuro_Congelado::AplicarEfectoCongelacion(ACharacter* Personaje, float Distancia, float DeltaTime)
{
    // Calcular la proporción de congelación en función de la distancia
    float ProporciónCongelación = 1.0f - (Distancia / RadioDeCongelacion);

    // Acumular el progreso de congelación de manera gradual
    ProgresoCongelacion += VelocidadCongelacion * DeltaTime * ProporciónCongelación;
    ProgresoCongelacion = FMath::Clamp(ProgresoCongelacion, 0.0f, 1.0f);

    // Obtener la velocidad actual del personaje
    float VelocidadActual = Personaje->GetCharacterMovement()->MaxWalkSpeed;

    // Aplicar la reducción gradual en función del progreso de congelación
    Personaje->GetCharacterMovement()->MaxWalkSpeed = FMath::Lerp(VelocidadActual, 0.0f, ProgresoCongelacion);

}