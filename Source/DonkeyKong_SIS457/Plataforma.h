// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plataforma.generated.h"

class UStaticMeshComponent;

UCLASS()
class DONKEYKONG_SIS457_API APlataforma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlataforma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UStaticMeshComponent* meshPlataforma;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UInputComponent* InputComponent;
	void SetupInputBindings();
	void CustomAction();
};
