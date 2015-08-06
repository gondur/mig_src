// new header file...
#define	INTABLE(ename)				\
inline int operator + (ename a,ename b) {return ((int)a+(int)b);}\
inline int operator - (ename a,ename b) {return ((int)a-(int)b);}\
inline int operator * (ename a,ename b) {return ((int)a*(int)b);}\
inline int operator / (ename a,ename b) {return ((int)a/(int)b);}\
inline int operator % (ename a,ename b) {return ((int)a%(int)b);}\
inline int operator & (ename a,ename b) {return ((int)a&(int)b);}\
\
inline int operator + (ename a,int b) {return ((int)a+(int)b);}\
inline int operator - (ename a,int b) {return ((int)a-(int)b);}\
inline int operator * (ename a,int b) {return ((int)a*(int)b);}\
inline int operator / (ename a,int b) {return ((int)a/(int)b);}\
inline int operator % (ename a,int b) {return ((int)a%(int)b);}\
inline int operator & (ename a,int b) {return ((int)a&(int)b);}\
\
inline int operator + (int a,ename b) {return ((int)a+(int)b);}\
inline int operator - (int a,ename b) {return ((int)a-(int)b);}\
inline int operator * (int a,ename b) {return ((int)a*(int)b);}\
inline int operator / (int a,ename b) {return ((int)a/(int)b);}\
inline int operator % (int a,ename b) {return ((int)a%(int)b);}\
inline int operator & (int a,ename b) {return ((int)a&(int)b);}\
\
inline int operator | (ename a,ename b) {return ((int)a|(int)b);}\
inline int operator | (int a,ename b) {return ((int)a|(int)b);}\
inline int operator | (ename a,int b) {return ((int)a|(int)b);}\
\
inline int operator == (ename a,ename b) {return ((int)a==(int)b);}\
inline int operator == (int a,ename b) {return ((int)a==(int)b);}\
inline int operator == (ename a,int b) {return ((int)a==(int)b);}\
\
inline int operator <  (ename a,ename b) {return ((int)a<(int)b);}\
inline int operator << (ename a,ename b) {return ((int)a<<(int)b);}\
inline int operator <= (ename a,ename b) {return ((int)a<=(int)b);}\
inline int operator >  (ename a,ename b) {return ((int)a>(int)b);}\
inline int operator >> (ename a,ename b) {return ((int)a>>(int)b);}\
inline int operator >= (ename a,ename b) {return ((int)a>=(int)b);}\
\
inline int operator <  (ename a,int b) {return ((int)a<(int)b);}\
inline int operator << (ename a,int b) {return ((int)a<<(int)b);}\
inline int operator <= (ename a,int b) {return ((int)a<=(int)b);}\
inline int operator >  (ename a,int b) {return ((int)a>(int)b);}\
inline int operator >> (ename a,int b) {return ((int)a>>(int)b);}\
inline int operator >= (ename a,int b) {return ((int)a>=(int)b);}\
\
inline int operator <  (int a,ename b) {return ((int)a<(int)b);}\
inline int operator << (int a,ename b) {return ((int)a<<(int)b);}\
inline int operator <= (int a,ename b) {return ((int)a<=(int)b);}\
inline int operator >  (int a,ename b) {return ((int)a>(int)b);}\
inline int operator >> (int a,ename b) {return ((int)a>>(int)b);}\
inline int operator >= (int a,ename b) {return ((int)a>=(int)b);}\
\
inline	int	operator+= (int& a,ename b) {return (a+=(int)b);}\
inline	int	operator-= (int& a,ename b) {return (a-=(int)b);}\

