copy /qu s:\projects\mig\music\musichi\field1.wav ..\game\samples
copy /qu s:\projects\mig\music\musichi\field2.wav ..\game\samples

copy s:\projects\mig\music\fieldsnr.sf2 ..\game\music

copy s:\projects\mig\music\wavetabh.txt ..\game\music
wavelib ..\game\music\wavetabh.txt

rem copy s:\projects\mig\music\wavetabl.txt .
rem wavelib wavetabl.txt
rem delete wavetabl.txt

copy /qu s:\projects\mig\music\musichi\*.xmi ..\game\music
copy /qu s:\projects\mig\music\musicmed\*.xmi ..\game\musicmed
copy /qu s:\projects\mig\music\musiclo\*.xmi ..\game\musiclow
copy /qu s:\projects\mig\music\musiclo\*.wav ..\game\musiclow
