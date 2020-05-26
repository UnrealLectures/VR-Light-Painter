// Copyright Jeff Brown 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MotionControllerComponent.h"
#include "Stroke.h"

#include "HandController.generated.h"

UCLASS()
class LIGHTPAINTER_API AHandController : public AActor
{
  GENERATED_BODY()

public:
  AHandController();
  virtual void Tick(float DeltaTime) override;

  void TriggerPressed();
  void TriggerReleased();

protected:
  virtual void BeginPlay() override;

private:
  // Config
  UPROPERTY(EditAnywhere)
  TSubclassOf<AStroke> StrokeClass;

  // Components
  UPROPERTY(VisibleAnywhere)
  UMotionControllerComponent *MotionController;

  // References
  UPROPERTY()
  AStroke *CurrentStroke;
};
