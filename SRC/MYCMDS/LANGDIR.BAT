del ..\game\stdprof\*.* /qsy
rd ..\game\stdprof
mkdir ..\game\english
mkdir ..\game\french
mkdir ..\game\german
mkdir ..\game\italian
mkdir ..\game\spanish
mkdir ..\game\english\StdProf
mkdir ..\game\french\StdProf
mkdir ..\game\german\StdProf
mkdir ..\game\italian\StdProf
mkdir ..\game\spanish\StdProf
copy ..\game\english\dir.dir /s ..\game\german
copy ..\game\english\dir.dir /s ..\game\french
copy ..\game\english\dir.dir /s ..\game\italian
copy ..\game\english\dir.dir /s ..\game\spanish
copy u:\game\english ..\game\english /su
copy u:\game\french ..\game\french /su
copy u:\game\german ..\game\german /su
copy u:\game\italian ..\game\italian /su
copy u:\game\spanish ..\game\spanish /su

