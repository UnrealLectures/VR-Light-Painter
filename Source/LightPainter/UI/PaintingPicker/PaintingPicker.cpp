// Copyright Jeff Brown 2020

#include "PaintingPicker.h"

#include "Kismet/StereoLayerFunctionLibrary.h"
#include "../../Saving/PainterSaveGameIndex.h"
#include "../../Saving/PainterSaveGame.h"
#include "PaintingGrid.h"
#include "ActionBar.h"

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

  UActionBar *ActionBarWidget = Cast<UActionBar>(ActionBarComponent->GetUserWidgetObject());
  if (ActionBarWidget)
  {
    ActionBarWidget->SetParentPicker(this);
  }

  RefreshSlots();
}

void APaintingPicker::RefreshSlots()
{
  UPaintingGrid *PaintingGridWidget = Cast<UPaintingGrid>(PaintingGridComponent->GetUserWidgetObject());
  if (!PaintingGridWidget)
    return;

  PaintingGridWidget->ClearPaintings();

  int32 Index = 0;
  for (FString CurrentSlotName : UPainterSaveGameIndex::Load()->GetSlotNames())
  {
    PaintingGridWidget->AddPainting(Index, CurrentSlotName);
    ++Index;
  }
}

void APaintingPicker::AddPainting()
{
  UPainterSaveGame::Create();
  RefreshSlots();
}

void APaintingPicker::ToggleDeleteMode()
{
  UPaintingGrid *PaintingGridWidget = Cast<UPaintingGrid>(PaintingGridComponent->GetUserWidgetObject());
  if (!PaintingGridWidget)
    return;
  PaintingGridWidget->ClearPaintings();
}
