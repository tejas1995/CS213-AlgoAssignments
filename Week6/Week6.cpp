#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char str[1000];
    cin.getline(str, 1000);
    int n = strlen(str);
    bool matchingWords = false;
    int startPos = 0, matchLength = 0;
    int l = 1;

    do
    {


        for(int i = 0; i < n; i += l)
        {
            int p = 0, q = 0, bj;   //p, q - Counters, bj - starting index of matching 2nd block
            bool matchingBlocks = false;
            for(int j = i+2*l-1; j <= i+4*l-2 && j+q < n;)
            {
                if(str[i+p] != str[j+q])
                {
                    if(p != 0)
                        j=j+q;
                    else
                        j=j+q+1;
                    p = 0;
                    q = 0;
                }
                else if(q == l-1 && p == l-1)
                {
                    matchingBlocks = true;
                    bj = j;
                    break;
                }
                else
                {
                    p++;
                    q++;
                }
            }

            if(matchingBlocks == true)
            {
                int k = 0;
                do
                {
                    k++;
                    if(bj+l-1+k == n)
                        break;
                } while(str[i+l-1+k] == str[bj+l-1+k]);
                k--;

                int r = 2*i+k+l-bj, s = i+k+l;
                if(r==i && s==bj)
                {
                    matchingWords = true;
                    startPos = 2*i+k+l-bj;
                    matchLength = bj - i;
                    break;
                }
                else
                {
                    while(r < i && s < bj)
                    {
                        if(str[r] != str[s])
                            break;
                        else if(r == i-1 && s==bj-1)
                        {
                            matchingWords = true;
                            startPos = 2*i+k+l-bj;
                            matchLength = bj - i;
                            break;
                        }
                        else
                        {
                            r++;
                            s++;
                        }

                    }
                }

            }

            if(matchingWords == true)
                break;
        }

        if(matchingWords == true)
            break;

        l *= 2;
    } while( l < n);

    cout << matchLength << " " << startPos << endl;
    return 0;
}