// Copyright Jeff Brown 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Stroke.h"
#include "HandControllerBase.h"

#include "PaintBrushHandController.generated.h"

UCLASS()
class LIGHTPAINTER_API APaintBrushHandController : public AHandControllerBase
{
  GENERATED_BODY()

public:
  APaintBrushHandController();
  virtual void Tick(float DeltaTime) override;

  void TriggerPressed() override;
  void TriggerReleased() override;

protected:
  virtual void BeginPlay() override;

private:
  // Config
  UPROPERTY(EditAnywhere)
  TSubclassOf<AStroke> StrokeClass;

  // References
  UPROPERTY()
  AStroke *CurrentStroke;
};
