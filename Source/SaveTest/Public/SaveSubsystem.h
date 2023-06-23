// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VectorRotatorPair.h"
#include "SaveContainer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/StaticMeshActor.h"
#include "SaveSubsystem.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class SAVETEST_API USaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	USaveSubsystem();

	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// End USubsystem
	UFUNCTION(BlueprintCallable, Category = "Save Subsysmte")
		void Save();

	UFUNCTION(BlueprintCallable, Category = "Save Subsysmte")
		void Load();

	UFUNCTION(BlueprintCallable, Category = "Save Subsysmte")
		void SetCharacter(FVector location, FRotator rotation);

	UFUNCTION(BlueprintCallable, Category = "Save Subsysmte")
		FVectorRotatorPair GetCharacter();

	UFUNCTION(BlueprintCallable, Category = "Save Subsysmte")
		void SetBox(int index, FVector location, FRotator rotation, int type);

	UFUNCTION(BlueprintCallable, Category = "Save Subsysmte")
		FVectorRotatorPair GetBox(int index);

	UFUNCTION(BlueprintCallable, Category = "Save Subsysmte")
		int32 GetIndex();

protected:
	FString savePath;
	FString filename;
	bool firstBoxGet = false;
	int internalIndex;

	TSubclassOf<AStaticMeshActor> whiteBoxBP;
	TSubclassOf<AStaticMeshActor> blueBoxBP;

	UPROPERTY()
		FSaveContainer currentSave;

	void SpawnExtraBoxes();
};
