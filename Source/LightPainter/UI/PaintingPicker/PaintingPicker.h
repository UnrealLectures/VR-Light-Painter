// Copyright Jeff Brown 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/WidgetComponent.h"

#include "PaintingGrid.h"

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

  void UpdateCurrentPage(int32 Offset);

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

private:
  // Methods
  void Refresh();
  void RefreshSlots();
  void RefreshDots();

  int32 GetNumberOfPages() const;
  UPaintingGrid *GetPaintingGrid() const { return Cast<UPaintingGrid>(PaintingGridComponent->GetUserWidgetObject()); }

  // Components
  UPROPERTY(VisibleAnywhere)
  USceneComponent *Root;

  UPROPERTY(VisibleAnywhere)
  UWidgetComponent *PaintingGridComponent;

  UPROPERTY(VisibleAnywhere)
  UWidgetComponent *ActionBarComponent;

  // State
  int32 CurrentPage = 0;
};
