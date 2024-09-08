// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_SIS457GameMode.h"
#include "DonkeyKong_SIS457Character.h"
#include "UObject/ConstructorHelpers.h"
#include "DonkeyKong_SIS457.h"
#include "Obstaculo.h"
#include "Plataforma.h"

class ADonkeyKong_SIS457;

ADonkeyKong_SIS457GameMode::ADonkeyKong_SIS457GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	obstaculo01 = nullptr;
	player01 = nullptr;

	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		player01 = Cast<ADonkeyKong_SIS457>(PlayerPawnBPClass.Class);

	}
}

void ADonkeyKong_SIS457GameMode::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("Actor Spawning"));

	FTransform SpawnLocation;
	/*/SpawnLocation.SetLocation(FVector(1160.0f, -210.0f, 140.0f));
	SpawnLocation.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
	obstaculo01 = GetWorld()->SpawnActor<AObstaculo>(AObstaculo::StaticClass(), SpawnLocation);
	if (player01 != nullptr)
	{
		player01->SetObstaculo(obstaculo01);
	}*/

	FVector posicionInicial = FVector(1160.0f, -1100.0f, 400.f);
	FRotator rotacionInicial = FRotator(0.0f, 0.0f, 10.0f);
	FTransform SpawnLocationCP;
	float anchoComponentePlataforma = 600.0f;
	float incrementoAltoComponentePlataforma = -105.0f;
	float incrementoAltoEntrePisos = 800.0f;
	float incrementoInicioPiso = 100.0f;

	for (int npp = 0; npp < 5; npp++) {
		rotacionInicial.Roll = rotacionInicial.Roll * -1;
		incrementoInicioPiso = incrementoInicioPiso * -1;
		incrementoAltoComponentePlataforma = incrementoAltoComponentePlataforma * -1;
		SpawnLocationCP.SetRotation(FQuat(rotacionInicial));

		SpawnLocationCP.SetRotation(FQuat(rotacionInicial));
		for (int ncp = 0; ncp < 5; ncp++) {
			SpawnLocationCP.SetLocation(FVector(posicionInicial.X, posicionInicial.Y + anchoComponentePlataforma * ncp, posicionInicial.Z));
			Plataforma.Add(GetWorld()->SpawnActor<APlataforma>(APlataforma::StaticClass(), SpawnLocationCP));
			if(ncp < 4){
				posicionInicial.Z = posicionInicial.Z + incrementoAltoComponentePlataforma;
			}
		}
		posicionInicial.Z = posicionInicial.Z + incrementoAltoEntrePisos;
		posicionInicial.Y = posicionInicial.Y + incrementoInicioPiso;
	}

	// ********** Generación de la primera columna **********
	FTransform SpawnLocationColumna1;
	FVector posicionColumna1 = FVector(1210.0f, 1800.0f, 910.0f); // Posición de la primera columna
	FRotator rotacionColumna1 = FRotator(0.0f, 0.0f, 90.0f); // Rotación de 90 grados en el eje Y

	SpawnLocationColumna1.SetLocation(posicionColumna1);
	SpawnLocationColumna1.SetRotation(FQuat(rotacionColumna1));

	// Escala personalizada para la primera columna
	FVector escalaColumna1 = FVector(0.5f, 25.5f, 3.0f); // Alargada en el eje Z (altura)
	SpawnLocationColumna1.SetScale3D(escalaColumna1);

	// Spawnea la primera plataforma como columna
	APlataforma* columnaPlataforma1 = GetWorld()->SpawnActor<APlataforma>(APlataforma::StaticClass(), SpawnLocationColumna1);
	Plataforma.Add(columnaPlataforma1);

	// ********** Generación de la segunda columna **********
	FTransform SpawnLocationColumna2;
	FVector posicionColumna2 = FVector(1210.0f, -1730.0f, 910.0f); // Posición diferente para la segunda columna
	FRotator rotacionColumna2 = FRotator(0.0f, 0.0f, 90.0f); // Mantiene la rotación de 90 grados en el eje Y

	SpawnLocationColumna2.SetLocation(posicionColumna2);
	SpawnLocationColumna2.SetRotation(FQuat(rotacionColumna2));

	// Escala personalizada para la segunda columna (puedes cambiarla si lo deseas)
	FVector escalaColumna2 = FVector(0.5f, 25.5f, 3.0f); // Diferente escala (más baja que la primera)
	SpawnLocationColumna2.SetScale3D(escalaColumna2);

	// Spawnea la segunda plataforma como columna
	APlataforma* columnaPlataforma2 = GetWorld()->SpawnActor<APlataforma>(APlataforma::StaticClass(), SpawnLocationColumna2);
	Plataforma.Add(columnaPlataforma2);

	// ********** Fin de la generación de columnas **********
}
