// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "C_GameStateBase.generated.h"

/**Gameì‡èÓïÒÇÃï€éùÉNÉâÉX
 * 
 */
UCLASS()
class PAPERNINJA_API AC_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AC_GameStateBase();

private:
	virtual void BeginPlay() override;

public:
#pragma region InlineFunction

	FORCEINLINE void InitScrolls(const uint8 size)
	{
		if (size == 0) { return; }
		_hasScrolls.Init(false, size);
	};
	FORCEINLINE void ObtainScroll(const int index)
	{
		if (_hasScrolls.Num() <= index) { return; }
		_hasScrolls[index] = true;
	};
	FORCEINLINE void SetCheckpoint(AActor* point) { _checkpoint = point; };
	FORCEINLINE AActor* GetCheckpoint() const { return _checkpoint; };
#pragma endregion

	bool HasCompletedLevel() const;

protected:
	UPROPERTY(EditAnywhere)
	TArray<bool> _hasScrolls;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> _checkpoint;
};
