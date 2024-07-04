// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpaceActor.generated.h"

UENUM(BlueprintType)
enum ESpaceMass {
	Earth   UMETA(DisplayName = "Earth"),
	Moon    UMETA(DisplayName = "Moon"),
	Hubble  UMETA(DisplayName = "Hubble Telescope"),
};

UCLASS()
class GRAVM_API ASpaceActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	double SpaceMassValue;

	UFUNCTION(BlueprintCallable)
		void SetFreeze(bool bFreeze);
	UFUNCTION(BlueprintCallable)
		void Freeze();
	UFUNCTION(BlueprintCallable)
		void UnFreeze();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<ESpaceMass> SpaceMass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "For this to work, the root component must simulate physics."))
		bool GravitateToOthers = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "For this to work, the root component must simulate physics."))
		bool GravitateToSelf = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool FreezeOnStart = false;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		bool Freezed = false;

private:
	const double gconst = 6.6743e-11;
	USceneComponent* Root;
	UPrimitiveComponent* Primitive;

	FVector FreezedVelocity;
};