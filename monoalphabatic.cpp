#include <bits/stdc++.h>
using namespace std;

unordered_map<char, char> hashMap;

string encrypt(string msg)
{
    string ciphertext;
    for (int i = 0; i < msg.size(); i++)
    {
        ciphertext.push_back(hashMap[msg[i]]);
    }

    return ciphertext;
}

string decrypt(string msg)
{
    string plaintext;
    for (int i = 0; i < msg.size(); i++)
    {
        if(msg[i] == '1')  plaintext.push_back(' ');
        else plaintext.push_back(hashMap[msg[i]]);
    }

    return plaintext;
}

void hashFn(string a,int n, string b)
{
    
    for (int i = 0; i < n; i++)
    {
        hashMap.insert(make_pair(a[i], b[i]));
    }
    hashMap['1'] = '1';
}

string makeCircularRotation(string input, int targetLength) {
    int inputLength = input.length();

    if (inputLength >= targetLength) {
        return input.substr(0, targetLength); // Truncate if necessary
    }

    // Perform circular rotation to make the string length 26
    while (input.length() < targetLength) {
        input += input; // Double the string
    }

    return input.substr(0, targetLength);
}

int main()
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string alphabet2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    string substitution,sub;
    //cout << "Enter the key : ";
    //cin >> sub;
    int targetLength = 26;
    sub = "qwertyuioplkjhgfdaszxcvbnm";
   string sub2 = "QWERTYUIOPLKJHGFDASZXCVBNM";

    substitution = makeCircularRotation(sub, targetLength);

    cout << "Enter the message : ";
    string message;
    string line;
    int numOfLine = 0;
    while (true)
    {
        getline(cin, line);
        if (line.empty())
        {
            break;
        }
        message += line + ' ';
        numOfLine++;
    }


    cout << "You entered the following message:\n";
    cout << message<<"\n";
    numOfLine = message.size() - numOfLine;
    cout <<"message length : "<<numOfLine << endl;
    
    for(int i = 0 ; i< numOfLine ; i++) 
    {
        if(message[i] == ' ')
        {
            message[i] = '1';
        }
    }

    hashFn(alphabet,targetLength, substitution);
    hashFn(alphabet2,targetLength, sub2);

    string cipher = encrypt(message);
    cout << "Encrypted Cipher Text: " << cipher << endl;
    hashMap.clear();
    hashFn(substitution,targetLength, alphabet);
     hashFn(sub2,targetLength, alphabet2);
    string plain = decrypt(cipher);
    cout << "Decrypted Plain Text: " << plain << endl;
}