// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Muro_Ladrillo.generated.h"

UCLASS()
class DONKEYKONG_SIS457_API AMuro_Ladrillo : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMuro_Ladrillo();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* MuroMesh;
};
