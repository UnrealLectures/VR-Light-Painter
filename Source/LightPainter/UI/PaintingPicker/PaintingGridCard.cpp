// Copyright Jeff Brown 2020

#include "PaintingGridCard.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"

void UPaintingGridCard::SetPaintingName(FString NewPaintingName)
{
  PaintingName = NewPaintingName;
  SlotName->SetText(FText::FromString(PaintingName));

  Button->OnClicked.AddDynamic(this, &UPaintingGridCard::ButtonClicked);
}

void UPaintingGridCard::ButtonClicked()
{
  UStereoLayerFunctionLibrary::ShowSplashScreen();
  // TODO: Factor out magic string
  UGameplayStatics::OpenLevel(GetWorld(), TEXT("Canvas"), true, "SlotName=" + PaintingName);
};