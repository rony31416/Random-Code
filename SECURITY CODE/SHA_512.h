#ifndef SHA512_H
#define SHA512_H

#define N 1024
using namespace std;
typedef long long ll;
typedef bitset<1024>block;
typedef bitset<64>word;
const word k[80] = { 0x428a2f98d728ae22, 0x7137449123ef65cd,
                     0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
                     0x3956c25bf348b538, 0x59f111f1b605d019,
                     0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
                     0xd807aa98a3030242, 0x12835b0145706fbe,
                     0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
                     0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
                     0x9bdc06a725c71235, 0xc19bf174cf692694,
                     0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
                     0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
                     0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
                     0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
                     0x983e5152ee66dfab, 0xa831c66d2db43210,
                     0xb00327c898fb213f, 0xbf597fc7beef0ee4,
                     0xc6e00bf33da88fc2, 0xd5a79147930aa725,
                     0x06ca6351e003826f, 0x142929670a0e6e70,
                     0x27b70a8546d22ffc, 0x2e1b21385c26c926,
                     0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
                     0x650a73548baf63de, 0x766a0abb3c77b2a8,
                     0x81c2c92e47edaee6, 0x92722c851482353b,
                     0xa2bfe8a14cf10364, 0xa81a664bbc423001,
                     0xc24b8b70d0f89791, 0xc76c51a30654be30,
                     0xd192e819d6ef5218, 0xd69906245565a910,
                     0xf40e35855771202a, 0x106aa07032bbd1b8,
                     0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
                     0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
                     0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
                     0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
                     0x748f82ee5defb2fc, 0x78a5636f43172f60,
                     0x84c87814a1f0ab72, 0x8cc702081a6439ec,
                     0x90befffa23631e28, 0xa4506cebde82bde9,
                     0xbef9a3f7b2c67915, 0xc67178f2e372532b,
                     0xca273eceea26619c, 0xd186b8c721c0c207,
                     0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
                     0x06f067aa72176fba, 0x0a637dc5a2c898a6,
                     0x113f9804bef90dae, 0x1b710b35131c471b,
                     0x28db77f523047d84, 0x32caab7b40c72493,
                     0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
                     0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
                     0x5fcb6fab3ad6faec, 0x6c44198c4a475817
                   };
string str;
ll blockNumber;
block bk[1000]= {};
word rotr(word w,ll k)
{
    return (w>>k)|(w<<(64-k));
}
word phi0_512(word w)
{
    return rotr(w,1)^rotr(w,8)^w>>7;
}
word phi1_512(word w)
{
    return rotr(w,19)^rotr(w,61)^w>>6;
}

void makeWord(block b, word w[])
{
    for(ll i=0; i<16; i++)
    {
        ll k=63;
        for(ll j=1023; j>959; j--)
        {
            w[i][k--]=b[j];
        }
        b<<=64;
    }
    for(ll i=16; i<80; i++)
    {
        w[i]=(w[i-16].to_ullong()+phi0_512(w[i-15]).to_ullong()+w[i-7].to_ullong()+phi1_512(w[i-2]).to_ullong());
    }
}

 /*
     Ch(E, F, G) = (E AND F) XOR ((NOT E) AND G)
     Ma(A, B, C) = (A AND B) XOR (A AND C) XOR (B AND C)
         ∑(A)    = (A >>> 2) XOR (A >>> 13) XOR (A >>> 22)
         ∑(E)    = (E >>> 6) XOR (E >>> 11) XOR (E >>> 25)
          +      = addition modulo 2⁶⁴     */

word calculateT1(word e,word f,word g,word h, word w,word k)
{

    word ch=(e&f)^(~e&g);
    word condition=rotr(e,14)^rotr(e,18)^rotr(e,41);
    return (h.to_ullong()+ch.to_ullong()+condition.to_ullong()+w.to_ullong()+k.to_ullong())&(0xffffffffffffffff);
}
word calculateT2(word a, word b, word c)
{
    word maj=(a&b)^(b&c)^(c&a);
    word x=rotr(a,28)^rotr(a,34)^rotr(a,39);
    return maj.to_ullong()+x.to_ullong();
}
void padding(block b[])
{
    stringstream fixedstream;
    for (int i = 0; i < str.size(); ++i)
    {
        fixedstream << bitset<8>(str[i]);
    }
    string binStr;
    binStr = fixedstream.str();

     //cout<<"print "<<binStr<<"\n";

    int strLen = binStr.length();
    //cout<<"test len :"<<str.size()<<"binstr len " <<strLen<<"\n";
    int paddingZero;
    int remainning = binStr.length() % 1024;

    if (1024 - remainning >= 128)
    {
        paddingZero = 1024 - remainning;
    }
    else if (1024 - remainning < 128)
    {
        paddingZero = 2048 - remainning;
    }
    binStr += "1";
    for (int y = 0; y < paddingZero - 129; y++)
    {
        binStr += "0";
    }
    string lengthbits= std::bitset<128>(strLen).to_string();
    binStr += lengthbits;

 //   cout<<"length bits : "<< lengthbits<<"\n";
    //cout<<"print "<<binStr<<"\n";

    ll n=-1;
    blockNumber=binStr.length()/1024;
    for(ll i=0; i<binStr.length(); i++)
    {
        if(i%1024==0)
        {
            n++;
            b[n].reset();
        }
        b[n][1023-i%1024]=binStr[i]-48;
    }
}

int hash_sha512()
{
    ios::sync_with_stdio(false);

    cout << "=============================" << endl;
	cout << "     SHA-512 Tool " << endl;
	cout << "=============================" << endl;
    cout<<"Enter your text for generarting hash\n";
	getline(cin, str);
	cout << str << endl;


    word a = 0x6a09e667f3bcc908;
    word b = 0xbb67ae8584caa73b;
    word c = 0x3c6ef372fe94f82b;
    word d = 0xa54ff53a5f1d36f1;
    word e = 0x510e527fade682d1;
    word f = 0x9b05688c2b3e6c1f;
    word g = 0x1f83d9abfb41bd6b;
    word h = 0x5be0cd19137e2179;
    word A=a,B=b,C=c,D=d,E=e,F=f,G=g,H=h;
    padding(bk);
    for(ll i=0; i<blockNumber; i++)
    {
        word w[80]= {};
        makeWord(bk[i],w);
        for(ll j=0; j<80; j++)
        {
            word T1=calculateT1(e,f,g,h,w[j],k[j]);
            word T2=calculateT2(a,b,c);
            h=g;
            g=f;
            f=e;
            e=(d.to_ullong()+T1.to_ullong());
            d=c;
            c=b;
            b=a;
            a=(T1.to_ullong()+T2.to_ullong());

        }
        a=(A.to_ullong()+a.to_ullong());
        b=(B.to_ullong()+b.to_ullong());
        c=(C.to_ullong()+c.to_ullong());
        d=(D.to_ullong()+d.to_ullong());
        e=(E.to_ullong()+e.to_ullong());
        f=(F.to_ullong()+f.to_ullong());
        g=(G.to_ullong()+g.to_ullong());
        h=(H.to_ullong()+h.to_ullong());
        //cerr<<a.to_ullong()<<" "<<b.to_ullong()<<endl;
        A=a,B=b,C=c,D=d,E=e,F=f,G=g,H=h;
    }
    cout<<hex<<a.to_ullong()<<b.to_ullong()<<c.to_ullong()<<d.to_ullong()<<e.to_ullong()<<f.to_ullong()<<g.to_ullong()<<h.to_ullong()<<endl;
    return 0;
}
#endif
