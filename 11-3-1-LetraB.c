#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 3

double p(double x)
{	
	return (0);
}

double q(double x)
{	
	return (4);
}

double r(double x)
{	
	return (-4*x);
}

double y(double x)
{	
	return exp(2)*(exp(2*x)-exp(-2*x))/(exp(4)-1) + x;
}

void imprime(double **M, int NL, int NC)
{
	int i, j;
	
	for(i=0; i<NL; i++)
	{
		for(j=0; j<NC; j++)
		{
			printf("%.4lf\t ", M[i][j]); 
		} 
		puts("");
	}	
}

void **pivoteamento(double **M, int NL, int NC)
{
        double l, pivot, maior, aux;
        int i,j,k,m,n;
        
        for(j=0; j<NL-1; j++)
        {	
			pivot = M[j][j];
			maior = pivot;

			for(k=j; k<NL; k++)
			{	
				if(fabs(maior) < fabs(M[k][j]))
				{	
					maior = M[k][j];
					m = k;
				}
			}

			if(maior != pivot)
			{	
				for(n=0; n<NC; n++)
				{	
					aux = M[m][n];
					M[m][n] = M[j][n];
					M[j][n] = aux;
				}
			}
			for(i=j+1; i<NL; i++)
			{
				l = M[i][j]/M[j][j];       
				for(k=0; k<NC; k++)
				{
					M[i][k] -= l*M[j][k]; 
				}
			}
		}       
}

void subreversa(double **M, double *w, int dim, double *x)
{
	int i,j;
	double soma;

	FILE *h025;

	w = malloc( dim* sizeof(double));
	
	h025 = fopen("11-3-1-LetraB.dat", "w");
	
	for(i=dim-1; i>=0; i--)
	{
		soma=0;
		
		for(j=i+1; j<dim; j++)
		{	
			soma += M[i][j]* w[j];
		}	

		w[i] = (M[i][dim] - soma)/M[i][i];
	}
	
	fprintf(h025,"i \tx \t\ty ( numérico ) \ty ( exato ) \n");
	for(i=1; i<=dim; i++)
	{
		fprintf(h025, "%d \t %lf \t %lf \t %lf \n",i,x[i],w[i-1],y(x[i]));
	}
	
	fclose(h025);
}

int main(int argc, char **argv)
{	
	double	**M;
	double x[N+2], w[N+2];
	double h;
	int NL=N, NC=N+1;
	int i, j;
	double xi=0, xf=1., yi=0, yf=2;
 
	M = malloc(N*sizeof(double*));
	
	for(i=0; i<NC; i++)
	{
		M[i] = malloc(NC*sizeof(double));
	}
	
	h = 1./4.;
	x[0] = xi;
	
	for(i=1; i<=N; i++)
	{	
		x[i] = xi + i*h;
	}
	x[N+1] = xf;
		
	//Matriz
	for( i = 0; i < N; i++ )
	{	
		if( i == 0 )
		{	M[i][i] = 2 + pow(h, 2)* q(x[i+1]);
			M[i][i+1] = - 1 + (h/2.)* p(x[i+1]);
		}
		else if( i == N-1 )
		{	M[i][i-1] = - 1 - (h/2.)* p(x[i+1]);
			M[i][i] = 2 + pow(h, 2)* q(x[i+1]);
		}
		else
		{	M[i][i-1] = - 1 - (h/2.)* p(x[i+1]);
			M[i][i] = 2 + pow(h, 2)* q(x[i+1]);
			M[i][i+1] = - 1 + (h/2.)* p(x[i+1]);
		}
	}
	M[0][N] = -pow(h, 2)*r(x[1]) + (1 +(h/2.)*p(x[1]))*y(x[0]);
	M[N-1][N] = -pow(h, 2)*r(x[N]) + (1 -(h/2.)*p(x[N]))*y(x[N+1]);
	
	for(i=1; i<N-1; i++)
	{	
		M[i][N] = -pow(h, 2)*r(x[i+1]);
	}	
	//imprime(M,NL,NC);
	pivoteamento(M,NL,NC);
	subreversa(M,w,NL,x);
}
