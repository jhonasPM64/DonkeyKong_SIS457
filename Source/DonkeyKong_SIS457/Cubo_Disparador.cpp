#include "Cubo_Disparador.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ACubo_Disparador::ACubo_Disparador()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Static Mesh Component
	CuboMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CuboMesh"));
	RootComponent = CuboMesh;

	// Set a default mesh for the cube (you can set this in the editor or in code)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/CuboMesh/Shape_Cube.Shape_Cube'"));
	if (CubeMeshAsset.Succeeded())
	{
		CuboMesh->SetStaticMesh(CubeMeshAsset.Object);
	}

	// Optionally, set default scale and size
	CuboMesh->SetWorldScale3D(FVector(1.0f));  // Set the size of the cube
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
}
