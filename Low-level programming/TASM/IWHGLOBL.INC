
;   FILENAME: IWHGLOBL.DEC
;
;   DESCRIPTION: This include file declares all the public symbols used by
;   the WHEREIS program. It also contains some data structure definitions
;   used by the various modules.

; Public symbols

global  LocateString:proc
global  PspAddress:word
global  DisplayPage:byte
global  ParamCount:proc
global  ParamString:proc
global  DisplayErrorMsg:proc
global  FindFiles:proc
global  Terminate:proc
global  FindBytePos:proc
global  FindAndReplace:proc
global  ByteCopy:proc
global  WritePascalString:proc
global  WriteChar:proc
global  SkipSpaces:proc
global  GetASCIIZStrLen:proc
global  ParseFilename:proc
global  WriteASCIIZString:proc
global  FileSpec:byte
global  DeleteChar:proc
global  Drive:byte:5


; Equates

MAX_PATH_LENGTH = 80
