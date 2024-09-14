// Fill out your copyright notice in the Description page of Project Settings.


#include "Proyectil.h" 
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProyectil::AProyectil()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Projectile(TEXT("StaticMesh'/Game/Geometry/Meshes/ProyectilMesh/Shape_Sphere.Shape_Sphere'"));
	ProyectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Projectile"));
	ProyectileMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	ProyectileMesh->SetStaticMesh(Projectile.Object);
	ProyectileMesh->OnComponentHit.AddDynamic(this, &AProyectil::OnHit);
	SetRootComponent(ProyectileMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement_Projectile"));
	ProjectileMovement->UpdatedComponent = ProyectileMesh;
	ProjectileMovement->InitialSpeed = 2500.f;
	ProjectileMovement->MaxSpeed = 2500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f;

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
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	this->Destroy();
}

