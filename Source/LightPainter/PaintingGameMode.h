// Copyright Jeff Brown 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PaintingGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API APaintingGameMode : public AGameModeBase
{
  GENERATED_BODY()

public:
  void InitGame(const FString &MapName, const FString &Options, FString &ErrorMessage) override;

  void Save();
  void Load();

  UFUNCTION(BlueprintCallable)
  void SaveAndQuit();

protected:
  void BeginPlay() override;

private:
  // State
  FString SlotName;
};
