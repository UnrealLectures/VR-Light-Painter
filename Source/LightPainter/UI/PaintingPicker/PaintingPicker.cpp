// Copyright Jeff Brown 2020

#include "PaintingPicker.h"

#include "Kismet/StereoLayerFunctionLibrary.h"
#include "../../Saving/PainterSaveGameIndex.h"
#include "../../Saving/PainterSaveGame.h"
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

  Refresh();
}

void APaintingPicker::Refresh()
{
  RefreshSlots();
  RefreshDots();
}

void APaintingPicker::RefreshSlots()
{
  if (!GetPaintingGrid())
    return;

  GetPaintingGrid()->ClearPaintings();

  int32 StartOffset = CurrentPage * (GetPaintingGrid()->GetNumberOfSlots());
  auto SlotNames = UPainterSaveGameIndex::Load()->GetSlotNames();
  for (int32 i = 0; i < GetPaintingGrid()->GetNumberOfSlots() && StartOffset + i < SlotNames.Num(); ++i)
  {
    GetPaintingGrid()->AddPainting(i, SlotNames[StartOffset + i]);
  }
}

void APaintingPicker::RefreshDots()
{
  if (!GetPaintingGrid())
    return;

  GetPaintingGrid()->ClearPaginationDots();

  for (int32 i = 0; i < GetNumberOfPages(); i++)
  {
    GetPaintingGrid()->AddPaginationDot(CurrentPage == i);
  }
}

int32 APaintingPicker::GetNumberOfPages() const
{
  if (!GetPaintingGrid())
    return -1;
  int32 TotalNumberOfSlots = UPainterSaveGameIndex::Load()->GetSlotNames().Num();
  int32 SlotsPerPage = GetPaintingGrid()->GetNumberOfSlots();
  return FMath::CeilToInt((float)TotalNumberOfSlots / SlotsPerPage);
}

void APaintingPicker::AddPainting()
{
  UPainterSaveGame::Create();
  Refresh();
}

void APaintingPicker::ToggleDeleteMode()
{
  if (!GetPaintingGrid())
    return;
  GetPaintingGrid()->ClearPaintings();
}

void APaintingPicker::UpdateCurrentPage(int32 Offset)
{
  CurrentPage = FMath::Clamp(CurrentPage + Offset, 0, GetNumberOfPages() - 1);

  Refresh();
}