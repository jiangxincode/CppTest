/* lcd.h */
/* need file : cvm++.h */

long N[10];
int  _dos;
int  page_ex;

char textout_string[99];

void clean();
void IF_ETR();

struct STRUCLCD
{
	int w;
	int h;
	int stx;
	int sty;
	int x; /* x,y 代表真实的坐标　*/
	int y;
	int flip;
	int maxh;
	int bbmode;
	int etr;
}lcd;
typedef struct STRUCLCD _STRUCLCD;
struct STRUCFONT
{
	int value;
	int w;
	int h;
}ft;
typedef struct STRUCFONT _STRUCFONT;
int SET_LCD(int envir) /* 320*240 */
{
	lcd.w = 320;
	lcd.h = 240;

	SetLcd(lcd.w , lcd.h);
	return(envir);
}

int SET_FONT(int value) /* 012.345.678 */
{
	if (value < 0)	value = 0;
	else if (value > 8) value = 8;
	ft.value = value;

	if (ft.value <3)		ft.w = 6;
	else if (ft.value <6)	ft.w = 8;
	else					ft.w = 12;

	ft.h = ft.w * 2;
	Font(ft.value);
	return(ft.value);
}

void SET_PAGE(int page)
{
	if (page == 0)
	{
		_dos = CreatePage();
	}
	else 
	{
		DeletePage(_dos);
		_dos = page;
	}
}

void SET_BBMODE(int value)
{
	if (value == 0)
		lcd.bbmode = 0;
	else
		lcd.bbmode = 1;
}

void SET_FLIP(int value)
{
	lcd.flip = value;
}

void SET_STYX(int sty,int stx)
{
	lcd.stx = stx;
	lcd.sty = sty;
}

void SET_MAXH(int value)
{
	lcd.maxh = value;
}

void IF_ETR()
{
	if (lcd.etr == 1)
	{
		lcd.etr = 0;
		clean();
	}
}

char *ntos(char *string)
{
	char room[999];
	char byte;
	int  length;
	int  i,j;
	strcpy(room,"");
	length = strlen(string);

	for (i=0; i<length ; i++)
	{
		byte = *(string + i);
		if (byte == 37)
		{
			i++;
			byte = *(string + i);
			if (byte>47 && byte<58)
			{
				strcat(room,str(N[byte-48]));
			}
		}
		else
		{
			addchr(room,byte);
		}
	}
	room[i] = 0;
	return (strcpy(string,room));
}


/*-----*/
int INIT_LCD()
{
	page_ex = CreatePage();
	SET_PAGE(0);
	SET_FLIP(1);
	SET_STYX(0,0);
	SET_MAXH(224);
	lcd.bbmode = 0;
	lcd.etr = 0;
}

void clean()
{
	lcd.x = lcd.stx;
	lcd.y = lcd.sty;
	FillPage(_dos, lcd.stx , lcd.sty ,320 - lcd.stx , 240 - lcd.sty , 0xffffff);
}

void print_etr()
{
	/**/
	lcd.x = lcd.stx;
	if (lcd.y+ft.h >= lcd.maxh)
	{
		if (lcd.bbmode == 0)
		{
			StretchBltPage(0,-ft.h,page_ex,_dos);
			FillPage(page_ex, 0,lcd.h-ft.h, lcd.w,ft.h, 0xffffff);
			BitBltPage(_dos,page_ex);
			FlipPage(_dos);
		}
		else 
		{
			lcd.etr = 1;
		}
	}
	else
		lcd.y = lcd.y + ft.h;
}

short textout(char *string , short begin)
{
	char chr;
	short length;
	short length_max;
	short label_etr;

	length_max = (lcd.w - lcd.x) / ft.w;
	if (length_max > strlen(string + begin))
	{
		label_etr = 0;
		length_max = strlen(string + begin);
	}
	else
		label_etr = 1;

	for (length = 0 ; length < length_max ; )
	{
		chr = *(string + length + begin);
		textout_string[length] = chr;
		length ++;
		if (chr < 0)
		{
			textout_string[length] = *(string + begin + length);
			length ++;
		}
	}

	textout_string[length ] = 0;
	OutTextxy(_dos , lcd.x , lcd.y , textout_string);
	if (lcd.flip == 1)
		FlipPage(_dos);

	if (label_etr == 0)
		lcd.x = lcd.x + ft.w*length;
	else
		print_etr();

	return(length);
}

void print(char *string) /* 先打印,再换行 */
{
	int i;
	IF_ETR();
	for (i = 0 ; i < strlen(string) ;)
	{
		i = i + textout(string , i);
	}
	print_etr();
}

void print_(char *string)
{
	int i;
	IF_ETR();
	for (i = 0 ; i < strlen(string) ;)
	{
		i = i + textout(string , i);
	}
}

void printn(int value)
{
	char room[50];
	IF_ETR();
	print(itoa(value,room,10));
}

void printn_(long value)
{
	char room[50];
	IF_ETR();
	print_(itoa(value,room,10));
}

void pfloat(float value)
{
	char room[50];
	IF_ETR();
	print(ftoa(value,room));
}

void pfloat_(float value)
{
	char room[50];
	IF_ETR();
	print_(ftoa(value,room));
}

void locate(int line,int row)
{
	lcd.x = ft.w * row;
	lcd.y = ft.h * line;
}

void printf0(char *string, long number0)
{
	IF_ETR();
	N[0] = number0;
	print(ntos(string));
}

void flipdos()
{
	FlipPage(_dos);
}