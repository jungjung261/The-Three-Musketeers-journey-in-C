#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int doc_File(int *hp1, int *hp2, int *d, int *s, char t[])
{
    FILE *in;
    in = fopen("input.txt", "r");
    if (in == 0)
    {
        return 1;
    }
    fscanf(in, "%d", hp1);
    fscanf(in, "%d", hp2);
    fscanf(in, "%d", d);
    fscanf(in, "%s", t);
    fscanf(in, "%d", s);
    fclose(in);
    return 0;
}

void ghi_File(float p)
{
    FILE *ghi;
    ghi = fopen("output.txt", "w");
    fprintf(ghi, "%.3f", p);
    fclose(ghi);
}

int isPrime(int n)
{
    int i;
    for (i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int checkWeather(char t[])
{
    if (strcmp(t, "Flood") == 0)
        return 1;
    if (strcmp(t, "Storm") == 0)
        return 1;
    if (strcmp(t, "Rain") == 0)
        return 1;
    if (strcmp(t, "Shower") == 0)
        return 1;
    if (strcmp(t, "Drizzle") == 0)
        return 1;
    if (strcmp(t, "Cloudy") == 0)
        return 1;
    else
        return 0;
}

int checkArmstrong(int n)
{
    int sum = 0, temp = n;
    while (n != 0)
    {
        int r = n % 10;
        sum += pow(r, 3);
        n /= 10;
    }
    if (sum == temp)
        return 1;
    else
        return 0;
}

int findTriangular(int n)
{
    int sum = 0, i;
    for (i = 1; i <= n; i++)
    {
        sum += i;
    }
    return sum;
}

float gs(int s)
{
    if (s % 6 == 0)
        return s * 2.0;
    else if (s % 6 == 1)
        return s / 2.0;
    else if (s % 6 == 2)
        return -pow((s % 9), 3) / 5.0;
    else if (s % 6 == 3)
        return -pow(s % 30, 2) + 3.0 * s;
    else if (s % 6 == 4)
        return -1.0 * s;
    else if (s % 6 == 5)
        return findTriangular((s % 5) + 5) * -1.0;
}

float pt(int s, char t[])
{
    float pt[6][6] = {
        {-0.1, -0.15, -0.2, -0.25, -0.05, 0},
        {-0.05, -0.1, -0.15, -0.2, 0, 0.05},
        {0, -0.05, -0.1, -0.15, 0.05, 0.1},
        {0.05, 0, -0.05, -0.1, 0.1, 0.15},
        {0.1, 0.05, 0, -0.05, 0.15, 0.2},
        {0.15, 0.1, 0.05, 0, 0.2, 0.25}};
    if (strcmp(t, "Flood") == 0)
        return pt[0][s % 6];
    else if (strcmp(t, "Storm") == 0)
        return pt[1][s % 6];
    else if (strcmp(t, "Rain") == 0)
        return pt[2][s % 6];
    else if (strcmp(t, "Shower") == 0)
        return pt[3][s % 6];
    else if (strcmp(t, "Drizzle") == 0)
        return pt[4][s % 6];
    else if (strcmp(t, "Cloudy") == 0)
        return pt[5][s % 6];
}

float caculateP(int d, int s, char t[], int hp1, int hp2)
{
    int flag = 0, P1, P2, P3, P4;
    float snakeBite = 1, f;
    int isPrimeHp1 = isPrime(hp1);
    int isPrimeHp2 = isPrime(hp2);
    if (isPrimeHp1 == 1)
    {
        P1 = 1000;
        P2 = (hp1 + s) % 1000;
    }
    else
    {
        P1 = hp1;
        P2 = (hp1 + d) % 100;
    }

    if (isPrimeHp2 == 0)
    {
        P3 = 1000;
        P4 = (hp2 + s) % 1000;
    }
    else
    {
        P3 = hp2;
        P4 = (hp2 + d) % 100;
    }

    if (checkArmstrong(hp1) == 1 && checkArmstrong(hp2) == 1)
    {
        return 1.0;
    }
    if (d < 200)
    {
        f = 0.0;
    }
    if (d >= 200 && d < 300)
    {
        snakeBite = (d + d + P1 + P2 + P3 + P4 + P4) / 2000.0;
        if (snakeBite > 0.8)
        {
            return 0;
        }
        else
        {
            hp1 -= 100;
            hp2 -= 50;
            d += 100;

            if (isPrimeHp1 == 1)
            {
                P1 = 1000;
                P2 = (hp1 + s) % 1000;
            }
            else
            {
                P1 = hp1;
                P2 = (hp1 + d) % 100;
            }

            if (isPrimeHp2 == 0)
            {
                P3 = 1000;
                P4 = (hp2 + s) % 1000;
            }
            else
            {
                P3 = hp2;
                P4 = (hp2 + d) % 100;
            }
        }
    }
    if ((d >= 300 && d <= 800) || snakeBite <= 0.8)
    {
        f = (40 - abs(d - 500) / 20.0 + gs(s)) * (1 + pt(s, t));
    }
    if (d > 800)
    {
        f = (-d * s) / 1000.0;
    }
    return (((P1 + P2 * f) / (1000 + fabs(1.0 * P2 * f))) 
        + ((P3 + P4 * f) / (1000 + fabs(1.0 * P4 * f)))) / 2.0;
}

int main()
{
    int hp1, hp2, d, s;
    char t[100];
    float p = -1;

    if (doc_File(&hp1, &hp2, &d, &s, t) == 0)
    {
        if ((hp1 < 1) || (hp1 > 999))
        {
            p = -1;
            ghi_File(p);
            return 0;
        }

        if ((hp2 < 0) || (hp2 > 500))
        {
            p = -1;
            ghi_File(p);
            return 0;
        }

        if ((d < 1) || (d > 1000))
        {
            p = -1;
            ghi_File(p);
            return 0;
        }

        if ((s < 1) || (s > 99))
        {
            p = -1;
            ghi_File(p);
            return 0;
        }

        if (checkWeather(t) == 0)
        {
            p = -1;
            ghi_File(p);
            return 0;
        }

        p = caculateP(d, s, t, hp1, hp2);

        if (p < 0)
        {
            p = 0.0;
            ghi_File(p);
        }
        else if (p > 1)
        {
            p = 1.0;
            ghi_File(p);
        }
        else
            ghi_File(p);
    }
}
