#addin "Cake.CMake"
using Cake.Common.Diagnostics;
using System.Text.RegularExpressions;

var target = Argument("target", "Default");
var configuration = Argument("configuration", "Release");
var generator = Argument("generator", "");
var toolset = Argument("toolset", "");

var tempParts = new [] {
	"tmp",
	SimplifyGeneratorName(generator),
	toolset,
}.Where(x => !string.IsNullOrEmpty(x));

var zipFileParts = new [] {
	"diadocsdk-cpp",
	SimplifyGeneratorName(generator),
	toolset,
}.Where(x => !string.IsNullOrEmpty(x));

var buildDir = new DirectoryPath(string.Join("/", tempParts)).MakeAbsolute(Context.Environment);
var toolchainName = string.Join("-", tempParts.Skip(1));
var zipFileName = buildDir.CombineWithFilePath(string.Join("-", zipFileParts) + ".zip");
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
		EnsureDirectoryExists(buildDir);
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
	
Task("PrepareBinaries")
	.IsDependentOn("CMake-Build")
	.Does(() =>
	{
		CopyDirectory("./third-party/include", buildDir.Combine(configuration + "/include"));
		CopyFilesRelative(GetFiles("./src/**/*.h"), "./src", buildDir.Combine(configuration).Combine("include").Combine("DiadocApi"));
		CopyDirectory(buildDir.Combine("bin/" + configuration), buildDir.Combine(configuration + "/bin"));
		CopyDirectory(buildDir.Combine("lib/" + configuration), buildDir.Combine(configuration + "/lib"));
		Zip(buildDir.Combine(configuration), zipFileName);
	});
	
Task("PublishArtifactsToAppVeyor")
	.IsDependentOn("PrepareBinaries")
	.WithCriteria(x => BuildSystem.IsRunningOnAppVeyor)
	.Does(() =>
	{
		AppVeyor.UploadArtifact(zipFileName);
	});
	
//////////////////////////////////////////////////////////////////////
// TASK TARGETS
//////////////////////////////////////////////////////////////////////

Task("Default")
	.IsDependentOn("AppVeyor");
	
Task("AppVeyor")
	.IsDependentOn("PrepareBinaries")
	.IsDependentOn("PublishArtifactsToAppVeyor");

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

	foreach (var file in files)
	{
		protocArguments.WithArguments(args => args.Append(file.FullPath));
	}
	
	var exitCode = StartProcess(protocExe, protocArguments);
	if (exitCode != 0)
	{
		throw new Exception(string.Format("Error processing proto files, protoc exit code: {0} ({1})", exitCode, protocArguments));
	}
}

public void CopyFilesRelative(IEnumerable<FilePath> files, DirectoryPath sourceDir, DirectoryPath destinationDir)
{
	sourceDir = sourceDir.MakeAbsolute(Context.Environment);
	foreach (var file in files)
	{
		var relativeFile = sourceDir.GetRelativePath(file);
		var destinationFile = destinationDir.CombineWithFilePath(relativeFile);
		EnsureDirectoryExists(destinationFile.GetDirectory());
		CopyFile(file, destinationFile);
	}
}

static string SimplifyGeneratorName(string generator)
{
	switch (generator)
	{
		case "Visual Studio 14 2015": return "vs2015";
		case "Visual Studio 14 2015 Win64": return "vs2015-x64";
		case "Visual Studio 14 2015 ARM": return "vs2015-arm";
		case "Visual Studio 12 2013": return "vs2013";
		case "Visual Studio 12 2013 Win64": return "vs2013-x64";
		case "Visual Studio 12 2013 ARM": return "vs2013-arm";
		case "Visual Studio 11 2012": return "vs2012";
		case "Visual Studio 11 2012 Win64": return "vs2012-x64";
		case "Visual Studio 11 2012 ARM": return "vs2012-arm";
		case "Visual Studio 10 2010": return "vs2010";
		case "Visual Studio 10 2010 Win64": return "vs2010-x64";
		case "Visual Studio 10 2010 IA64": return "vs2010-ia64";
		case "Visual Studio 9 2008": return "vs2008";
		case "Visual Studio 9 2008 Win64": return "vs2008-x64";
		case "Visual Studio 9 2005": return "vs2005";
		case "Visual Studio 9 2005 Win64": return "vs2005-x64";
        case "Visual Studio 7 .NET 2003": return "vs2003";
        case "Visual Studio 7": return "vs2002";
        case "Visual Studio 6": return "msvs6";
		default: return generator;
	}
}
