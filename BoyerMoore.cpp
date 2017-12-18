#include <chrono>
# include <limits.h>
# include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
# define NO_OF_CHARS 256

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}
void getInput(char *txt, char *pat)
{
    ifstream fin1("Text.txt");//Text File
    ifstream fin2("Pattern.txt");//Pattern File
    string line1,line2;
    //Take txt file into char[] txt
    if (fin1.is_open())
  {
    while (getline (fin1,line1)){}
   fin1.close();
  }
  else cout << "Unable to open file";

  	//Take pattern file into char[] pat
     if (fin2.is_open())
  {
    while (getline (fin2,line2)){}
    fin2.close();
  }
    else cout << "Unable to open file";

        /*fin1.open(text);//work for no space text
    if ( !fin1 )
	{
		cout << "Error reading file. Program Exit." << endl;//check file exist
	}
	fin1>> txt;*/

   /* fin2.open(pattern);//work for no space pattern
    if ( !fin2 )
	{
		cout << "Error reading file. Program Exit." << endl;//check file exist

	}
	fin2>> pat;
}*/
strcpy(txt, line1.c_str());
strcpy(pat, line2.c_str());
}
// The preprocessing function for Boyer Moore'sLastOccuranceHeuristic
void LastOccuranceHeuristic(char *str, int size, int LastOccurance[NO_OF_CHARS])
{
    int i;

    for (int i=0;i<=size;i++)
        {
            LastOccurance[(int) str[i]]=i;
        }
    for (i = 0; i < size; i++)
        {
            LastOccurance[(int) str[i]] = i;
        }
    cout<<"Last= ";
    for(int i=0;i<size;i++)
        {
        cout<<LastOccurance[(int) str[i]];
        }
    cout<<endl;
    system("PAUSE");
    system("Cls");
    // Fill the actual value of last occurrence of a character
      /*  for (int i=0;i<size;i++){
      for (int j=0;j<=size;j++)
    {
        if (str[i]==str[j]&& LastOccurance[(int) str[i]]<=LastOccurance[(int) str[j]])
        {
               LastOccurance[(int) str[i]]=LastOccurance[(int) str[j]];
        }
    }
}*/
    // Fill the actual value of last occurrence of a character
}
void LastOccuranceHeuristic1(char *str, int size, int LastOccurance[NO_OF_CHARS])//to show time spend for txt >60
{
    int i;

    for (int i=0;i<=size;i++)
        {
            LastOccurance[(int) str[i]]=i;
        }
    for (i = 0; i < size; i++)
        {
            LastOccurance[(int) str[i]] = i;
        }
    cout<<"Last= ";
    for(int i=0;i<size;i++)
        {
        cout<<LastOccurance[(int) str[i]];
        }
    cout<<endl;
}
void suffix(char *pat, int *suff)
{
    int len = strlen(pat);
    int f = 0, g;
    suff[len - 1] = len;
    g = len - 1;
    for (int i = len - 2; i >= 0; --i)
        {
            if (i > g && suff[i + len - 1 - f] < i - g)
                suff[i] = suff[i + len - 1 - f];
            else
            {
                if (i < g) g = i;
                f = i;
                while (g >= 0 && pat[g] == pat[g + len - 1 - f]) --g;
                suff[i] = f - g;
            }
        }
}
void GoodStr(char *pat,int *goodStr) {
    int len = strlen(pat);
    int suff[len];
    int m=strlen(pat);
    suffix(pat, suff);

    for(int i = 0; i < len; i++)
        goodStr[i] = len;


    int j = 0;
    for(int i = len - 1; i >= 0; i--)
    {
        if(suff[i] == i + 1)
        {
            for(; j < len - 1 - i; j++)
            {
                if(goodStr[j] == len)
                    goodStr[j] = len - 1 - i;
            }
        }
    }

    for(int i = 0; i <= len - 2; i++)
    {
        goodStr[len - 1 - suff[i]] = len - 1 - i;
    }
}
void BoyerMoore(char *txt, char *pat, int &count2,int (&temp)[256],int &compare)//stop after finding 1 matching pattern
{
    compare=0;
    int m = strlen(pat);
    int n = strlen(txt);
    int LastOccurance[NO_OF_CHARS];
    int GoodSufflixes[m];
    LastOccuranceHeuristic(pat, m, LastOccurance);
    GoodStr(pat,GoodSufflixes);
    count2=0;
    temp[count2];
    int s = 0; // s is array of the pattern with respect to text
    while (s <= (n - m))
    {
        int j = m - 1;
        while (j >= 0 && pat[j] == txt[s + j])
        {
            j--;
            cout<<endl;
            cout<<txt<<endl;
            for (int k=(s+j);k>=0;k--)
            cout<<" ";
            cout<<"|"<<endl;
            for(int k=(s-1);k>=0;k--)
            cout<<" ";
            cout<<pat<<endl;
            compare++;
            cout<<"Compare :"<<compare<<endl;
            system("PAUSE");
            system("Cls");
        }
        if (j < 0)
        {
           cout<<"Pattern occurs at shift ="<< s<<endl;
            temp[count2]=s;
            count2++;
            s=s+n;

        }
        else
        {
            cout<<endl;
            cout<<txt<<endl;
            for (int k=(s+j)-1;k>=0;k--)
            cout<<" ";
            cout<<"X"<<endl;
            for(int k=(s-1);k>=0;k--)
            cout<<" ";
            cout<<pat<<endl;
            compare++;
            cout<<"Compare :"<<compare<<endl;
            system("PAUSE");
            system("Cls");
            s += max(GoodSufflixes[j], j-LastOccurance[txt[s + j]]-m+1+j);
        //s += std::max(1, j - get_lambda(txt[s + j - 1]));
        //s=s+m-min(j,1+LastOccurance[txt[s+j]]);
        }
    }
}
void BoyerMoore1(char *txt, char *pat, int &count2,int (&temp)[256],int &compare)//continue search
{
    compare=0;
    int m = strlen(pat);
    int n = strlen(txt);
    int LastOccurance[NO_OF_CHARS];
    int GoodSufflixes[m];
    GoodStr(pat,GoodSufflixes);
    LastOccuranceHeuristic(pat, m, LastOccurance);
    count2=0;
    temp[count2];
    int s = 0; // s is array of the pattern with respect to text
    while (s <= (n - m))
    {
        int j = m - 1;
        while (j >= 0 && pat[j] == txt[s + j])
        {
            j--;
            cout<<endl;
            cout<<txt<<endl;
            for (int k=(s+j);k>=0;k--)
            cout<<" ";
            cout<<"|"<<endl;
            for(int k=(s-1);k>=0;k--)
            cout<<" ";
            cout<<pat<<endl;
            compare++;
            cout<<"Compare :"<<compare<<endl;
            system("PAUSE");
            system("Cls");
        }
        if (j < 0)
        {
            cout<<"Pattern occurs at shift= "<< s<<endl;
            temp[count2]=s;
            count2++;
            s+=(s + m < n) ? m - LastOccurance[txt[s]] : 1;
        }
        else
        {
            cout<<endl;
            cout<<txt<<endl;
            for (int k=(s+j)-1;k>=0;k--)
            cout<<" ";
            cout<<"X"<<endl;
            for(int k=(s-1);k>=0;k--)
            cout<<" ";
            cout<<pat<<endl;
            compare++;
            cout<<"Compare :"<<compare<<endl;
            system("PAUSE");
            system("Cls");
            s += max(GoodSufflixes[j], j-LastOccurance[txt[s + j]]-m+1+j);
        //s += std::max(1, j - get_lambda(txt[s + j - 1]));
        //s=s+m-min(j,1+LastOccurance[txt[s+j]]);
        }
    }
}
void search(char *txt, char *pat, int &count2,int (&temp)[256],int &compare)
{
    int m = strlen(pat);
    int n = strlen(txt);
    count2=0;
    compare=0;
    int LastOccurance[NO_OF_CHARS];
    int GoodSufflixes[m];
    GoodStr(pat,GoodSufflixes);

    LastOccuranceHeuristic1(pat, m, LastOccurance);

    int s = 0; // s is array of the pattern with respect to text
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j]){
            j--;
            compare++;
        }
        if (j < 0)
        {
            temp[count2]=s;
            count2++;
            s+=(s + m < n) ? m - LastOccurance[txt[s]] : 1;
           //  s+=(s + m < n) ? m - LastOccurance[txt[s + m]] : 1;
        }

        else{
            s += max(GoodSufflixes[j], j-LastOccurance[txt[s + j]]-m+1+j);
            compare++;
        }
    }
}

/* Driver program to test above funtion */
int main()
{

    char txt[1000000],pat[256];
    getInput(txt,pat);
    int matches,PatternMatch[256];
    int compare;
    // show TEXT AND PATTERN
    //if txt>60 doesnt show simulation but will show running time(disable system pause and cls for Last Occurance)
    if(strlen(txt)>60){
        cout<<"TEXT= "<<txt<<endl;
        cout<<"PATT= "<<pat<<endl;
    auto start = chrono::system_clock::now();
    search(txt, pat,matches,PatternMatch,compare);
    cout<<"Total Pattern Match= "<<matches<<endl<<endl;
    for(int i=0;i<matches;i++)
    {
       cout<<"\nPattern occurs at shift ="<< PatternMatch[i];
    }
    cout<<endl<<"Comparison :"<<compare<<endl<<endl<<endl;
    cout<<"THANK YOU "<<endl;
    auto end = chrono::system_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Duration: " << duration.count() << "s\n";
    }
    //if txt<60 show simulation
    else if (strlen(txt)<60)
    {
        int selection;
        cout<<"1. Boyer Moore Find only 1 Pattern and Exit"<<endl;
        cout<<"2. Boyer Moore Find more than 1 Pattern"<<endl;
        cout<<"Enter Your Choice :";
        cin>>selection;
    if(selection==1)
    {
        system("Cls");
        cout<<"TEXT= "<<txt<<endl;
        cout<<"PATT= "<<pat<<endl;
        BoyerMoore(txt,pat,matches,PatternMatch,compare);
        cout<<"\nTotal Pattern Match= "<<matches<<endl;
        cout<<endl<<"Comparison :"<<compare<<endl<<endl<<endl;
        cout<<"THANK YOU "<<endl;
    }
    if(selection==2)
    {
        system("Cls");
        cout<<"TEXT= "<<txt<<endl;
        cout<<"PATT= "<<pat<<endl;
        BoyerMoore1(txt,pat,matches,PatternMatch,compare);
        cout<<endl;
        system("PAUSE");
        system("Cls");
        cout<<"Total Pattern Match= "<<matches<<endl;
        for(int i=0;i<matches;i++)
        {
            cout<<"\nPattern occurs at shift ="<< PatternMatch[i];
        }
        cout<<endl<<"Comparison :"<<compare<<endl<<endl<<endl;
        cout<<"THANK YOU "<<endl;
    }
     if(selection!=1&&selection!=2)
     {
         cout<<"Error Invalid Input"<<endl;
         return 0;
     }

    }
}
