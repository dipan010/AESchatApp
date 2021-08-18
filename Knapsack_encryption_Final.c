#include <stdio.h>
#include<stdlib.h>

int public_key[8],knapsack[8];

int make_knapsack()
{
    int i,minimum=0,maximum=10;
    for(i=0;i<8;i++)
    {
        knapsack[i]=rand() % maximum+minimum;
        minimum+=knapsack[i];
        maximum=minimum+10;
    }
    return minimum;
}

void public_knapsack(int n,int m)
{
    int i;
    for(i=0;i<8;i++)
    {
        public_key[i]=(knapsack[i]*n)%m;
    }
}

int find(int decimal_number)
{
    if (decimal_number == 0)
        return 0;
    else
        return (decimal_number % 2 + 10 *
                find(decimal_number / 2));
}

int encrypt(int *cipher,int n)
{
    int i,sum=0,j=7;
    for(i=0;i<n;i++)
    {
        sum+=(cipher[i]*public_key[j]);
        j--;
    }
    return sum;
}

int main()
{
    int i=0,minimum,m,n,j,hcf=0;

    minimum=make_knapsack();

    m=rand() % 10+minimum;
    
    while(hcf!=1)
    {
        j=rand()% m+2;
        for(i=1;i<=m;i++)
        {
        if(m%i==0 && j%i==0)
        {
        hcf = i;
        }
        }
    }
    n=j;

    printf("n=%d m=%d",n,m);
    public_knapsack(n,m);

    int ch,decimal,deci_arr[30],encrypted;
    FILE *fin,*fout;
    fin=fopen("E:/C_C++/CNS/Knapsack/smstext.txt","r");
    if(fin==NULL)
	{   printf("\n Unable to open the file ");
		exit(1);
	}
    ch=fgetc(fin);
    j=0;

    fout=fopen("E:/C_C++/CNS/Knapsack/smsencrypted.txt","w");

    while (ch!=EOF)
    {
        i=0;
        decimal=find(ch);
        while(decimal!=0)
        {
            deci_arr[i]=decimal%10;
            decimal=decimal/10;
            i++;
        }
        
        encrypted=encrypt(deci_arr,i);
        fprintf(fout,"%d ",encrypted);
        ch=fgetc(fin);
    }
    fclose(fout);
    printf("\nCOMPLETED\n");
    return 0;
}