// Fill out your copyright notice in the Description page of Project Settings.


#include "Proyectil.h" 
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProyectil::AProyectil()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Projectile(TEXT("StaticMesh'/Game/Geometry/Meshes/ProyectilMesh/Shape_Sphere.Shape_Sphere'"));
	ProyectilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Projectile"));
	ProyectilMesh->SetRelativeScale3D(FVector(0.4f, 0.05f, 0.4f));
	ProyectilMesh->SetStaticMesh(Projectile.Object);
	ProyectilMesh->OnComponentHit.AddDynamic(this, &AProyectil::OnHit);
	SetRootComponent(ProyectilMesh);

	ProyectilMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);  // Ignora a los personajes

	ProyectilMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement_Projectile"));
	ProyectilMovement->UpdatedComponent = ProyectilMesh;
	ProyectilMovement->InitialSpeed = 2500.f;
	ProyectilMovement->MaxSpeed = 2500.f;
	ProyectilMovement->bRotationFollowsVelocity = true;
	ProyectilMovement->bShouldBounce = false;
	ProyectilMovement->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 2.f;
}

// Called when the game starts or when spawned
void AProyectil::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProyectil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProyectil::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Si el otro actor es un objeto que simula físicas, aplica un impulso
	if (OtherActor && OtherActor != this && OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	// Destruye el proyectil
	Destroy();
}