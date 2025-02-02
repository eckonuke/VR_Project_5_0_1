// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_Player.h"
#include "Camera/CameraComponent.h"
#include "MotionControllerComponent.h"
#include "Components/TextRenderComponent.h"
#include <GameFramework/Actor.h>



// Sets default values
AVR_Player::AVR_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cam->SetupAttachment(RootComponent);

	headMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	headMesh->SetupAttachment(cam);
	headMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	leftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Controller"));
	leftController->SetupAttachment(RootComponent);
	// 모션 소스 선택
	leftController->MotionSource = "Left";

	leftHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHand"));
	leftHand->SetupAttachment(leftController);
	leftHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	leftLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Left Log Text"));
	leftLog->SetupAttachment(leftController);
	leftLog->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	leftLog->SetTextRenderColor(FColor::Yellow);
	leftLog->SetHorizontalAlignment(EHTA_Center);
	leftLog->SetVerticalAlignment(EVRTA_TextCenter);

	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	rightController->SetupAttachment(RootComponent);
	rightController->MotionSource = "Right";

	rightHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHand"));
	rightHand->SetupAttachment(rightController);
	rightHand->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	rightLog = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Right Log Text"));
	rightLog->SetupAttachment(rightController);
	rightLog->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	rightLog->SetTextRenderColor(FColor::Yellow);
	rightLog->SetHorizontalAlignment(EHTA_Center);
	rightLog->SetVerticalAlignment(EVRTA_TextCenter);
}

// Called when the game starts or when spawned
void AVR_Player::BeginPlay()
{
	Super::BeginPlay();
	
	// 헤드 장비의 기준 위치를 설정한다.
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(trackOrigin.GetValue());

	if (testActor != nullptr) {
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		spawnedActor = GetWorld()->SpawnActor<AActor>(testActor, cam->GetComponentLocation() + cam->GetForwardVector() * 30.0f, FRotator::ZeroRotator, param);
	}
}

// Called every frame
void AVR_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FString msg = hor + ver;
	//leftLog->SetText(FText::FromString(msg));
	//UE_LOG(LogTemp, Log, TEXT("%s"), *msg);
	FVector newScale = FMath::Lerp(minSize, maxSize, indexValue);
	if (spawnedActor != nullptr) {
		spawnedActor->SetActorRelativeScale3D(newScale);
	}

}

// Called to bind functionality to input
void AVR_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAction("TriggerLeft", IE_Pressed, this, &AVR_Player::OnTriggerLeft);
	//PlayerInputComponent->BindAction("GripLeft", IE_Pressed, this, &AVR_Player::OnGripLeft);
	//PlayerInputComponent->BindAction("TriggerTouchLeft", IE_Pressed, this, &AVR_Player::OnTriggerTouchLeft);
	//PlayerInputComponent->BindAction("TumbstickTouchLeft", IE_Pressed, this, &AVR_Player::OnTumbstrickTouchLeft);

	//PlayerInputComponent->BindAxis("ThumbstickHorizontal", this, &AVR_Player::Horizontal_Left);
	//PlayerInputComponent->BindAxis("ThumbstickVertical", this, &AVR_Player::Vertical_Left);
	PlayerInputComponent->BindAxis("Index_pinch", this, &AVR_Player::IndexPinch);
	PlayerInputComponent->BindAction("Middle_Click", IE_Pressed, this, &AVR_Player::MiddleClick);
	PlayerInputComponent->BindAction("Middle_Click", IE_Released, this, &AVR_Player::MiddleClickEnd);
}

void AVR_Player::OnTriggerLeft()
{
	leftLog->SetText(FText::FromString(__FUNCTION__));
}

void AVR_Player::OnGripLeft()
{
	leftLog->SetText(FText::FromString(__FUNCTION__));
}

void AVR_Player::OnTriggerTouchLeft()
{
	leftLog->SetText(FText::FromString(__FUNCTION__));
}

void AVR_Player::OnTumbstrickTouchLeft()
{
	leftLog->SetText(FText::FromString(__FUNCTION__));
}

void AVR_Player::Horizontal_Left(float value)
{
	//FString msg = FString::Printf(TEXT("%.3f, "), value);


	////FString result = leftLog->Text.ToString() + msg;
	//leftLog->SetText(FText::FromString(msg));
	hor = FString::Printf(TEXT("X: %f"), value);
}

void AVR_Player::Vertical_Left(float value)
{
	/*FString msg = FString::Printf(TEXT("%.3f"), value);
	FString result = leftLog->Text.ToString() + msg;
	leftLog->SetText(FText::FromString(result));*/
	ver = FString::Printf(TEXT("\r\nY: %f"), value);
}

//손가락의 구부림 정도를 출력하는 함수
//구부림의 기준은 엄지 손가락과의 거리이다
void AVR_Player::IndexPinch(float value) {
	indexValue = value;
	leftLog->SetText(FText::FromString(FString::Printf(TEXT("Index : %f"), value)));
}

//엄지와 닿았을 때 실행될 함수
void AVR_Player::MiddleClick() {
	rightLog->SetText(FText::FromString(FString::Printf(TEXT("Click"))));
}

//엄지로부터 떨어졌을때 실행될 함수
void AVR_Player::MiddleClickEnd() {
	rightLog->SetText(FText::FromString(FString::Printf(TEXT("Release"))));
}

