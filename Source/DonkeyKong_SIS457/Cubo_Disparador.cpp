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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/CuboMesh/Shape_Cube.Shape_Cube'"));
	CuboMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Cubo"));
	CuboMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	CuboMesh->SetStaticMesh(CubeMeshAsset.Object);
	SetRootComponent(CuboMesh);

	Fire = FVector(0.f, 90.f, 0.f);
	FireRate = 0.5f;
	bCanFire = true;

    ProjectileCount = 0;   // Contador de proyectiles empieza en 0
    MaxProjectiles = 999;  // Nmero mximo de proyectiles permitidos

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
    // Verificar si ya hemos alcanzado el mximo de proyectiles
    if (ProjectileCount >= MaxProjectiles) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Lmite de proyectiles alcanzado"));
        return; // No generar ms proyectiles
    }

    if (bCanFire) {
        // Obtener el personaje del jugador
        ADonkeyKong_SIS457Character* Character = Cast<ADonkeyKong_SIS457Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
        
        if (Character)
        {
            // Obtener la posición X del personaje
            float CharacterX = Character->GetActorLocation().X;
            
            // Dirección en la que se disparan los proyectiles
            FVector DirectionRight = FVector(0.f, 1.f, 0.f);
            FVector DirectionLeft = FVector(0.f, -1.f, 0.f);

            // Rotación para los proyectiles
            const FRotator FireRotationRight = DirectionRight.Rotation();
            const FRotator FireRotationLeft = DirectionLeft.Rotation();

            float MinDistanceBetweenProjectiles = 200.0f; // Ajusta este valor segn la distancia deseada

            // Ubicación desde donde se dispararán los proyectiles, usando la X del personaje
            const FVector SpawnLocationRight = FVector(CharacterX, GetActorLocation().Y, GetActorLocation().Z) + FireRotationRight.RotateVector(Fire) + DirectionRight * MinDistanceBetweenProjectiles;
            const FVector SpawnLocationLeft = FVector(CharacterX, GetActorLocation().Y, GetActorLocation().Z) + FireRotationLeft.RotateVector(Fire) + DirectionLeft * MinDistanceBetweenProjectiles;

            // Obtener el mundo actual
            UWorld* const World = GetWorld();
            if (World != nullptr) {
                // Crear proyectiles
                World->SpawnActor<AProyectil>(SpawnLocationRight, FireRotationRight);
                World->SpawnActor<AProyectil>(SpawnLocationLeft, FireRotationLeft);

                // Incrementar el contador de proyectiles
                ProjectileCount += 2; // Disparamos dos proyectiles, uno hacia la derecha y otro hacia la izquierda
            }
        }
    }
}

void ACubo_Disparador::ShotTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("ShotTimer aqui"));

	bCanFire = true;
}
