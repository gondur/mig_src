:wait
delay 1
if exist \mig\src\bferr.txt goto end
if not exist \mig\src\bfieldsm.fil goto wait
:end
