
#include	"bfenum.h"

enum	Process {P_COMBOBOX,P_INT,P_SPIN,P_HOMEBASE,P_TARGET,P_PAINT,P_ALT};
struct	EventProcessor
{
	EnumListNames	enumtype;
	Process	process;
	int		min;
	int		max;
	int		stepsize;
};

struct	GlobalsInfo
	{
		char*			identifier;

		int				text;
		int				help;
		EventProcessor*  processor;
		int				value;

	};
struct GlobalRef;
extern   GlobalRef	BFieldGlobalTable[];
extern   EventProcessor	ShapeProcess;
#include "makebf.h"


