// Copyright Jeff Brown 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Camera/CameraComponent.h"
#include "HandController.h"

#include "VRPawn.generated.h"

UCLASS()
class LIGHTPAINTER_API AVRPawn : public APawn
{
  GENERATED_BODY()

public:
  AVRPawn();

protected:
  virtual void BeginPlay() override;
  virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

private:
  // Methods
  void RightTriggerPressed();
  void RightTriggerReleased();

  // Config
  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<AHandController> HandControllerClass;

  // Components
  UPROPERTY(VisibleAnywhere)
  USceneComponent *VRRoot;

  UPROPERTY(VisibleAnywhere)
  UCameraComponent *Camera;

  // Reference
  UPROPERTY()
  AHandController *RightHandController;
};
