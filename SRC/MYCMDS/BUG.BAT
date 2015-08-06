mode mono
iff "%1"=="" then
s:\watdeb\wd /i=%user%.dbg wmig.exe %&
else
s:\watcom\binnt\wd /i=%user%.db9 wmig.exe %&
endiff
mode co80
50
