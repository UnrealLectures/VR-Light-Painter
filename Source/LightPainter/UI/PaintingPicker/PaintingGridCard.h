// Copyright Jeff Brown 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "PaintingGridCard.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingGridCard : public UUserWidget
{
  GENERATED_BODY()

public:
  void SetPaintingName(FString NewPaintingName);

protected:
  UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
  UTextBlock *SlotName;

  UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
  UButton *Button;

private:
  UFUNCTION()
  void ButtonClicked();

  // State
  FString PaintingName;
};
