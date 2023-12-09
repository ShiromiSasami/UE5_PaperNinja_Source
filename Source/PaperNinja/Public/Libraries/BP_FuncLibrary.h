#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BP_FuncLibrary.generated.h"

USTRUCT(BlueprintType)
struct FCalcRayStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	FVector Start;

	UPROPERTY(BlueprintReadWrite)
	FVector End;
};

/**
 * BP�p�֐����C�u����
 */

UCLASS()
class PAPERNINJA_API UBP_FuncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UBP_FuncLibrary();

	/* �����̌v�Z(BP�p)
	* origin : ���_�ʒu
	* direction : �����̔�΂�����
	* length : �����̒���
	* �߂�l : �����̊J�n,�I���ʒu
	*/
	UFUNCTION(BlueprintCallable)
	FCalcRayStruct CalcRay(FVector origin, FVector direction, float length);

	/* PlayerPawn���̔��f
	* actor: �Ώۂ̃A�N�^�[
	* �߂�l : ���f����
	*/
	UFUNCTION(BlueprintCallable)
	bool IsPlayerPawn(AActor* actor);

	/* �z��̗v�f���C�ӂ̑ҋ@���ԋ���ŌJ��Ԃ�����������
	* Array�F�v�f�����m�F����z��
	* Duration�F�ҋ@����
	* Obj : �o�C���h�����֐������|�C���^(UObject���p���K�{)
	* LoopBodyFuncName : �J��Ԃ����Ƀo�C���h����֐���(���� int)
	* CompletedFuncName : �������Ƀo�C���h����֐���(���� int)
	*/
	template <typename T>
	UFUNCTION(BlueprintCallable)
	void ForEachLoopWithDelay(TArray<T> Array, float Duration, UObject* Obj, const FName LoopBodyFuncName, const FName CompletedFuncName);

	/* �ҋ@���Ԍ�Q�Ƃ���bool�l��false�ɂ���
	* IsCooldown�F�Q�Ƃ���bool�l
	* Duration�F�ҋ@����
	*/
	UFUNCTION(BlueprintCallable)
	void Cooldown(bool& IsCooldown, float Duration = 0.5f);

	/* 4�̃p�����[�^����T�C���̒l���擾����
	* time�F����
	* phase�F�ʑ�(���W�A��)
	* amplitude�F�U��
	* period�F����
	* �߂�l�FSine�l
	*/
	UFUNCTION(BlueprintCallable)
	float SineCurve(float time, float phase, float amplitude, float period);
	
};


