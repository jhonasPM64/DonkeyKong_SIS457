// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DonkeyKong_SIS457 : ModuleRules
{
	public DonkeyKong_SIS457(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
