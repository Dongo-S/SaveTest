// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveObjectComponent.h"
#include "SaveSubsystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USaveObjectComponent::USaveObjectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void USaveObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (autoInit)
	{

		UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		USaveSubsystem* saveSystem = GameInstance->GetSubsystem<USaveSubsystem>();

		//if (index < 0)
		//{
		//	index = saveSystem->GetIndex();
		//}

		UE_LOG(LogTemp, Warning, TEXT(" After Current Index of %s Savesystem %i"), *GetOwner()->GetName(), index);
		FVectorRotatorPair vectorRotator = saveSystem->GetBox(index);

		if (vectorRotator.location != FVector::ZeroVector)
			GetOwner()->SetActorLocation(vectorRotator.location);
		if (vectorRotator.rotation != FRotator::ZeroRotator)
			GetOwner()->SetActorRotation(vectorRotator.rotation);

	}
}



void USaveObjectComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	USaveSubsystem* saveSystem = GameInstance->GetSubsystem<USaveSubsystem>();
	FVectorRotatorPair vectorRotator = saveSystem->GetCharacter();

	if (saveSystem != nullptr)
		saveSystem->SetBox(index, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), type);
}


// Called every frame
void USaveObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

