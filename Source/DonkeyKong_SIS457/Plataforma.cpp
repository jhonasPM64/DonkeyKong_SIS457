// Fill out your copyright notice in the Description page of Project Settings.


#include "Plataforma.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APlataforma::APlataforma()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));

	meshPlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	meshPlataforma->SetStaticMesh(MeshAsset.Object);
	RootComponent = meshPlataforma;

	FVector NewScale(2.0f, 3.0f, 0.5f);
	SetActorScale3D(NewScale);

	bMoviendose = false;
	PosicionInicial = GetActorLocation();
}

void APlataforma::MoverPlataforma(const FVector& NuevaPosicion)
{
	SetActorLocation(NuevaPosicion);

	// Mensaje en pantalla
	//FString Mensaje = FString::Printf(TEXT("Plataforma movida a: %s"), *NuevaPosicion.ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Mensaje);
}

// Called when the game starts or when spawned
void APlataforma::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void APlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bMoviendose)
	{
		FVector NuevaPosicion = GetActorLocation();

		// Mover en la dirección especificada por DireccionMovimiento
		if (DireccionMovimiento.Z != 0.0f) // Movimiento vertical (arriba-abajo)
		{
			NuevaPosicion.Z += FMath::Sin(GetWorld()->GetTimeSeconds()) * DeltaTime * 100.0f; // Oscilar en Z
		}
		else if (DireccionMovimiento.X != 0.0f) // Movimiento horizontal (izquierda-derecha)
		{
			NuevaPosicion.X += FMath::Sin(GetWorld()->GetTimeSeconds()) * DeltaTime * 100.0f; // Oscilar en X
		}

		SetActorLocation(NuevaPosicion);
	}
}

void APlataforma::SetupInputBindings()
{
	InputComponent->BindAction("CustomAction", IE_Pressed, this, &APlataforma::CustomAction);
}

void APlataforma::CustomAction()
{
}