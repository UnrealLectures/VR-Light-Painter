// Copyright Jeff Brown 2020

#include "PaintingGameMode.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"

#include "Saving/PainterSaveGame.h"

void APaintingGameMode::InitGame(const FString &MapName, const FString &Options, FString &ErrorMessage)
{
  Super::InitGame(MapName, Options, ErrorMessage);

  // TODO: Factor out magic string
  SlotName = UGameplayStatics::ParseOption(Options, "SlotName");
  UE_LOG(LogTemp, Warning, TEXT("SlotName: %s"), *SlotName);
}

void APaintingGameMode::Save()
{
  UPainterSaveGame *Painting = UPainterSaveGame::Load(SlotName);
  if (Painting)
  {
    Painting->SerializeFromWorld(GetWorld());
    Painting->Save();
  }
}

void APaintingGameMode::Load()
{
  UPainterSaveGame *Painting = UPainterSaveGame::Load(SlotName);
  if (Painting)
  {
    Painting->DeserializeToWorld(GetWorld());
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Game slot not found: %s"), *SlotName);
  }
}

void APaintingGameMode::SaveAndQuit()
{
  Save();

  UStereoLayerFunctionLibrary::ShowSplashScreen();
  UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}

void APaintingGameMode::BeginPlay()
{
  Super::BeginPlay();

  Load();

  UStereoLayerFunctionLibrary::HideSplashScreen();
}