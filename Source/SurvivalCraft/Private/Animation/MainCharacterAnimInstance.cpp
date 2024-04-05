// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/MainCharacterAnimInstance.h"

#include "Character/MainCharacter.h"

void UMainCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
}

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MainCharacter == nullptr)
	{
		MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	}

	if (MainCharacter)
	{
		//设置速度
		Speed = MainCharacter->GetVelocity().Size();
		// UE_LOG(LogTemp, Warning, TEXT("Speed=%f"), Speed);
	}
}
