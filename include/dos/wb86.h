/* wb86.h */
/* belongs to : dos.h */
long wubi_addr[26];

int wubi_init()
{
	wubi_addr[0] = 0x000005;
	wubi_addr[1] = 0x0019af;
	wubi_addr[2] = 0x0024a9;
	wubi_addr[3] = 0x002e31;
	wubi_addr[4] = 0x00454c;

	wubi_addr[5] = 0x005019;
	wubi_addr[6] = 0x006a13;
	wubi_addr[7] = 0x00835e;
	wubi_addr[8] = 0x008b60;
	wubi_addr[9] = 0x00a7fd;

	wubi_addr[10] = 0x00b8d3;
	wubi_addr[11] = 0x00cb89;
	wubi_addr[12] = 0x00d917;
	wubi_addr[13] = 0x00e5e2;
	wubi_addr[14] = 0x00f69f;

	wubi_addr[15] = 0x00fe9c;
	wubi_addr[16] = 0x010fea;
	wubi_addr[17] = 0x0128db;
	wubi_addr[18] = 0x014762;
	wubi_addr[19] = 0x015c1b;

	wubi_addr[20] = 0x017cf5;
	wubi_addr[21] = 0x01986b;
	wubi_addr[22] = 0x01a36a;
	wubi_addr[23] = 0x01c165;
	wubi_addr[24] = 0x01cfa2;
	wubi_addr[25] = 0x01ecdf;

	if (lof("wb.idx") == -1)
		return(0);
	else 
		return(1);
}

int wbcode(char *tostr,char *incode)
{
	FILE *fpi,*fpd;
	char code[5];
	char word[20];
	char *ptell;
	int i;
	int j;
	int loop;
	char head;
	int la,lb,lc;
	int ret;

	loop = 1;
	ret = wubi_init();
		if (ret == 0)
		{
			print("no wb file ..");
			return(0);
		}

	head = *(incode);
	head = head - 97;
	la = wubi_addr[head];
	lb = wubi_addr[head+1];
	lc = (lb - la)/5 + 1;
	strcpy(word ,"");
	fpi = fopen("wb.idx","rb");
	fpd = fopen("wb.dat","rb");

	fseek(fpi,la,0);
	fread(_memory_,lc*5,1,fpi);
	for (j = 0; j < lc; j++)
	{
		if (KeyPress(38))
			break;
		ptell = _memory_ + j*5;
		/*
		FillPage(0 , ft.w * 4 , 240 - ft.h , ft.w * 4 , ft.h , 0xaaaaaa);
		OutTextxy(0 , ft.w * 4 , 240 - ft.h ,ptell);
		*/
		if (strcmp(ptell,incode) == 0)
		{
			i = la / 5 + j;
			fseek(fpd,i * 20,0);
			fread(word,20,1,fpd);
			strcpy(tostr,word);
			break;
		}
	}

	fclose(fpi);
	fclose(fpd);
	return(1);
}