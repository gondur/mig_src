set /r s:\projects\mig\admin\%user%.ver
except (obj\*.* tmp\*.* *.log *.cfg *.sym *.map mig.*) dir /sba-d /a-h /[d%DateForUp@%TimeForUp]

