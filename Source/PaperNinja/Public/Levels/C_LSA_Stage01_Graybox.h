// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "AITypes.h"
#include "Navigation/PathFollowingComponent.h"
#include "Components/TimelineComponent.h"
#include "C_LSA_Stage01_Graybox.generated.h"

/**
 * Grayboxサブレベルのレベルスクリプト
 */
UCLASS()
class PAPERNINJA_API AC_LSA_Stage01_Graybox : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	AC_LSA_Stage01_Graybox();
	~AC_LSA_Stage01_Graybox();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
#pragma region BindFunction
	/// <summary>
	/// 死亡エリアに入った時の処理
	/// </summary>
	/// <param name="OverlappedActor">接触したアクター</param>
	/// <param name="OtherActor">接触されたアクター</param>
	UFUNCTION()
	void OnTriggerOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void GearAlphaTimelineStep(float value);
	UFUNCTION()
	void OnNorthSwitchChanged(AC_SwitchBase* switchActor);
	UFUNCTION()
	void OnCraneSwitchChanged(AC_SwitchBase* switchActor);
	UFUNCTION()
	void SouthJumpCubeReset(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void WestJumpCubeReset(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnFloatBoxHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnIronSphereHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnSeesawHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

#pragma endregion
	
protected:
#pragma region InLevelActor
	UPROPERTY(EditAnywhere);
	TObjectPtr<class AStaticMeshActor> _gearTop;
	UPROPERTY(EditAnywhere);
	TObjectPtr<class ATriggerBox> _deathTrigger;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class ALevelSequenceActor> _craneSequence;
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<class AC_SwitchBase>> _northSwiches;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class AC_GateBase> _northGate;
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<class AC_SwitchBase>> _craneSwiches;
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<class AC_JumpCubeBase>> _southJumpCubes;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class ATriggerBox> _checkpointNE;
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<class AC_JumpCubeBase>> _westJumpCubes;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class ATriggerBox> _checkpointSW;
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<class ATargetPoint>> _bonusCoinPoints;
	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<class AC_ScrollBase>> _scrolls;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class AStaticMeshActor> _floatBox;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class AStaticMeshActor> _boxBalloon;
	UPROPERTY(EditAnywhere);
	TObjectPtr<class APhysicsConstraintActor> _floatBalloonJoint;
	UPROPERTY(EditAnywhere);
	TObjectPtr<class AStaticMeshActor> _ironSphere;
	UPROPERTY(EditAnywhere);
	TObjectPtr<class AStaticMeshActor> _seesaw;
	UPROPERTY(EditAnywhere);
	TObjectPtr<class AC_ChestBase> _floatChest;
	UPROPERTY(EditAnywhere);
	TObjectPtr<class AStaticMeshActor> _chestBalloon;
#pragma endregion

	UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "屋上の床スイッチの点灯数"))
	int _switchCounter;

	FTimeline* _gearTimeline;
	bool bIsPlayingForward;
	int8 _floatBoxHitCount;
	bool bFloatBoxisHitting;
	TSubclassOf<class UUserWidget> _clearWidgetClass;
	bool _loadTitleLevel;

};
