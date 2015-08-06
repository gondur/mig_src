cd ..
tasm /t /ishapes /ks255 shapes\shpgrp\%1%.shp,m:\shapes\%1%.obj
tlink /t /x m:\shapes\%1%.obj,m:\shapes\%1%.bin
copy m:\shapes\%1%.bin game\shpbin\%1%.com
cd -
