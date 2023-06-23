// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SaveObjectComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SAVETEST_API USaveObjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Object")
		int index = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Object")
		int type = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Object")
		bool autoInit = false;

	// Sets default values for this component's properties
	USaveObjectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
