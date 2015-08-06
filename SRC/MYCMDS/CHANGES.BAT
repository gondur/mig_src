pushd
call FIXDATE.bat
echo y|y:\map delete n:
subst /d n:
subst n: .
n:
set /r s:\projects\mig\admin\version\%user%.ver
del *.pch *.cfg *.flg /s >&>nul
del mfc\migold.rc)
except (*.sym *.map *.exe mig.* ) dir /sb /a-h /a-d /[d%DateForUp@%TimeForUp] >m:poo
if not %@filedate[m:poo]==%@filedate[s:\transfer\updates\mig\%user.zip] mv s:\transfer\updates\mig\%user.zip s:\transfer\updates\mig\lastver\%user.zip
if exist s:\transfer\updates\mig\%user.zip del s:\transfer\updates\mig\%user.zip
type m:poo
%1 %2
pkzip -exrP s:\transfer\updates\mig\%user @m:poo
cd ..\game
dir /sba-d /[d%DateForUp@%TimeForUp] >s:\transfer\updates\mig\%user.gam
pmail -f m:poo -t rattus -s "Update from %user for Migalley"
popd
subst /d n:
