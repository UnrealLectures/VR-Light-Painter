// Copyright Jeff Brown 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/UniformGridPanel.h"
#include "PaintingGridCard.h"

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
  void AddPainting(int32 index, FString PaintingName);

  void ClearPaintings();

protected:
  UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
  UUniformGridPanel *PaintingGrid;

private:
  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<UPaintingGridCard> GridCardClass;
};
