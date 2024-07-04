// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceActor.h"

// Sets default values
ASpaceActor::ASpaceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpaceActor::BeginPlay()
{
	Root = GetRootComponent();
	Primitive = Cast<UPrimitiveComponent>(Root);

	switch (SpaceMass)
	{
	case Earth:
		SpaceMassValue = 5.972e24;
		break;
	case Moon:
		SpaceMassValue = 7.36e22;
		break;
	case Hubble:
		SpaceMassValue = 12500;
		break;
	default:
		SpaceMassValue = 1000;
		break;
	}

	if (FreezeOnStart) Freeze();

	Super::BeginPlay();
}

// Called every frame
void ASpaceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Root->IsSimulatingPhysics() || !GravitateToOthers || Freezed) return;

	TArray<AActor*> OtherSpaceActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpaceActor::StaticClass(), OtherSpaceActors);

	for (AActor* Actor : OtherSpaceActors)
	{
		ASpaceActor* OtherActor = Cast<ASpaceActor>(Actor);

		if (!OtherActor->GravitateToSelf || Actor == this) continue;

		UPrimitiveComponent* OtherActorPrimitive = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());

		double m1 = SpaceMassValue;
		double m2 = OtherActor->SpaceMassValue;
		FVector centerOfMass1 = Primitive->GetCenterOfMass();
		FVector centerOfMass2 = OtherActorPrimitive->GetCenterOfMass();
		double dist_squared = UKismetMathLibrary::Vector_DistanceSquared(centerOfMass1, centerOfMass2);

		double ForceScalar = gconst * ((m1 * m2) / 1e3) / dist_squared;
		FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(centerOfMass1, centerOfMass2);
		FVector Force = Direction * ForceScalar;

		Primitive->AddForce(Force);
	}
}

void ASpaceActor::SetFreeze(bool bFreeze) {
	Freezed = bFreeze;

	if (bFreeze) {
		FreezedVelocity = GetVelocity();
		Primitive->SetPhysicsLinearVelocity(FVector::ZeroVector);
	}
	else {
		Primitive->SetPhysicsLinearVelocity(FreezedVelocity);
	}

	Primitive->BodyInstance.bLockXTranslation = bFreeze;
	Primitive->BodyInstance.bLockYTranslation = bFreeze;
	Primitive->BodyInstance.bLockZTranslation = bFreeze;
	Primitive->BodyInstance.bLockXRotation = bFreeze;
	Primitive->BodyInstance.bLockYRotation = bFreeze;
	Primitive->BodyInstance.bLockZRotation = bFreeze;

	Primitive->BodyInstance.CreateDOFLock();
}

void ASpaceActor::Freeze() {
	SetFreeze(true);
}

void ASpaceActor::UnFreeze() {
	SetFreeze(false);
}
