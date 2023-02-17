// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "VR_Player.generated.h"

UCLASS()
class VR_PROJECT_API AVR_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVR_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UCameraComponent* cam;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UStaticMeshComponent* headMesh;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UMotionControllerComponent* leftController;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UStaticMeshComponent* leftHand;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UTextRenderComponent* leftLog;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UMotionControllerComponent* rightController;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UStaticMeshComponent* rightHand;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|Components")
		class UTextRenderComponent* rightLog;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|ModuleSetting")
		TEnumAsByte<enum EHMDTrackingOrigin::Type> trackOrigin;

	UPROPERTY(EditAnywhere, Category = "VR_Settings|ModuleSetting")
	TSubclassOf<class AActor> testActor;
	UPROPERTY(EditAnywhere)
	FVector minSize = FVector(0.05f);
	UPROPERTY(EditAnywhere)
	FVector maxSize = FVector(0.1f);

private:

	void OnTriggerLeft();
	void OnGripLeft();
	void OnTriggerTouchLeft();
	void OnTumbstrickTouchLeft();
	void Horizontal_Left(float value);
	void Vertical_Left(float value);
	void IndexPinch(float value);
	void MiddleClick();
	void MiddleClickEnd();
	FString hor, ver;
	AActor* spawnedActor;
	float indexValue;
};
