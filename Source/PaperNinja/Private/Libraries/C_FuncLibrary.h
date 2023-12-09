#pragma once

#include <Async/Async.h>

DECLARE_DELEGATE_OneParam(FFELWDLoopBodySignature, int);
DECLARE_DELEGATE_OneParam(FFELWDCompletedSignature, int);

/// <summary>
/// Debug表示の設定
/// </summary>
/// <param name="bEnable"> Debug表示の有無 </param>
/// <param name="LifeSpan"> Debug表示のLifeSpan </param>
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

/**C++内専用関数ライブラリ
 *
 */
class C_FuncLibrary
{
public:
	C_FuncLibrary();

	/// <summary>
	/// 光線の計算
	/// </summary>
	/// <param name="start"> 光線の開始位置 </param>
	/// <param name="direction"> 光線の飛ばす方向 </param>
	/// <param name="length"> 光線の長さ </param>
	/// <returns> 光線の終了位置 </returns>
	static FVector CalcRay(FVector start, FVector direction, float length);

	/// <summary>
	/// PlayerPawnかの判断
	/// </summary>
	/// <param name="actor"> 対象のアクター </param>
	/// <returns> 判断結果 </returns>
	static bool IsPlayerPawn(class AActor* actor);

	/// <summary>
	/// 0除算を行わない保証処理
	/// </summary>
	/// <param name="num"> 除算される値 </param>
	/// <param name="den"> 除算する値 </param>
	/// <returns> 計算結果 </returns>
	static float SafeDivide(float num, float den);

	/// <summary>
	/// 配列の要素数任意の待機時間挟んで繰り返し処理をする
	/// </summary>
	/// <typeparam name="T"> 配列の要素型 </typeparam>
	/// <param name="Array"> 要素数を確認する配列 </param>
	/// <param name="Duration"> 待機時間 </param>
	/// <param name="Obj"> バインドした関数を持つポインタ(UObjectを継承必須) </param>
	/// <param name="LoopBodyFuncName"> 繰り返し時にバインドする関数名(引数 int) </param>
	/// <param name="CompletedFuncName"> 完了時にバインドする関数名(引数 int) </param>
	template <typename T>
	static void ForEachLoopWithDelay(TArray<T> Array, float Duration, UObject* Obj, const FName LoopBodyFuncName, const FName CompletedFuncName);

	/// <summary>
	///  待機時間後参照したbool値をfalseにする
	/// </summary>
	/// <param name="IsCooldown"> 参照するbool値 </param>
	/// <param name="Duration"> 待機時間 </param>
	static void Cooldown(bool& IsCooldown, float Duration = 0.5f);

	/// <summary>
	/// 4つのパラメータからサインの値を取得する
	/// </summary>
	/// <param name="time"> 時間 </param>
	/// <param name="phase"> 位相(ラジアン) </param>
	/// <param name="amplitude"> 振幅 </param>
	/// <param name="period"> 周期 </param>
	/// <returns> Sine値 </returns>
	static float SineCurve(float time, float phase, float amplitude, float period);

	/// <summary>
	/// 線でのトレースを行う(チャンネル)
	/// </summary>
	/// <param name="world"> ワールドポインタ </param>
	/// <param name="result"> トレース結果 </param>
	/// <param name="start"> トレース開始位置 </param>
	/// <param name="end"> トレース終了位置 </param>
	/// <param name="traceChannel"> トレースのチャンネル(コリジョンの種類) </param>
	/// <param name="debugParams"> デバッグ表示の設定 </param>
	/// <param name="params"> 衝突検出の設定 </param>
	/// <param name="responseParams"> 衝突応答の設定 </param>
	/// <returns> Hit結果 </returns>
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
	/// 箱でのトレースを行う(チャンネル)
	/// </summary>
	/// <param name="world"> ワールドポインタ </param>
	/// <param name="result"> トレース結果 </param>
	/// <param name="start"> トレース開始位置 </param>
	/// <param name="end"> トレース終了位置 </param>
	/// <param name="halfSize"> Boxの半径 </param>
	/// <param name="quat"> 角度 </param>
	/// <param name="traceChannel"> トレースのチャンネル(コリジョンの種類) </param>
	/// <param name="debugParams"> デバッグ表示の設定 </param>
	/// <param name="params"> 衝突検出の設定 </param>
	/// <param name="responseParams"> 衝突応答の設定 </param>
	/// <returns> Hit結果 </returns>
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
	/// 線でのトレースを行う(プロファイル)
	/// </summary>
	/// <param name="world"> ワールドポインタ </param>
	/// <param name="result"> トレース結果 </param>
	/// <param name="start"> トレース開始位置 </param>
	/// <param name="end"> トレース終了位置 </param>
	/// <param name="profileName"> トレースのプロファイル(コリジョンの種類) </param>
	/// <param name="debugParams"> デバッグ表示の設定 </param>
	/// <param name="params"> 衝突検出の設定 </param>
	/// <returns> Hit結果 </returns>
	static bool LineTraceByProfile(
		UWorld* world,
		FHitResult& result,
		const FVector start,
		const FVector end,
		const FName profileName,
		FTraceDebugParams& debugParams = FTraceDebugParams::DefaultTraceDebugParam,
		const FCollisionQueryParams& params = FCollisionQueryParams::DefaultQueryParam);

	/// <summary>
	/// 球体でのトレースを行う(チャンネル)
	/// </summary>
	/// <param name="world"> ワールドポインタ </param>
	/// <param name="outActors"> ヒットしたActor </param>
	/// <param name="start"> トレース開始位置 </param>
	/// <param name="radius"> 球の半径 </param>
	/// <param name="objectTypes"> トレースのオブジェクトタイプ(コリジョンの種類) </param>
	/// <param name="actorClassFilter"> トレースの対象となるオブジェクトの型 </param>
	/// <param name="actorsToIgnore"> トレースの除外となるアクター </param>
	/// <param name="debugParams"> デバッグ表示の設定 </param>
	/// <returns> Hit結果 </returns>
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