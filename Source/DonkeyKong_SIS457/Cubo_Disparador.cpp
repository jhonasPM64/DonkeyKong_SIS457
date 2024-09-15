
#include "Cubo_Disparador.h"
#include "Proyectil.h"
#include "TimerManager.h"

// Sets default values
ACubo_Disparador::ACubo_Disparador()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/CuboMesh/Shape_Cube.Shape_Cube'"));
	CuboMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Cubo"));
	CuboMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	CuboMesh->SetStaticMesh(CubeMeshAsset.Object);
	SetRootComponent(CuboMesh);

	Fire = FVector(0.f, 90.f, 0.f);
	FireRate = 0.5f;
	bCanFire = true;
}

// Called when the game starts or when spawned
void ACubo_Disparador::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("proyectil"));

	// Estableel cer temporizador para llamar a FireShot cada 'FireRate' segundos
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ACubo_Disparador::FireShot, FireRate, true);

}

// Called every frame
void ACubo_Disparador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubo_Disparador::FireShot()
{
    if (bCanFire) {
        // Dirección en la que se disparan los proyectiles
        FVector DirectionRight = FVector(1.f, 0.f, 0.f);
        FVector DirectionLeft = FVector(-1.f, 0.f, 0.f);

        // Rotación para los proyectiles
        const FRotator FireRotationRight = DirectionRight.Rotation();
        const FRotator FireRotationLeft = DirectionLeft.Rotation();

        // Ubicación desde donde se dispararán los proyectiles
        const FVector SpawnLocationRight = GetActorLocation() + FireRotationRight.RotateVector(Fire);
        const FVector SpawnLocationLeft = GetActorLocation() + FireRotationLeft.RotateVector(Fire);

        // Obtener el mundo actual
        UWorld* const World = GetWorld();
        if (World != nullptr) {
            // Crear proyectiles en vez de cubos
            World->SpawnActor<AProyectil>(SpawnLocationRight, FireRotationRight);  // Cambia ACubo_Disparador a AProyectil
            World->SpawnActor<AProyectil>(SpawnLocationLeft, FireRotationLeft);   // Cambia ACubo_Disparador a AProyectil
        }

        // Deshabilitar el disparo hasta que ShotTimer vuelva a activarlo
        bCanFire = false;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ACubo_Disparador::ShotTimer, FireRate);
    }
}

void ACubo_Disparador::ShotTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("ShotTimer aqui"));

	bCanFire = true;
}
