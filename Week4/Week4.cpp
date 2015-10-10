#include <iostream>
#include <list>
#include <algorithm>

using namespace std;
typedef unsigned long int uLong;

class webPageContainer
{
    uLong pageCount[100000];
    list<list<int> >::iterator pageCountList[100000];
    uLong maxCount;
    uLong numMaxCount;
    list<list<int> >::iterator maxCountIter;
    uLong n;
    list< list<int> > webCountList;

public:
    webPageContainer(uLong num)
    {
        n = num;
        maxCount = 0;
        numMaxCount = n;
        list<int> countZeroList;
        uLong i;

        for(i = 0; i < n; i++)
        {
            pageCount[i] = 0;                           //Set counter to zero
            countZeroList.push_back(i);                 //Add to countList of zero counts
        }

        webCountList.push_back(countZeroList);

        for(i = 0; i < n; i++)
        {
            pageCountList[i] = webCountList.begin();   //Point ith iterator to beginning of webCountList
        }
    }


    void increment(uLong i)
    {   
        
        pageCount[i] += 1;

        list<list<int> >::iterator currPCListIter = pageCountList[i];
        list<list<int> >::iterator nextPCListIter = currPCListIter;
        ++nextPCListIter;

        if(nextPCListIter == webCountList.end())
        {
            list<int> newCountList;
            newCountList.push_back(i);
            webCountList.push_back(newCountList);
            pageCountList[i]++;
            nextPCListIter = currPCListIter;
            ++nextPCListIter;
        }
        else if(pageCount[ *((*nextPCListIter).begin()) ] != pageCount[i])
        {
            list<int> newCountList;
            newCountList.push_back(i);
            webCountList.insert(nextPCListIter, newCountList);
            pageCountList[i]++;
        }
        else
        {
            (*nextPCListIter).push_back(i);
            pageCountList[i] = nextPCListIter;
        }

        //Find way to ID which element in currPCListIter is ith page, and delete it in O(1) time
        (*currPCListIter).erase(remove((*currPCListIter).begin(), (*currPCListIter).end(), i), (*currPCListIter).end());
 
        //Delete the list if empty
        if((*currPCListIter).empty() == true)
        {
            webCountList.erase(currPCListIter);
        }

        //Check for new maxCount
        if(pageCount[*((*nextPCListIter).begin())] > maxCount)
        {
            maxCount = pageCount[ *((*nextPCListIter).begin()) ];
            maxCountIter = nextPCListIter;
        }
        
        
    }

    void decrement(uLong i)
    {
        if(pageCount[i] > 0)
        {
            bool currMaxCount = false;
            if(pageCount[i] == maxCount)
                currMaxCount = true;       
            
            pageCount[i] -= 1;

            list<list<int> >::iterator currPCListIter = pageCountList[i];
            list<list<int> >::iterator prevPCListIter = currPCListIter;
            --prevPCListIter;

            if(currPCListIter == webCountList.begin())
            {
                list<int> newCountList;
                newCountList.push_back(i);
                webCountList.push_front(newCountList);
                pageCountList[i]--;
            }
            else
            if(pageCount[ *((*prevPCListIter).begin()) ] != pageCount[i])
            {
                list<int> newCountList;
                newCountList.push_back(i);
                webCountList.insert(currPCListIter, newCountList);
                pageCountList[i]--;
            }
            else
            {
                (*prevPCListIter).push_back(i);
                pageCountList[i] = prevPCListIter;
            }

            //Find way to ID which element in currPCListIter is ith page, and delete it in O(1) time
            (*currPCListIter).erase(remove((*currPCListIter).begin(), (*currPCListIter).end(), i), (*currPCListIter).end());

            bool resetCurr = false;
            //Delete the list if empty
            if((*currPCListIter).empty() == true)
            {
                resetCurr = true;
                webCountList.erase(currPCListIter);
            }
            
            //Check for new maxCount
            if(resetCurr == true && currMaxCount == true)
            {
                maxCount = pageCount[ *((*prevPCListIter).begin()) ];
                maxCountIter = prevPCListIter;
            }
        }
    }

    void reset(uLong i)
    {

        bool currMaxCount = false;
        if(pageCount[i] == maxCount)
            currMaxCount = true;

        pageCount[i] = 0;

        list<list<int> >::iterator currPCListIter = pageCountList[i];
        list<list<int> >::iterator beginPCListIter = webCountList.begin();
        list<list<int> >::iterator prevPCListIter = currPCListIter;
        prevPCListIter--;

        if(pageCount[ *((*beginPCListIter).begin()) ] != pageCount[i])
        {
            list<int> newCountList;
            newCountList.push_back(i);
            webCountList.insert(beginPCListIter, newCountList);
            pageCountList[i] = beginPCListIter;
        }
        else
        {
            (*beginPCListIter).push_back(i);
            pageCountList[i] = beginPCListIter;
        }

        //Find way to ID which element in currPCListIter is ith page, and delete it in O(1) time
        (*currPCListIter).erase(remove((*currPCListIter).begin(), (*currPCListIter).end(), i), (*currPCListIter).end());
        
        bool resetCurr = false;
        //Delete the list if empty
        if((*currPCListIter).empty() == true)
        {
            resetCurr = true;
            webCountList.erase(currPCListIter);
        }

        //Check for new maxCount
        if(resetCurr == true && currMaxCount == true)
        {
            maxCount = pageCount[ *((*prevPCListIter).begin()) ];
            maxCountIter = prevPCListIter;
        }
    }

    uLong findMax()
    {
        return maxCount;
    }

    uLong numMax()
    {
        return (*maxCountIter).size();
    }

    uLong count(uLong i)
    {
        return pageCount[i];
    }

    void printMax()
    {
        list<int>::iterator listIter;
        for(listIter = (*maxCountIter).begin(); listIter != (*maxCountIter).end(); listIter++)
            cout << (*listIter) << " ";
        cout << endl;
    }

    void print()
    {
        list<list<int> >::iterator webPCIter;
        for(webPCIter = webCountList.begin(); webPCIter != webCountList.end(); webPCIter++)
        {
            cout << "New webPageCountList\n";
            list<int>::iterator countIter;
            for(countIter = (*webPCIter).begin(); countIter != (*webPCIter).end(); countIter++)
            {
                cout << *countIter << " " << pageCount[*countIter] << endl;
            }
        }
    }
    
};

int main()
{
    webPageContainer worldWideWeb(10);
    worldWideWeb.increment(1);
    worldWideWeb.increment(1);
    worldWideWeb.increment(2);
    worldWideWeb.increment(0);
    worldWideWeb.increment(1);
    worldWideWeb.increment(0);
    worldWideWeb.increment(0);
    worldWideWeb.increment(0);
    worldWideWeb.reset(0);
    worldWideWeb.decrement(2);
    cout << worldWideWeb.findMax() << endl;
    cout << worldWideWeb.numMax() << endl;
    worldWideWeb.printMax();
    worldWideWeb.print();

    return 0;

}