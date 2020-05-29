// Copyright Jeff Brown 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/WidgetComponent.h"

#include "PaintingPicker.generated.h"

UCLASS()
class LIGHTPAINTER_API APaintingPicker : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  APaintingPicker();

  void AddPainting();
  void ToggleDeleteMode();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:
  void RefreshSlots();

  UPROPERTY(VisibleAnywhere)
  USceneComponent *Root;

  UPROPERTY(VisibleAnywhere)
  UWidgetComponent *PaintingGridComponent;

  UPROPERTY(VisibleAnywhere)
  UWidgetComponent *ActionBarComponent;
};
