// Copyright Jeff Brown 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/InstancedStaticMeshComponent.h"

#include "Stroke.generated.h"

UCLASS()
class LIGHTPAINTER_API AStroke : public AActor
{
  GENERATED_BODY()

public:
  AStroke();

  void Update(FVector CursorLocation);

private:
  // Methods
  FTransform GetNextSegmentTransform(FVector CurrentLocation) const;

  // Components
  UPROPERTY(VisibleAnywhere)
  USceneComponent *Root;

  UPROPERTY(VisibleAnywhere)
  UInstancedStaticMeshComponent *StrokeMeshes;

  // State
  FVector PreviousCursorLocation;
};
