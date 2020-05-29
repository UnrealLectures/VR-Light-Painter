// Copyright Jeff Brown 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/UniformGridPanel.h"
#include "Components/HorizontalBox.h"

#include "PaintingGridCard.h"
#include "PaginationDot.h"

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
  void AddPaginationDot(bool Active);

  void ClearPaintings();
  void ClearPaginationDots();

  int32 GetNumberOfSlots() const;

protected:
  UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
  UUniformGridPanel *PaintingGrid;

  UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
  UHorizontalBox *PaginationDots;

private:
  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<UPaintingGridCard> GridCardClass;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<UPaginationDot> PaginationDotsClass;

  UPROPERTY(EditDefaultsOnly)
  float PaginationDotPadding = 8.f;
};
