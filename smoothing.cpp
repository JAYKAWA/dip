#include<stdio.h>
#include <iostream>
using namespace std;
#define H 512
#define W 512
struct{
      unsigned char B,G,R;
}pp,Pixel[H][W];
int smoothing(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8);
int main()
{
    FILE *inputfile,*outfile;
	char filehead[54];
	int i,j;
	inputfile = fopen("ori/lady.bmp","rb");//处理已经加噪声文件
	fread(filehead,1,54,inputfile);
	int grayTmp;
	for(i = 0;i<H;i++)
		for(j=0;j<W;j++)
		{
			fread(&pp,1,3,inputfile);
			Pixel[i][j].B=pp.B;
			Pixel[i][j].G=pp.G;
			Pixel[i][j].R=pp.R;
		}
	for(i = 0;i<H;i++){
		for(j=0;j<W;j++)
		{
			Pixel[i][j].R = smoothing(Pixel[i-1][j-1].R,Pixel[i-1][j].R,Pixel[i-1][j+1].R,Pixel[i][j-1].R,Pixel[i][j].R,Pixel[i][j+1].R,Pixel[i+1][j-1].R,Pixel[i+1][j].R,Pixel[i+1][j+1].R);
			Pixel[i][j].G = smoothing(Pixel[i-1][j-1].G,Pixel[i-1][j].G,Pixel[i-1][j+1].G,Pixel[i][j-1].G,Pixel[i][j].G,Pixel[i][j+1].G,Pixel[i+1][j-1].G,Pixel[i+1][j].G,Pixel[i+1][j+1].G);
			Pixel[i][j].B = smoothing(Pixel[i-1][j-1].B,Pixel[i-1][j].B,Pixel[i-1][j+1].B,Pixel[i][j-1].B,Pixel[i][j].B,Pixel[i][j+1].B,Pixel[i+1][j-1].B,Pixel[i+1][j].B,Pixel[i+1][j+1].B);
		}
	}
	outfile=fopen("Smoothing.bmp","wb");
	fwrite(filehead,1,54,outfile);
	for(i = 0;i<H;i++)
		for(j=0;j<W;j++)
			fwrite(&Pixel[i][j],1,3,outfile);
	fclose(outfile);
	fclose(inputfile);
	return 0;

}
int smoothing(int a0,int a1,int a2,int a3,int a4,int a5,int a6,int a7,int a8){
	return (a1+a3+a4+a5+a7)/9;
}