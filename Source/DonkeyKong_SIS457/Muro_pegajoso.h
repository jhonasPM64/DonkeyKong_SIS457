#pragma once

#include "CoreMinimal.h"
#include "Muro.h"
#include "Muro_pegajoso.generated.h"

UCLASS()
class DONKEYKONG_SIS457_API AMuro_pegajoso : public AMuro
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMuro_pegajoso();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	void LiberarPersonaje();

	ACharacter* PegadoPersonaje;

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, Category = "Muro_pegajoso")
	float TiempoPegado;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Muro_pegajoso")
	UTexture2D* Texturepegajoso;
};
