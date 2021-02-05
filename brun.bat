@echo off

rem Compiler Flags

rem remove from compiler flags for older computers /Wv:18 -MT

set CommonCompilerFlags= /EHsc -MTd -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4456 -FC -Z7 /IC:\z\bin\SDL2-devel-2.0.4-VC\include /IC:\z\bin\SDL2_ttf-2.0.14\include /IC:\z\bin\SDL2_devel_image-2.0.1-VC\include /IC:\z\bin\SDL2_mixer-2.0.1\include /IC:\z\bin\glew\include /IC:\z\bin\allegro-5.0.10-msvc-10.0\include /IC:\z\bin\SFML-2.3.2\include /I"C:\Program Files\Microsoft DirectX SDK (June 2010)\Include"

rem Linker Flags

set CommonLinkerFlags= -incremental:no -opt:ref user32.lib gdi32.lib dxerr.lib d3dx9.lib d3dx10.lib dxguid.lib d3d9.lib comctl32.lib  winmm.lib SDL2.lib SDL2main.lib SDL2_image.lib SDL2_ttf.lib SDL2_mixer.lib opengl32.lib openal32.lib glu32.lib allegro-5.0.10-monolith-md-debug.lib sfml-graphics-d.lib sfml-window-d.lib sfml-system-d.lib sfml-network-d.lib sfml-audio-d.lib /LIBPATH:C:\z\bin\SDL2-devel-2.0.4-VC\lib\x86 /LIBPATH:C:\z\bin\SDL2_ttf-2.0.14\lib\x86 /LIBPATH:C:\z\bin\SDL2_devel_image-2.0.1-VC\lib\x86 /LIBPATH:C:\z\bin\SDL2_mixer-2.0.1\lib\x86 /LIBPATH:C:\z\bin\allegro-5.0.10-msvc-10.0\lib /LIBPATH:C:\z\bin\SFML-2.3.2\lib /LIBPATH:"C:\Program Files\Microsoft DirectX SDK (June 2010)\Lib\x86"

rem build project directory

IF NOT EXIST build mkdir build
pushd build

IF EXIST *.exe del *.exe > NUL 2> NUL
IF EXIST *.pdb del *.pdb > NUL 2> NUL

rem begin compilation

rem RC EXAMPLE
rem rc ../main.rc

cl %CommonCompilerFlags% ../main.cpp c:/z/_MI/Window.cpp c:/z/_MI/LTexture.cpp -Fmmain.map /link %CommonLinkerFlags%

rem RUN EXE

rem runs executable in CONSOLE
IF ERRORLEVEL 0 start "New Window" cmd /c main.exe popd IF NOT popd

rem runs executable in EDITOR
rem main.exe

popd

rem ###########################################################################

rem DLL EXAMPLE
rem cl %CommonCompilerFlags% ../mfile.cpp -Fmmfile.map /LD /link %CommonLinkerFlags% -PDB:mfile_%date:~-4,4%%date:~-10,2%%date:~-7,2%_%time:~3,2%%time:~6,2%.pdb -EXPORT:GameUpdateAndRender
rem cl %CommonCompilerFlags% ../main.cpp mfile.map %CommonLinkerFlags%

@echo on
