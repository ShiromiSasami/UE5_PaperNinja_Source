#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "E_AICommand.generated.h"

UENUM(BlueprintType)
enum class E_AICommand : uint8
{
	BeginSprint UMETA(DisplayName = "BeginSprint"),
	EndSprint UMETA(DisplayName = "EndSprint")
};