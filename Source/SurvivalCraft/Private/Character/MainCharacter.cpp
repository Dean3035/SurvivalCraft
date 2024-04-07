// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	//添加摇臂和摄像机组件
	SetSpringCameraComp();

	//设置骨骼网格体和动画实例
	SetSkeletalMeshAnimInstanceClass();

	//设置增强输入相关
	SetEnhancedInput();
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//检查动画实例
	CheckAnimInstanceClass();

	//设置上下文映射
	if (DefaultMappingContext)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (Subsystem)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMainCharacter::Movement);//绑定移动
		EnhancedInputComponent->BindAction(YawPitchAction, ETriggerEvent::Triggered, this, &AMainCharacter::YawPitch);//绑定上下左右看
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &AMainCharacter::SwitchRun);//跑步
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AMainCharacter::SwitchWalk);//走路
	}
}

void AMainCharacter::CheckAnimInstanceClass()
{
	if (GetMesh()->GetAnimInstance() == nullptr)
	{
		//关于动画的
		UClass* AnimInstanceClass = LoadObject<UClass>(nullptr,
			TEXT("/Script/Engine.AnimBlueprint'/Game/Dean/Animations/Animations/ABP/ABP_MainCharacter.ABP_MainCharacter_C'"));
		if (AnimInstanceClass)
		{
			GetMesh()->SetAnimInstanceClass(AnimInstanceClass);
		}
	}
}

void AMainCharacter::Movement(const FInputActionValue& Value)
{
	FVector2D MovementValue = Value.Get<FVector2D>();

	const FRotator ControlRotator = GetControlRotation();
	const FRotator YawRotator = FRotator(0.0f, ControlRotator.Yaw, 0.0f);

	const FVector Forward = YawRotator.Quaternion().GetForwardVector();
	const FVector Right = YawRotator.Quaternion().GetRightVector();
	
	AddMovementInput(Forward, MovementValue.Y);
	AddMovementInput(Right, MovementValue.X);
}

void AMainCharacter::YawPitch(const FInputActionValue& Value)
{
	FVector2D YawPitchValue = Value.Get<FVector2D>();

	UE_LOG(LogTemp, Log, TEXT("dean YawPitchValue x=%f  y=%f"), YawPitchValue.X, YawPitchValue.Y);
	
	AddControllerYawInput(YawPitchValue.X);
	AddControllerPitchInput(YawPitchValue.Y);
}

void AMainCharacter::SwitchWalk(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
}

void AMainCharacter::SwitchRun(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void AMainCharacter::SetSpringCameraComp()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
}

void AMainCharacter::SetSkeletalMeshAnimInstanceClass()
{
	//加载骨骼网格体
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/Man/Mesh/Full/SK_Man_Full_01.SK_Man_Full_01'"));
	if (SkeletalMeshAsset.Succeeded())
	{
		//设置
		GetMesh()->SetSkeletalMesh(SkeletalMeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));
		GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));//(Pitch=0.000000,Yaw=-90.000000,Roll=0.000000)
	}

	//关于动画的
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationClassFinder(TEXT("//Script/Engine.AnimBlueprint'/Game/Dean/Animations/Animations/ABP/ABP_MainCharacter.ABP_MainCharacter_C'"));
	if (AnimationClassFinder.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimationClassFinder.Class);
	}
}

void AMainCharacter::SetEnhancedInput()
{
	//加载上下文映射
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> DefaultMappingContextAsset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Dean/Input/IMC_Default.IMC_Default'"));
	if (DefaultMappingContextAsset.Succeeded())
	{
		DefaultMappingContext = DefaultMappingContextAsset.Object;
	}
	
	//移动
	static ConstructorHelpers::FObjectFinder<UInputAction> InputAction_Movement_Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Dean/Input/IA_Movement.IA_Movement'"));
	if (InputAction_Movement_Asset.Succeeded())
	{
		MovementAction = InputAction_Movement_Asset.Object;
	}

	//左右看
	static ConstructorHelpers::FObjectFinder<UInputAction> InputAction_YawPitch_Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Dean/Input/IA_ControlYawPitch.IA_ControlYawPitch'"));
	if (InputAction_YawPitch_Asset.Succeeded())
	{
		YawPitchAction = InputAction_YawPitch_Asset.Object;
	}

	//跑步
	static ConstructorHelpers::FObjectFinder<UInputAction> Run_Asset(TEXT("/Script/EnhancedInput.InputAction'/Game/Dean/Input/IA_Run.IA_Run'"));
	if (Run_Asset.Succeeded())
	{
		RunAction = Run_Asset.Object;
	}
}

