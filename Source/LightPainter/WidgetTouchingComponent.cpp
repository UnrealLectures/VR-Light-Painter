// Copyright Jeff Brown 2020

#include "WidgetTouchingComponent.h"

void UWidgetTouchingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  if (IsOverInteractableWidget() && !bIsClicked)
  {
    PressPointerKey(EKeys::LeftMouseButton);
    bIsClicked = true;
  }

  if (!IsOverInteractableWidget() && bIsClicked)
  {
    ReleasePointerKey(EKeys::LeftMouseButton);
    bIsClicked = false;
  }
}
