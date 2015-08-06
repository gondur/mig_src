set /r s:\projects\mig\admin\version\%user%.ver
except (obj\*.* tmp\*.* mig.* install.* demo.*) dir /sba-d /a-h %& /[d%DateForUp@%TimeForUp] >m:poo
type m:poo
