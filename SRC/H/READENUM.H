#ifndef	READENUM_Included
#define	READENUM_Included

class ifstream;

class	EnumCtrl
{
static    void	Strcpy(char*,char*);
public:
	enum	{enumeltnamelen=40};


struct enumlinkelt
{	//24 bytes long
	//better if <2/3 full.
	int				value;
	char			name[enumeltnamelen];
	enumlinkelt*	next;
	~enumlinkelt()	{delete next;}
	enumlinkelt()	{next=NULL;}
};

struct	enumarrelt
{	//16 bytes long
	//faster to access - better if>2/3 full
	char	name[enumeltnamelen];
	static    void	strcpy(char*,char*);
};

int	min,max,sillymax;
	enumlinkelt*	links;
	enumarrelt*		arr;
public:
	EnumCtrl();
	~EnumCtrl();
	Bool	Add(int i,char* s);
	char*	Translate(int i);
	int		Translate(char* s);
	Bool	Optimise(int breakevenpercentutilised=50);
	void	readenumfromfile(ifstream& f);
	void	readconstfromfile(ifstream& f);
	int	Min()	{return min;}
	int	Max()	{return max;}

};

class	EnumStuff
{
static    void	Strcpy(char*,char*);
	char		fnames[30][40];
	char		enumnames[30][40];
	static		char	*listcmpnames[30];
	static 		int		listcmp2listname[30];
	int			enumname2listname[30];
	void	readfilelist(char*);
	void	readfilesfromlist();
	void	EnumStuff::readenumlist(char* name);

public:

public:
	char		listnames[30][40];
	static	EnumCtrl	listentries[30];
	enum	AvailEnums {};
	void	readenums();
	#ifdef	BFENUM_Included
	friend	EnumCtrl&	GetList(EnumListNames i);
	#endif
   	void	convertstrings(char*keyword,char*leadchars,EnumCtrl& tokenlist,char*fname,int newentry,int tokenentry);
static    void	savestrings(char* pre,char* mid,char* post,EnumCtrl& tokenlist,char*fname,EnumCtrl& textlist);
};

	#ifdef	BFENUM_Included
inline	EnumCtrl& GetList(EnumListNames i)
{
	return  EnumStuff::listentries[EnumStuff::listcmp2listname[i]];
}
	#endif
                                       
extern	EnumStuff	IEnumStuff;

#endif
