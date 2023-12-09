#include<stdio.h>
#include<string.h>

int check(char *str);
int state[4],trans[4][2];

int main() {
    printf("States: (first one is starting state and last one is accepting state)\n");
    for(int i=0;i<4;i++) {
        scanf("%d", &state[i]);
    }
    for(int i=0;i<4;i++) {
        int a,b; scanf("%d %d", &a,&b);
        trans[state[i]][0]=a,trans[state[i]][1]=b;
    }
    char str[1000];
    scanf("%s", str);
    if(check(str)) printf("Accepted...\n");
    else printf("Not accepted...\n");
}

int check(char* str) {
    int init=state[0],prev=init,final;
    for(int i=0;i<strlen(str);i++) {
        if(prev==state[0]) {
            if(str[i]=='0') final=trans[state[0]][0];
            else if(str[i]=='1') final=trans[state[0]][1];
        }
        if(prev==state[1]) {
            if(str[i]=='0') final=trans[state[1]][0];
            else if(str[i]=='1') final=trans[state[1]][1];
        }
        if(prev==state[2]) {
            if(str[i]=='0') final=trans[state[2]][0];
            else if(str[i]=='1') final=trans[state[2]][1];
        }
        if(prev==state[3]) final=trans[state[3]][1];
        prev=final;
        printf("Current state: %d\n", final);
    }
    
    if(final==trans[state[3]][1]) return 1;
    else return 0;
}

/*
 2 3 0 1
 2 3
 2 0
 2 1
 1 1
 00011001111000 (accepted)
 00011000101 (not accecpted)
 */
