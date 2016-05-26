#addin "Cake.CMake"
using Cake.Common.Diagnostics;
using System.Text.RegularExpressions;

var target = Argument("target", "Default");
var configuration = Argument("configuration", "Release");

var buildDir = new DirectoryPath("./tmp").MakeAbsolute(Context.Environment);
var protocExe = buildDir.CombineWithFilePath(string.Format("third-party/{0}/protoc.exe", configuration));

//////////////////////////////////////////////////////////////////////
// TASKS
//////////////////////////////////////////////////////////////////////

Task("Clean")
	.Does(() =>
	{
		CleanDirectory(buildDir);
	});

Task("CMake-Generate")
	.Does(() =>
	{
		CreateDirectory(buildDir);
		var settings = new CMakeSettings
		{
			OutputPath = buildDir
		};
		CMake("./", settings);
	});
	
Task("CMake-Build-ProtoC")
	.IsDependentOn("CMake-Generate")
	.Does(() =>
	{
		var cmakeBuildSettings = new ProcessSettings()
			.WithArguments(x => x
				.AppendSwitch("--build", buildDir.FullPath)
				.AppendSwitch("--target", "protoc")
				.AppendSwitch("--config", configuration));

		var exitCode = StartProcess("cmake", cmakeBuildSettings);
		if (exitCode != 0)
			throw new Exception("failed to build with cmake");
			
		if (!FileExists(protocExe))
			throw new Exception("protoc not found");
	});

Task("CMake-Build")
	.IsDependentOn("CMake-Generate")
	.IsDependentOn("GenerateProtoFiles")
	.Does(() =>
	{
		var cmakeBuildSettings = new ProcessSettings()
			.WithArguments(x =>	x
				.AppendSwitch("--build", buildDir.FullPath)
				.AppendSwitch("--config", configuration));

		var exitCode = StartProcess("cmake", cmakeBuildSettings);
		if (exitCode != 0)
			throw new Exception("failed to build with cmake"); 
	});

	
Task("GenerateProtoFiles")
	.IsDependentOn("CMake-Build-ProtoC")
	.Does(() =>
	{
		var sourceProtoDir = new DirectoryPath("./proto/").MakeAbsolute(Context.Environment);
		var destinationProtoDir = new DirectoryPath("./src/protos/").MakeAbsolute(Context.Environment);

		var files = GetFiles("./proto/**/*.proto");
		foreach (var file in files)
		{
			var relativeFile = sourceProtoDir.GetRelativePath(file);
			var destinationFile = destinationProtoDir.CombineWithFilePath(relativeFile).ChangeExtension("pb.h");
			var destinationDir = destinationFile.GetDirectory(); 
			
			// if (FileExists(destinationFile) &&
			// 	System.IO.File.GetLastWriteTime(file.FullPath) < System.IO.File.GetLastWriteTime(destinationFile.FullPath))
			// {
			// 	Debug("Skip protogen for file: {0}", file.FullPath);
			// 	continue;
			// }
			
			var protocArguments = new ProcessSettings()
				.WithArguments(args => args
					.Append("-I=" + sourceProtoDir.FullPath)
					.Append("--cpp_out=" + destinationProtoDir.FullPath)
					.Append(file.FullPath));
			
			var exitCode = StartProcess(protocExe, protocArguments);
			if (exitCode != 0)
			{
				Error("Error processing file {0} to {1}, protoc exit code: {2}",
					file,
					destinationFile,
					exitCode);
			}
		}

		{
			// Legacy code, is still used in 1C
			var file = destinationProtoDir.CombineWithFilePath("BoxList.proto");
			var protocArguments = new ProcessSettings()
				.WithArguments(args => args
					.Append("-I=" + destinationProtoDir.FullPath)
					.Append("--cpp_out=" + destinationProtoDir.FullPath)
					.Append(file.FullPath));
		
			var exitCode = StartProcess(protocExe, protocArguments);
			if (exitCode != 0)
			{
				Error("Error processing file {0}, protoc exit code: {1}", file, exitCode);
			}
		}		
	});
	
//////////////////////////////////////////////////////////////////////
// TASK TARGETS
//////////////////////////////////////////////////////////////////////

Task("Default")
	.IsDependentOn("CMake-Build");

//////////////////////////////////////////////////////////////////////
// EXECUTION
//////////////////////////////////////////////////////////////////////

RunTarget(target);
