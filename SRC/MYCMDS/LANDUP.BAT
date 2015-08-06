@echo off
goto l_%1
:l_
echo Parameter 1 should be 1 of:
echo 	NEW		newest landscape
echo 	CURR		newest landscape (same)
echo 	PREV		previous newest landscape
echo 	SAFE		safest landscape
echo 	FROM who	steal off another machine

goto end
/////////////////////
:l_NEW
:l_CURR
start \\jimsbigone\crap\whatever.exe>NUL
copy  \\jimsbigone\landscape\cd_10m.l2\cd_data\currland\*.* \mig\game\landscap\*.*
goto end
/////////////////////
:l_PREV
start \\jimsbigone\share_c\windows\net.exe ver
copy  \\jimsbigone\landscape\cd_10m.l2\cd_data\prevland\*.* \mig\game\landscap\*.*
goto end
/////////////////////
:l_SAFE
copy s:\projects\mig\game\landscap\*.* \mig\game\landscap\*.*
goto end
:l_from
/////////////////////
start \\%2\crap\whatever.exe>NUL
start \\%2\c\windows\net.exe ver
if exist \\%2\share_c\mig\game\landscap\*.dat copy \\%2\share_c\mig\game\landscap\*.* \mig\game\landscap\*.*
if exist \\%2\c\mig\game\landscap\*.dat copy \\%2\c\mig\game\landscap\*.* \mig\game\landscap\*.*
if exist \\%2\share_d\mig\game\landscap\*.dat copy \\%2\share_d\mig\game\landscap\*.* \mig\game\landscap\*.*
goto end




:end
