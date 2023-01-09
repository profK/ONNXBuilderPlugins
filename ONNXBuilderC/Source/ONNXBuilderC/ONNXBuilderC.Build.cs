// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using System.Reflection;
using UnrealBuildTool;

public class ONNXBuilderC : ModuleRules
{
    public string GetUProjectPath()
    {
		//Change this according to your module's relative location to your project file. If there is any better way to do this I'm interested!
		//Assuming Source/ThirdParty/YourLib/
        return Directory.GetParent(ModuleDirectory).Parent.Parent.ToString();
    }

    private void CopyToBinaries(string Filepath, ReadOnlyTargetRules Target)
    {
        string binariesDir = Path.Combine(GetUProjectPath(),"..","..", "Binaries", Target.Platform.ToString());
        string filename = Path.GetFileName(Filepath);
        
        Console.WriteLine(" - copying to ---- >" + binariesDir);
 
        if (!Directory.Exists(binariesDir))
            Directory.CreateDirectory(binariesDir);

        if (!File.Exists(Path.Combine(binariesDir, filename)))
            File.Copy(Filepath, Path.Combine(binariesDir, filename), true);
    }

	public ONNXBuilderC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseRTTI = true;
		
		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory,"ThirdParty","include")
			}
			);
		
		string onnxPath =
			Path.Combine(ModuleDirectory, "ThirdParty", "lib", "ONNXBuilder.lib");
		Console.WriteLine("... LibrariesPath -> " + onnxPath);
		PublicAdditionalLibraries.AddRange(
			new string[]
			{
				onnxPath,
				Path.Combine(ModuleDirectory, "ThirdParty", "lib","libprotobuf.lib" )
			}
			);	
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "ThirdParty", "lib","libprotobuf.lib" ));
		//PublicDelayLoadDLLs.Add("libprotobuf.dll");
		RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "ThirdParty", "lib","libprotobuf.dll")) ;
		CopyToBinaries(Path.Combine(ModuleDirectory, "ThirdParty", "lib","libprotobuf.dll"),Target);
	}
}
