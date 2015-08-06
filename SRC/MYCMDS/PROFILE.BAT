@echo off
if "%1"=="" goto usage
set trg=
if "%1"=="upload" set trg=u:\game\
if "%1"=="spread" set trg=..\game\

if "%trg"=="" goto usage

if "%1"=="spread" goto bypassenglish

copy /q "..\game\english\stdprof\Alpha Strike.prf"			"%trg%english\stdprof\Alpha Strike.prf"
copy /q "..\game\english\stdprof\Armed Reconn.prf"			"%trg%english\stdprof\Armed Reconn.prf"
copy /q "..\game\english\stdprof\BARCAP.PRF"				"%trg%english\stdprof\BARCAP.PRF"
copy /q "..\game\english\stdprof\Close Air Support.prf"		"%trg%english\stdprof\Close Air Support.prf"
copy /q "..\game\english\stdprof\Crack 'n' Burn.prf"		"%trg%english\stdprof\Crack 'n' Burn.prf"
copy /q "..\game\english\stdprof\Fighter Bomber Strike.prf"	"%trg%english\stdprof\Fighter Bomber Strike.prf"
copy /q "..\game\english\stdprof\Medium Bomber Strike.prf"	"%trg%english\stdprof\Medium Bomber Strike.prf"
copy /q "..\game\english\stdprof\Minimum Strike.prf"		"%trg%english\stdprof\Minimum Strike.prf"
copy /q "..\game\english\stdprof\Napalm Strike.prf"			"%trg%english\stdprof\Napalm Strike.prf"
copy /q "..\game\english\stdprof\dir.dir"					"%trg%english\stdprof\dir.dir"

copy /q "..\game\english\stdprof\ALPHASTR.PRD"			"%trg%english\stdprof\"ALPHASTR.PRD"
copy /q "..\game\english\stdprof\ARCONN.PRD"  			"%trg%english\stdprof\"ARCONN.PRD"
copy /q "..\game\english\stdprof\BARCAP.PRD"  			"%trg%english\stdprof\"BARCAP.PRD"
copy /q "..\game\english\stdprof\CAS.PRD"     			"%trg%english\stdprof\"CAS.PRD"
copy /q "..\game\english\stdprof\CASPUSAN.PRD"			"%trg%english\stdprof\"CASPUSAN.PRD"
copy /q "..\game\english\stdprof\CRACK.PRD"   			"%trg%english\stdprof\"CRACK.PRD"
copy /q "..\game\english\stdprof\FBSTRIKE.PRD"			"%trg%english\stdprof\"FBSTRIKE.PRD"
copy /q "..\game\english\stdprof\MBSTRIKE.PRD"			"%trg%english\stdprof\"MBSTRIKE.PRD"
copy /q "..\game\english\stdprof\NAPALM.PRD"  			"%trg%english\stdprof\"NAPALM.PRD"
copy /q "..\game\english\stdprof\c1m1.PRD"  			"%trg%english\stdprof\"c1m1.PRD"
copy /q "..\game\english\stdprof\c1m3.PRD"  			"%trg%english\stdprof\"c1m3.PRD"

:bypassenglish
copy /q "..\game\english\stdprof\Alpha Strike.prf"		"%trg%french\stdprof\Frappe Alpha.prf"
copy /q "..\game\english\stdprof\Armed Reconn.prf"		"%trg%french\stdprof\Reconn. arm‚e.prf"
copy /q "..\game\english\stdprof\BARCAP.PRF"				"%trg%french\stdprof\BARCAP.PRF"
copy /q "..\game\english\stdprof\Close Air Support.prf"	"%trg%french\stdprof\Soutien a‚rien rapproch‚.prf"
copy /q "..\game\english\stdprof\Crack 'n' Burn.prf"		"%trg%french\stdprof\D‚truire br–ler.prf"
copy /q "..\game\english\stdprof\Fighter Bomber Strike.prf"	"%trg%french\stdprof\Frappe chasseurs-bombardiers.prf"
copy /q "..\game\english\stdprof\Medium Bomber Strike.prf"	"%trg%french\stdprof\Frappe bombardiers moyens.prf"
copy /q "..\game\english\stdprof\Minimum Strike.prf"		"%trg%french\stdprof\Frappe minimum.prf"
copy /q "..\game\english\stdprof\Napalm Strike.prf"		"%trg%french\stdprof\Frappe au napalm.prf"
copy /q "..\game\english\stdprof\dir.dir"					"%trg%french\stdprof\dir.dir"

copy /q "..\game\english\stdprof\ALPHASTR.PRD"			"%trg%french\stdprof\"ALPHASTR.PRD"
copy /q "..\game\english\stdprof\ARCONN.PRD"  			"%trg%french\stdprof\"ARCONN.PRD"
copy /q "..\game\english\stdprof\BARCAP.PRD"  			"%trg%french\stdprof\"BARCAP.PRD"
copy /q "..\game\english\stdprof\CAS.PRD"     			"%trg%french\stdprof\"CAS.PRD"
copy /q "..\game\english\stdprof\CASPUSAN.PRD"			"%trg%french\stdprof\"CASPUSAN.PRD"
copy /q "..\game\english\stdprof\CRACK.PRD"   			"%trg%french\stdprof\"CRACK.PRD"
copy /q "..\game\english\stdprof\FBSTRIKE.PRD"			"%trg%french\stdprof\"FBSTRIKE.PRD"
copy /q "..\game\english\stdprof\MBSTRIKE.PRD"			"%trg%french\stdprof\"MBSTRIKE.PRD"
copy /q "..\game\english\stdprof\NAPALM.PRD"  			"%trg%french\stdprof\"NAPALM.PRD"
copy /q "..\game\english\stdprof\c1m1.PRD"  			"%trg%french\stdprof\"c1m1.PRD"
copy /q "..\game\english\stdprof\c1m3.PRD"  			"%trg%french\stdprof\"c1m3.PRD"

copy /q "..\game\english\stdprof\Alpha Strike.prf"		"%trg%German\stdprof\Alpha-Angriff.prf"
copy /q "..\game\english\stdprof\Armed Reconn.prf"		"%trg%German\stdprof\Abschirmpatrouille.prf"
copy /q "..\game\english\stdprof\BARCAP.PRF"				"%trg%German\stdprof\Bewaffnete Aufkl„rung.prf"
copy /q "..\game\english\stdprof\Close Air Support.prf"	"%trg%German\stdprof\Crack 'n' Burn.prf"
copy /q "..\game\english\stdprof\Crack 'n' Burn.prf"		"%trg%German\stdprof\Geleitflugeins„tze.prf"
copy /q "..\game\english\stdprof\Fighter Bomber Strike.prf"	"%trg%German\stdprof\Kampfbomberangriff.prf"
copy /q "..\game\english\stdprof\Medium Bomber Strike.prf"	"%trg%German\stdprof\Minimumangriff.prf"
copy /q "..\game\english\stdprof\Minimum Strike.prf"		"%trg%German\stdprof\Mittelstreckenbomberangriff.prf"
copy /q "..\game\english\stdprof\Napalm Strike.prf"		"%trg%German\stdprof\Napalmangriff.prf"
copy /q "..\game\english\stdprof\dir.dir"					"%trg%german\stdprof\dir.dir"

copy /q "..\game\english\stdprof\ALPHASTR.PRD"			"%trg%german\stdprof\"ALPHASTR.PRD"
copy /q "..\game\english\stdprof\ARCONN.PRD"  			"%trg%german\stdprof\"ARCONN.PRD"
copy /q "..\game\english\stdprof\BARCAP.PRD"  			"%trg%german\stdprof\"BARCAP.PRD"
copy /q "..\game\english\stdprof\CAS.PRD"     			"%trg%german\stdprof\"CAS.PRD"
copy /q "..\game\english\stdprof\CASPUSAN.PRD"			"%trg%german\stdprof\"CASPUSAN.PRD"
copy /q "..\game\english\stdprof\CRACK.PRD"   			"%trg%german\stdprof\"CRACK.PRD"
copy /q "..\game\english\stdprof\FBSTRIKE.PRD"			"%trg%german\stdprof\"FBSTRIKE.PRD"
copy /q "..\game\english\stdprof\MBSTRIKE.PRD"			"%trg%german\stdprof\"MBSTRIKE.PRD"
copy /q "..\game\english\stdprof\NAPALM.PRD"  			"%trg%german\stdprof\"NAPALM.PRD"
copy /q "..\game\english\stdprof\c1m1.PRD"  			"%trg%german\stdprof\"c1m1.PRD"
copy /q "..\game\english\stdprof\c1m3.PRD"  			"%trg%german\stdprof\"c1m3.PRD"


copy /q "..\game\english\stdprof\Alpha Strike.prf"		"%trg%italian\stdprof\Attacco Alpha.prf"
copy /q "..\game\english\stdprof\Armed Reconn.prf"		"%trg%italian\stdprof\Ricogn. armata.prf"
copy /q "..\game\english\stdprof\BARCAP.PRF"				"%trg%italian\stdprof\PS.PRF"
copy /q "..\game\english\stdprof\Close Air Support.prf"	"%trg%italian\stdprof\Supp. aereo ravv.prf"
copy /q "..\game\english\stdprof\Crack 'n' Burn.prf"		"%trg%italian\stdprof\Rompi e brucia.prf"
copy /q "..\game\english\stdprof\Fighter Bomber Strike.prf"	"%trg%italian\stdprof\Attacco cacciabomb.prf"
copy /q "..\game\english\stdprof\Medium Bomber Strike.prf"	"%trg%italian\stdprof\Attacco bomb. medio.prf"
copy /q "..\game\english\stdprof\Minimum Strike.prf"		"%trg%italian\stdprof\Attacco minimo.prf"
copy /q "..\game\english\stdprof\Napalm Strike.prf"		"%trg%italian\stdprof\Attacco Napalm.prf"
copy /q "..\game\english\stdprof\dir.dir"					"%trg%italian\stdprof\dir.dir"

copy /q "..\game\english\stdprof\ALPHASTR.PRD"			"%trg%italian\stdprof\"ALPHASTR.PRD"
copy /q "..\game\english\stdprof\ARCONN.PRD"  			"%trg%italian\stdprof\"ARCONN.PRD"
copy /q "..\game\english\stdprof\BARCAP.PRD"  			"%trg%italian\stdprof\"BARCAP.PRD"
copy /q "..\game\english\stdprof\CAS.PRD"     			"%trg%italian\stdprof\"CAS.PRD"
copy /q "..\game\english\stdprof\CASPUSAN.PRD"			"%trg%italian\stdprof\"CASPUSAN.PRD"
copy /q "..\game\english\stdprof\CRACK.PRD"   			"%trg%italian\stdprof\"CRACK.PRD"
copy /q "..\game\english\stdprof\FBSTRIKE.PRD"			"%trg%italian\stdprof\"FBSTRIKE.PRD"
copy /q "..\game\english\stdprof\MBSTRIKE.PRD"			"%trg%italian\stdprof\"MBSTRIKE.PRD"
copy /q "..\game\english\stdprof\NAPALM.PRD"  			"%trg%italian\stdprof\"NAPALM.PRD"
copy /q "..\game\english\stdprof\c1m1.PRD"  			"%trg%italian\stdprof\"c1m1.PRD"
copy /q "..\game\english\stdprof\c1m3.PRD"  			"%trg%italian\stdprof\"c1m3.PRD"


copy /q "..\game\english\stdprof\Alpha Strike.prf"		"%trg%spanish\stdprof\Ataque Alfa.prf.prf"
copy /q "..\game\english\stdprof\Armed Reconn.prf"		"%trg%spanish\stdprof\Recon Armado.prf"
copy /q "..\game\english\stdprof\BARCAP.PRF"				"%trg%spanish\stdprof\BARCAP.PRF"
copy /q "..\game\english\stdprof\Close Air Support.prf"	"%trg%spanish\stdprof\Apoyo aereo cercano.prf"
copy /q "..\game\english\stdprof\Crack 'n' Burn.prf"		"%trg%spanish\stdprof\Ataque y Destruccion.prf"
copy /q "..\game\english\stdprof\Fighter Bomber Strike.prf"	"%trg%spanish\stdprof\Ataque Caza Bombardero.prf"
copy /q "..\game\english\stdprof\Medium Bomber Strike.prf"	"%trg%spanish\stdprof\Ataque Bombardero Medio.prf"
copy /q "..\game\english\stdprof\Minimum Strike.prf"		"%trg%spanish\stdprof\Ataque Limitado.prf"
copy /q "..\game\english\stdprof\Napalm Strike.prf"		"%trg%spanish\stdprof\Ataque Napalm.prf"
copy /q "..\game\english\stdprof\dir.dir"					"%trg%spanish\stdprof\dir.dir"

copy /q "..\game\english\stdprof\ALPHASTR.PRD"			"%trg%spanish\stdprof\"ALPHASTR.PRD"
copy /q "..\game\english\stdprof\ARCONN.PRD"  			"%trg%spanish\stdprof\"ARCONN.PRD"
copy /q "..\game\english\stdprof\BARCAP.PRD"  			"%trg%spanish\stdprof\"BARCAP.PRD"
copy /q "..\game\english\stdprof\CAS.PRD"     			"%trg%spanish\stdprof\"CAS.PRD"
copy /q "..\game\english\stdprof\CASPUSAN.PRD"			"%trg%spanish\stdprof\"CASPUSAN.PRD"
copy /q "..\game\english\stdprof\CRACK.PRD"   			"%trg%spanish\stdprof\"CRACK.PRD"
copy /q "..\game\english\stdprof\FBSTRIKE.PRD"			"%trg%spanish\stdprof\"FBSTRIKE.PRD"
copy /q "..\game\english\stdprof\MBSTRIKE.PRD"			"%trg%spanish\stdprof\"MBSTRIKE.PRD"
copy /q "..\game\english\stdprof\NAPALM.PRD"  			"%trg%spanish\stdprof\"NAPALM.PRD"
copy /q "..\game\english\stdprof\c1m1.PRD"  			"%trg%spanish\stdprof\"c1m1.PRD"
copy /q "..\game\english\stdprof\c1m3.PRD"  			"%trg%spanish\stdprof\"c1m3.PRD"


quit
:usage
Echo Profile upload 
echo 	will load all the profiles to the network
echo Profile spread
echo 	will spread the english profiles to all other langauges
echo	and keep their names
