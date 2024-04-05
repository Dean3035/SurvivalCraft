// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInputActorComponent.generated.h"


class AMainCharacter;
class UCharacterMovementComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALCRAFT_API UPlayerInputActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInputActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character", meta=(AllowPrivateAccess = "true"))
	AMainCharacter* MainCharacter;

	//增强输入组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(AllowPrivateAccess = "true"))
	UEnhancedInputComponent* EnhancedInputComponent;

	//输入映射
	//meta=(AllowPrivateAccess = "true"
	//当一个成员被声明为私有（Private）时，它只能在声明它的类内部被访问，而无法在其它类中直接访问。但是，有时候我们希望在外部的特定类中能够访问这个私有成员，这时就可以使用 meta=(AllowPrivateAccess = "true") 标记来允许特定的类访问私有成员。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	//移动Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* MovementAction;

	//添加输入映射
	void AddInputMapping();
	
	//设置输入
	void SetupPlayerInputComponent();

	//移动
	UFUNCTION()
	void Movement(const FInputActionValue& Value);
};
