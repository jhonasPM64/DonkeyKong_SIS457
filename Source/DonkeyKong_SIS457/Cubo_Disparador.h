#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cubo_Disparador.generated.h"

UCLASS()
class DONKEYKONG_SIS457_API ACubo_Disparador : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACubo_Disparador();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UStaticMeshComponent* CuboMesh;
	// Posición editable en el editor


};
