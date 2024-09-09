// Fill out your copyright notice in the Description page of Project Settings.


#include "Barril.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"  // Incluye esto para UCapsuleComponent
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


// Sets default values
ABarril::ABarril()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;


	// Crear un componente de malla est�tica para el barril (solo visual)
	BarrilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrilMesh"));
	RootComponent = BarrilMesh;

	// Cargar la malla del barril desde el contenido del juego
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BarrilMeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/BarrilMesh/StaticMesh.StaticMesh'"));  // Cambia aqu� la referencia a tu barril
	if (BarrilMeshAsset.Succeeded())
	{
		BarrilMesh->SetStaticMesh(BarrilMeshAsset.Object);
	}

	// Deshabilitar simulaci�n de f�sicas y colisiones en la malla del barril (solo es visual)
	BarrilMesh->SetSimulatePhysics(false);
	BarrilMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);  // Deshabilitar colisi�n en la malla visual

	// Crear y configurar el componente de colisi�n esf�rico
	BarrilColision = CreateDefaultSubobject<USphereComponent>(TEXT("BarrilColision"));
	BarrilColision->InitSphereRadius(50.0f);  // Ajusta el radio seg�n el tama�o de tu barril
	BarrilColision->SetCollisionProfileName(TEXT("PhysicsActor"));  // Configura el perfil de colisi�n
	BarrilColision->SetupAttachment(RootComponent);  // Asigna el componente de colisi�n al root (malla del barril)
	BarrilColision->SetSimulatePhysics(true);  // Habilita la simulaci�n de f�sicas
	BarrilColision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);  // Habilita las colisiones
	BarrilColision->OnComponentBeginOverlap.AddDynamic(this, &ABarril::OnOverlapBegin);  // Configura el evento de superposici�n

    // Configurar velocidad de rotaci�n
    RotationSpeed = 150.0f;
    SpeedIncrease = 250.0f;

	// Inicializar la escala del barril
	BarrilScale = FVector(0.2f, 0.2f, 0.2f);  // Cambia los valores si deseas una escala inicial diferente

	// Aplicar la escala a la malla del barril
	BarrilMesh->SetWorldScale3D(BarrilScale);

	FRotator Rotation(0.0f, 90.0f, 0.0f);
	BarrilMesh->SetRelativeRotation(Rotation);

}

// Called when the game starts or when spawned
void ABarril::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarril::Tick(float DeltaTime)
{
	   Super::Tick(DeltaTime);

    // Rotar el barril
   /* FRotator CurrentRotation = BarrilMesh->GetComponentRotation();
    CurrentRotation.Yaw += RotationSpeed * DeltaTime;
    BarrilMesh->SetWorldRotation(CurrentRotation);;*/
}

void ABarril::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);
		if (Character)
		{
			// Aplicar da�o al personaje
			UGameplayStatics::ApplyDamage(Character, 10.0f, nullptr, this, nullptr);
		}
	}
}

