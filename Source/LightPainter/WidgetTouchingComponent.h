// Copyright Jeff Brown 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetInteractionComponent.h"
#include "WidgetTouchingComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class LIGHTPAINTER_API UWidgetTouchingComponent : public UWidgetInteractionComponent
{
  GENERATED_BODY()

public:
  void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
  // State
  bool bIsClicked = false;
};
