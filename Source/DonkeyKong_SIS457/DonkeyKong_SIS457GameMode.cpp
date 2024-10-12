// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_SIS457GameMode.h"
#include "DonkeyKong_SIS457Character.h"
#include "UObject/ConstructorHelpers.h"
#include "DonkeyKong_SIS457.h"
#include "Obstaculo.h"
#include "Plataforma.h"
#include "Barril.h"
#include "Cubo_Disparador.h"
#include "Muro_Congelado.h"
#include "Muro_electrico.h"
#include "Muro_Ladrillo.h"
#include "Muro_pegajoso.h"

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
	    // Inicializa el array de clases de obstáculos
	/*Muro.Add(AMuro_Ladrillo::StaticClass());
	Muro.Add(AMuro_Congelado::StaticClass());
	Muro.Add(AMuro_pegajoso::StaticClass());
	Muro.Add(AMuro_electrico::StaticClass());*/

}

void ADonkeyKong_SIS457GameMode::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("Actor Spawning"));

	/*FTransform SpawnLocation;
	SpawnLocation.SetLocation(FVector(1160.0f, -210.0f, 140.0f));
	obstaculo01 = GetWorld()->SpawnActor<AObstaculo>(AObstaculo::StaticClass(), SpawnLocation);
	if (player01 != nullptr)
	{
		player01->SetObstaculo(obstaculo01);
	}//codigo de la pared en movimiento*/
	FVector posicionInicial = FVector(1200.0f, -1300.0f, 400.f);
	FTransform SpawnLocationCP;
	float anchoComponentePlataforma = 300.0f;
	float incrementoAltoComponentePlataforma = 0.0f;
	float incrementoAltoEntrePisos = 500.0f;
	float incrementoInicioPiso = 200.0f;

	for (int npp = 0; npp < 4; npp++) {
		incrementoInicioPiso = incrementoInicioPiso * -1;
		incrementoAltoComponentePlataforma = incrementoAltoComponentePlataforma * -1;

		for (int ncp = 0; ncp < 10; ncp++) {
			// Generar la ubicación de la plataforma
			FVector posicionActual = FVector(posicionInicial.X, posicionInicial.Y + anchoComponentePlataforma * ncp, posicionInicial.Z);

			SpawnLocationCP.SetLocation(posicionActual);

			// Spawnear la plataforma
			APlataforma* NuevaPlataforma = GetWorld()->SpawnActor<APlataforma>(APlataforma::StaticClass(), SpawnLocationCP);

			if (NuevaPlataforma) {
				// Almacenar en el TMap con la posición como clave
				Plataformas.Add(NuevaPlataforma);
			}
			// Modificar la altura si no es la última en la fila
			if (ncp < 4) {
				posicionInicial.Z = posicionInicial.Z + incrementoAltoComponentePlataforma;
			}

		}

		// Cambiar al siguiente piso
		posicionInicial.Z = posicionInicial.Z + incrementoAltoEntrePisos;
		posicionInicial.Y = posicionInicial.Y + incrementoInicioPiso;

		// Iterar sobre el TMap para mostrar los elementos almacenados (aquí es donde añades el código)
		/*for (const TPair<FVector, APlataforma*>& Elem : MapaPlataformas)
		{
			FVector Posicion = Elem.Key; // La clave es la posición FVector
			APlataforma* Plataforma = Elem.Value; // El valor es el puntero a la plataforma

			if (Plataforma)
			{
				//FString Mensaje = FString::Printf(TEXT("Plataforma en Posicion: %s"), *Posicion.ToString());
				//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, Mensaje);
			}
		}*/

		TArray<APlataforma*> PlataformasSeleccionadas;

		for (int32 i = Plataformas.Num() - 1; i > 0; --i)
		{
			int32 j = FMath::RandRange(0, i);
			Plataformas.Swap(i, j);
		}

		for (int32 i = 0; i < FMath::Min(2, Plataformas.Num()); ++i)
		{
			PlataformasSeleccionadas.Add(Plataformas[i]);
		}

		for (APlataforma* Plataforma : Plataformas)
		{
			if (Plataforma)
			{
				Plataforma->bMoviendose = false;
			}
		}

		for (APlataforma* Plataforma : PlataformasSeleccionadas)
		{
			if (Plataforma)
			{
				Plataforma->bMoviendose = true;

				int32 RandomDirection = FMath::RandRange(0, 1); 

				if (RandomDirection == 0)
				{
					Plataforma->DireccionMovimiento = FVector(0.f, 0.f, 1.f); 
				}
				else
				{
					Plataforma->DireccionMovimiento = FVector(0.f, 1.f, 0.f); 
				}
			}
		}

		// Crear plataformas pequeñas
		TArray<FVector> posicionesPequenas = {
			FVector(1200.0f, 1700.0f, 630.0f),
			FVector(1200.0f, -1700.0f, 1170.f),
			FVector(1200.0f, 1700.0f, 1630.f),
			FVector(1200.0f, -1700.0f, 2150.f)
		};

		for (int i = 0; i < posicionesPequenas.Num(); ++i) {
			FTransform SpawnLocationPlataformaPequena;
			SpawnLocationPlataformaPequena.SetLocation(posicionesPequenas[i]);
			FVector escalaPlataformaPequena = FVector(0.5f, 0.5f, 1.3f); // Ajusta según el tamaño deseado
			SpawnLocationPlataformaPequena.SetScale3D(escalaPlataformaPequena);
			// Cambiar el nombre de la variable local a 'PlataformaPequena'
			APlataforma* PlataformaPequena = GetWorld()->SpawnActor<APlataforma>(APlataforma::StaticClass(), SpawnLocationPlataformaPequena);
			// Usar el miembro de clase 'Plataforma' para almacenar las plataformas pequeñas
			PlataformasPequenas.Add(PlataformaPequena);
		}

	}
	GenerarCubosAleatoriamente(1);
//	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ADonkeyKong_SIS457GameMode::GenerarMurosAleatorios, 3.F, true);

}

void ADonkeyKong_SIS457GameMode::GenerarCubosAleatoriamente(int MaxCubos)
{
    int NumCubosGenerados = 0;

    // Recorrer el mapa de plataformas y generar cubos
    for (APlataforma* Plataforma : Plataformas)
    {
        if (NumCubosGenerados >= MaxCubos)
        {
            break; // Detener si ya hemos generado el número máximo de cubos
        }

        if (Plataforma && FMath::RandBool()) // 50% de probabilidad de generar un cubo en esta plataforma
        {
            // Obtener la ubicación de la plataforma
            FVector PlataformaLocation = Plataforma->GetActorLocation();
            FVector PlataformaEscala = Plataforma->GetActorScale3D();
            // Definir el ancho y largo de la plataforma según su escala (eje Y para ancho y Z para altura)
            float AnchoPlataforma = PlataformaEscala.Y * 100.0f;

            // Generar una posición aleatoria en el ancho (eje Y) de la plataforma
            float RangoY = FMath::RandRange(-AnchoPlataforma / 2, AnchoPlataforma / 2);

            // En lugar de usar un rango aleatorio para Z, colocamos el cubo justo encima de la plataforma
            float AlturaSobrePlataforma = PlataformaLocation.Z + (PlataformaEscala.Z * 50.0f) + 50.0f; // Ajuste de altura

            // La posición del cubo será aleatoria en el eje Y, pero la altura Z será fija para estar encima de la plataforma
            FVector PosicionCubo = FVector(PlataformaLocation.X, PlataformaLocation.Y + RangoY, AlturaSobrePlataforma);

            // Generar el cubo
            FTransform SpawnLocationCubo;
            SpawnLocationCubo.SetLocation(PosicionCubo);
            // Spawnear el cubo
            ACubo_Disparador* NuevoCubo = GetWorld()->SpawnActor<ACubo_Disparador>(ACubo_Disparador::StaticClass(), SpawnLocationCubo);
            if (NuevoCubo)
            {
                // Almacenar la posición de generación en el cubo
                NuevoCubo->SpawnLocation = PosicionCubo;

                NumCubosGenerados++;
            }
        }
    }
    // Si no se han generado suficientes cubos, hacer una segunda pasada por plataformas sin cubos
    if (NumCubosGenerados < MaxCubos)
    {
        for (APlataforma* Plataforma : Plataformas)
        {
            if (NumCubosGenerados >= MaxCubos)
            {
                break;
            }

            // Generar cubo en plataformas que no recibieron uno en la primera pasada
			if (Plataforma && !PlataformasConCubos.Contains(Plataforma))
			{
                FVector PlataformaLocation = Plataforma->GetActorLocation();
                FVector PlataformaEscala = Plataforma->GetActorScale3D();

                // Definir el ancho de la plataforma (eje Y)
                float AnchoPlataforma = PlataformaEscala.Y * 100.0f;

                // Generar una posición aleatoria en el ancho de la plataforma
                float RangoY = FMath::RandRange(-AnchoPlataforma / 2, AnchoPlataforma / 2);

                // Colocar el cubo justo encima de la plataforma
                float AlturaSobrePlataforma = PlataformaLocation.Z + (PlataformaEscala.Z * 50.0f) + 50.0f;

                FVector PosicionCubo = FVector(PlataformaLocation.X, PlataformaLocation.Y + RangoY, AlturaSobrePlataforma);

                FTransform SpawnLocationCubo;
                SpawnLocationCubo.SetLocation(PosicionCubo);

                ACubo_Disparador* NuevoCubo = GetWorld()->SpawnActor<ACubo_Disparador>(ACubo_Disparador::StaticClass(), SpawnLocationCubo);
                if (NuevoCubo)
                {
                    // Almacenar la posición de generación en el cubo
                    NuevoCubo->SpawnLocation = PosicionCubo;

                    NumCubosGenerados++;
                    PlataformasConCubos.Add(Plataforma); // Registrar esta plataforma
                }
            }
        }
    }

}

/*void ADonkeyKong_SIS457GameMode::GenerarMurosAleatorios()
{
	FVector UbicacionAleatoria = FVector(FMath::FRandRange(830.f, 1500.f), -680.f, 240.f);
	if (Muro.Num() > 0) {
		IndiceAleatorio = FMath::FRandRange(0, Muro.Num() - 1);
		MurosAleatorios = Muro[IndiceAleatorio];
		if (MurosAleatorios) {
			AMuro* NuevoMuro = GetWorld()->SpawnActor<AMuro>(MurosAleatorios, UbicacionAleatoria, FRotator::ZeroRotator);
			if (NuevoMuro)
			{
				// Configurar un temporizador para destruir el muro después de 3 segundos
				FTimerHandle TempTimer;
				GetWorld()->GetTimerManager().SetTimer(TempTimer, [NuevoMuro]()
					{
						if (NuevoMuro)
						{
							NuevoMuro->Destroy();
						}
					}, 2.0f, false); // 3 segundos y no se repite
			}
		}
	}
}*/
