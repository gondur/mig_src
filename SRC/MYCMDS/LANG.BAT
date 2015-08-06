goto X_%1
:x_all
for %r in (french german italian spanish) call %0 %r %2
:X_
%0 english %2

:X_english 
:X_french 
:X_german 
:X_italian 
:X_spanish
set bigbuild=
set Lang=%1
if "%#" == "2" set bigbuild=/a

echo y|c:\windows\net use u: \\migalley\mig

call mycmds\newchat.bat
call mycmds\makechat.bat

call mycmds\mergetxt
