// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacterAnimInstance.generated.h"

class AMainCharacter;
/**
 * 
 */
UCLASS()
class SURVIVALCRAFT_API UMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY()
	AMainCharacter* MainCharacter;

	//移动速度
	UPROPERTY(BlueprintReadOnly)
	float Speed;
};
