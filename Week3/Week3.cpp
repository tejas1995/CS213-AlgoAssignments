#include <iostream>
#include <vector>

using namespace std;
typedef unsigned long int uLong;

struct Subsequence
{
    uLong size;
    vector<uLong> subseq_index;
};

Subsequence current_subsequence;
Subsequence min_subsequence;

uLong *seq_1, *seq_2;
uLong n, m;

Subsequence find_subsequence(uLong end_index_1, uLong end_index_2)
{
    Subsequence min_subsequence;
    Subsequence current_subsequence;

    min_subsequence.size = -1;

    for(long i = end_index_1; i >= end_index_2; i--)
    {
        if(seq_1[i] == seq_2[end_index_2])
        {
            if(end_index_2 > 0)
            {
                //cout << "Match found at: " << i << " " << end_index_2 << endl;
                current_subsequence = find_subsequence(i-1, end_index_2-1);
                
                if(current_subsequence.size == -1)
                {
                    min_subsequence.size = -1;
                    return min_subsequence;
                }

                /*
                cout << "Subsequence returned : ";
                for(int j = 0; j < current_subsequence.subseq_index.size(); j++)
                    cout << current_subsequence.subseq_index[j] << " ";
                cout << endl;
                */
                

                if(i - current_subsequence.subseq_index[0] <= min_subsequence.size || min_subsequence.size < 0)
                {
                    min_subsequence.subseq_index = current_subsequence.subseq_index;
                    min_subsequence.subseq_index.push_back(i);
                    min_subsequence.size = i - min_subsequence.subseq_index[0];

                    /*
                    cout << "New min_subsequence: ";
                    for(int j = 0; j < min_subsequence.subseq_index.size(); j++)
                        cout << min_subsequence.subseq_index[j] << " ";
                    cout << endl;
                    */
                }
            }
            else
            {
                //cout << "Last match found: " << i << " " << end_index_2 << endl;
                current_subsequence.subseq_index.push_back(i);
                current_subsequence.size = 0;
                return current_subsequence;
            }

            //cout << "------------------\n" << endl;
            if(!(end_index_2 == m-1 || end_index_2 == 0))
                break;

        }
        else if (i == end_index_2 && min_subsequence.size == -1)
        {
            return min_subsequence;
        }
        
    }

    //cout << "Returning min_subsequence\n";
    return min_subsequence;
}

int main()
{
    cin >> n >> m;

    seq_1 = new uLong [n];
    seq_2 = new uLong [m];

    for(uLong i = 0; i < n; i++)
        cin >> seq_1[i];

    for(uLong i = 0; i < m; i++)
        cin >> seq_2[i];
    
    Subsequence min_subsequence = find_subsequence(n-1, m-1);
    
    if(min_subsequence.size == -1)
        cout << "infinity" << endl;
    else
    {
        /*
        for(int i = 0; i < min_subsequence.subseq_index.size(); i++)
            cout << min_subsequence.subseq_index[i] << " ";
        cout << endl;
        */

        uLong subseq_length = min_subsequence.subseq_index.back() - min_subsequence.subseq_index[0] + 1;

        cout << subseq_length << " " << min_subsequence.subseq_index[0]+1 << endl;
    }
    
    return 0;

}