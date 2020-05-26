// Copyright Jeff Brown 2020

#include "VRPawn.h"

#include "Engine/World.h"

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

  if (!HandControllerClass)
    return;

  RightHandController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
  RightHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
  RightHandController->SetOwner(this);
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Pressed, this, &AVRPawn::RightTriggerPressed);
  PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Released, this, &AVRPawn::RightTriggerReleased);
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
