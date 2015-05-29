/* menu.h */
/* need file: cvm++.h */

char *mnu[20];
int  mnukey[20];
char mnupool[999];
int mnu_width;  /* 长度 */
int mnu_total;  /* 项数 */
int mnu_stt;    /* 起始项 , 是否显示题目 */
int mn_back;    /* 背景页面 */
int mn_multi ;  /* 菜单集 */

int menu(int x,int y);
int menu_reload(char *title , char *string);

void SET_BACKPAGE(int page)
{
	mn_back = page;
}

void SET_MULTIMENU(int value)
{
	mn_multi = value;
}

int menu_handle()
{
	int i;
	if (KeyPress(13))	return(13);  /* 确认 */
	if (KeyPress(32))	return(32);
	if (KeyPress(27))	return(27);  /* 取消 */
	if (KeyPress(37))	return(37);
	if (KeyPress(38))	return(38);  /* 上   */
	if (KeyPress(39))	return(39);
	if (KeyPress(40))	return(40);  /* 下   */
	for (i=65; i<91; i++)            /* 大写字母 */
		if (KeyPress(i))	return(i);
	return(0);                       /* 空 */
}

int menu_reload(char *title , char *string)
{
	int length;    /* 长度 */
	int total;     /* 项数 */
	int i;
	char chri;     /* 一个字符变量 */
	int width;     /* 最长长度 */
	/* copy string */
	mnu[0] = title;
	if (strlen(title) == 0) mnu_stt = 1;  /* title */
	else mnu_stt = 0;
	strcpy(mnupool , string);
	length = strlen(mnupool);
	total = 0;

	/* 载入项地址和快捷键 */
	for (i = 0; i < length ; i ++)
	{
		chri = mnupool[i];
		if (chri == 42) /* if is star * */
		{
			total ++;
			mnupool[i] = 0;
			mnu[total] = mnupool + i + 1;
			mnukey[total ] = 0;
		}
		else if (chri == 38)
		{
			mnukey[total] = mnupool[i+1];
			mnupool[i] = 32;
		}
	}

	/* 得到最长长度 */
	width = 0;
	for (i = 0; i <= total ; i ++)
	{
		if (strlen(mnu[i]) > width ) width = strlen(mnu[i]);
	}
	width = width * ft.w;

	/* 总结 */
	mnu_width = width;
	mnu_total = total;
	return(1);
}

int super_menu(int x , int y , char *string_item , char *source)
{
	int i;
	int key;

	menu_reload("???" , source);

	for (i = 0 ; i < strlen(string_item) ; i ++)
	{
		mnukey[i] = *(string_item + i) - 48;
	}

	for (i = 0 ; i < strlen(string_item) ; i ++)
	{
		FillPage(0 , x , ft.h * i + y , strlen(mnu[mnukey[i]])*ft.w , ft.h , 0xaaaaaa);
		OutTextxy(0 , x , ft.h * i + y, mnu[mnukey[i]]);
	}

	/*88*/
	i = 0;
	while (1)
	{
		if (i < 0 ) i = strlen(string_item)-1;
		else if (i == strlen(string_item)) i = 0;

		FillPage(0 , x , ft.h * i + y , strlen(mnu[mnukey[i]])*ft.w , ft.h , 0x000000);
		Color(0xffffff, 0x000000 , 0x000000);
		OutTextxy(0 , x , ft.h * i + y, mnu[mnukey[i]]);

		while (menu_handle() != 0);
		do { key = menu_handle(); } while (key == 0);
		FillPage(0 , x , ft.h * i + y , strlen(mnu[mnukey[i]])*ft.w , ft.h , 0xaaaaaa);
		Color(0x000000 , 0xffffff, 0x000000);
		OutTextxy(0 , x , ft.h * i + y, mnu[mnukey[i]]);
		if (key == 38)
		{
			i --;
		}
		else if (key == 40)
		{
			i ++;
		}
		else
			break;
	}

	return(i);
}

int menu(int x,int y)
{
	/* declare */
	int  i;
	int  length;
	int  total;
	int  mi;
	int  key;
	int  wlength;
	int  page;
	int  ret;
	int  forecolor,backcolor;
	int  k_conf;
	int stt;

	backcolor = 0xffffff;
	k_conf = -1;
	/* init */
	wlength = mnu_width;
	total   = mnu_total;
	stt     = mnu_stt;
	/* 背景处理 */
	FillPage(0,x-1,y-1,wlength+2,(total+1-stt)*ft.h+2,0x000000);
	FillPage(0,x,y,wlength,(total+1-stt)*ft.h,backcolor);
	if (stt == 0) /* 菜单标题 */
	{
		Color(0x000000, 0xaaaaaa , 0);
		FillPage(0,x,y,wlength,ft.h,0xaaaaaa);
		OutTextxy(0,x,y,mnu[0]);
	}
	Color(0x000000,backcolor,0);
	for (i = 1;i<= total;i++)
		OutTextxy(0,x,y+(i-stt)*ft.h,mnu[i]);
	mi = 1;

	/* 进入选择循环 */
	while (menu_handle() != 0);
	while (1)
	{
		/* 选中行 */
		FillPage(0,x,y+(mi-stt)*ft.h,wlength,ft.h,0);
		Color(0xffffff,0,0);
		OutTextxy(0,x,y+(mi-stt)*ft.h,mnu[mi]);
		while(getkey() == key);

		do{
			key = getkey();
		} while(key == 0);

		FillPage(0,x,y+(mi-stt)*ft.h,wlength,ft.h,backcolor);
		Color(0x000000,backcolor,0);
		OutTextxy(0,x,y+(mi-stt)*ft.h,mnu[mi]);
		if (key == 13)  /*yes */
		{
			if (mnukey[mi] != 0)
				ret = mnukey[mi];
			else 
				ret = mi;
			break;
		}
		else if (key == 27)
		{
			ret = 0;
			break;
		}
		else if (key == 38) mi--;
		else if (key == 40) mi++;
		else if (key >64 && key <91)
		{
			for (i = 1; i <= total; i ++)
			{
				if (key == mnukey[i])
				{
					mi = i;
					k_conf = 1;
					break;
				}
			}
			if (k_conf == 1)
			{
				ret = key;
				break;
			}
		}
		else if (mn_multi == 1)
		{
			if (key == 37)
			{
				ret = 37;
				break;
			}
			else if (key == 39)
			{
				ret = 39;
				break;
			}
		}

		if (mi<1)			mi = total;
		else if (mi>total)	mi = 1;
	}

	FlipPage(mn_back);
	Color(0x000000,0xffffff,0);
	return(ret);
}

int cmenu(char *title,char *string)
{
	int x , y;
	menu_reload(title , string);
	/* centre */
	x = (lcd.w - mnu_width) / 2;
	y = (lcd.h - (mnu_total + 1)*ft.h) / 2;

	return(menu(x,y));
}

int rmenu(int x,int y,char *string , int box_length)
{
	int width , height;
	/* load */
	menu_reload("",string);
	/* loc */
	width = mnu_width;
	height = mnu_total * ft.h;
	if (x + width >= lcd.w)
		x = x - width - box_length;
	if (y + height > lcd.h )
		y = y - height - box_length;
	/* main */
	return(menu(x,y));
}

/* message */
void message(char *string)
{
	int x,y;
	int f_width,f_height;
	int bg_message;

	bg_message = LoadRes("dos.rlb" , 1);
	f_width = ft.w * (strlen(string) + 2);
	f_height = ft.h * 2;
	/*
	x = (lcd.w - f_width) / 2;
	y = (lcd.h - f_height) / 2; */
	x = 20 ;
	y = 20;

	ShowPic(0 , bg_message , 0 , 0 , f_width , 32 , x , y , 1);
	ShowPic(0 , bg_message , 240 , 0 , 2 , 32 , x+ f_width , y , 1);
	Color(0,0xffffff,0);
	OutTextxy(0,x+ft.w,y+ft.w,string);
	FreeRes(bg_message);
	killkey();
}

/* ==end== */