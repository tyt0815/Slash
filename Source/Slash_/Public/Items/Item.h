// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
class UNiagaraComponent;
class UNiagaraSystem;

enum class EItemState : uint8
{
	EIS_Hovering,
	EIS_Eqipped
};

UCLASS()
class SLASH__API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float amplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float timeConstant;

	UFUNCTION(BlueprintPure)
	float TransformSin();

	UFUNCTION(BlueprintPure)
	float TransformCos();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UStaticMeshComponent* itemMesh;

	template<typename T>
	T  Avg(T first, T second);

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void SpawnPickupSystem();
	virtual void SpawnPickupSound();

	EItemState ItemState = EItemState::EIS_Hovering;
	
	UPROPERTY(VisibleAnywhere);
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ItemEffect;

	UPROPERTY(EditAnywhere)
	USoundBase* PickupSound;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float runningTime;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* PickupEffect;

};

template<typename T>
inline T AItem::Avg(T first, T second)
{
	return (first + second) / 2;
}
