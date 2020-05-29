// Copyright Jeff Brown 2020

#include "PaintingGrid.h"

#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"

void UPaintingGrid::AddPainting(int32 index, FString PaintingName)
{
  if (!PaintingGrid)
    return;

  UPaintingGridCard *NewWidget = CreateWidget<UPaintingGridCard>(GetWorld(), GridCardClass);

  if (!NewWidget)
    return;

  NewWidget->SetPaintingName(PaintingName);

  USizeBox *CardContainer = Cast<USizeBox>(PaintingGrid->GetChildAt(index));
  if (!CardContainer)
    return;
  CardContainer->AddChild(NewWidget);
}

void UPaintingGrid::AddPaginationDot(bool Active)
{
  if (!PaginationDots)
    return;

  auto Dot = CreateWidget<UPaginationDot>(GetWorld(), PaginationDotsClass);
  if (!Dot)
    return;

  Dot->SetActive(Active);
  UHorizontalBoxSlot *DotSlot = PaginationDots->AddChildToHorizontalBox(Dot);
  DotSlot->SetPadding(FMargin(PaginationDotPadding));
}

void UPaintingGrid::ClearPaintings()
{
  for (int32 i = 0; i < PaintingGrid->GetChildrenCount(); i++)
  {
    USizeBox *CardContainer = Cast<USizeBox>(PaintingGrid->GetChildAt(i));
    if (!CardContainer)
      continue;

    CardContainer->ClearChildren();
  }
}

void UPaintingGrid::ClearPaginationDots()
{
  if (!PaginationDots)
    return;

  PaginationDots->ClearChildren();
}

int32 UPaintingGrid::GetNumberOfSlots() const
{
  return PaintingGrid->GetChildrenCount();
}