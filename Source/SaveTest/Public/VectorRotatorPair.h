// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "VectorRotatorPair.generated.h"

USTRUCT(BlueprintType)
struct SAVETEST_API FVectorRotatorPair
{
    GENERATED_BODY()

public:
    UPROPERTY()
        FVector location;

    UPROPERTY()
        FRotator rotation;

    UPROPERTY()
        int type;

    UPROPERTY()
        bool isEmpty = true;
};
