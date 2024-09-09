#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barril.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class DONKEYKONG_SIS457_API ABarril : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABarril();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called when an overlap begins
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
    // Malla del barril
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Configuración")
    UStaticMeshComponent* BarrilMesh;  // <--- Aquí verifica que no esté duplicada

    // Componente de colisión
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    USphereComponent* BarrilColision;

    // Componente de movimiento
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UProjectileMovementComponent* BarrilMovement;

    // Velocidad de rotación
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float RotationSpeed;

    // Aumenta la velocidad al colisionar
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float SpeedIncrease;

    // Escala del barril
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuración")
    FVector BarrilScale;
};
