// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasks/BTT_AICommand.h"

#include "Characters/C_Pawn.h"

#include <AIController.h>

UBTT_AICommand::UBTT_AICommand()
{
	NodeName = "AICommand";
}

EBTNodeResult::Type UBTT_AICommand::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto pawn = Cast<AC_Pawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!pawn) { return EBTNodeResult::Failed; }

	bool success = false;
	switch (_command)
	{
		case E_AICommand::BeginSprint:
			success = pawn->BeginSprint();
			break;
		case E_AICommand::EndSprint:
			success = pawn->EndSprint();
			break;
		default:
			success = false;
			break;
	}

	return success ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}

FString UBTT_AICommand::GetStaticDescription() const
{
	const auto Enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("E_AICommand"), true);
	if (!Enum)
	{
		return FString("Invalid");
	}
	FString CommandName = Enum->GetNameByValue(static_cast<uint8>(_command)).ToString();
	return CommandName;
}
