// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSubsystem.h"
#include "PathUtils.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Serialization/ArchiveSaveCompressedProxy.h"
#include "Serialization/ArchiveLoadCompressedProxy.h"
#include "SaveObjectComponent.h"


USaveSubsystem::USaveSubsystem()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<AStaticMeshActor> WhiteBox(TEXT("/Game/Blueprints/Boxes/BP_WhiteBox"));
	if (WhiteBox.Class != NULL)
	{
		whiteBoxBP = WhiteBox.Class;
	}

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<AStaticMeshActor> Bluebox(TEXT("/Game/Blueprints/Boxes/BP_BlueBox"));
	if (Bluebox.Class != NULL)
	{
		blueBoxBP = Bluebox.Class;
	}
}

void USaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
#if platform_1
	savePath = PathUtils::UserRoamingDir();
#elif platform_2
	savePath = FPlatformProcess::UserSettingsDir();
#else
	savePath = FPlatformProcess::UserSettingsDir();
#endif

	savePath = FPaths::Combine(savePath, "GCTest");
	filename = FPaths::Combine(savePath, "saveFile.json");
	currentSave = FSaveContainer();
	currentSave.locationRotationPairs.Init(FVectorRotatorPair(), 8);
	internalIndex = 7;


	Load();
}


void USaveSubsystem::Deinitialize()
{
	Save();
}

void USaveSubsystem::Save()
{
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	if (!FileManager.DirectoryExists(*savePath))
		FileManager.CreateDirectory(*savePath);


	for (int32 i = currentSave.locationRotationPairs.Num() - 1; i >= 0; --i)
	{
		if ((currentSave.locationRotationPairs[i].location == FVector::ZeroVector &&
			currentSave.locationRotationPairs[i].rotation == FRotator::ZeroRotator))
		{
			currentSave.locationRotationPairs.RemoveAt(i);
		}
	}

	FString results;
	FJsonObjectConverter::UStructToJsonObjectString(currentSave, results, 0, 0);

	//UZipPlatformFileBlueprintFunctionLibrary::save(filename, *results);
	FFileHelper::SaveStringToFile(results, *filename);

}

void USaveSubsystem::Load()
{
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

	if (!FileManager.DirectoryExists(*savePath))
	{
		FileManager.CreateDirectory(*savePath);
	}


	if (!FileManager.FileExists(*filename))
	{
		return; // No file found, first time or file deleted
	}

	FString jsonString;

	if (FFileHelper::LoadFileToString(jsonString, *filename))
	{
		if (!FJsonObjectConverter::JsonObjectStringToUStruct(jsonString, &currentSave, 0, 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("File Load Error SaveSystem"));
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Files Load SaveSystem %i"), currentSave.locationRotationPairs.Num());
}

void USaveSubsystem::SetCharacter(FVector location, FRotator rotation)
{
	currentSave.locationRotationPairs[0].location = location;
	currentSave.locationRotationPairs[0].rotation = rotation;
}

FVectorRotatorPair USaveSubsystem::GetCharacter()
{

	if (!firstBoxGet)
		SpawnExtraBoxes();

	return currentSave.locationRotationPairs[0];
}

void USaveSubsystem::SetBox(int index, FVector location, FRotator rotation, int type)
{
	if (index < 0 || index >7)
	{
		internalIndex++;
		index = internalIndex;
		currentSave.locationRotationPairs.Add(FVectorRotatorPair());

		UE_LOG(LogTemp, Warning, TEXT("Current Index of Savesystem %i"), index);

	}

	if (index < 0 || index >= currentSave.locationRotationPairs.Num())
		return;

	currentSave.locationRotationPairs[index].location = location;
	currentSave.locationRotationPairs[index].rotation = rotation;
	currentSave.locationRotationPairs[index].type = type;
	currentSave.locationRotationPairs[index].isEmpty = false;
}

FVectorRotatorPair USaveSubsystem::GetBox(int index)
{
	if (index > currentSave.locationRotationPairs.Num() || index < 0)
		return FVectorRotatorPair();

	return currentSave.locationRotationPairs[index];
}

int32 USaveSubsystem::GetIndex()
{
	int count = currentSave.locationRotationPairs.Num();
	int emptyIndex = count - 1;
	bool somewhereEmpty = false;

	for (int32 i = 8; i < count; ++i)
	{
		if (currentSave.locationRotationPairs[i].isEmpty)
		{
			somewhereEmpty = true;
			emptyIndex = i;
			break;
		}
	}

	if (!somewhereEmpty)
	{
		currentSave.locationRotationPairs.Add(FVectorRotatorPair());
		count = currentSave.locationRotationPairs.Num() - 1;
	}
	else
	{
		count = emptyIndex;
	}

	UE_LOG(LogTemp, Warning, TEXT("Adding box SaveSystem %i"), count);
	currentSave.locationRotationPairs[count].isEmpty = false;
	return count;
}

void USaveSubsystem::SpawnExtraBoxes()
{
	firstBoxGet = true;

	FActorSpawnParameters SpawnParams;
	UE_LOG(LogTemp, Warning, TEXT("Spawning boxes SaveSystem"));

	FTransform newTransform;
	int count = currentSave.locationRotationPairs.Num();
	for (int32 i = 8; i < count; ++i)
	{
		if (currentSave.locationRotationPairs[i].type == -1)
			continue;

		newTransform.SetLocation(currentSave.locationRotationPairs[i].location);
		newTransform.SetRotation(currentSave.locationRotationPairs[i].rotation.Quaternion());

		AStaticMeshActor* newElement;

		if (currentSave.locationRotationPairs[i].type == 1)
		{
			newElement = GetWorld()->SpawnActor<AStaticMeshActor>(whiteBoxBP, newTransform, SpawnParams);
		}
		else //2
		{
			newElement = GetWorld()->SpawnActor<AStaticMeshActor>(blueBoxBP, newTransform, SpawnParams);
		}

		UActorComponent* saveComponent = newElement->GetComponentByClass(USaveObjectComponent::StaticClass());
		if (USaveObjectComponent* component = Cast<USaveObjectComponent>(saveComponent))
		{
			component->type = currentSave.locationRotationPairs[i].type;
			//component->index = i;
		}
		UE_LOG(LogTemp, Warning, TEXT("Instancing box SaveSystem %i"), i);

	}

}

