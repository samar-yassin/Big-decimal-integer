#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
using namespace std;


class bigInteger
{
private :
    string number ;
    bool sign ; // sign =0 for positive , sign = 1 for negative

public :
    bigInteger()
    {
        number ="0";
        sign =false;
    }
    bigInteger(string s)
    {
        if(isdigit(s[0]))
        {
            setNumber(s);
            setSign(false);
        }
        else
        {
            setNumber(s.substr(1));
            setSign(true);

        }
    }
    bigInteger(int n)
    {
        stringstream ss;
        string s;
        ss<<n;
        ss>>s;
        if(isdigit(s[0]))
        {
            setNumber(s);
            setSign(false);
        }
        else
        {
            setNumber(s.substr(1));
            setSign(true);

        }

    }

    bigInteger operator = (bigInteger b)
    {
        setNumber(b.getNumber());
        setSign(b.getSign());
    }

    bool operator <(bigInteger b)
    {
        int len1=this->getNumber().length(),len2=b.getNumber().length();
        if(len1<len2)
            return true;
        else if(len1>len2)
            return false;

        for(int i =0 ; i <len1 ; i++)
        {
            if(this->getNumber()[i]<b.getNumber()[i])
                return true;
            else if(b.getNumber()[i]<b.getNumber()[i])
                return true;
        }

        return false;
    }

    bigInteger operator +(bigInteger b)
    {
        bigInteger res;

        if(getSign()==b.getSign())
        {
            res.setNumber(add(getNumber(),b.getNumber()));
            res.setSign(getSign());
        }
        else
        {
            if(b.getNumber()<getNumber())
            {
                res.setNumber(getDiff(getNumber(),b.getNumber()));
                res.setSign(getSign());
            }
            else
            {
                res.setNumber(getDiff(b.getNumber(),getNumber()));
                res.setSign(b.getSign());
            }
        }

        if(res.getNumber()=="0")
            res.setSign(false);

        return res;

    }

    bigInteger operator -(bigInteger b)
    {
        b.setSign(!b.getSign());
        return *this+b;
    }

    void setNumber(string s)
    {
        number =s;
    }

    string getNumber()
    {
        return number;
    }

    void setSign(bool n)
    {
        sign=n;
    }

    bool getSign()
    {
        return sign;
    }

    int size()
    {
        return number.length();
    }



    string add(string num1,string num2)
    {
        if(num1.length()>num2.length())
            swap(num1,num2);

        string res="";

        int len1 = num1.length(),len2 = num2.length();

        reverse(num1.begin(),num1.end());
        reverse(num2.begin(),num2.end());

        int carry =0;
        int sum=0;
        for(int i=0 ; i <len1;i++){
            sum =((num1[i]-'0')+(num2[i]-'0')+carry);
            res.push_back((sum%10)+'0');
            carry=sum/10;
        }
      for(int i =len1 ;i <len2 ;i++){
            sum =((num2[i]-'0')+carry);
            res.push_back((sum%10)+'0');
            carry=sum/10;
        }

        if(carry){
            res.push_back(carry+'0');
        }

        reverse(res.begin(),res.end());

        return res;

    }



    string getDiff(string num1, string num2)
    {
        cout<<"n1 : "<<num1<<endl;
        string res="";

        int len1 = num1.length(),len2 = num2.length();

        int diff= len1-len2 ;

        int sub=0 ,carry=0;

        for(int i =len2-1 ; i>=0 ; i--){
            sub = (num1[i+diff]-'0')-(num2[i]-'0')-carry ;

            if(sub<0){
                sub+=10;
                carry=1;
            }
            else carry =0;

            res.push_back(sub + '0');
        }

        for(int i =diff-1 ; i>=0 ; i--){

            if(num1[i]=='0'&&carry){
                res.push_back('9');
                continue;
            }

            sub=(num1[i]-'0')-carry;

            if(i>0||sub>0)
                res.push_back(sub+'0');

            carry=0;

        }


        reverse(res.begin(),res.end());

        return res;

    }



    friend ostream& operator<<(ostream& o, bigInteger& b)
    {
        if(b.getSign())
            o<<"-";

        o<<b.getNumber();

        return o;
    }


};


int main()
{
    string str1,str2,choice;
    while (true)
    {
        cout << "Welcome to FCI Calculator\n------------------------------\n";
        cout <<"1- Perform Addition\n2- Perform Subtraction\n3- Exit\n";
        cin>>choice;
        if(choice!="1"&&choice!="2"&&choice!="3")
            cout <<endl<<"\t|!|Something went wrong."<<endl<<endl;
        else if(choice=="3")
            return 0;
        else
        {
            cout <<"enter first number : ";
            cin>>str1;
            cout <<"enter second number : ";
            cin>>str2;

            bigInteger a(str1), b(str2);
            bigInteger c;

            if(choice=="1")
                c= a+b;
            else if(choice=="2")
                c=a-b;
            else
                return 0;

            cout<<a.getSign()<<endl<<b.getSign()<<endl;
            cout<<endl<<"\t--This equals = "<<c<<endl<<endl;

        }
    }
    return 0;
}
