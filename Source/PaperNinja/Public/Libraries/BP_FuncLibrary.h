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
 * BP用関数ライブラリ
 */

UCLASS()
class PAPERNINJA_API UBP_FuncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UBP_FuncLibrary();

	/* 光線の計算(BP用)
	* origin : 原点位置
	* direction : 光線の飛ばす方向
	* length : 光線の長さ
	* 戻り値 : 光線の開始,終了位置
	*/
	UFUNCTION(BlueprintCallable)
	FCalcRayStruct CalcRay(FVector origin, FVector direction, float length);

	/* PlayerPawnかの判断
	* actor: 対象のアクター
	* 戻り値 : 判断結果
	*/
	UFUNCTION(BlueprintCallable)
	bool IsPlayerPawn(AActor* actor);

	/* 配列の要素数任意の待機時間挟んで繰り返し処理をする
	* Array：要素数を確認する配列
	* Duration：待機時間
	* Obj : バインドした関数を持つポインタ(UObjectを継承必須)
	* LoopBodyFuncName : 繰り返し時にバインドする関数名(引数 int)
	* CompletedFuncName : 完了時にバインドする関数名(引数 int)
	*/
	template <typename T>
	UFUNCTION(BlueprintCallable)
	void ForEachLoopWithDelay(TArray<T> Array, float Duration, UObject* Obj, const FName LoopBodyFuncName, const FName CompletedFuncName);

	/* 待機時間後参照したbool値をfalseにする
	* IsCooldown：参照するbool値
	* Duration：待機時間
	*/
	UFUNCTION(BlueprintCallable)
	void Cooldown(bool& IsCooldown, float Duration = 0.5f);

	/* 4つのパラメータからサインの値を取得する
	* time：時間
	* phase：位相(ラジアン)
	* amplitude：振幅
	* period：周期
	* 戻り値：Sine値
	*/
	UFUNCTION(BlueprintCallable)
	float SineCurve(float time, float phase, float amplitude, float period);
	
};


