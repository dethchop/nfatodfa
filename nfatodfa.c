#include <stdio.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 5

int n, m;
char symbols[MAX_SYMBOLS];


int nfa[MAX_STATES][MAX_SYMBOLS][MAX_STATES];


int dfaStates[100][MAX_STATES];
int dfaCount = 0;


int dfaTrans[100][MAX_SYMBOLS];


int equal(int a[], int b[])
{
    for(int i=0;i<n;i++)
        if(a[i]!=b[i])
            return 0;
    return 1;
}

int findSubset(int subset[])
{
    for(int i=0;i<dfaCount;i++)
        if(equal(subset, dfaStates[i]))
            return i;
    return -1;
}

void addSubset(int subset[])
{
    for(int i=0;i<n;i++)
        dfaStates[dfaCount][i]=subset[i];
    dfaCount++;
}

int main()
{
    int i,j,k;

    printf("Enter number of NFA states: ");
    scanf("%d",&n);

    printf("Enter number of input symbols: ");
    scanf("%d",&m);

    printf("Enter input symbols: ");
    for(i=0;i<m;i++)
        scanf(" %c",&symbols[i]);


    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            int count;

            printf("Number of transitions from q%d using %c: ",i,symbols[j]);
            scanf("%d",&count);

            printf("Enter destination states: ");

            while(count--)
            {
                scanf("%d",&k);
                nfa[i][j][k]=1;
            }
        }
    }

    int start[MAX_STATES]={0};
    start[0]=1;

    addSubset(start);


    for(i=0;i<dfaCount;i++)
    {
        for(j=0;j<m;j++)
        {
            int newSubset[MAX_STATES]={0};

            for(k=0;k<n;k++)
            {
                if(dfaStates[i][k])
                {
                    for(int x=0;x<n;x++)
                    {
                        if(nfa[k][j][x])
                            newSubset[x]=1;
                    }
                }
            }

            int index=findSubset(newSubset);

            if(index==-1)
            {
                addSubset(newSubset);
                index=dfaCount-1;
            }

            dfaTrans[i][j]=index;
        }
    }


    printf("\nDFA States:\n");

    for(i=0;i<dfaCount;i++)
    {
        printf("D%d = { ",i);

        for(j=0;j<n;j++)
            if(dfaStates[i][j])
                printf("q%d ",j);

        printf("}\n");
    }


    printf("\nDFA Transition Table\n");

    printf("--------------------------------\n");
    printf("State\t");

    for(i=0;i<m;i++)
        printf("%c\t",symbols[i]);

    printf("\n--------------------------------\n");

    for(i=0;i<dfaCount;i++)
    {
        printf("D%d\t",i);

        for(j=0;j<m;j++)
            printf("D%d\t",dfaTrans[i][j]);

        printf("\n");
    }

    return 0;
}
