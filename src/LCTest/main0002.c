/*
这是一个生成正弦波函数值的小程序：
首先您在此文件夹中应该看到一些以".c"结尾的C语言源文件、Makefile文件以及本README，（或许还有一些其它的以".o"结尾的目标文件，此时您首先可以执行make clean进行删除。）当您执行make命令后便会发现在此文件夹中出现一个名为sine_wave的可执行文件，之后您可以执行./sine_wave frequency samplerate path_name即可获得相应参数的正弦波函数值。

改进：
1.use open() instead of fopen();
2.use binary file to save the data;
3.make sure data manage process can read and deal the binary file;
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define PI 3.1415926

void generate(int, int, double*);
void save(char *, int , double *);

int main0002(int argc, char * argv[])
{

	int frequency,samplerate;
	char path_name[100];
	frequency = 400;
	samplerate = 8000;
	strcpy(path_name, "sine_wave.out");
	if(argc!=4)	//不正确的输入数量
	{
		puts("\nInput Warning!!\n");
		puts("*****************************************************\n");
		puts("Sine_wave_generator\n");
		puts("Input:./sine_wave samplerate frequency path_name\n");
		puts("(Divide with space,End with Enter!)\n");
		puts("Default Value:\nSamplerate:8000\tFrequency:400\tOutput Filename:./sine_wave.out\n");
		puts("Output:sine wave file!\n");
		puts("By Jiangxin\t2013.9.20\n");
		puts("*****************************************************\n");
	}
	else	//正确的输入数量
	{
		samplerate = atoi(argv[1]);
		frequency = atoi(argv[2]);
		strcpy(path_name,argv[3]);
	}

	double sine_buffer[samplerate];	//建立数组暂时保存函数值
	generate(frequency, samplerate, sine_buffer);
	save(path_name, samplerate, sine_buffer);
	printf("GENERATE SINE WAVE OK!\n");

	return 0;
}

void generate(int frequency, int samplerate, double *data)
{
	int i ;
	double angle = 0;
	double temp = (double) ((2 * PI * frequency )/samplerate);
	for (i = 0; i < samplerate ; i ++)
	{
		data[i] = (double)(50*sin(angle));   /* 50 is the amplitude of sine wave */
		angle += temp ;
	}
}

void save(char *path_name, int samplerate, double *data)
{
	FILE *fp;
	int i;
	if((fp = fopen(path_name, "w+")) == NULL)
		puts("Can not Open or Create this file!\n");
	for(i=0;i<samplerate;i++)
	{
		fprintf(fp,"%lf\n",data[i]);
	}
	fclose(fp);
}
