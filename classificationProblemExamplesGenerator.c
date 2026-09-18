// Μπουζούκας Κωνσταντίνος - Λευτέρης   5302
// Νικολακόπουλος Αριστείδης            5308
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    FILE *fpt;
    FILE *fpt2;

    fpt = fopen("trainingData.csv", "w+");
    fpt2 = fopen("testData.csv", "w+");

    fprintf(fpt, "X1,X2,Class\n");
    fprintf(fpt2, "X1,X2,Class\n");

    int negInd;

    float x1;
    float x2;
    char c[] = "C0";

    for (int i = 0; i < 4000; i++)
    {
        c[1] = '0';
        negInd = (rand() % 2);
        x1 = (float)rand() / RAND_MAX;
        if (negInd == 1)
        {
            x1 *= -1;
        }

        negInd = (rand() % 2);
        x2 = (float)rand() / RAND_MAX;
        if (negInd == 1)
        {
            x2 *= -1;
        }

        if ((x1 - 0.5) * (x1 - 0.5) + (x2 - 0.5) * (x2 - 0.5) < 0.2 && x2 > 0.5 ||
            (x1 + 0.5) * (x1 + 0.5) + (x2 + 0.5) * (x2 + 0.5) < 0.2 && x2 > -0.5 ||
            (x1 - 0.5) * (x1 - 0.5) + (x2 + 0.5) * (x2 + 0.5) < 0.2 && x2 > -0.5 ||
            (x1 + 0.5) * (x1 + 0.5) + (x2 - 0.5) * (x2 - 0.5) < 0.2 && x2 > 0.5)
        {
            c[1] = '1';
        }
        else if ((x1 - 0.5) * (x1 - 0.5) + (x2 - 0.5) * (x2 - 0.5) < 0.2 && x2 < 0.5 ||
                 (x1 + 0.5) * (x1 + 0.5) + (x2 + 0.5) * (x2 + 0.5) < 0.2 && x2 < -0.5 ||
                 (x1 - 0.5) * (x1 - 0.5) + (x2 + 0.5) * (x2 + 0.5) < 0.2 && x2 < -0.5 ||
                 (x1 + 0.5) * (x1 + 0.5) + (x2 - 0.5) * (x2 - 0.5) < 0.2 && x2 < 0.5)
        {
            c[1] = '2';
        }
        else if (x1 * x2 > 0)
        {
            c[1] = '3';
        }
        else if (x1 * x2 < 0)
        {
            c[1] = '4';
        }

        fprintf(fpt, "%f, %f, %s\n", x1, x2, c);
    }

    for (int i = 0; i < 4000; i++)
    {
        c[1] = '0';
        negInd = (rand() % 2);
        x1 = (float)rand() / RAND_MAX;
        if (negInd == 1)
        {
            x1 *= -1;
        }

        negInd = (rand() % 2);
        x2 = (float)rand() / RAND_MAX;
        if (negInd == 1)
        {
            x2 *= -1;
        }

        if ((x1 - 0.5) * (x1 - 0.5) + (x2 - 0.5) * (x2 - 0.5) < 0.2 && x2 > 0.5 ||
            (x1 + 0.5) * (x1 + 0.5) + (x2 + 0.5) * (x2 + 0.5) < 0.2 && x2 > -0.5 ||
            (x1 - 0.5) * (x1 - 0.5) + (x2 + 0.5) * (x2 + 0.5) < 0.2 && x2 > -0.5 ||
            (x1 + 0.5) * (x1 + 0.5) + (x2 - 0.5) * (x2 - 0.5) < 0.2 && x2 > 0.5)
        {
            c[1] = '1';
        }
        else if ((x1 - 0.5) * (x1 - 0.5) + (x2 - 0.5) * (x2 - 0.5) < 0.2 && x2 < 0.5 ||
                 (x1 + 0.5) * (x1 + 0.5) + (x2 + 0.5) * (x2 + 0.5) < 0.2 && x2 < -0.5 ||
                 (x1 - 0.5) * (x1 - 0.5) + (x2 + 0.5) * (x2 + 0.5) < 0.2 && x2 < -0.5 ||
                 (x1 + 0.5) * (x1 + 0.5) + (x2 - 0.5) * (x2 - 0.5) < 0.2 && x2 < 0.5)
        {
            c[1] = '2';
        }
        else if (x1 * x2 > 0)
        {
            c[1] = '3';
        }
        else if (x1 * x2 < 0)
        {
            c[1] = '4';
        }

        fprintf(fpt2, "%f, %f, %s\n", x1, x2, c);
    }

    fclose(fpt);
    fclose(fpt2);

    return 0;
}