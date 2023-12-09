// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AI/E_AICommand.h"
#include "BTT_AICommand.generated.h"

/**
 * AIのコマンドを実行するタスク
 */
UCLASS()
class PAPERNINJA_API UBTT_AICommand : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_AICommand();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

private:
	UPROPERTY(EditAnywhere, Category = "Command")
	E_AICommand _command;
};
