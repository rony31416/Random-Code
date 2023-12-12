#include<stdio.h>
#include<math.h>
# define MAXN 10
int main()
{
    int n=4;
    double rat,sum;
    double x[MAXN + 1]= { 0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0 };
    double f[MAXN + 1]= { 1.0,1.04,1.16,1.36,1.64,2.0,2.44,2.96,3.56,4.24,5.0 };
    double matrix[MAXN+1][4];
    double coefficient[MAXN+1][1];
    double t_matrix[4][MAXN+1];
    double mul[4][4];
    double mulCoefficient[4][1];
    double augmentMat[4][4+1];
    double value[4];

    //initialize matrix
    for(int i=0; i<MAXN+1; i++)
    {
        matrix[i][0]=1;

        matrix[i][1]=x[i];

        matrix[i][2]=x[i]*x[i];
        matrix[i][3]=x[i]*x[i]*x[i];


    }
    //print matrix
    printf("matrix:\n");

    for(int i=0; i<MAXN+1; i++)
    {
        for(int j=0; j<4; j++)
            printf("%lf        ",matrix[i][j]);
        printf("\n");
    }
    printf("\n");

    for(int i=0; i<MAXN+1; i++)
        coefficient[i][0]=f[i];

    //transpose matrix

    for(int i=0; i<MAXN+1; i++)
    {
        for(int j=0; j<4; j++)
        {
            t_matrix[j][i]=matrix[i][j];
        }

    }
    printf("\n");
//print t_matrix
    printf("transpose matrix\n");
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<MAXN+1; j++)
            printf("%lf        ",t_matrix[i][j]);
        printf("\n");
    }
    printf("\n");


    //t_matrix*matrix
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            mul[i][j]=0;
        }
    }

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<MAXN+1; k++)
            {
                mul[i][j]+=(t_matrix[i][k]*matrix[k][j]);
            }
        }
    }

    //print t*m
    printf("transpose*matrix\n");
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            //mul[i][j]=0;
            printf("%lf   ",mul[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //t_matrix*coefficient
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<1; j++)
        {
            mulCoefficient[i][j]=0;
        }
    }

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<1; j++)
        {
            for(int k=0; k<MAXN+1; k++)
            {
                mulCoefficient[i][j]+=(t_matrix[i][k]*coefficient[k][j]);
            }
        }
    }

//print t*c
    printf("transpose* Coefficient_matrix\n");
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<1; j++)
            printf("%lf   ",mulCoefficient[i][j]);
        printf("\n");
    }

    printf("\n");




    for(int i=0; i<4; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(j==4)
                augmentMat[i][j]=mulCoefficient[i][0];
            else
                augmentMat[i][j]=mul[i][j];

        }
    }

    printf("augment matrix\n");
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<5; j++)
            printf("%lf   ",augmentMat[i][j]);
        printf("\n");
    }

    //convert upper triangular matrix

    for( int i=0; i<4; i++)
    {

        for(int j=0; j<4; j++)
        {
            if(j>i)
            {
                rat=augmentMat[j][i]/augmentMat[i][i];
                for(int k=0; k<n+1; k++)
                    augmentMat[j][k]=augmentMat[j][k] -( rat * augmentMat[i][k]);



            }
        }
    }
    //back substitution

    value[n-1]=augmentMat[n-1][n]/augmentMat[n-1][n-1];

    for(int i=n-2; i>=0; i--)
    {
        sum=0;
        for(int j=i+1; j<n; j++)
            sum=sum+augmentMat[i][j]*value[j];
            value[i] = (augmentMat[i][n]-sum)/augmentMat[i][i];
    }
    //print result

    for(int i=0; i<4; i++)
    {
        printf("c[%d]=%lf \n",i,value[i]);
    }


}
