// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacter.h"

#include "Camera/CameraComponent.h"
#include "Component/PlayerInputActorComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//添加摇臂和摄像机组件
	AddSpringCameraComp();
	
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

	//绑定自己写的组件
	PlayerInputActorComponent = CreateDefaultSubobject<UPlayerInputActorComponent>(TEXT("PlayerInputActorComponent"));
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	CheckAnimInstanceClass();
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

void AMainCharacter::AddSpringCameraComp()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
}

