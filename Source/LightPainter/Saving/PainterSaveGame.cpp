// Copyright Jeff Brown 2020

#include "PainterSaveGame.h"

#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Misc/Guid.h"
#include "PainterSaveGameIndex.h"

#include "../Stroke.h"

UPainterSaveGame *UPainterSaveGame::Create()
{
  UPainterSaveGame *NewSaveGame = Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));

  NewSaveGame->SlotName = FGuid::NewGuid().ToString();

  if (!NewSaveGame->Save())
    return nullptr;

  UPainterSaveGameIndex *Index = UPainterSaveGameIndex::Load();
  Index->AddSaveGame(NewSaveGame);
  Index->Save();

  return NewSaveGame;
}

bool UPainterSaveGame::Save()
{
  UE_LOG(LogTemp, Warning, TEXT("Painting Index:"));
  for (FString CurrentSlotName : UPainterSaveGameIndex::Load()->GetSlotNames())
  {
    UE_LOG(LogTemp, Warning, TEXT("Painting name: %s"), *CurrentSlotName);
  }
  return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

UPainterSaveGame *UPainterSaveGame::Load(FString SlotName)
{
  return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
}

void UPainterSaveGame::SerializeFromWorld(UWorld *World)
{
  Strokes.Empty();
  for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
  {
    Strokes.Add(StrokeItr->SerializeToStruct());
  }
}

void UPainterSaveGame::DeserializeToWorld(UWorld *World)
{
  ClearWorld(World);
  for (FStrokeState StrokeState : Strokes)
  {
    AStroke::SpawnAndDeserializeFromStruct(World, StrokeState);
  }
}

void UPainterSaveGame::ClearWorld(UWorld *World)
{
  for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
  {
    StrokeItr->Destroy();
  }
}