#include "Muro_pegajoso.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

AMuro_pegajoso::AMuro_pegajoso()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> MuroPegajosoMaterial(TEXT("Material'/Game/StarterContent/Materials/M_Ground_Grass.M_Ground_Grass'"));
	if (MuroPegajosoMaterial.Succeeded()) {
		MeshMuro->SetMaterial(0, MuroPegajosoMaterial.Object);
	}

	MeshMuro->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshMuro->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	MeshMuro->OnComponentBeginOverlap.AddDynamic(this, &AMuro_pegajoso::OnOverlapBegin);

	TiempoPegado = 3.0f;  
}

void AMuro_pegajoso::BeginPlay()
{
	Super::BeginPlay();
}

void AMuro_pegajoso::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// Verifica si el actor que colisiona es un personaje
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (PlayerCharacter)
	{
		PegadoPersonaje = PlayerCharacter;

		PegadoPersonaje->GetCharacterMovement()->DisableMovement();

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMuro_pegajoso::LiberarPersonaje, TiempoPegado, false);
	}
}

void AMuro_pegajoso::LiberarPersonaje()
{
	if (PegadoPersonaje)
	{
		PegadoPersonaje->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

		PegadoPersonaje = nullptr;
	}
}

void AMuro_pegajoso::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
