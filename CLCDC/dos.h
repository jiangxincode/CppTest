
/* dos.h */
#include "cvm++.h"
#include "lcd.h"
#include "keyboard.h"
#include "menu.h"

void dos();

void wait(int value)
{
	while (! KeyPress(value) && ! KeyPress(27));
	while (KeyPress(value) || KeyPress(27));
}

void fill(int page , int color)
{
	FillPage(page , 0 , 0 , lcd.w , lcd.h , color);
}

int max(int number1 , int number2)
{
	if (number2 > number1)
		return(number2);
	else
		return(number1);
}

int min(int number1 , int number2)
{
	if (number1 < number2)
		return(number1);
	else
		return(number2);
}

int getxt(char *title,char *tostr,char *back,int max)
{
	int value;
	print_(title);
	value = keyb(lcd.x,lcd.y,back,tostr,max);
	print(key__label);
	return (value);
}

int getnum(char *title,int *tonum)
{
	int value;
	print_(title);
	value = nkeyb(lcd.x,lcd.y,tonum,0,0,0xffffff);
	print(key__label);
	return(value);
}

int getval(char *title, long *tonum , long min , long back , long max)
{
	int ret;
	print_(title);
	ret = nkeyb(lcd.x,lcd.y, tonum ,min , back, max);
	print(key__label);
	return(ret);
}

/* ===================== */
int rnd()
{
	srand(getsecond() * rand() + rand() % getminute());
	return(rand());
}

void main()
{
	/* */
	SET_LCD(9288);
	SET_FONT(3);
	INIT_LCD();
	Color(0x000000,0xffffff,0x000000);
	SetBKMode(1); /* Éè³ÉÍ¸Ã÷Ä£Ê½ */
	SET_BACKPAGE(_dos);
	SET_MULTIMENU(0);
	key__lock = 0;
	/* */
	clean();
	dos();
	DeletePage(page_ex);
	return;
}