// Copyright Jeff Brown 2020

#include "PaintingGrid.h"

#include "Components/SizeBox.h"

void UPaintingGrid::AddPainting()
{
  if (!PaintingGrid)
    return;

  UUserWidget *NewWidget = CreateWidget<UUserWidget>(GetWorld(), GridCardClass);

  if (!NewWidget)
    return;

  USizeBox *CardContainer = Cast<USizeBox>(PaintingGrid->GetChildAt(0));
  if (!CardContainer)
    return;
  CardContainer->AddChild(NewWidget);
}