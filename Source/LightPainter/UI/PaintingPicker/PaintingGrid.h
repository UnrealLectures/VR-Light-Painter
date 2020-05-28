// Copyright Jeff Brown 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/UniformGridPanel.h"

#include "PaintingGrid.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingGrid : public UUserWidget
{
  GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable)
  void AddPainting();

protected:
  UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
  UUniformGridPanel *PaintingGrid;

private:
  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<UUserWidget> GridCardClass;
};
