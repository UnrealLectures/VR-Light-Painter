// Copyright Jeff Brown 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"

#include "PaintingPicker.h"

#include "ActionBar.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UActionBar : public UUserWidget
{
  GENERATED_BODY()

public:
  bool Initialize() override;

  void SetParentPicker(APaintingPicker *NewParentPicker) { ParentPicker = NewParentPicker; }

protected:
  UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
  UButton *DeleteButton;

  UPROPERTY(BlueprintReadonly, VisibleAnywhere, meta = (BindWidget))
  UButton *AddButton;

private:
  UFUNCTION()
  void AddButtonClicked();

  UFUNCTION()
  void DeleteButtonClicked();

  UPROPERTY()
  APaintingPicker *ParentPicker;
};
