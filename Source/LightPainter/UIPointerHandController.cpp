// Copyright Jeff Brown 2020

#include "UIPointerHandController.h"
#include "InputCoreTypes.h"

AUIPointerHandController::AUIPointerHandController()
{
  Pointer = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("Pointer"));
  Pointer->SetupAttachment(GetRootComponent());
}

void AUIPointerHandController::TriggerPressed()
{
  Pointer->PressPointerKey(EKeys::LeftMouseButton);
}

void AUIPointerHandController::TriggerReleased()
{
  Pointer->ReleasePointerKey(EKeys::LeftMouseButton);
}