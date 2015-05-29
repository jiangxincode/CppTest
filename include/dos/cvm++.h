
/* cvm.h */

#define	NULL	0

/*math.h*/

int abs (int x);
float sin (float x);
float cos (float x);
float tan (float x);
float sqrt (float x);
void srand (int seed);
int rand();
char * itoa( int value, char *string, int radix );
char * ftoa( float value, char *string);
int atoi( char *string );
float atof( char *string );



/*string.h*/

int isalnum (int ch);
int isalpha (int ch);
int iscntrl (int ch);
int isdigit (int ch);
int isgraph (int ch);
int islower (int ch);
int isprint (int ch);
int ispunct (int ch);
int isspace (int ch);
int isupper (int ch);
int isxdigit (int ch);
char * strcat (char * str1, char * str2);
char * strchr (char * str, int ch);
int strcmp (char * str1, char * str2);
char * strcpy (char * str1, char * str2);
unsigned int strlen (char * str);
char * strstr (char * str1, char * str2);
int tolower (int ch);
int toupper (int ch);


/*stdlib.h*/

void * calloc (unsigned n, unsigned size);
void free (void *p);
void * malloc (unsigned size);
void * realloc (void * p, unsigned size);

/*stdio.h*/

#define	SEEK_END	2
#define	SEEK_CUR	1
#define	SEEK_SET	0


typedef int FILE;

int putchar (char ch);
int puts (char * str);
char *gets (char *buffer);
int getchar (void);

int fclose (FILE * fp);
int feof (FILE * fp);
FILE * fopen (char * filename, char * mode);
int fread (char * pt, unsigned size, unsigned n, FILE * fp);
long fseek (FILE * fp, long offset, int base);
long ftell (FILE * fp);
int fwrite (char * ptr, unsigned size, unsigned n, FILE * fp);

/**game**/

#define	KEY_UP		38
#define	KEY_DOWN	40
#define	KEY_LEFT	37
#define	KEY_RIGHT	39
#define	KEY_SPACE	32
#define	KEY_ESCAPE	27
#define	KEY_ENTER	13

#define	FONT_12SONG		0
#define	FONT_12KAI		1
#define	FONT_12HEI		2
#define	FONT_16SONG		3
#define	FONT_16KAI		4
#define	FONT_16HEI		5
#define	FONT_24SONG		6
#define	FONT_24KAI		7
#define	FONT_24HEI		8

#define	TRANSPARENT		1
#define	OPAQUE			2

#define	ENV_SIM			0
#define	ENV_9288		9288
#define	ENV_9188		9188
#define	ENV_9288T		9287
#define	ENV_9288S		9286

int CreatePage ();
void DeletePage (int page);
int LoadRes (char *file, int ID);
void FreeRes (int res);
void ShowPic (int page, int pic, int dx, int dy, int w, int h, int x, int y, int mode);
void FlipPage (int page);
void BitBltPage (int dest, int src);
void StretchBltPage (int x, int y, int dest, int src);
void FillPage (int page, int x, int y, int wid, int hgt, int color);
void Pixel (int page, int x, int y, int color);
int ReadPixel (int page, int x, int y);
void Color (int front, int back, int frame);
void Font (int f);
void SetBKMode (int mode);
int GetPicWid (int pic);
int GetPicHgt (int pic);
int KeyPress (int key);
int WaitKey ();
int GetENV ();
void mdelay(int msec);
int getsecond();
int getminute();
int gethour();
int getday();
int getmonth();
int getyear();
int getweek();
int getyearday();
void SetLcd(int wid, int hgt);

/**graph**/

#define	PEN_SOLID		0
#define	PEN_DASH		1

void Line (int page, int x1, int y1, int x2, int y2, int style, int color);
void Rectangle (int page, int left, int top, int right, int bottom, int style, int color);
void Circle (int page, int cx, int cy, int cr, int style, int color);
void Cls();
void OutTextxy(int page, int x, int y, char * str);


/* end of cvm.h */

/* plus.h */
char _string_str[99];
unsigned char _memory_[80000];

long putn(long value)
{
	char _room[99];
	puts(itoa(value,_room,10));
	return(value);
}

long putx(long value)
{
	char _room[99];
	puts(itoa(value,_room,16));
	return(value);
}

char *str(int value)
{
	return(itoa(value,_string_str,10));
}

char *strx(int value)
{
	return(itoa(value , _string_str , 16));
}

char *addchr(char *string,char value)
{
	char _room[2];
	_room[0] = value;
	_room[1] = 0;
	return(strcat(string,_room));
}

char *backspace(char *string)
{
	int length;
	length = strlen(string);
	if (length > 0)
		*(string + length - 1) = 0;
	return(string);
}

long lof(char *filename)
{
	FILE *fp;
	long length;
	fp = fopen(filename,"r");
	if (fp == 0)	return(-1);
	fseek(fp,0,2);
	length = ftell(fp);
	fclose(fp);
	return(length);
}

/*
cr();
putn(21);
putx(21);
str(9288);
*/