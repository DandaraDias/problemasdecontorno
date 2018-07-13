#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 2
#define Npontos 100

typedef double (*sistfunc)();

double f0( double x, double *y )
{	
	return (y[1]);
}

double f2( double x, double *y )
{	
	return (100*y[0]);
}

double f1( double x, double *y )
{	
	return (f2(x, y));
}

double RK4(sistfunc func[], double *y, double x, double h)
{	
	double k1[N], k2[N], k3[N], k4[N];
	double yaux[N];
	int i;
	
	for(i=0; i<N; i++)
	{
		k1[i] = func[i](x, y);
	}
	for(i=0; i<N; i++)
	{
		yaux[i] = y[i] + h*k1[i]/2.;
	}
	
	for(i=0; i<N; i++)
	{
		k2[i] = func[i](x + h/2., yaux);
	}
	for(i=0; i<N; i++)
	{
		yaux[i] = y[i] + h*k2[i]/2.;
	}
	
	for(i=0; i<N; i++)
	{
		k3[i] = func[i](x + h/2., yaux);
	}
	for(i=0; i<N; i++)
	{	
		yaux[i] = y[i] + h*k3[i];
	}
	
	for(i=0; i<N; i++)
	{
		k4[i] = func[i](x + h, yaux);	
	}
	for(i=0; i<N; i++)
	{
		y[i] += (k1[i] + 2*k2[i] + 2*k3[i] + k4[i])*h/6.;
	}
	
	return (y[0]);	
}

int main(int argc, char **argv)
{	double x, h, y, y1b, y2b;
	double yp1[Npontos+1], yp2[Npontos+1];
	double xmin=0, xmax=1, B=exp(1e-10);
	double y1[N]={1, 0}, y2[N]={0, 1};
	sistfunc equacoes1[N]={f0,f1};
	sistfunc equacoes2[N]={f0,f2};
	int i;
	
	FILE *h01;
	
	h = 0.1;
	i = 0;
	yp1[0] = y1[0];
	yp2[0] = y2[0];
	
	h01 = fopen("11-1-5-LetraA.dat", "w");
	
	for(x=xmin+h; x<=xmax; x+=h)
	{	
		i++;
		yp1[i] = RK4(equacoes1, y1, x, h);
		yp2[i] = RK4(equacoes2, y2, x, h);
	}
	
	y1b = yp1[i];
	y2b = yp2[i];
	i = 0;
	
	for(x=xmin; x<=xmax; x+=h)
	{	
		y = yp1[i] + ((B - y1b)/y2b)*yp2[i]; 
		fprintf(h01, "%lf\t%lf\n", x, y);
		i++;
	}
	
	fclose(h01);
} 
