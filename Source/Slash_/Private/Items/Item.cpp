// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "DrawDebugHelpers.h"
#include "Slash_/DebugMacros.h"
#include "Components/SphereComponent.h"
#include "Characters/SlashCharacter.h"
#include "NiagaraComponent.h"


AItem::AItem() : amplitude(0.25f), timeConstant(5.f)
{
	PrimaryActorTick.bCanEverTick = true;

	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	itemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	itemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = itemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	ItemEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
	ItemEffect->SetupAttachment(GetRootComponent());

}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::EndSphereOverlap);
}

float AItem::TransformSin()
{
	return amplitude * FMath::Sin(runningTime * timeConstant);
}

float AItem::TransformCos()
{
	return amplitude * FMath::Cos(runningTime * timeConstant);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	runningTime += DeltaTime;

	if(ItemState == EItemState::EIS_Hovering)
	{
		AddActorWorldOffset(FVector(0.f,0.f,TransformSin()));
	}
	// DRAW_SPHERE_SingleFrame(GetActorLocation());
	// DRAW_VECTOR_SingleFrame(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f);
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	if(SlashCharacter)
	{
		SlashCharacter->SetOverlappingItem(this);
	}
}

void AItem::EndSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	if(SlashCharacter)
	{
		SlashCharacter->SetOverlappingItem(nullptr);
	}
}