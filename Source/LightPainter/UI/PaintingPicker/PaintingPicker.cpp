// Copyright Jeff Brown 2020

#include "PaintingPicker.h"

#include "../../Saving/PainterSaveGameIndex.h"
#include "PaintingGrid.h"

// Sets default values
APaintingPicker::APaintingPicker()
{
  PrimaryActorTick.bCanEverTick = false;

  Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
  SetRootComponent(Root);

  PaintingGridComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaintingGridComponent"));
  PaintingGridComponent->SetupAttachment(GetRootComponent());

  ActionBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionBarComponent"));
  ActionBarComponent->SetupAttachment(GetRootComponent());
}

void APaintingPicker::BeginPlay()
{
  Super::BeginPlay();

  UPaintingGrid *PaintingGridWidget = Cast<UPaintingGrid>(PaintingGridComponent->GetUserWidgetObject());
  if (!PaintingGridWidget)
    return;

  int32 Index = 0;
  for (FString CurrentSlotName : UPainterSaveGameIndex::Load()->GetSlotNames())
  {
    PaintingGridWidget->AddPainting(Index, CurrentSlotName);
    ++Index;
  }
}
