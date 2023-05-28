#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterTypes.h"
#include "SlashAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SLASH__API USlashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	// 이벤트 그래프에서 초기화 노드에 해당
	virtual void NativeInitializeAnimation() override;
	// 이벤트 그래프에서 Update노드에 해당
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	// 변수들. 애니메이션 BP에디터에서 선언했던 변수들이다.
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class ASlashCharacter* SlashCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* SlashCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool isFalling;

	UPROPERTY(BlueprintReadOnly, Category = "Movement | Character State")
	ECharacterState CharacterState;
};
