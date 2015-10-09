#include <iostream>
#include <stdio.h>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    char cmd;
    string acc_name, amount_string;
    unsigned int amount;
    int illegal_commands = 0;

    map<string,int> accBalanceMap;
    map<int, set<string> >  balAccsMap;
    vector<string> accNames;

    do
    {
        cin >> cmd;

        switch(cmd)
        {
            case 'O':
            {
                getline(cin, acc_name);
                bool accExists = false;
                vector<string>::iterator accIter;
                accIter = find(accNames.begin(), accNames.end(), acc_name);
                if(accIter != accNames.end())               //acc_name already exists in accNames
                {
                    illegal_commands++;
                }
                else
                {
                    accBalanceMap[acc_name] = 0;
                    balAccsMap[0].insert(acc_name);
                    accNames.push_back(acc_name);
                }
                break;
            }
            case 'C':
            {   
                getline(cin, acc_name);
                set<string>::iterator accIter;
                accIter = balAccsMap[0].find(acc_name);

                if(accIter == balAccsMap[0].end())          //acc_name not in set of accounts with 0 balance
                {
                    illegal_commands++;
                }
                else
                {
                    map<string, int>::iterator it;
                    it = accBalanceMap.find(acc_name);
                    accBalanceMap.erase(it);                //Remove acc_name key from accBalanceMap
                    balAccsMap[0].erase(acc_name);          //Remove acc_name from set of accounts with 0 balance
                    accNames.erase(remove(accNames.begin(), accNames.end(), acc_name));               //Remove acc_name from accNames vector
                }
                
                break;
            }
            case 'D':
            {    
                cin >> acc_name;
                cin >> amount_string;
                amount = atoi(amount_string.c_str());
                acc_name = ' ' + acc_name;
                vector<string>::iterator accIter;
                accIter = find(accNames.begin(), accNames.end(), acc_name);
                
                if(accIter == accNames.end())               //acc_name not in accNames
                {
                    illegal_commands++;
                }
                else
                {
                    balAccsMap[ accBalanceMap[acc_name] ].erase(acc_name);
                    if(balAccsMap[ accBalanceMap[acc_name] ].empty() == true)
                    {
                        balAccsMap.erase(accBalanceMap[acc_name]);
                    }
                    accBalanceMap[acc_name] += amount;

                
                    if(balAccsMap.find(accBalanceMap[acc_name]) == balAccsMap.end())
                    {
                        set<string> newStringSet;
                        newStringSet.insert(acc_name);
                        balAccsMap[ accBalanceMap[acc_name] ] = newStringSet;    
                    }
                    else
                    {
                        balAccsMap[ accBalanceMap[acc_name] ].insert(acc_name);
                    }
                }
                break;
            }
            case 'W':
            {  
                cin >> acc_name;
                cin >> amount_string;
                amount = atoi(amount_string.c_str());
                acc_name = ' ' + acc_name;
                vector<string>::iterator accIter;
                accIter = find(accNames.begin(), accNames.end(), acc_name);

                if(accIter == accNames.end())               //acc_name not in accNames
                {
                    illegal_commands++;
                }
                else if(amount > accBalanceMap[ acc_name ]) //Withdraw more than balance
                {
                    illegal_commands++;
                }
                else
                {
                    balAccsMap[ accBalanceMap[acc_name] ].erase(acc_name);
                    if(balAccsMap[ accBalanceMap[acc_name] ].empty() == true)
                    {
                        balAccsMap.erase(accBalanceMap[acc_name]);
                    }
                    accBalanceMap[acc_name] -= amount;
                    balAccsMap[ accBalanceMap[acc_name] ].insert(acc_name);
                }
                
                break;
            }
            case 'P':
            {
                unsigned int min, max;
                cin >> min >> max;
                map<int, set<string> >::iterator printIter;
                for(printIter = balAccsMap.begin(); printIter != balAccsMap.end(); printIter++)
                {
                    if((*printIter).first >= min && (*printIter).first <= max)
                    {
                        cout << (*printIter).first;
                        set<string>::iterator printSetIter;
                        for(printSetIter = ((*printIter).second).begin(); printSetIter != ((*printIter).second).end(); printSetIter++)
                            cout << (*printSetIter);
                        cout << endl;
                    }
                }
                break;
            }
            
        }

    } while(cmd != 'E');

    cout << illegal_commands << endl;
}