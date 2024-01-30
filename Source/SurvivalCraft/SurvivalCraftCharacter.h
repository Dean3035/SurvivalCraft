// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SurvivalCraftCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ASurvivalCraftCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */    //译文：角色网格体：第一人称视角（手臂;只能自己看到）
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */    //译文：第一人称摄像机
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */    //UE5中引入的新的
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */    //跳跃
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */    //移动
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
public:
	ASurvivalCraftCharacter();

protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */    //看？动作
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */    //译文Bool使AnimBP切换到另一个动画集。 其实就是判断有没有手持步枪
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */    //设置有没有手持步枪
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */    //得到是否手持步枪
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	/** Called for movement input */    //移动对调函数？
	void Move(const FInputActionValue& Value);

	/** Called for looking input */    //look？看？回调函数？
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface    设置玩家的输入组件
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override; 
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/    //内联 返回骨骼网格体模型
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; } 
	/** Returns FirstPersonCameraComponent subobject **/    //内联 返回第一人称摄像机组件
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

