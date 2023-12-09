#include<bits/stdc++.h>
#include "aes_encrypt.h"
#include "aes_decrypt.h"
#include "SHA_512.h"
#include "rsa.h"

using namespace std;
int main()
{

    printf("Enter your choice : \n");
    cout<<"1.AES Encryption\n";
    cout<<"2.AES Decryption\n";
    cout<<"3.SHA512 HASH TOOL\n";
    cout<<"4.RSA ENCRYPTION AND DECRYPTION\n";
    int choice;
    cin>>choice;
    getchar();
    if(choice == 1)
    {
       aes_encryption();
    }
    else if(choice == 2)
    {
        aes_decryption();
    }
    else if(choice == 3) 
    {
        hash_sha512();
    }
    else if(choice==4)
    {
        rsa_algo();
    }
    return 0;
}
