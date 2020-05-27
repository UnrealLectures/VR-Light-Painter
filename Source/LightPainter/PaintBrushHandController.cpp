// Copyright Jeff Brown 2020

#include "PaintBrushHandController.h"

#include "Engine/World.h"

APaintBrushHandController::APaintBrushHandController()
{
  PrimaryActorTick.bCanEverTick = true;
}

void APaintBrushHandController::BeginPlay()
{
  Super::BeginPlay();
}

void APaintBrushHandController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (CurrentStroke)
  {
    CurrentStroke->Update(GetActorLocation());
  }
}

void APaintBrushHandController::TriggerPressed()
{
  if (!StrokeClass)
    return;

  CurrentStroke = GetWorld()->SpawnActor<AStroke>(StrokeClass);
  CurrentStroke->SetActorLocation(GetActorLocation());
}

void APaintBrushHandController::TriggerReleased()
{
  CurrentStroke = nullptr;
}
