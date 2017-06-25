#include <iostream>
#include <conio.h>
#include <string>
#include "math.h"
#include <windows.h>


using namespace std;

void dec_to_hex(char*buffer,int number)
{
    long int decimalNumber,remainder,quotient;
    int i=1,j,temp;
    char hexadecimalNumber[100];

    decimalNumber=number;

    quotient = decimalNumber;

    while(quotient!=0)
    {
         temp = quotient % 16;

      //To convert integer into character
      if( temp < 10)
           temp =temp + 48;
      else
         temp = temp + 55;

      hexadecimalNumber[i++]= temp;
      quotient = quotient / 16;
    }
    int p=0;
    if(i==2)
    {
        buffer[0]='0';
        p=1;
    }
    for(j = i -1 ;j> 0;j--)
    {
        buffer[p]=hexadecimalNumber[j];
        p++;
    }
    return;
}

int hex2dec(string hex)
{
    unsigned long result = 0;
    for (int i=0; i<hex.length(); i++) {
        if (hex[i]>=48 && hex[i]<=57)
        {
            result += (hex[i]-48)*pow(16,hex.length()-i-1);
        } else if (hex[i]>=65 && hex[i]<=70) {
            result += (hex[i]-55)*pow(16,hex.length( )-i-1);
        } else if (hex[i]>=97 && hex[i]<=102) {
            result += (hex[i]-87)*pow(16,hex.length()-i-1);
        }
    }
    return result;
}


int main()
{
    unsigned int S[256]; ///array con valores del 0 al 256
    unsigned int K[256]; /// array con valores de la llave
    for(int i=0;i<256;i++)
    {
        S[i]=i;
        //cout<<"Inserto "<<S[i]<<" en S"<<endl;
        //Sleep(100);
    }
    string key="Key";
    char pass[key.size()];
    int j=0;
    int auxi;
    for(int i=0;i<key.size();i++)
    {
        pass[i]=key[i];
    }
    ///KSA
    for (int i=0;i<256;i++)
    {
        j=(j+S[i]+(int)pass[i%key.size()])%256;
        auxi=S[j];
        S[j]=S[i];
        S[i]=auxi;
    }
    char buffer[2];
    ///PRGA
    int a=0,b=0;
    string text="Plaintext";
    int message[text.size()];
    for (int i=0;i<text.size();i++)
    {
        message[i]=(int)text[i];
        cout<<message[i]<<endl;
    }
    for (int i=0;i<256;i++)
    {
        a=(a+1);
        b=(b+S[a])%256;
        auxi=S[a];
        S[a]=S[b];
        S[b]=auxi;
        dec_to_hex(buffer,S[(S[a]+S[b])%256]);
        K[i]=S[(S[a]+S[b])%256];
        cout<<S[(S[a]+S[b])%256]<<" -> "<<buffer[0]<<buffer[1]<<": "<<K[i]<<endl;
    }
    int ixor;

    for (int i=0;i<text.size();i++)
    {
        ixor=K[i]^message[i];
        dec_to_hex(buffer,ixor);
        cout<<ixor<<" -> "<<buffer[0]<<buffer[1]<<endl;
    }
    string cypher="BBF316E8D940AF0AD3";
    int decypher[cypher.size()/2];
    for (int i=0;i<cypher.size()/2;i++)
    {
        decypher[i]=hex2dec(cypher.substr(i*2,2));
    }
    for(int i=0;i<cypher.size()/2;i++)
    {
        ixor=decypher[i]^K[i];
        char aux=ixor;
        cout<<aux;
    }
    cout<<endl;
        /*
    int aux;
    for(int i=0;i<256;i++)
    {
        //cout<<pass[i%key.size()]<<endl;
        //aux=(int)pass[i%key.size()];
        //cout<<aux<<endl;
        K[i]=(int)pass[i%key.size()];
        cout<<"Inserto "<<K[i]<<" en K"<<endl;
        //Sleep(100);
    }

    ///KSA
    for(int i=0;i<256;i++)
    {
        j=(j+S[i]+K[i])%256;
        cout<<"Intercambia: "<<S[i]<<" por "<<S[j]<<endl;
        Sleep(100);
        auxi=S[j];
        S[i]=S[j];
        S[j]=auxi;
    }
    */

}
