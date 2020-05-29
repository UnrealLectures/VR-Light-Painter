// Copyright Jeff Brown 2020

#include "VRPawn.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"

#include "Saving/PainterSaveGame.h"
#include "PaintingGameMode.h"

AVRPawn::AVRPawn()
{
  PrimaryActorTick.bCanEverTick = false;

  VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
  SetRootComponent(VRRoot);

  Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  Camera->SetupAttachment(VRRoot);
}

void AVRPawn::BeginPlay()
{
  Super::BeginPlay();

  UPainterSaveGame *Painting = UPainterSaveGame::Create();
  if (Painting && Painting->Save())
  {
    CurrentSlotName = Painting->GetSlotName();
  }

  if (!PaintBrushHandControllerClass)
    return;

  RightPaintBrushHandController = GetWorld()->SpawnActor<AHandControllerBase>(PaintBrushHandControllerClass);
  RightPaintBrushHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
  RightPaintBrushHandController->SetOwner(this);
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Pressed, this, &AVRPawn::RightTriggerPressed);
  PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Released, this, &AVRPawn::RightTriggerReleased);

  PlayerInputComponent->BindAction(TEXT("Save"), IE_Released, this, &AVRPawn::Save);
}

void AVRPawn::RightTriggerPressed()
{
  if (RightPaintBrushHandController)
    RightPaintBrushHandController->TriggerPressed();
}

void AVRPawn::RightTriggerReleased()
{
  if (RightPaintBrushHandController)
    RightPaintBrushHandController->TriggerReleased();
}

void AVRPawn::Save()
{
  auto GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());
  if (!GameMode)
    return;
  GameMode->Save();

  UStereoLayerFunctionLibrary::ShowSplashScreen();
  UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}
