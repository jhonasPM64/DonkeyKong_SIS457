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

	// Nueva variable para almacenar la posición de generación
	FVector SpawnLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* CuboMesh;

	//Para que dispare a la derecha
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MovementSpeed;

	uint32 bCanFire : 1;

	void FireShot();

	FTimerHandle TimerHandle_ShotTimerExpired;
	void ShotTimer();

	// Contador de proyectiles disparados
	int32 ProjectileCount;

	// Mximo de proyectiles permitidos
	int32 MaxProjectiles;
};
