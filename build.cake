#addin "Cake.CMake"
using Cake.Common.Diagnostics;
using System.Text.RegularExpressions;

var target = Argument("target", "Default");
var configuration = Argument("configuration", "Release");
var generator = Argument("generator", "");
var toolset = Argument("toolset", "");

var tempParts = new [] {
	"tmp",
	generator,
	toolset,
}.Where(x => !string.IsNullOrEmpty(x));
var buildDir = new DirectoryPath(string.Join(".", tempParts)).MakeAbsolute(Context.Environment);
var protocExe = buildDir.CombineWithFilePath(string.Format("bin/{0}/protoc.exe", configuration));

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
			OutputPath = buildDir,
			Generator = generator,
			Toolset = toolset,
		};
		CMake("./", settings);
	});
	
Task("CMake-Build-ProtoC")
	.IsDependentOn("CMake-Generate")
	.Does(() =>
	{
		var cmakeBuildSettings = GetBuildCMakeSettings()
			.WithArguments(args => args.AppendSwitch("--target", "protoc"));
				
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
		var cmakeBuildSettings = GetBuildCMakeSettings();
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

		var protoFiles = GetFiles("./proto/**/*.proto");
		CompileProtoFiles(protoFiles, sourceProtoDir, destinationProtoDir);

		// Legacy code, is still used in 1C
		var boxListFile = destinationProtoDir.CombineWithFilePath("BoxList.proto");
		CompileProtoFiles(new [] { boxListFile }, destinationProtoDir, destinationProtoDir);
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

//////////////////////////////////////////////////////////////////////
// HELPERS
//////////////////////////////////////////////////////////////////////

public ProcessSettings GetBuildCMakeSettings()
{
	var cmakeBuildSettings = new ProcessSettings()
		.WithArguments(x => x
			.AppendSwitchQuoted("--build", buildDir.FullPath)
			.AppendSwitch("--config", configuration));
			
	return cmakeBuildSettings;
}

public void CompileProtoFiles(IEnumerable<FilePath> files, DirectoryPath sourceProtoDir, DirectoryPath destinationProtoDir)
{
	var protocArguments = new ProcessSettings()
		.WithArguments(args => args
			.Append("-I=" + sourceProtoDir.FullPath)
			.Append("--cpp_out=" + destinationProtoDir.FullPath));

	var dirtyFiles = files.Where(file => {
		var relativeFile = sourceProtoDir.GetRelativePath(file);
		var destinationFileHeader = destinationProtoDir.CombineWithFilePath(relativeFile.ChangeExtension("pb.h"));
		var destinationFileSource = destinationProtoDir.CombineWithFilePath(relativeFile.ChangeExtension("pb.cc"));
		if (!NeedUpdateFile(file, destinationFileHeader) &&
			!NeedUpdateFile(file, destinationFileSource))
		{
			Debug("Skip protoc for file: {0}", file.FullPath);
			return false;
		}
		return true;
	}).ToArray();
	
	if (dirtyFiles.Length == 0)
	{
		Information("All files are up to date");
		return;
	}
	
	foreach (var file in dirtyFiles)
	{
		protocArguments.WithArguments(args => args.Append(file.FullPath));
	}
	
	var exitCode = StartProcess(protocExe, protocArguments);
	if (exitCode != 0)
	{
		Error("Error processing proto files, protoc exit code: {0} ({1})", exitCode, protocArguments);
	}
}

public bool NeedUpdateFile(FilePath file, FilePath destinationFile)
{
	return !(FileExists(destinationFile)
		&& System.IO.File.GetLastWriteTime(file.FullPath) < System.IO.File.GetLastWriteTime(destinationFile.FullPath));
}
