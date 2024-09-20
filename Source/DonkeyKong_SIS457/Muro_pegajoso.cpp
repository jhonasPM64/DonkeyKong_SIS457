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

	// Habilitamos la colisión para el MeshMuro
	MeshMuro->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshMuro->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	// Vinculamos la función de colisión
	MeshMuro->OnComponentBeginOverlap.AddDynamic(this, &AMuro_pegajoso::OnOverlapBegin);

	TiempoPegado = 3.0f;  // El personaje estará pegado 3 segundos
}

void AMuro_pegajoso::BeginPlay()
{
	Super::BeginPlay();
}

// Esta función se llama cuando algo colisiona con el muro
void AMuro_pegajoso::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// Verifica si el actor que colisiona es un personaje
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// Asignamos el personaje a la variable PegadoPersonaje
		PegadoPersonaje = PlayerCharacter;

		// Desactiva el movimiento del personaje
		PegadoPersonaje->GetCharacterMovement()->DisableMovement();

		// Inicia un temporizador para liberar al personaje después de `TiempoPegado` segundos
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMuro_pegajoso::LiberarPersonaje, TiempoPegado, false);
	}
}

void AMuro_pegajoso::LiberarPersonaje()
{
	if (PegadoPersonaje)
	{
		// Reactiva el movimiento del personaje
		PegadoPersonaje->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

		// Limpia la referencia al personaje pegado
		PegadoPersonaje = nullptr;
	}
}

void AMuro_pegajoso::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
