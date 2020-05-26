// Copyright Jeff Brown 2020

#include "HandController.h"

#include "Engine/World.h"

AHandController::AHandController()
{
  PrimaryActorTick.bCanEverTick = true;

  MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
  SetRootComponent(MotionController);
  MotionController->SetTrackingSource(EControllerHand::Right);
  MotionController->SetShowDeviceModel(true);
}

void AHandController::BeginPlay()
{
  Super::BeginPlay();
}

void AHandController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (CurrentStroke)
  {
    CurrentStroke->Update(GetActorLocation());
  }
}

void AHandController::TriggerPressed()
{
  if (!StrokeClass)
    return;

  CurrentStroke = GetWorld()->SpawnActor<AStroke>(StrokeClass);
  CurrentStroke->SetActorLocation(GetActorLocation());
}

void AHandController::TriggerReleased()
{
  CurrentStroke = nullptr;
}
