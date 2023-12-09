#pragma once

#include <Async/Async.h>

DECLARE_DELEGATE_OneParam(FFELWDLoopBodySignature, int);
DECLARE_DELEGATE_OneParam(FFELWDCompletedSignature, int);

/// <summary>
/// Debug�\���̐ݒ�
/// </summary>
/// <param name="bEnable"> Debug�\���̗L�� </param>
/// <param name="LifeSpan"> Debug�\����LifeSpan </param>
struct FTraceDebugParams
{
	bool bEnable;
	float LifeSpan;

	FTraceDebugParams()
	{
		bEnable = false;
		LifeSpan = -1.f;
	}

	FTraceDebugParams(bool enable, float lifeSpan = -1.f)
	{
		bEnable = enable;
		LifeSpan = lifeSpan;
	}

	static FTraceDebugParams DefaultTraceDebugParam;
};

/**C++����p�֐����C�u����
 *
 */
class C_FuncLibrary
{
public:
	C_FuncLibrary();

	/// <summary>
	/// �����̌v�Z
	/// </summary>
	/// <param name="start"> �����̊J�n�ʒu </param>
	/// <param name="direction"> �����̔�΂����� </param>
	/// <param name="length"> �����̒��� </param>
	/// <returns> �����̏I���ʒu </returns>
	static FVector CalcRay(FVector start, FVector direction, float length);

	/// <summary>
	/// PlayerPawn���̔��f
	/// </summary>
	/// <param name="actor"> �Ώۂ̃A�N�^�[ </param>
	/// <returns> ���f���� </returns>
	static bool IsPlayerPawn(class AActor* actor);

	/// <summary>
	/// 0���Z���s��Ȃ��ۏ؏���
	/// </summary>
	/// <param name="num"> ���Z�����l </param>
	/// <param name="den"> ���Z����l </param>
	/// <returns> �v�Z���� </returns>
	static float SafeDivide(float num, float den);

	/// <summary>
	/// �z��̗v�f���C�ӂ̑ҋ@���ԋ���ŌJ��Ԃ�����������
	/// </summary>
	/// <typeparam name="T"> �z��̗v�f�^ </typeparam>
	/// <param name="Array"> �v�f�����m�F����z�� </param>
	/// <param name="Duration"> �ҋ@���� </param>
	/// <param name="Obj"> �o�C���h�����֐������|�C���^(UObject���p���K�{) </param>
	/// <param name="LoopBodyFuncName"> �J��Ԃ����Ƀo�C���h����֐���(���� int) </param>
	/// <param name="CompletedFuncName"> �������Ƀo�C���h����֐���(���� int) </param>
	template <typename T>
	static void ForEachLoopWithDelay(TArray<T> Array, float Duration, UObject* Obj, const FName LoopBodyFuncName, const FName CompletedFuncName);

	/// <summary>
	///  �ҋ@���Ԍ�Q�Ƃ���bool�l��false�ɂ���
	/// </summary>
	/// <param name="IsCooldown"> �Q�Ƃ���bool�l </param>
	/// <param name="Duration"> �ҋ@���� </param>
	static void Cooldown(bool& IsCooldown, float Duration = 0.5f);

	/// <summary>
	/// 4�̃p�����[�^����T�C���̒l���擾����
	/// </summary>
	/// <param name="time"> ���� </param>
	/// <param name="phase"> �ʑ�(���W�A��) </param>
	/// <param name="amplitude"> �U�� </param>
	/// <param name="period"> ���� </param>
	/// <returns> Sine�l </returns>
	static float SineCurve(float time, float phase, float amplitude, float period);

	/// <summary>
	/// ���ł̃g���[�X���s��(�`�����l��)
	/// </summary>
	/// <param name="world"> ���[���h�|�C���^ </param>
	/// <param name="result"> �g���[�X���� </param>
	/// <param name="start"> �g���[�X�J�n�ʒu </param>
	/// <param name="end"> �g���[�X�I���ʒu </param>
	/// <param name="traceChannel"> �g���[�X�̃`�����l��(�R���W�����̎��) </param>
	/// <param name="debugParams"> �f�o�b�O�\���̐ݒ� </param>
	/// <param name="params"> �Փˌ��o�̐ݒ� </param>
	/// <param name="responseParams"> �Փˉ����̐ݒ� </param>
	/// <returns> Hit���� </returns>
	static bool LineTraceByChannel(
		UWorld* world,
		FHitResult& result,
		const FVector start,
		const FVector end,
		ECollisionChannel traceChannel,
		FTraceDebugParams& debugParams = FTraceDebugParams::DefaultTraceDebugParam,
		const FCollisionQueryParams& params = FCollisionQueryParams::DefaultQueryParam,
		const FCollisionResponseParams& responseParams = FCollisionResponseParams::DefaultResponseParam);

	/// <summary>
	/// ���ł̃g���[�X���s��(�`�����l��)
	/// </summary>
	/// <param name="world"> ���[���h�|�C���^ </param>
	/// <param name="result"> �g���[�X���� </param>
	/// <param name="start"> �g���[�X�J�n�ʒu </param>
	/// <param name="end"> �g���[�X�I���ʒu </param>
	/// <param name="halfSize"> Box�̔��a </param>
	/// <param name="quat"> �p�x </param>
	/// <param name="traceChannel"> �g���[�X�̃`�����l��(�R���W�����̎��) </param>
	/// <param name="debugParams"> �f�o�b�O�\���̐ݒ� </param>
	/// <param name="params"> �Փˌ��o�̐ݒ� </param>
	/// <param name="responseParams"> �Փˉ����̐ݒ� </param>
	/// <returns> Hit���� </returns>
	static bool MultiBoxTraceByChannel(
		UWorld* world,
		TArray<FHitResult>& results,
		const FVector start,
		const FVector end,
		const FVector halfSize,
		const FQuat quat,
		ECollisionChannel traceChannel,
		FTraceDebugParams& debugParams = FTraceDebugParams::DefaultTraceDebugParam,
		const FCollisionQueryParams& params = FCollisionQueryParams::DefaultQueryParam,
		const FCollisionResponseParams& responseParams = FCollisionResponseParams::DefaultResponseParam);

	/// <summary>
	/// ���ł̃g���[�X���s��(�v���t�@�C��)
	/// </summary>
	/// <param name="world"> ���[���h�|�C���^ </param>
	/// <param name="result"> �g���[�X���� </param>
	/// <param name="start"> �g���[�X�J�n�ʒu </param>
	/// <param name="end"> �g���[�X�I���ʒu </param>
	/// <param name="profileName"> �g���[�X�̃v���t�@�C��(�R���W�����̎��) </param>
	/// <param name="debugParams"> �f�o�b�O�\���̐ݒ� </param>
	/// <param name="params"> �Փˌ��o�̐ݒ� </param>
	/// <returns> Hit���� </returns>
	static bool LineTraceByProfile(
		UWorld* world,
		FHitResult& result,
		const FVector start,
		const FVector end,
		const FName profileName,
		FTraceDebugParams& debugParams = FTraceDebugParams::DefaultTraceDebugParam,
		const FCollisionQueryParams& params = FCollisionQueryParams::DefaultQueryParam);

	/// <summary>
	/// ���̂ł̃g���[�X���s��(�`�����l��)
	/// </summary>
	/// <param name="world"> ���[���h�|�C���^ </param>
	/// <param name="outActors"> �q�b�g����Actor </param>
	/// <param name="start"> �g���[�X�J�n�ʒu </param>
	/// <param name="radius"> ���̔��a </param>
	/// <param name="objectTypes"> �g���[�X�̃I�u�W�F�N�g�^�C�v(�R���W�����̎��) </param>
	/// <param name="actorClassFilter"> �g���[�X�̑ΏۂƂȂ�I�u�W�F�N�g�̌^ </param>
	/// <param name="actorsToIgnore"> �g���[�X�̏��O�ƂȂ�A�N�^�[ </param>
	/// <param name="debugParams"> �f�o�b�O�\���̐ݒ� </param>
	/// <returns> Hit���� </returns>
	static bool SphereOverlapByChannel(
		UWorld* world,
		TArray<AActor*>& outActors,
		const FVector start,
		const float radius,
		const TArray<TEnumAsByte<EObjectTypeQuery> >& objectTypes,
		UClass* actorClassFilter,
		const TArray<AActor*>& actorsToIgnore,
		FTraceDebugParams& debugParams = FTraceDebugParams::DefaultTraceDebugParam);
};

template <typename T>
void C_FuncLibrary::ForEachLoopWithDelay(TArray<T> Array, float Duration, UObject* Obj, const FName LoopBodyFuncName, const FName CompletedFuncName)
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [Array, Duration, Obj, LoopBodyFuncName, CompletedFuncName]()
		{
			int index = 0;
			while (index < Array.Num())
			{
				AsyncTask(ENamedThreads::GameThread, [Obj, LoopBodyFuncName, index]()
					{
						FFELWDLoopBodySignature LoopBody;
						LoopBody.BindUFunction(Obj, LoopBodyFuncName);
						LoopBody.ExecuteIfBound(index);
					});

				++index;
				FPlatformProcess::Sleep(Duration);
			}

			AsyncTask(ENamedThreads::GameThread, [Obj, CompletedFuncName, index]()
				{
					FFELWDCompletedSignature Completed;
					Completed.BindUFunction(Obj, CompletedFuncName);
					Completed.ExecuteIfBound(index);
				});
		});
}