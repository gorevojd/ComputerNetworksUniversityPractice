@echo off

set CommonCompilerFlags= -Zi -MTd

set CommonLinkerFlags= -nologo -opt:ref
set CommonLinkerFlags= user32.lib kernel32.lib WS2_32.lib %CommonLinkerFlags%

cl %CommonCompilerFlags% ../Code/
