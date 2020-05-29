// Copyright Jeff Brown 2020

#include "HandControllerBase.h"

// Sets default values
AHandControllerBase::AHandControllerBase()
{
  PrimaryActorTick.bCanEverTick = false;

  MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
  SetRootComponent(MotionController);
  MotionController->SetShowDeviceModel(true);
}

void AHandControllerBase::SetHand(EControllerHand Hand)
{
  MotionController->SetTrackingSource(Hand);
}