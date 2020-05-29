// Copyright Jeff Brown 2020

#include "VRPawn.h"

#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"

#include "UI/PaintingPicker/PaintingPicker.h"
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

  if (RightHandControllerClass)
  {
    RightHandController = GetWorld()->SpawnActor<AHandControllerBase>(RightHandControllerClass);
    RightHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
    RightHandController->SetHand(EControllerHand::Right);
    RightHandController->SetOwner(this);
  }

  if (LeftHandControllerClass)
  {
    LeftHandController = GetWorld()->SpawnActor<AHandControllerBase>(LeftHandControllerClass);
    LeftHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
    LeftHandController->SetHand(EControllerHand::Left);
    LeftHandController->SetOwner(this);
  }
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Pressed, this, &AVRPawn::RightTriggerPressed);
  PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Released, this, &AVRPawn::RightTriggerReleased);

  PlayerInputComponent->BindAxis(TEXT("PaginateRight"), this, &AVRPawn::PaginateRightAxisInput);
}

void AVRPawn::RightTriggerPressed()
{
  if (RightHandController)
    RightHandController->TriggerPressed();
}

void AVRPawn::RightTriggerReleased()
{
  if (RightHandController)
    RightHandController->TriggerReleased();
}

void AVRPawn::PaginateRightAxisInput(float AxisValue)
{
  int32 PaginationOffset = 0;
  PaginationOffset += AxisValue > PaginationThumbstickThreshold ? 1 : 0;
  PaginationOffset += AxisValue < -PaginationThumbstickThreshold ? -1 : 0;
  if (PaginationOffset != LastPaginationOffset && PaginationOffset != 0)
  {
    UpdateCurrentPage(PaginationOffset);
  }

  LastPaginationOffset = PaginationOffset;
}

void AVRPawn::UpdateCurrentPage(int32 Offset)
{
  for (TActorIterator<APaintingPicker> PaintingPickerItr(GetWorld()); PaintingPickerItr; ++PaintingPickerItr)
  {
    PaintingPickerItr->UpdateCurrentPage(Offset);
  }
}
