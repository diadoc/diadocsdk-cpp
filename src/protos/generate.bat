@echo off

echo Generating code from protobuf files...

set proto_rel_path=..\..\..\Proto
set proto_path=%~dp0%proto_rel_path%
pushd .
cd %proto_path%
for /f "delims=" %%a in ('cd') do @set proto_path=%%a
popd

echo Proto files path: %proto_path%
for /R "%proto_path%" %%f in ("*.proto") DO (
	echo Processing %%~ff
 	..\..\protobuf\protoc.exe %%~ff --cpp_out=..\protos --proto_path=%proto_path%
)

echo Done