#include<stdio.h>
// The source code was downloaded from the GitHub account MiskatHossain8.
int dp[100][100];
int coins[100];
int sortMatching(int *a, int *b) {
    return *a-*b;
}

void bubbleSort(int x[], int y[], int z[], int n)
{
    int temp;
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(y[j]>y[j+1])
            {
                temp=x[j];
                x[j]=x[j+1];
                x[j+1]=temp;

                temp=y[j];
                y[j]=y[j+1];
                y[j+1]=temp;

                temp=z[j];
                z[j]=z[j+1];
                z[j+1]=temp;
            }
        }
    }
}
void activitySelection(int x[], int y[],int m,int z[],int n)
{
    int i, j,result;
    i = 0;
    for (int k = 0; k <= m; k++)
    {
        for (int j = 0; j <= z[i]; j++)
        {
            dp[k][j] = -1;
        }
    }
    result= coinChange(m,z[i]);
    while (result <= 0)
    {
        i++;
        if (i >= n)
        {
            printf("\nNo more activities available.");
            return;
        }
        //printf("\n%d Activity Start at %d, Finish at %d Selected ", i + 1, x[i], y[i]);

        for (int k = 0; k <= m; k++)
        {
            for (int j = 0; j <= z[i]; j++)
            {
                dp[k][j] = -1;
            }
        }

        result = coinChange(m, z[i]);
    }
    if (result > 0)
    {
        int a,b;
        a=m;
        b=z[i];
        printf("%d Activity Start at %d, Finish at %d Selected ",i+1, x[i], y[i]);
        printf("\nPossible to Pay with ");
        while (a > 0 && b > 0)
        {
            if (dp[a][b] == dp[a - 1][b])
            {
                a--;
            }
            else
            {
                printf("%d ", coins[a - 1]);
                b = b-coins[a - 1];
            }
        }
        printf(" Coins");
    }
    else
    {
        printf("\nNot Possible to pay with available coins");
    }
    printf("\n\n");
    for (j = 1+i; j < n; j++)
    {
        if (x[j] >= y[i])
        {
            for (int k = 0; k <= m; k++)
            {
                for (int l = 0; l <= z[j]; l++)
                {
                    dp[k][l] = -1;
                }
            }
            result= coinChange(m,z[j]);
            while (result <= 0)
            {
                j++;
                if (j >= n)
                {
                    printf("\nNo more activities available.");
                    return;
                }
                //printf("\n%d Activity Start at %d, Finish at %d Selected ", i + 1, x[i], y[i]);

                for (int k = 0; k <= m; k++)
                {
                    for (int l = 0; l <= z[j]; l++)
                    {
                        dp[k][l] = -1;
                    }
                }

                result = coinChange(m, z[j]);
            }
            if (result > 0)
            {
                int a,b;
                a=m;
                b=z[j];
                printf("%d Activity Start at %d, Finish at %d Selected ",j+1, x[j], y[j]);
                printf("\nPossible to Pay with ");
                while (a > 0 && b > 0)
                {
                    if (dp[a][b] == dp[a - 1][b])
                    {
                        a--;
                    }
                    else
                    {
                        printf("%d ", coins[a - 1]);
                        b = b-coins[a - 1];
                    }
                }
                printf("Coins");
            }
            else
            {
                printf("\nNot Possible to pay with available coins");
            }
            i = j;
            printf("\n\n");
        }
    }
}

int coinChange(int m, int k)
{
    if (k == 0)
    {
        return 1;
    }
    if (k < 0 || m == 0)
    {
        return 0;
    }
    if (dp[m][k] != -1)
    {
        return dp[m][k];
    }
    dp[m][k] = coinChange(m, k - coins[m - 1]) + coinChange(m - 1, k);
    return dp[m][k];
}

int main()
{
    int n, shoppingStart[100], shoppingFinish[100], spent[100];
    int m;
    printf("Input the number of Activities/Shopping Malls: ");
    scanf("%d",&n);
    printf("Input the number of coins variety: ");
    scanf("%d",&m);
    printf("Enter the numbers of shopping starting, finishing time and spent coins of \n");
    for(int i=0; i<n; i++)
    {
        printf("Activity %d: ",i+1);
        scanf("%d %d %d",&shoppingStart[i],&shoppingFinish[i],&spent[i]);
    }
    printf("Enter the amount of each coins: ");
    for(int j=0; j<m; j++)
    {
        scanf("%d",&coins[j]);
    }
    printf("\n");
    qsort(coins, m, sizeof(int), sortMatching);
    bubbleSort(shoppingStart,shoppingFinish,spent,n);
    activitySelection(shoppingStart, shoppingFinish,m,spent,n);

}