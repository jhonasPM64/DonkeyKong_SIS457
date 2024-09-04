#include "Enemigo.h"

// Sets default values
AEnemigo::AEnemigo()
{
    // Set this actor to call Tick() every frame.  
    PrimaryActorTick.bCanEverTick = true;

    // Inicializaci�n de valores por defecto
    Nombre = "Enemigo Desconocido";
    Vida = 100;
    Ataque = 10;
    Defensa = 5;
    Velocidad = 600.f;
}

// Called when the game starts or when spawned
void AEnemigo::BeginPlay()
{
    Super::BeginPlay();

    // L�gica de inicio del enemigo
}

// Called every frame
void AEnemigo::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // L�gica a ejecutar cada frame
}

void AEnemigo::atacar()
{
}

void AEnemigo::AtaqueMagia()
{
}

void AEnemigo::RecibidoDano()
{
}

void AEnemigo::RecibirVida()
{
}
