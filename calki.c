#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define skok 10000000

double f1 (double x)
{
    return x*x*x;
}

double f2 (double x)
{
    return sin(x);
}

double f3 (double x)
{
return x/(x+2);
}

int wyb()
{
    int f;
    printf("Wybierz funkcje do calkowania\n");
    printf("1. x*x*x\n");
    printf("2. sin(x)\n");
    printf("3. x/(x+2)\n");
    printf("4. Aby zmienic zakres \n");
    printf("5. Zakoncz\n");

    scanf ("%d", &f);

    return f;
}

void *zakresy(double *pocz, double *kon)
{
    double start, koniec;

    printf ("Podaj \"od\": ");
    scanf ("%lf", &start);

    printf ("Podaj \"do\": ");
    scanf ("%lf", &koniec);

    *pocz=start;
    *kon=koniec;
    printf("pocz: %lf --- kon: %lf \n\n", *pocz, *kon);
}


double prostokat(double (*funkcja)(double), double **pocz, double **kon)
{
    double dx;
    double suma=0;
    double xi;
    double przed, po;
    int i;


    dx = (**kon - **pocz)/skok;
    przed = time(0);

    for (i=1; i<=skok; i++)
        {
        xi=**pocz+((1.*i)/skok)*(**kon-**pocz);
        suma +=funkcja (xi);
        }
        po = time(0);
        printf("Czas wykonania: %.2lf --- ",(po-przed) );
    return dx*suma;
}


double trapez (double (*funkcja)(double), double **pocz, double **kon)
{
    double dx;
    double suma=0;
    double xi;
    double poprz;
    int i;
    double przed, po;


    dx = (**kon - **pocz)/skok;
    poprz = funkcja (**pocz);
    przed = time(0);

    for (i=1; i<=skok; i++)
        {
        xi=(**pocz)+((1.*i)/skok)*((**kon)-(**pocz));
        suma +=(funkcja (xi)+poprz)/2;
        poprz = funkcja (xi);
        }
        po = time(0);
        printf("Czas wykonania: %.2lf --- ",(po-przed) );
        return dx*suma;
}


double monte (double (*funkcja)(double), double **pocz, double **kon)
{
srand(time(NULL));
double x, y;
double min=0, max=0;
int in=0;
int i;
double j;
double yp, yk;
double calka;
double przed, po;


przed = time(0);
for (j=**pocz; j<=**kon; j+=(**kon-**pocz)/skok)
    {
    if (min>funkcja(j)) min=funkcja(j);
    if (max<funkcja(j)) max=funkcja(j);
    }
yp=min-1;
yk=max+1;

for (i=0; i<=skok; i++)
    {

    x= **pocz + (double)rand()/(double)(RAND_MAX+1) * (**kon-**pocz);
    y= yp + (double)rand()/(double)(RAND_MAX+1) * (yk-yp);
    if ( (y<=funkcja (x)) &&  (y>0))
        {
        in++;
        }
    else if ( (y>=funkcja (x)) &&  (y<0))
        {
        in--;
        }
    }
    po = time(0);
    printf("Czas wykonania: %.2lf --- ",(po-przed));
return abs(calka = (in / (double)skok) * ((**kon-**pocz) * (yk-yp)));
}


int wybor(int f, double *pocz, double *kon)
{

    switch(f)
        {
            case 1:
            printf("f(x)= x*x*x \n");
            printf ("Calka obliczona metoda prostokatow: %.6lf \n", prostokat(&f1, &pocz, &kon));
            printf ("Calka obliczona metoda trapezow: %.6lf \n", trapez(&f1, &pocz, &kon));
            printf ("Calka obliczona metoda Monte Carlo: %0.6lf \n\n", monte(&f1, &pocz, &kon));
            break;

            case 2:
            printf("f(x)= sin(x) \n");
            printf ("Calka obliczona metoda prostokatow: %.6lf \n", prostokat(&f2, &pocz, &kon));
            printf ("Calka obliczona metoda trapezow: %.6lf \n", trapez(&f2, &pocz, &kon));
            printf ("Calka obliczona metoda Monte Carlo: %0.6lf \n\n", monte(&f2, &pocz, &kon));
            break;

            case 3:
            printf("f(x)= x/(x+2) \n");
            printf ("Calka obliczona metoda prostokatow: %.6lf \n", prostokat(&f3, &pocz, &kon));
            printf ("Calka obliczona metoda trapezow: %.6lf \n", trapez(&f3, &pocz, &kon));
            printf ("Calka obliczona metoda Monte Carlo: %0.6lf \n\n", monte(&f3, &pocz, &kon));
            break;

            case 4:
            printf("Zmiana zakresu \n");
            zakresy(&pocz, &kon);
            break;

            default:
            printf("Podales zla funkcje!!!\n");
            break;

        }
}


int main ()
{
    double pocz, kon;
    int f;

    zakresy(&pocz, &kon);
    f=wyb();


    while (f!=5)
    {
    wybor(f, &pocz, &kon);
    f=wyb();
    }


    return 0;
}
