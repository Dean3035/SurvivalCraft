// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PlayerInputActorComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Character/MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayerInputActorComponent::UPlayerInputActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	MainCharacter =  Cast<AMainCharacter>(GetOwner());
	
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetOwner()->InputComponent);

	DefaultMappingContext = nullptr;
	MovementAction = nullptr;
}


// Called when the game starts
void UPlayerInputActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	//添加映射
	AddInputMapping();

	//设置玩家输入组件，并完成一些绑定
	SetupPlayerInputComponent();
}


// Called every frame
void UPlayerInputActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerInputActorComponent::AddInputMapping()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (Subsystem)
	{
		if (DefaultMappingContext)
		{
			//添加默认映射
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
		
	}
}

void UPlayerInputActorComponent::SetupPlayerInputComponent()
{
	if (EnhancedInputComponent == nullptr)
	{
		EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetOwner()->InputComponent);
	}
	
	//增强输入组件不为空
	if (EnhancedInputComponent != nullptr)
	{
		//绑定MovementAction
		if (MovementAction)
		{
			//绑定movement函数
			EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &UPlayerInputActorComponent::Movement);
		}
	}
}

void UPlayerInputActorComponent::Movement(const FInputActionValue& Value)
{
	//转为2D向量
	FVector2D MovementValue = Value.Get<FVector2D>();

	if (MainCharacter && MainCharacter->GetCharacterMovement())
	{
		//获取控制器旋转
		const FRotator ControlRotator = MainCharacter->GetControlRotation();
		const FRotator YawRotator = FRotator(0.0f, ControlRotator.Yaw, 0.0f);

		// 获取向前向量
		const FVector ForwardDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
		//获取向右向量
		const FVector RightDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);

		UE_LOG(LogTemp, Log, TEXT("dean ForwardDirection=%f,%f,%f x=%f   y=%f"),
			ForwardDirection.X, ForwardDirection.Y, ForwardDirection.Z, MovementValue.X, MovementValue.Y);
		MainCharacter->AddMovementInput(ForwardDirection,  MovementValue.Y);
		MainCharacter->AddMovementInput(RightDirection, MovementValue.X);
	}
}

