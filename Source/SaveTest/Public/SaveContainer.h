// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VectorRotatorPair.h"
#include "SaveContainer.generated.h"

/**
 * 
 */
USTRUCT()
struct SAVETEST_API FSaveContainer
{
    GENERATED_BODY()

public:

    UPROPERTY()
        TArray<FVectorRotatorPair> locationRotationPairs;
};
