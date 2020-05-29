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

  PlayerInputComponent->BindAction(TEXT("Save"), IE_Released, this, &AVRPawn::Save);
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

void AVRPawn::Save()
{
  auto GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());
  if (!GameMode)
    return;
  GameMode->Save();

  UStereoLayerFunctionLibrary::ShowSplashScreen();
  UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}
