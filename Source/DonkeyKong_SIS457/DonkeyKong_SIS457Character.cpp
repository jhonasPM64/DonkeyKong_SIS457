// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_SIS457Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Obstaculo.h"
#include "DonkeyKong_SIS457GameMode.h"
#include "DonkeyKong_SIS457.h"

ADonkeyKong_SIS457Character::ADonkeyKong_SIS457Character()
{

	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 1500.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)zz
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADonkeyKong_SIS457Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADonkeyKong_SIS457Character::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADonkeyKong_SIS457Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADonkeyKong_SIS457Character::TouchStopped);
}

void ADonkeyKong_SIS457Character::Parar()
{
	detener = !detener;
	AObstaculo01->setDetener(detener);
}

void ADonkeyKong_SIS457Character::BeginPlay()
{
	Super::BeginPlay();

	// Establecer la nueva ubicación del personaje al inicio del juego
	FVector NuevaUbicacion(1200.0f, 300.0f, 2500.0f); // Cambia estos valores a la ubicación deseada
	CambiarUbicacion(NuevaUbicacion);

	ADonkeyKong_SIS457* GameMode = Cast<ADonkeyKong_SIS457>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		AObstaculo01 = GameMode->GetObstaculo();
	}
}

void ADonkeyKong_SIS457Character::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
}

void ADonkeyKong_SIS457Character::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ADonkeyKong_SIS457Character::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ADonkeyKong_SIS457Character::CambiarUbicacion(FVector NuevaUbicacion)
{
	SetActorLocation(NuevaUbicacion);
}