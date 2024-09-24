#include "Cubo_Disparador.h"
#include "Proyectil.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "DonkeyKong_SIS457Character.h"

// Sets default values
ACubo_Disparador::ACubo_Disparador()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	CuboMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Cubo"));
	CuboMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	CuboMesh->SetStaticMesh(CubeMeshAsset.Object);
	SetRootComponent(CuboMesh);

	Fire = FVector(0.f, 90.f, 0.f);
	FireRate = 0.5f;
	bCanFire = true;

    ProjectileCount = 0;   // Contador de proyectiles empieza en 0
    MaxProjectiles = 999;  // Nmero mximo de proyectiles permitidos

    // Inicializar la posición de generación
    SpawnLocation = FVector::ZeroVector;

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
    // Verificar si ya hemos alcanzado el máximo de proyectiles
    if (ProjectileCount >= MaxProjectiles) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Límite de proyectiles alcanzado"));
        return; // No generar más proyectiles
    }

    if (bCanFire) {
        // Generar una dirección aleatoria en el plano XY para el primer proyectil
        float RandomAngleRight = FMath::RandRange(0.0f, 360.0f);
        FVector RandomDirectionRight = FVector(FMath::Cos(FMath::DegreesToRadians(RandomAngleRight)), FMath::Sin(FMath::DegreesToRadians(RandomAngleRight)), 0.0f);

        // Generar una dirección aleatoria en el plano XY para el segundo proyectil
        float RandomAngleLeft = FMath::RandRange(0.0f, 360.0f);
        FVector RandomDirectionLeft = FVector(FMath::Cos(FMath::DegreesToRadians(RandomAngleLeft)), FMath::Sin(FMath::DegreesToRadians(RandomAngleLeft)), 0.0f);

        // Rotación para los proyectiles
        const FRotator FireRotationRight = RandomDirectionRight.Rotation();
        const FRotator FireRotationLeft = RandomDirectionLeft.Rotation();

        // Ubicación desde donde se dispararán los proyectiles, usando la posición de generación del cubo
        const FVector SpawnLocationRight = FVector(SpawnLocation.X, SpawnLocation.Y + 100.0f, SpawnLocation.Z); // Ajusta este valor según la distancia lateral deseada
        const FVector SpawnLocationLeft = FVector(SpawnLocation.X, SpawnLocation.Y - 100.0f, SpawnLocation.Z); // Ajusta este valor según la distancia lateral deseada

        // Obtener el mundo actual
        UWorld* const World = GetWorld();
        if (World != nullptr) {
            // Crear proyectiles
            World->SpawnActor<AProyectil>(SpawnLocationRight, FireRotationRight);
            World->SpawnActor<AProyectil>(SpawnLocationLeft, FireRotationLeft);

            // Incrementar el contador de proyectiles
            ProjectileCount += 2; // Disparamos dos proyectiles en direcciones aleatorias
        }
    }
}

void ACubo_Disparador::ShotTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("ShotTimer aqui"));

	bCanFire = true;
}
