// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UPlayerInputActorComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SURVIVALCRAFT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//摇臂组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	//摄像机组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(AllowPrivateAccess = "true"))
	UPlayerInputActorComponent* PlayerInputActorComponent;

private:

	//检查AnimInstanceClass
	void CheckAnimInstanceClass();

	//加载摄像机和摇臂组件
	void AddSpringCameraComp();
};
