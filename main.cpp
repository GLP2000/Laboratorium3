#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "winbgi2.h"
#include "nonlin.h"

double fun1(double x);
double fun2(double x);
double poch1(double x);
double poch2(double x);
double newton(double x, double (px)(double),double (pf)(double), double eps, int* i_iter);
double sieczne(double x1, double x2, double (px)(double), double eps, int* i_iter);
double w=0.5;

int main()
{
	FILE *p;
	p=fopen("lab3.txt","w");
	if(p==NULL)
	printf("BLAD");


	double a, b, eps,kk1,nw1,si1,nw2,si2,kk2;
	int iter;
	int* i_iter = &iter;
	
	
	printf("podaj a:\n");
	scanf("%lf",&a);
	printf("podaj b:\n");
	scanf("%lf",&b);
	printf("\n\nLiczymy dla f1=cos(x)- x\n\n");

	if(fun1(a)*fun1(b)<=0)
	{

		graphics(700, 600);
		log_scale(0.0, 0.0, 30, 0.125);

		fprintf(p,"dla a=%lf, b=%lf \n",a,b);
		fprintf(p,"Bisec\t");
		fprintf(p,"Newton\t");
		fprintf(p,"Sieczne\n");

		for(int i=-20;i<=-3;i++)
		{	
			eps=pow(2.0,i);

			kk1=bisec( a, b, fun1, eps, i_iter);
			setcolor(0.6);
			point(iter,eps);

			nw1=newton (a, fun1, poch1, eps, i_iter);
			setcolor(0.3);
			point(iter, eps);

			si1=sieczne( a, b, fun1, eps, i_iter);
			setcolor(0.9);
			point(iter,eps);

			fprintf(p,"%lf\t",kk1 );
			fprintf(p,"%lf\t",nw1 );
			fprintf(p,"%lf\n",si1 );	

			printf("Bi1[%d]=%lf\t ilosc iter=%d\t doklad=%lf \n",i,kk1,iter,eps);
			printf("Nw1[%d]=%lf\t ilosc iter=%d\n",i,nw1,iter);
			printf("Sieczne1[%d]=%lf\t ilosc iter=%d\n",i,si1,iter);		
		}

		printf("\nLiczymy dla f2=cos(x)-w*x \n\n");
		for(int h=0;h<146;h++)
		{
			eps=pow(10.0,-6.0);
			w+=0.1;
			kk2=bisec( a, b, fun2, eps, i_iter);
			nw2=newton(a, fun1,poch2, eps, i_iter);
			si2=sieczne( a, b, fun2, eps, i_iter);

			printf("w=%lf\t",w);
			printf("Bi2=%lf\t",kk2);
			printf("Nw2=%lf\t",nw2);
			printf("Sieczne2=%lf\n",si2);	
		}
	}
	else printf("Nie spelnia f(a)*f(b)<0 \n");

	fclose(p);
	wait(); 

}

double fun1(double x)
{
	return (cos(x)- x);
}


double fun2(double x)
{
	return cos(x)-w*x;
}

double poch1(double x)
{
	return -sin(x) - 1;
}

double poch2(double x)
{
	return -sin(x) - w;
}

double newton(double x, double (px)(double),double (pf)(double), double eps, int* i_iter)
{
	for (int i = 0; i < 1000;i++)
	{
		x = x - px(x)/pf(x);
		*i_iter = i;
		if (fabs(px(x)) < eps)	break;
	}

	return x;
}

double sieczne(double x1, double x2, double (px)(double), double eps, int* i_iter)
{	
	double cz;

	for (int i = 0; i < 1000;i++)
	{
	

		cz = x1 - px(x1)*((x1-x2)/(px(x1)-px(x2)));
		x1=x2;
		x2=cz;
		*i_iter = i;

		if (fabs(px(x1)) < eps && abs(x2-x1)<eps)	break;
	}

	return cz;
}

