@echo off
goto A_%1
:A_
for %i in (800 1024 1280) call %0 FULLSCR %i
for %i in (1 2) call %0 WATER %i
for %i in (std user) call %0 NOSEART %i
call %0 LOADERART
echo ACTIVEX ARTWORK
set src=u:\artsrc\stills\icons
set dst=..\game\artwork\axart
set dst2=..\game\artwork\axart2

copy /qu %src\redtbt.bmp %dst
copy /qu %src\routes.bmp %dst
copy /qu %src\routes2.bmp %dst
copy /qu %src\routes3.bmp %dst
copy /qu %src\front.bmp %dst
copy /qu %src\front2.bmp %dst
copy /qu %src\front3.bmp %dst
copy /qu %src\smfront.bmp %dst
copy /qu %src\smfront2.bmp %dst
copy /qu %src\smfront3.bmp %dst

copy /qu %src\flight1.bmp %dst
copy /qu %src\flight1d.bmp %dst
copy /qu %src\flight2.bmp %dst
copy /qu %src\flight2d.bmp %dst
copy /qu %src\flight3.bmp %dst
copy /qu %src\flight3d.bmp %dst
copy /qu %src\flight4.bmp %dst
copy /qu %src\flight4d.bmp %dst
copy /qu %src\flight5.bmp %dst
copy /qu %src\flight5d.bmp %dst
copy /qu %src\flight6.bmp %dst
copy /qu %src\flight6d.bmp %dst
copy /qu %src\element1.bmp %dst
copy /qu %src\element2.bmp %dst
copy /qu %src\elemen1d.bmp %dst
copy /qu %src\elemen2d.bmp %dst


copy /qu %src\spindown.bmp %dst
copy /qu %src\spinup.bmp %dst

copy /qu %src\F51_0_3.bmp %dst
copy /qu %src\F51_1_2.bmp %dst
copy /qu %src\F51_2_1.bmp %dst
copy /qu %src\F51_3_0.bmp %dst
copy /qu %src\F86_0_3.bmp %dst
copy /qu %src\F86_1_2.bmp %dst
copy /qu %src\F86_2_1.bmp %dst
copy /qu %src\F86_3_0.bmp %dst
copy /qu %src\arrow.bmp %dst
copy /qu %src\red1.bmp %dst
copy /qu %src\red2.bmp %dst
copy /qu %src\redq1.bmp %dst
copy /qu %src\redq2.bmp %dst
copy /qu %src\blue1.bmp %dst
copy /qu %src\blue2.bmp %dst
copy /qu %src\yellow1.bmp %dst
copy /qu %src\yellow2.bmp %dst
copy /qu %src\green1.bmp %dst
copy /qu %src\green2.bmp %dst
copy /qu %src\tick1.bmp %dst
copy /qu %src\tick2.bmp %dst
copy /qu %src\bye.bmp %dst
copy /qu %src\bye2.bmp %dst
copy /qu %src\large1.bmp %dst
copy /qu %src\large2.bmp %dst
copy /qu %src\large3.bmp %dst
copy /qu %src\large4.bmp %dst
copy /qu %src\button1.bmp %dst
copy /qu %src\button2.bmp %dst
copy /qu %src\b_ac1.bmp %dst
copy /qu %src\b_ac2.bmp %dst
copy /qu %src\b_ac3.bmp %dst
copy /qu %src\b_af1.bmp %dst
copy /qu %src\b_af2.bmp %dst
copy /qu %src\b_af3.bmp %dst
copy /qu %src\b_all1.bmp %dst
copy /qu %src\b_all2.bmp %dst
copy /qu %src\b_all3.bmp %dst
copy /qu %src\b_artie1.bmp %dst
copy /qu %src\b_artie2.bmp %dst
copy /qu %src\b_artie3.bmp %dst
copy /qu %src\b_bridg1.bmp %dst
copy /qu %src\b_bridg2.bmp %dst
copy /qu %src\b_bridg3.bmp %dst
copy /qu %src\b_civil1.bmp %dst
copy /qu %src\b_civil2.bmp %dst
copy /qu %src\b_civil3.bmp %dst
copy /qu %src\b_myrd1.bmp %dst
copy /qu %src\b_myrd2.bmp %dst
copy /qu %src\b_myrd3.bmp %dst
copy /qu %src\b_rail1.bmp %dst
copy /qu %src\b_rail2.bmp %dst
copy /qu %src\b_rail3.bmp %dst
copy /qu %src\b_road1.bmp %dst
copy /qu %src\b_road2.bmp %dst
copy /qu %src\b_road3.bmp %dst
copy /qu %src\b_suply1.bmp %dst
copy /qu %src\b_suply2.bmp %dst
copy /qu %src\b_suply3.bmp %dst
copy /qu %src\b_tank1.bmp %dst
copy /qu %src\b_tank2.bmp %dst
copy /qu %src\b_tank3.bmp %dst
copy /qu %src\b_train1.bmp %dst
copy /qu %src\b_train2.bmp %dst
copy /qu %src\b_train3.bmp %dst
copy /qu %src\b_troop1.bmp %dst
copy /qu %src\b_troop2.bmp %dst
copy /qu %src\b_troop3.bmp %dst
copy /qu %src\b_truck1.bmp %dst
copy /qu %src\b_truck2.bmp %dst
copy /qu %src\b_truck3.bmp %dst
copy /qu %src\combo.bmp %dst
copy /qu %src\ccombo.bmp %dst
copy /qu %src\redbt.bmp %dst
copy /qu %src\dbutt1.bmp %dst
copy /qu %src\dbutt2.bmp %dst
copy /qu %src\forty.bmp %dst
copy /qu %src\forty2.bmp %dst
copy /qu %src\grip.bmp %dst
copy /qu %src\hilite.bmp %dst
copy /qu %src\i_bases.bmp %dst
copy /qu %src\i_bases2.bmp %dst
copy /qu %src\i_close.bmp %dst
copy /qu %src\i_close2.bmp %dst
copy /qu %src\i_cloud2.bmp %dst
copy /qu %src\i_clouds.bmp %dst
copy /qu %src\i_comms1.bmp %dst
copy /qu %src\i_comms2.bmp %dst
copy /qu %src\i_direc2.bmp %dst2
copy /qu %src\i_direct.bmp %dst2
copy /qu %src\i_dirdis.bmp %dst2
copy /qu %src\i_dirdis.bmp %dst2
copy /qu %src\i_dis.bmp %dst
copy /qu %src\i_dis2.bmp %dst
copy /qu %src\i_files1.bmp %dst
copy /qu %src\i_files2.bmp %dst
copy /qu %src\i_frag1.bmp %dst
copy /qu %src\i_frag2.bmp %dst
copy /qu %src\i_fulls2.bmp %dst
copy /qu %src\i_fullsc.bmp %dst
copy /qu %src\i_gap.bmp %dst
copy /qu %src\i_intel2.bmp %dst
copy /qu %src\i_intell.bmp %dst
copy /qu %src\i_misn.bmp %dst
copy /qu %src\i_misn2.bmp %dst
copy /qu %src\i_move1.bmp %dst
copy /qu %src\i_move2.bmp %dst
copy /qu %src\i_overv2.bmp %dst
copy /qu %src\i_overvw.bmp %dst
copy /qu %src\i_playe2.bmp %dst
copy /qu %src\i_player.bmp %dst
copy /qu %src\i_reply1.bmp %dst2
copy /qu %src\i_reply2.bmp %dst2
copy /qu %src\i_repdis.bmp %dst2
copy /qu %src\i_ready1.bmp %dst2
copy /qu %src\i_ready2.bmp %dst2
copy /qu %src\i_resul2.bmp %dst
copy /qu %src\i_result.bmp %dst
copy /qu %src\i_scree2.bmp %dst
copy /qu %src\i_screen.bmp %dst
copy /qu %src\i_squad2.bmp %dst
copy /qu %src\i_squads.bmp %dst
copy /qu %src\i_thumb1.bmp %dst
copy /qu %src\i_thumb2.bmp %dst
copy /qu %src\i_toolb.bmp %dst
copy /qu %src\i_toolb2.bmp %dst
copy /qu %src\i_zm_in1.bmp %dst
copy /qu %src\i_zm_in2.bmp %dst
copy /qu %src\i_zm_ot1.bmp %dst
copy /qu %src\i_zm_ot2.bmp %dst
copy /qu %src\mainwp.bmp %dst
copy /qu %src\mainwp2.bmp %dst
copy /qu %src\mainwp3.bmp %dst
copy /qu %src\mainwp4.bmp %dst
copy /qu %src\mainwp5.bmp %dst
copy /qu %src\n_wpnav1.bmp %dst
copy /qu %src\n_wpnav2.bmp %dst
copy /qu %src\n_wptgt1.bmp %dst
copy /qu %src\n_wptgt2.bmp %dst
copy /qu %src\piltbut1.bmp %dst
copy /qu %src\piltbut2.bmp %dst
copy /qu %src\piltbut3.bmp %dst
copy /qu %src\puckbot.bmp %dst
copy /qu %src\puckhorz.bmp %dst
copy /qu %src\puckleft.bmp %dst
copy /qu %src\puckrght.bmp %dst
copy /qu %src\pucktop.bmp %dst
copy /qu %src\puckvert.bmp %dst
copy /qu %src\radiodn.bmp %dst
copy /qu %src\radioup.bmp %dst
copy /qu %src\radiodnd.bmp %dst
copy /qu %src\radioupd.bmp %dst
copy /qu %src\r_ac1.bmp %dst
copy /qu %src\r_ac2.bmp %dst
copy /qu %src\r_ac3.bmp %dst
copy /qu %src\r_af1.bmp %dst
copy /qu %src\r_af2.bmp %dst
copy /qu %src\r_af3.bmp %dst
copy /qu %src\r_all1.bmp %dst
copy /qu %src\r_all2.bmp %dst
copy /qu %src\r_all3.bmp %dst
copy /qu %src\r_artie1.bmp %dst
copy /qu %src\r_artie2.bmp %dst
copy /qu %src\r_artie3.bmp %dst
copy /qu %src\r_bridg1.bmp %dst
copy /qu %src\r_bridg2.bmp %dst
copy /qu %src\r_bridg3.bmp %dst
copy /qu %src\r_civil1.bmp %dst
copy /qu %src\r_civil2.bmp %dst
copy /qu %src\r_civil3.bmp %dst
copy /qu %src\dead1.bmp %dst2
copy /qu %src\dead2.bmp %dst2
copy /qu %src\dead3.bmp %dst2
copy /qu %src\r_myrd1.bmp %dst
copy /qu %src\r_myrd2.bmp %dst
copy /qu %src\r_myrd3.bmp %dst
copy /qu %src\r_rail1.bmp %dst
copy /qu %src\r_rail2.bmp %dst
copy /qu %src\r_rail3.bmp %dst
copy /qu %src\r_road1.bmp %dst
copy /qu %src\r_road2.bmp %dst
copy /qu %src\r_road3.bmp %dst
copy /qu %src\r_suply1.bmp %dst
copy /qu %src\r_suply2.bmp %dst
copy /qu %src\r_suply3.bmp %dst
copy /qu %src\r_tank1.bmp %dst
copy /qu %src\r_tank2.bmp %dst
copy /qu %src\r_tank3.bmp %dst
copy /qu %src\r_train1.bmp %dst
copy /qu %src\r_train2.bmp %dst
copy /qu %src\r_train3.bmp %dst
copy /qu %src\r_troop1.bmp %dst
copy /qu %src\r_troop2.bmp %dst
copy /qu %src\r_troop3.bmp %dst
copy /qu %src\r_truck1.bmp %dst
copy /qu %src\r_truck2.bmp %dst
copy /qu %src\r_truck3.bmp %dst
copy /qu %src\scrlbutd.bmp %dst
copy /qu %src\scrlbutu.bmp %dst
copy /qu %src\scrlhorz.bmp %dst
copy /qu %src\scrlvert.bmp %dst
copy /qu %src\subwp.bmp %dst
copy /qu %src\subwp2.bmp %dst
copy /qu %src\subwp3.bmp %dst
copy /qu %src\subwp4.bmp %dst
copy /qu %src\subwp5.bmp %dst
copy /qu %src\tickbox1.bmp %dst
copy /qu %src\tickbox2.bmp %dst
copy /qu %src\tickbox3.bmp %dst
copy /qu %src\titleb.bmp %dst
copy /qu %src\toolside.bmp %dst
copy /qu %src\tooltop.bmp %dst
copy /qu %src\unhilite.bmp %dst
copy /qu %src\piltbut3.bmp ..\game\artwork\axart 
copy /qu %src\radioup.bmp ..\game\artwork\axart 

goto end
:A_FULLSCR
set src=u:\artsrc\stills\finish\%2
set trg=..\game\artwork\dial%2
echo FRONT END SCREENS %2

copy /qu %src\autopilt.bmp 	%trg 
copy /qu %src\d3disply.bmp 	%trg 
copy /qu %src\flghtcon.bmp 	%trg 
copy /qu %src\gamsetup.bmp 	%trg 
copy /qu %src\quickmis.bmp 	%trg 
copy /qu %src\soundset.bmp	%trg 
copy /qu %src\title.bmp 		%trg 
copy /qu %src\repscrn.bmp 	%trg 
copy /qu %src\viewer00.bmp 	%trg 
copy /qu %src\campaign.bmp 	%trg 
copy /qu %src\locker.bmp 	%trg 
copy /qu %src\ready.bmp 	%trg 
copy /qu %src\paintshp.bmp 	%trg 
copy /qu %src\loadsave.bmp 	%trg 

goto end
:A_WATER
set src=u:artsrc\stills\capfin
set trg=..\game\artwork\water%2
echo MAP DIALOGUE ART %2

copy /qu %src\warn.bmp 		%trg
copy /qu %src\resource.bmp	%trg 
copy /qu %src\f86sqdn.bmp	%trg 
copy /qu %src\f51sqdn.bmp	%trg 
copy /qu %src\f84sqdn.bmp	%trg 
copy /qu %src\f80sqdn.bmp	%trg 
copy /qu %src\pilots.bmp	%trg 
copy /qu %src\losses.bmp	%trg 
copy /qu %src\tactics.bmp	%trg 
copy /qu %src\cloud1.bmp	%trg 
copy /qu %src\cloud2.bmp	%trg 
copy /qu %src\cloud3.bmp	%trg 
copy /qu %src\cloud4.bmp	%trg 
copy /qu %src\dis.bmp		%trg 
copy /qu %src\directs.bmp	%trg 
copy /qu %src\choke.bmp		%trg 
copy /qu %src\traffic.bmp	%trg 
copy /qu %src\supply.bmp	%trg 
copy /qu %src\airfield.bmp	%trg 
copy /qu %src\army.bmp		%trg 
copy /qu %src\mig.bmp		%trg 
copy /qu %src\library.bmp	%trg 
copy /qu %src\requests.bmp	%trg 
copy /qu %src\misnfldr.bmp	%trg 
copy /qu %src\profile.bmp	%trg 
copy /qu %src\route.bmp		%trg 
copy /qu %src\migcap.bmp	%trg 
copy /qu %src\strike.bmp	%trg 
copy /qu %src\aaa.bmp		%trg 
copy /qu %src\aimpoint.bmp	%trg 
copy /qu %src\payload.bmp	%trg 
copy /qu %src\misnrslt.bmp	%trg 
copy /qu %src\player.bmp	%trg 
copy /qu %src\waypoint.bmp	%trg 
copy /qu %src\congrats.bmp	%trg 
copy /qu %src\overview.bmp	%trg 

goto end

:A_NOSEART
for %i in (1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16) copy /qu u:\artsrc\stills\nose\%2%%i.bmp ..\game\artwork\nose%2\nose%i.bmp
goto end

:A_LOADERART
set src=u:\artsrc\stills\finish\800
set trg=..\game\artwork
echo LOADERART
copy /q %src\loadb.bmp %trg\water2\contr2.bmp

copy /q %src\load.bmp %trg\water2\photo.bmp
:end


