
#include "Cubo_Disparador.h"
#include "Proyectil.h"

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
}

// Called every frame
void ACubo_Disparador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FireShot();

}

void ACubo_Disparador::FireShot()
{
	if (bCanFire == true) {
		FVector DirectionRight = FVector(0.f, -1.f, 0.f);
		FVector DirectionLeft = FVector(0.f, 1.f, 0.f);
		const FRotator FireRotationRight = DirectionRight.Rotation();
		const FRotator FireRotationLeft = DirectionLeft.Rotation();
		const FVector SpawnLocationRight = GetActorLocation() + FireRotationRight.RotateVector(Fire);
		const FVector SpawnLocationLeft = GetActorLocation() + FireRotationLeft.RotateVector(Fire);
		UWorld* const World1 = GetWorld();
		if (World1 != nullptr) {
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("Spawneo")));
			World1->SpawnActor<ACubo_Disparador>(SpawnLocationRight, FireRotationRight);
			World1->SpawnActor<ACubo_Disparador>(SpawnLocationLeft, FireRotationLeft);
		}
		bCanFire = false;
		World1->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ACubo_Disparador::ShotTimer, FireRate);
	}
}

void ACubo_Disparador::ShotTimer()
{
	bCanFire = true;
}
