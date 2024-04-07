// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
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

	//=============================关于增强输入的==========================

	//默认的上下文映射
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	//增强输入组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(AllowPrivateAccess = "true"))
	UEnhancedInputComponent* EnhancedInputComponent;

	//移动动作
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* MovementAction;

	//Yaw和Pitch动作
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* YawPitchAction;

	//跑步
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* RunAction;

	//移动动作
	UFUNCTION()
	void Movement(const FInputActionValue& Value);

	//Yaw和Pitch动作
	UFUNCTION()
	void YawPitch(const FInputActionValue& Value);

	//Run动作 跑步
	UFUNCTION()
	void SwitchWalk(const FInputActionValue& Value);
	
	//Run动作 跑步
	UFUNCTION()
	void SwitchRun(const FInputActionValue& Value);

private:

	//=======================一些前置设置和检查===================================
	
	//加载摄像机和摇臂组件
	void SetSpringCameraComp();

	//设置骨骼网格体和动画实例
	void SetSkeletalMeshAnimInstanceClass();

	//检查AnimInstanceClass
	void CheckAnimInstanceClass();

	//设置增强输入相关
	void SetEnhancedInput();

	//===========================================================================
};
