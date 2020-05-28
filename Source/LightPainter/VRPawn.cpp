// Copyright Jeff Brown 2020

#include "VRPawn.h"

#include "Engine/World.h"

#include "Saving/PainterSaveGame.h"

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
  PlayerInputComponent->BindAction(TEXT("Load"), IE_Released, this, &AVRPawn::Load);
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
  UPainterSaveGame *Painting = UPainterSaveGame::Load(CurrentSlotName);
  if (Painting)
  {
    Painting->SetState("Hello World");
    Painting->SerializeFromWorld(GetWorld());
    Painting->Save();
  }
}

void AVRPawn::Load()
{
  UPainterSaveGame *Painting = UPainterSaveGame::Load(CurrentSlotName);
  if (Painting)
  {
    Painting->DeserializeToWorld(GetWorld());
    UE_LOG(LogTemp, Warning, TEXT("Painting State %s"), *Painting->GetState());
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Not found"));
  }
}