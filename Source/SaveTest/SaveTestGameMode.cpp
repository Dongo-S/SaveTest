// Copyright Epic Games, Inc. All Rights Reserved.

#include "SaveTestGameMode.h"
#include "SaveTestCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MyHUD.h"

ASaveTestGameMode::ASaveTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<AMyHUD> HUDClasse(TEXT("/Game/Blueprints/BP_HUD_Base"));
	if (HUDClasse.Class != NULL)
	{
		HUDClass = HUDClasse.Class;
	}

}
