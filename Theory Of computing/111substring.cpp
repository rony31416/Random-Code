#include<stdio.h>
#include<string.h>
int main()
{
    char states[10],acceptState,startState;
    char zero[100][3]= {"",""};
    int numberOfState;

    printf("Enter the number of states : ");
    scanf("%d",&numberOfState);


    printf("Enter all states : ");
    for(int i = 0 ; i < numberOfState ; i++)
    {
        scanf(" %c",&states[i]);
    }


    printf("Enter starting state : ");
    scanf(" %c",&startState);

    printf("Enter accepting state: ");
    scanf(" %c",&acceptState);

    printf("Enter transition table : \n");
    printf("ð | 0 | 1\n");
    printf("---------\n");

    for(int ii = 0 ; ii < numberOfState ; ii++)
    {
        char c1,c2,c;
        scanf(" %c",&c);
        scanf(" %c",&c1);
        scanf(" %c",&c2);
        int i;
        for( i = 0 ; i < numberOfState ; i++)
        {
            if(states[i] == c)
            {
                break;
            }
        }
        zero[i][0] = c1;
        zero[i][1] = c2;
    }


    int length;
    char checkString[200] = {'0'};
    printf("Enter the string for check : ");
    scanf("%s",checkString);
    length = strlen(checkString);

    int index,k,tt;
    char temp,currentState;
    for(index = 0,tt = 0 ; tt< length ; tt++)
    {
        char c = checkString[tt];
        if(c == '0')
        {
            currentState = zero[index][0];
            int k;
            for( k = 0 ; k< numberOfState; k++ )
            {
                if(states[k] == currentState)break;
            }

            index = k;
        }
        else
        {
            currentState = zero[index][1];
            int k;
            for( k = 0 ; k< numberOfState; k++ )
            {
                if(states[k] == currentState)break;
            }

            index = k;
        }
        printf("Current state -> %c  \n",currentState);
    }
    if(states[index] == acceptState)
    {
        printf("\n\nAccepted\n");
    }
    else
    {
        printf("\n\nNot Accepted\n");
    }
    return 0;
}
/*
//sample input

Enter the number of state : 4
Enter the states : a b c d
Enter starting state : a
Enter accepting state: d
Enter transition table:
ð | 0 | 1
----------
a   a   b
b   a   c
c   a   d
d   d   d
Enter the string for check : 10111001

Current state -> b
Current state -> a
Current state -> b
Current state -> c
Current state -> d
Current state -> d
Current state -> d
Current state -> d

Accepted
*/