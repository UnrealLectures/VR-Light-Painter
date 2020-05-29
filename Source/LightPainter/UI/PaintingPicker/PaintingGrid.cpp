// Copyright Jeff Brown 2020

#include "PaintingGrid.h"

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