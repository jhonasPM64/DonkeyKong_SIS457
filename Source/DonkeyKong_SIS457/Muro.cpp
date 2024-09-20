// Fill out your copyright notice in the Description page of Project Settings.


#include "Muro.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMuro::AMuro()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	MeshMuro = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	MeshMuro->SetStaticMesh(MeshAsset.Object);
	RootComponent = MeshMuro;

	FVector NewScale(2.0f, 0.25f, 2.0f);
	SetActorScale3D(NewScale);
}

// Called when the game starts or when spawned
void AMuro::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMuro::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

