/* keyboard.h */
#include "wb86.h"

short key_shift;
char *key__label;
char key__body[500];
short key__lock;

int getkey()
{
	int i;
	if (KeyPress(27))	return(27);
	if (KeyPress(13))	return(13);
	if (KeyPress(32))	return(32);
	if (KeyPress(37))	return(37);
	if (KeyPress(38))	return(38);
	if (KeyPress(39))	return(39);
	for (i = 48; i < 58; i ++)
		if (KeyPress(i))	return(i);
	for (i = 65; i < 91; i ++)
		if (KeyPress(i))	return(i);
	if (KeyPress(40))	return(40);
	return(0);
}

void killkey()
{
	while(getkey() != 0);
	while(getkey() == 0);
	while(getkey() != 0);
}

int readkey()
{
	int key;
	int i;
	while (getkey() != 0 && getkey() != 40);
	key = 0;
	while (key == 0)
	{
		if (KeyPress(40)) key_shift = 1;
		else key_shift = 0;
		if (KeyPress(27))	key = 27;
		if (KeyPress(13))	key = 13;
		if (KeyPress(32))	key = 32;
		if (KeyPress(37))	key = 37;
		if (KeyPress(38))	key = 38;
		if (KeyPress(39))	key = 39;
		for (i = 48; i < 58; i ++)
			if (KeyPress(i))	key = i;
		for (i = 65; i < 91; i ++)
			if (KeyPress(i))	key = i;
	}

	return(key);
}

int keyb(int x,int y , char *head , char *aim , int max) /* del title */
{
	int  key;
	int  loc_x;
	int  capslock;
	char menu_sym[20];
	int  ret;
	char room[99];
	int  cmenu(char *title,char *string);
	char wubi_room[30];
	char string[99];
	int picture;

	char wb_code[6];

	char ctfmon;

	/* init */
	strcpy(menu_sym," \\.:_$#%&*");
	strcpy(key__body,head);

	strcpy(wb_code,"");
	key = 0;
	capslock = 0;
	ctfmon = -1;

	/* main */
	FillPage(0 , 0 , 240-ft.h , 320 , ft.h , 0x555555);
	while (1)
	{
		if (strlen(key__body) > max)
			key__body[max] = 0;

		loc_x = x;

		if (strlen(key__body) > 30)
			key__label = key__body + strlen(key__body) - 30;
		else
			key__label = key__body;

		FillPage(0,loc_x-1,y-1,ft.w * 31+2 ,ft.h+2,0x000000);
		FillPage(0,loc_x,y,ft.w * 31 ,ft.h,0xffffff);
		FillPage(0 , 0 , 240 - ft.h , ft.w * 4 , ft.h , 0xaaaaaa);
		OutTextxy(0,loc_x,y,key__label);
		OutTextxy(0 , 0 , 240 - ft.h , wb_code);
		FillPage(0,x+strlen(key__label)*ft.w,y,1,ft.h,0);

		key = readkey();
		if (capslock == 1)
			key_shift = 1;

		if (key == 27)
		{
			while( KeyPress(27));
			return(0);
		}
		else if (key == 32)
		{
			if (capslock < 2)
			{
				addchr(key__body , 32);
			}
			else
			{
				if (strlen(wb_code) > 0)
				{
					strcpy(wubi_room , "");
					wbcode(wubi_room,wb_code);
					strcat(key__body , wubi_room);
					strcpy(wb_code,"");
				}
			}
		}
		else if (key == 13)
		{
			while(KeyPress(13));
			break;
		}
		else if (key > 47 && key < 58)
		{
			if (key_shift == 1)
			{
				addchr(key__body , menu_sym[key - 48]);
			}
			else
				addchr(key__body,key);
		}
		else if (key > 64 && key < 91)
		{
			if (capslock == 2)
			{
				if (strlen(wb_code) < 4)
					addchr(wb_code , key + 32);
			}
			else
			{
				if (key_shift == 0)
					addchr(key__body,key+32);
				else
					addchr(key__body , key);
			}
		}
		else if (key == 37)
		{
			if (capslock == 2 && strlen(wb_code)>0)
				backspace(wb_code);
			else
				backspace(key__body);
		}
		else if (key == 38)
		{
			if (strlen(key__body) > 0)
				strcpy(key__body , "");
			else 
				strcpy(key__body , head);
		}
		else if (key == 39)
		{
			while(KeyPress(38));
			if (key__lock == 0)
			{
				capslock ++;
				strcpy(wb_code , "");
				if (capslock == 3)	capslock = 0;
				picture = LoadRes("dos.rlb" , 2);
				ShowPic(0 , picture , capslock*16 , 0 , 16 , 16 , 320 - 16 , 240 - 16 , 1);
				FreeRes(picture);
			}
		}
	}
	/* end */
	strcpy(aim,key__body);
	return(1);
}

int KeyToVal(char *string)
{
	int i;
	char room[20];
	int length;
	char value;
	int mode;  /* ½øÖÆ */
	int ret;

	if (*(string) == 48 && *(string +1) == 120)
	{
		mode = 16;
		strcpy(room , string + 2);
	}
	else 
	{
		mode = 10;
		strcpy(room , string);
	}

	length = strlen(room);
	if (length == 0)
		return(-1);

	if (mode == 10)
	{
		return(atoi(room));
	}
	else if (mode == 16)
	{
		ret = 0;
		for (i = 0 ; i < length ; i ++)
		{
			value = room[i];
			if (value > 47 && value < 58)
			{
				ret = ret * 16;
				ret = ret + (value - 48);
			}
			else if (value > 96 && value < 103)
			{
				ret = ret * 16;
				ret = ret + (value - 97 + 10);
			}
			else 
				break;
		}
		return(ret);
	}
	return(1);
}

int nkeyb(int x , int y , long *aim , long min , long back ,long max)
{
	int  key;
	long value;
	int  string_len;
	/* init */
	key = 0;
	value = 0;
	string_len = 15;
	strcpy(_memory_ , str(back));

	while(1)
	{
		_memory_[string_len] = 0;
		key__label = _memory_;

		FillPage(0 , x -1, y -1, ft.w * string_len+ ft.w +2, ft.h +2, 0x000000);
		FillPage(0 , x , y , ft.w * string_len+ ft.w , ft.h , 0xaaaaaa);
		OutTextxy(0,x,y,key__label);
		FillPage(0 , x + ft.w * strlen(_memory_) , y+ft.h-2 , ft.w , 2 , 0x000000);
		while (getkey() != 0);

		do {
			key = getkey();
		}while(key == 0);

		if (key == 27)
		{
			while(KeyPress(27));
			return(0);
		}
		else if (key == 13)
		{
			while(KeyPress(13));
			value = KeyToVal(_memory_);
			if (value == -1)
			{
				strcpy(_memory_ , str(back));
				continue;
			}

			if (value < min)
				strcpy(_memory_ , "<min");
			else if (value > max)
				strcpy(_memory_ , ">max");
			else
				break;
		}
		else if (key > 47 && key < 58)
		{
			addchr(_memory_ , key);
		}
		else if (key > 64 && key < 91)
		{
			addchr(_memory_ , key+32);
		}
		else if (key == 37)
		{
			backspace(_memory_);
		}
		else if (key == 38)
		{
			strcpy(_memory_ , str(min));
		}
		else if (key == 39)
			strcpy(_memory_ , "");
		else if (key == 40)
			strcpy(_memory_ , str(max));
		else if (key == 32)
		{
			strcpy(_memory_ , str(back));
		}
	}

	*aim = value;
	return(1);
}

