#include "defs.h"
#include <math.h>

int isPrime(int h2)
{
    if (h2 < 1)
        return 0;
    for (int i = 2; i <= sqrt(h2); i++)
    {
        if (h2 % i == 0)
            return 0;
    }
    return 1;
}

int isFibonaci(int n)
{
    if (n == 1)
        return 1;
    int temp1 = 1, temp2 = 1, temp;
    while (temp2 < n)
    {
        temp = temp1 + temp2;
        temp1 = temp2;
        temp2 = temp;
    }
    if (temp2 == n)
        return 1;
    else
        return 0;
}

int min(int a, int b)
{
    return (a < b ? a : b);
}

int GCD(int a, int b)
{
    int gcd = 0;
    for (int i = 1; i <= a || i <= b; i++)
    {
        if (a % i == 0 && b % i == 0)
        {
            gcd = i;
        }
    }
    return gcd;
}

int calculate(struct musketeer theMusketeer, int R, int N, int nEvent, int *arrEvent)
{
    int mainResult = 0;
    int numEvent;
    int xyEvent;
    int flag = 0;
    int mythrilFlag = 0;
    int faildAvatarFlag = 0;
    int helpOfTitan = 0;
    int count = 0;
    theMusketeer.nBlueDiamonds = 0;
    theMusketeer.nRedDiamonds = 0;
    // Write your code here. Please!
    // Update the return value also. Please!
    if (theMusketeer.ID == 1)
    {
        theMusketeer.nHealthPoint = 999;
        theMusketeer.HP = 999;
    }
    else if (theMusketeer.ID == 2)
    {
        theMusketeer.nHealthPoint = 900;
        theMusketeer.HP = 900;
    }
    else if (theMusketeer.ID == 3)
    {
        theMusketeer.nHealthPoint = 888;
        theMusketeer.HP = 888;
    }
    else
    {
        theMusketeer.nHealthPoint = 777;
        theMusketeer.HP = 777;
    }

    for (int i = 1; i <= nEvent; i++)
    {
        numEvent = arrEvent[i] / 100;
        xyEvent = arrEvent[i] % 100;
        //Get dimond red and blue
        if ((numEvent == 1 || numEvent == 2))
        {
            if (numEvent == 1)
            {
                theMusketeer.nBlueDiamonds++;
            }
            else
            {
                theMusketeer.nRedDiamonds++;
            }

            // theMusketer Porthos
            if (theMusketeer.ID == 3 && numEvent == 1)
            {
                theMusketeer.nBlueDiamonds--;
                theMusketeer.nGoldCoin += arrEvent[i] % 100;
                arrEvent[i] = 0;
            }
        }

        //Fighting with Ambush guards
        if (numEvent == 4)
        {
            //Win 3 times of Porthos
            if (helpOfTitan)
            {
                helpOfTitan--;
                continue;
            }

            int h1 = (arrEvent[i] % 100) * R;
            int h2 = (theMusketeer.nHealthPoint + h1) % (100 + R);

            if (theMusketeer.ID == 2)
            {
                if (isPrime(h2) && h2 > R)
                    if (!mythrilFlag)
                    {
                        theMusketeer.nHealthPoint -= arrEvent[i] % 100;
                    }
                    else
                    {
                        theMusketeer.nHealthPoint -= round((arrEvent[i] % 100) * ((R + 1) / (pow(2, R))));
                    }
                continue;
            }

            //Win
            if (theMusketeer.nHealthPoint >= h1)
            {
                if (theMusketeer.ID == 1 || theMusketeer.ID == 3 || theMusketeer.ID == 4)
                {
                    theMusketeer.nGoldCoin = min((theMusketeer.nGoldCoin + arrEvent[i] % 100), 999);
                }
            }
            else //Lose
            {
                if (!mythrilFlag)
                {
                    theMusketeer.nHealthPoint -= arrEvent[i] % 100;
                }
                else
                {
                    theMusketeer.nHealthPoint -= round((arrEvent[i] % 100) * ((R + 1) / (pow(2, R))));
                }
            }

            if (h2 == 0)
            {
                theMusketeer.nHealthPoint -= arrEvent[i] % 100;
            }

            //Aramis pass Fight
            if (theMusketeer.nHealthPoint < 1 & theMusketeer.ID == 4)
            {
                if (!mythrilFlag)
                {
                    theMusketeer.nHealthPoint += arrEvent[i] % 100;
                }
                else
                {
                    theMusketeer.nHealthPoint += round((arrEvent[i] % 100) * ((R + 1) / (pow(2, R))));
                }
            }

            //Fighting twice
            if (faildAvatarFlag)
            {
                faildAvatarFlag++;
                if (faildAvatarFlag <= 2)
                    i--;
                else
                    faildAvatarFlag = 1;
            }
        }

        //stay with Nina de Rings
        if (numEvent == 5)
        {
            if (flag == 1)
            {
                arrEvent[i] = 0;
                continue;
            }
            int h1 = (arrEvent[i] % 100) * R;
            int h2 = (theMusketeer.nHealthPoint + h1) % (100 + R);

            if (theMusketeer.nHealthPoint >= h1) //Win
            {
                //mythril clothes
                if (isPrime(theMusketeer.nBlueDiamonds) && isPrime(theMusketeer.nRedDiamonds))
                {
                    mythrilFlag = 1;
                    arrEvent[i] = 0;
                }
                else if (theMusketeer.ID == 3)
                {
                    theMusketeer.nRedDiamonds++;
                }
                else
                {
                    theMusketeer.nBlueDiamonds++;
                }
            }
            else //Loser
            {
                theMusketeer.nGoldCoin = (theMusketeer.nGoldCoin) / 2;
                theMusketeer.nHealthPoint -= arrEvent[i] % 100;
            }
            flag = 1;

            if (h2 == 0)
            {
                theMusketeer.nHealthPoint -= arrEvent[i] % 100;
            }
        }
        //Hostel and treatmentHealth
        if (numEvent == 3)
        {
            int pPorthos = 0;
            int HPTemp = min(theMusketeer.nHealthPoint + arrEvent[i] % 100, theMusketeer.HP);
            if (theMusketeer.ID == 3 && R >= 3)
            {
                for (int p = R - 1; p >= 2; p--)
                {
                    if (isPrime(p))
                    {
                        pPorthos = p;
                        break;
                    }
                }
                theMusketeer.nGoldCoin -= (HPTemp - theMusketeer.nHealthPoint) * pPorthos;
                theMusketeer.nHealthPoint = HPTemp;
            }
            else
            {
                theMusketeer.nGoldCoin -= HPTemp - theMusketeer.nHealthPoint;
                theMusketeer.nHealthPoint = HPTemp;
            }
        }

        //Getting Avatar
        if (numEvent == 6)
        {
            int h1 = (arrEvent[i] % 100) * R;
            int h2 = (theMusketeer.nHealthPoint + h1) % (100 + R);
            if (theMusketeer.nBlueDiamonds >= theMusketeer.nRedDiamonds)
            {
                theMusketeer.nHealthPoint = min((theMusketeer.nHealthPoint + arrEvent[i] % 100), theMusketeer.nHealthPoint);
                faildAvatarFlag = 0;
            }
            else
            {
                faildAvatarFlag = 1;
            }
        }

        //Meeting Titan
        if (numEvent == 7)
        {
            int h1 = (arrEvent[i] % 100) * R;
            int h2 = (theMusketeer.nHealthPoint + h1) % (100 + R);

            if (theMusketeer.ID == 3)
            {
                helpOfTitan = 3;
                continue;
            }
            else //Another musketer fighting twice
            {
                if (faildAvatarFlag)
                {
                    faildAvatarFlag++;
                    if (faildAvatarFlag <= 2)
                        i--;
                    else
                        faildAvatarFlag = 1;
                }
            }

            if (theMusketeer.nHealthPoint < h1 && (theMusketeer.ID == 1 || theMusketeer.ID == 2 || theMusketeer.ID == 4))
            {
                if (!mythrilFlag)
                {
                    theMusketeer.nHealthPoint -= arrEvent[i];
                }
                else
                {
                    theMusketeer.nHealthPoint -= round((arrEvent[i]) * ((R + 1) / (pow(2, R))));
                }
            }
            else
            {
                count++;
            }

            // Aramis pass fight
            if (theMusketeer.nHealthPoint < 1 & theMusketeer.ID == 4)
            {
                if (!mythrilFlag)
                {
                    theMusketeer.nHealthPoint += arrEvent[i];
                }
                else
                {
                    theMusketeer.nHealthPoint += round((arrEvent[i]) * ((R + 1) / (pow(2, R))));
                }
            }

            if (h2 == 0)
            {
                theMusketeer.nHealthPoint -= arrEvent[i] % 100;
            }
        }

        //Meeting Paladin Lancelot
        if (numEvent == 8)
        {
            if (theMusketeer.ID == 1)
            {
                return -1;
            }
            else if (theMusketeer.ID == 2 && theMusketeer.nHealthPoint > 700)
            {
                theMusketeer.nGoldCoin = 999;
            }
            else
            {
                int XY = arrEvent[i] % 100;
                int X = XY / 10;
                int Y = XY % 10;
                int diamondsTemp = GCD(X, Y);

                if ((theMusketeer.nHealthPoint <= 700) && (theMusketeer.ID == 3 || theMusketeer.ID == 4))
                {
                    if (X != 0 || Y != 0)
                    {
                        if (theMusketeer.ID == 3)
                        {
                            theMusketeer.nRedDiamonds -= diamondsTemp;
                            for (int j = i - 1; diamondsTemp > 0; j--)
                            {
                                if (arrEvent[j] / 100 == 1)
                                {
                                    arrEvent[j] = 0;
                                    diamondsTemp--;
                                }
                            }
                        }
                        else
                        {
                            theMusketeer.nBlueDiamonds -= diamondsTemp;
                            for (int j = i - 1; diamondsTemp > 0; j--)
                            {
                                if (arrEvent[j] / 100 == 1)
                                {
                                    arrEvent[j] = 0;
                                    diamondsTemp--;
                                }
                            }
                        }
                    }
                }
            }
        }

        // Meeting Paladin Lancelot
        if (numEvent == 9)
        {
            int h1 = (arrEvent[i] % 100) * R;
            int h2 = (theMusketeer.nHealthPoint + h1) % (100 + R);

            if (isFibonaci(i))
            {
                if (theMusketeer.nHealthPoint >= h1)
                {
                    if (theMusketeer.ID == 1)
                    {
                        theMusketeer.nHealthPoint = 999;
                    }
                    else if (theMusketeer.ID == 2)
                    {
                        theMusketeer.nHealthPoint = 900;
                    }
                    else if (theMusketeer.ID == 3)
                    {
                        theMusketeer.nHealthPoint = 888;
                    }
                    else
                    {
                        theMusketeer.nHealthPoint = 777;
                    }

                    theMusketeer.nGoldCoin = 999;
                }
                else
                {
                    return -1;
                }

                if (h2 == 0)
                {
                    theMusketeer.nHealthPoint -= arrEvent[i] % 100;
                }
            }
            else
            {
                return -1;
            }
        }

        // Red diamond equal Blue diamond
        if ((theMusketeer.nBlueDiamonds + theMusketeer.nRedDiamonds) == N)
        {
            break;
        }
        // Win titan
        if (count == 3)
        {
            break;
        }
    }

    if (count < 3)
    {
        if (theMusketeer.nHealthPoint <= 0) //TH2
        {
            return -1;
        }

        if (theMusketeer.nGoldCoin <= 0) //TH3
        {
            return -1;
        }

        if ((theMusketeer.nRedDiamonds + theMusketeer.nBlueDiamonds) != N) //TH4
        {
            return 0;
        }
    }

    // Values of Dimond
    int temp = theMusketeer.nBlueDiamonds + theMusketeer.nRedDiamonds;

    for (int i = 1; i <= nEvent; i++)
    {
        if (temp > 0 && (arrEvent[i] / 100 == 1 || arrEvent[i] / 100 == 5 || arrEvent[i] / 100 == 2))
        {
            mainResult += arrEvent[i] % 100;
            temp--;
        }
        else if (temp == 0)
            break;
    }

    if (count == 3)
    {
        return mainResult += theMusketeer.nHealthPoint + theMusketeer.nGoldCoin;
    }

    mainResult += theMusketeer.nHealthPoint + theMusketeer.nGoldCoin;
    return mainResult;
}
