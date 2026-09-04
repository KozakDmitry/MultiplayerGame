// Multiplayer Game

using UnrealBuildTool;

public class MultiplayerGame : ModuleRules
{
    public MultiplayerGame(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[] { "MultiplayerGame/Public/Player",
                                                   "MultiplayerGame/Public/Components",
                                                   "MultiplayerGame/Public/Dev",
                                                   "MultiplayerGame/Public/Weapon",
                                                   "MultiplayerGame/Public/UI",
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
