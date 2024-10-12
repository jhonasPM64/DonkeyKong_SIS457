
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Obstaculo.h"
#include "DonkeyKong_SIS457Character.generated.h"

UCLASS(config = Game)
class ADonkeyKong_SIS457Character : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	void BeginPlay() override;
	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	bool SaltoCargando;
	float TiempoCargado;
	float MaxTiempo;

	void SaltoCargado();
	void Saltolisto();

	virtual void Tick(float DeltaTime) override;

	void Parar();
	bool detener = false;

private:
	TArray<AObstaculo*> Plataformas;
	void CrearPlataforma();
	void EliminarPlataforma();

public:
	ADonkeyKong_SIS457Character();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	AObstaculo* AObstaculo01;

	FORCEINLINE AObstaculo* GetObstaculo() const { return AObstaculo01; }
	FORCEINLINE void SetObstaculo(AObstaculo* _obstaculo) { AObstaculo01 = _obstaculo; }

	// Nueva función para cambiar la ubicación del personaje
	void CambiarUbicacion(FVector NuevaUbicacion);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	float BaseJumpVelocity = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
	float MaxJumpVelocity = 1700.0f;
};
