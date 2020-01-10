#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

int enumerate(const string a[], int n, string target);
int locate(const string a[], int n, string target);
bool locateSequence(const string a[], int n, string target, int& begin, int& end);
int locationOfMin(const string a[], int n);
int moveToEnd(string a[], int n, int pos);
int moveToBeginning(string a[], int n, int pos);
int locateDifference(const string a1[], int n1, const string a2[], int n2);
int eliminateDups(string a[], int n);
bool subsequence(const string a1[], int n1, const string a2[], int n2);
int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max);
int divide(string a[], int n, string divider);

#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cassert>

using namespace std;

string c[6] = {
    "alpha", "beta", "beta", "delta", "gamma", "gamma"
};

string d[11] = {
    "alpha", "beta", "beta", "beta", "alpha",
    "alpha", "",     "delta", "beta", "beta",
    ""
};

string e[5] = {
    "alpha", "beta", "gamma", "gamma", "a"
};

string f[5] = {
    "azaz", "beta", "gamma", "mu", "a"
};

string g[100];

bool makeMergerCheck(const string a[], int n1, const string b[], int n2, const string c[])
{
    string z[100];
    merge(a,a+n1,b,b+n2,z);
    return equal(z,z+n1+n2,c);
}

bool divideCheck(const string a[], int n, int p, string divider)
{
    for (int k = 0; k < p; k++)
        if (a[k] >= divider)
            return false;
    for ( ; p < n  &&  a[p] == divider; p++)
        ;
    for (int k = p; k < n; k++)
        if (a[k] <= divider)
            return false;
    string b[100];
    copy(a,a+n,b);
    sort(b,b+n);
    return equal(b,b+n,c);
}

void testone(int n)
{
    const int N = 6;
    
    // Act as if  a  were declared:
    //   string a[6] = {
    //       "alpha", "beta", "gamma", "gamma", "beta", "delta"
    //   };
    // This is done in a way that will probably cause a crash if
    // a[-1] or a[6] is accessed:  We place garbage in those positions.
    string aa[1+N+1] = {
        "", "alpha", "beta", "gamma", "gamma", "beta", "delta", ""
    };
    string* a = &aa[1];
    string* z = aa;
    a[-1].string::~basic_string();
    a[N].string::~basic_string();
    fill_n(reinterpret_cast<char*>(&a[-1]), sizeof(a[-1]), 0xEF);
    fill_n(reinterpret_cast<char*>(&a[N]), sizeof(a[N]), 0xEF);
    
    string b[N] = {
        "alpha", "beta", "gamma", "delta", "beta", "delta"
    };
    
    switch (n)
    {
        case  1: {
            assert(enumerate(z, -1, "alpha") == -1);
        } break; case  2: {
            assert(enumerate(z, 0, "alpha") == 0);
        } break; case  3: {
            assert(enumerate(a, 6, "beta") == 2);
        } break; case  4: {
            assert(enumerate(a, 6, "delta") == 1);
        } break; case  5: {
            assert(enumerate(a, 6, "bet") == 0);
        } break; case  6: {
            assert(locate(z, -1, "alpha") == -1);
        } break; case  7: {
            assert(locate(z, 0, "alpha") == -1);
        } break; case  8: {
            assert(locate(a, 1, "alpha") == 0);
        } break; case  9: {
            assert(locate(a, 6, "alpha") == 0);
        } break; case 10: {
            assert(locate(a, 6, "gamma") == 2);
        } break; case 11: {
            assert(locate(a, 6, "zeta") == -1);
        } break; case 12: {
            int b = 999;
            int e = 999;
            assert(!locateSequence(z, -1, "alpha", b, e));
        } break; case 13: {
            int b = 999;
            int e = 999;
            assert(!locateSequence(z, 0, "alpha", b, e)  &&
                   b == 999  &&  e == 999);
        } break; case 14: {
            int b = 999;
            int e = 999;
            assert(locateSequence(d, 1, "alpha", b, e)  &&
                   b == 0  &&  e == 0);
        } break; case 15: {
            int b = 999;
            int e = 999;
            assert(!locateSequence(d, 1, "beta", b, e)  &&
                   b == 999  &&  e == 999);
        } break; case 16: {
            int b = 999;
            int e = 999;
            assert(locateSequence(d, 10, "alpha", b, e)  &&
                   b == 0  &&  e == 0);
        } break; case 17: {
            int b = 999;
            int e = 999;
            assert(locateSequence(d, 10, "beta", b, e)  &&
                   b == 1  &&  e == 3);
        } break; case 18: {
            int b = 999;
            int e = 999;
            assert(locateSequence(c, 6, "gamma", b, e)  &&
                   b == 4  &&  e == 5);
        } break; case 19: {
            assert(locationOfMin(z, -1) == -1);
        } break; case 20: {
            assert(locationOfMin(z, 0) == -1);
        } break; case 21: {
            assert(locationOfMin(a, 6) == 0);
        } break; case 22: {
            assert(locationOfMin(a+1, 5) == 0);
        } break; case 23: {
            assert(locationOfMin(a+2, 3) == 2);
        } break; case 24: {
            a[0] = "~~~~~~~~~~~";
            a[1] = "~~~~~~";
            a[2] = a[0];
            assert(locationOfMin(a, 3) == 1);
        } break; case 25: {
            assert(moveToEnd(z, -1, 0) == -1 &&
                   a[0] == "alpha" && a[1] == "beta");
        } break; case 26: {
            assert(moveToEnd(a, 6, -1) == -1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 27: {
            assert(moveToEnd(a, 6, 6) == -1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 28: {
            assert(moveToEnd(z, 0, 0) == -1 &&
                   a[0] == "alpha" && a[1] == "beta");
        } break; case 29: {
            assert(moveToEnd(a, 1, 0) == 0 &&
                   a[0] == "alpha" && a[1] == "beta");
        } break; case 30: {
            assert(moveToEnd(a, 6, 0) == 0 &&
                   a[0] == "beta" && a[1] == "gamma" && a[2] == "gamma" &&
                   a[3] == "beta" && a[4] == "delta" && a[5] == "alpha");
        } break; case 31: {
            assert(moveToEnd(a, 6, 5) == 5 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 32: {
            assert(moveToEnd(a, 6, 3) == 3 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "beta" && a[4] == "delta" && a[5] == "gamma");
        } break; case 33: {
            assert(moveToEnd(a, 5, 3) == 3 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "beta" && a[4] == "gamma" && a[5] == "delta");
        } break; case 34: {
            assert(moveToBeginning(z, -1, 0) == -1 &&
                   a[0] == "alpha" && a[1] == "beta");
        } break; case 35: {
            assert(moveToBeginning(a, 6, -1) == -1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 36: {
            assert(moveToBeginning(a, 6, 6) == -1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 37: {
            assert(moveToBeginning(z, 0, 0) == -1 &&
                   a[0] == "alpha" && a[1] == "beta");
        } break; case 38: {
            assert(moveToBeginning(a, 1, 0) == 0 &&
                   a[0] == "alpha" && a[1] == "beta");
        } break; case 39: {
            assert(moveToBeginning(a, 6, 0) == 0 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 40: {
            assert(moveToBeginning(a, 6, 5) == 5 &&
                   a[0] == "delta" && a[1] == "alpha" && a[2] == "beta" &&
                   a[3] == "gamma" && a[4] == "gamma" && a[5] == "beta");
        } break; case 41: {
            assert(moveToBeginning(a, 5, 3) == 3 &&
                   a[0] == "gamma" && a[1] == "alpha" && a[2] == "beta" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 42: {
            assert(locateDifference(z, -1, b, 6) == -1);
        } break; case 43: {
            assert(locateDifference(a, 6, z, -1) == -1);
        } break; case 44: {
            assert(locateDifference(z, 0, z, 0) == 0);
        } break; case 45: {
            assert(locateDifference(a, 3, b, 3) == 3);
        } break; case 46: {
            assert(locateDifference(a, 3, b, 2) == 2);
        } break; case 47: {
            assert(locateDifference(a, 2, b, 3) == 2);
        } break; case 48: {
            assert(locateDifference(a, 6, b, 6) == 3);
        } break; case 49: {
            assert(eliminateDups(d,10) == 6 && d[0] == "alpha"  &&
                   d[1] == "beta"  &&  d[2] == "alpha"  &&
                   d[3] == ""  &&  d[4] == "delta"  &&  d[5] == "beta");
        } break; case 50: {
            d[3] = "alpha";
            d[4] = "beta";
            assert(eliminateDups(d+3,6) == 6 && d[3] == "alpha"  &&
                   d[4] == "beta"  &&  d[5] == "alpha"  &&
                   d[6] == ""  &&  d[7] == "delta"  &&  d[8] == "beta");
        } break; case 51: {
            assert(eliminateDups(d,1) == 1  &&  d[0] == "alpha"  &&
                   d[1] == "beta");
        } break; case 52: {
            assert(eliminateDups(z,0) == 0  &&  a[0] == "alpha");
        } break; case 53: {
            assert(eliminateDups(z,-1) == -1  &&  a[0] == "alpha");
        } break; case 54: {
            assert(!subsequence(z, -1, b, 6));
        } break; case 55: {
            assert(!subsequence(a, 6, z, -1));
        } break; case 56: {
            assert(!subsequence(z, 0, b, 6));
        } break; case 57: {
            assert(subsequence(a, 6, z, 0));
        } break; case 58: {
            assert(subsequence(a, 6, b, 1));
        } break; case 59: {
            assert(subsequence(a, 6, b+1, 2));
        } break; case 60: {
            assert(subsequence(a, 6, b+1, 3));
        } break; case 61: {
            assert(!subsequence(a, 6, b+3, 2));
        } break; case 62: {
            assert(!subsequence(b, 6, a+2, 3));
        } break; case 63: {
            b[0] = "beta";
            assert(!subsequence(a, 3, b, 2));
        } break; case 64: {
            assert(subsequence(a, 6, a, 6));
        } break; case 65: {
            assert(makeMerger(e,1,f,1,g,10) == 2  &&  makeMergerCheck(e,1,f,1,g));
        } break; case 66: {
            assert(makeMerger(e+1,1,f+1,1,g,10) == 2  &&
                   makeMergerCheck(e+1,1,f+1,1,g));
        } break; case 67: {
            assert(makeMerger(e,4,f,4,g,10) == 8  &&  makeMergerCheck(e,4,f,4,g));
        } break; case 68: {
            assert(makeMerger(e,4,f,4,g,7) == -1);
        } break; case 69: {
            assert(makeMerger(z,0,f,4,g,7) == 4  &&  makeMergerCheck(z,0,f,4,g));
        } break; case 70: {
            e[2] = "mu";
            assert(makeMerger(e,4,f,4,g,10) == -1);
        } break; case 71: {
            assert(makeMerger(e,4,z,-1,g,7) == -1);
        } break; case 72: {
            assert(divide(z, -1, "beta") == -1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 73: {
            assert(divide(z, 0, "beta") == 0 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 74: {
            assert(divide(a, 1, "aaa") == 0 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 75: {
            assert(divide(a, 1, "alpha") == 0 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 76: {
            assert(divide(a, 1, "zeta") == 1 &&
                   a[0] == "alpha" && a[1] == "beta" && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 77: {
            assert(divide(a, 2, "aaa") == 0 &&
                   divideCheck(a, 2, 0, "aaa") && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 78: {
            assert(divide(a, 2, "alpha") == 0 &&
                   divideCheck(a, 2, 0, "alpha") && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 79: {
            assert(divide(a, 2, "beta") == 1 &&
                   divideCheck(a, 2, 1, "beta") && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 80: {
            assert(divide(a, 2, "zeta") == 2 &&
                   divideCheck(a, 2, 2, "zeta") && a[2] == "gamma" &&
                   a[3] == "gamma" && a[4] == "beta" && a[5] == "delta");
        } break; case 81: {
            assert(divide(a, 6, "aaa") == 0 && divideCheck(a, 6, 0, "aaa"));
        } break; case 82: {
            assert(divide(a, 6, "alpha") == 0 &&
                   divideCheck(a, 6, 0, "alpha"));
        } break; case 83: {
            assert(divide(a, 6, "beta") == 1 &&
                   divideCheck(a, 6, 1, "beta"));
        } break; case 84: {
            assert(divide(a, 6, "delta") == 3 &&
                   divideCheck(a, 6, 3, "delta"));
        } break; case 85: {
            assert(divide(a, 6, "gamma") == 4 &&
                   divideCheck(a, 6, 4, "gamma"));
        } break; case 86: {
            assert(divide(a, 6, "zeta") == 6 &&
                   divideCheck(a, 6, 6, "zeta"));
        } break; case 87: {
            a[2] = "mu";
            c[5] = "mu";
            assert(divide(a, 6, "mu") == 5 && divideCheck(a, 6, 5, "mu"));
        } break; case 88: {
            assert(divide(a, 6, "chi") == 3 && divideCheck(a, 6, 3, "chi"));
        } break; case 89: {
            // This case tested whether moveToEnd used an extra array.
        } break; case 90: {
            // This case tested whether moveToBeginning used an extra array.
        } break; case 91: {
            // This case tested whether eliminateDups used an extra array.
        } break; case 92: {
            // This case tested whether makeMerger used an extra array.
        } break; case 93: {
            // This case tested whether divide used an extra array.
        } break;
    }
    
    new (&a[-1]) string;
    new (&a[N]) string;
}

int main()
{
    for(;;)
    {
    cout << "Enter a test number (1 to 93): ";
    int n;
    cin >> n;
    if (n < 1  ||  n > 93)
    {
        cout << "Bad test number" << endl;
        return 1;
    }
    testone(n);
    cout << "Passed test " << n << endl;
    }
}

int enumerate(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    
    // Loop to find the number of matches
    int matches = 0;
    for(int k = 0; k < n; k++)
    {
        if(a[k] == target)
            matches++;
    }
    
    return matches;
}

int locate(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    
    // Loop to find the first match for target and return immediately
    for(int k = 0; k < n; k++)
    {
        if (a[k] == target)
            return k;
    }
    
    // If no matches, we return -1
    return -1;
}

bool locateSequence(const string a[], int n, string target, int& begin, int& end)
{
    if (n <= 0)
        return false;
    
    bool beginFound = false;
    
    // Loop to find the the first occurence of target
    for(int k = 0; k < n; k++)
    {
        // If we already found beginning, we loop until there is no match and we set end to that position
        if(beginFound)
        {
            if(a[k] != target)
            {
                end = k-1;
                return true;
            }
            // If we sequence continues until the end of the array, we set end to the last position
            else if(k == n-1)
            {
                end = k;
                return true;
            }
        }
        // if target is found, we set begin to its position and set beginFound to be true
        else
        {
            if (a[k] == target)
            {
                begin = k;
                beginFound = true;
            }
        }
    }
    // If there was no string in a that was equal to target, we return false
    return false;
}


int locationOfMin(const string a[], int n)
{
    if (n <= 0)
        return -1;
    
    int minPos = 0;
    
    // Loop through the array and compare each element
    for (int k = 0; k < n; k++)
    {
        // Store the position of the current string that is < the string being compared
        if(a[k] < a[minPos])
        {
            minPos = k;
        }
        // If there are more than one string that have the same minimum value, we want to keep the smallest position
        else if(a[k] == a[minPos])
        {
            if(k < minPos)
                minPos = k;
        }
    }
    
    return minPos;
}

int moveToEnd(string a[], int n, int pos)
{
    if (n <= 0)
        return -1;
    if (pos >= n)
        return -1;
    if (pos < 0)
        return -1;
    
    // Store the string at the pos
    string holder = a[pos];

    // Loop to shift the array leftward starting from pos
    for(int k = pos; k < n; k++)
    {
        // Set the stored string at pos to the end of the array
        if(k == n-1)
        {
            a[k] = holder;
        }
        // Shift left
        else
        {
            a[k] = a[k+1];
        }
    }
    
    return pos;
}

int moveToBeginning(string a[], int n, int pos)
{
    if (n <= 0)
        return -1;
    if (pos >= n && (pos != 0 && n != 0))
        return -1;
    if (pos < 0)
        return -1;
    
    // Store the string at pos
    string holder = a[pos];
    
    // Loop to shift the array rightward starting from pos
    for(int k = pos; k >= 0; k--)
    {
        // Set the stored string at pos to the beginning of the array
        if(k == 0)
        {
            a[k] = holder;
        }
        // Shift right
        else
        {
            a[k] = a[k-1];
        }
    }
    return pos;
}

int locateDifference(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    
    // If n1 and n2 are the same, we return the earliest position of difference, otherwise we return either n1 or n2
    if (n1 == n2)
    {
        for(int k = 0; k < n1; k++)
        {
            if(a1[k] != a2[k])
                return k;
        }
        return n1;
    }
    
    // Loop to look for difference in terms of n1's length because if runs out first
    if (n1 < n2)
    {
        for(int k = 0; k < n1; k++)
        {
            if(a1[k] != a2[k])
                return k;
        }
    }
    
    // Loop to look for difference in terms of n2's length because it runs out first
    if (n2 < n1)
    {
        for(int k = 0; k < n2; k++)
        {
            if(a1[k] != a2[k])
                return k;
        }
    }
    
    // If we get to this point, it means both a1 and a2 are equal up to the point where one or both ran out
    // Return the smaller of n1 and n2
    if (n1 < n2)
        return n1;
    else
        return n2;
}

int eliminateDups(string a[], int n)
{
    if (n < 0)
        return -1;
    
    // Loop through the array
    for (int k = 0; k < n; k++)
    {
        // If we encounter the empty string, it means we have finished removing all dupes
        if(a[k] == "")
            break;
        
        // If we find a dupe, we will set the dupe to empty string and move it to the end
        if(a[k] == a[k+1])
        {
            a[k+1] = "";
            int doesNothing = moveToEnd(a, n, k+1);
            k--;
        }
    }
    
    int retained = 0;
    
    // Loop to count how many elements are retained
    for(int j = 0; j < n; j++)
    {
        if(a[j] != "")
        {
            retained++;
        }
    }
    return retained;
}

bool subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return false;
    if (n2 > n1)
        return false;
    if (n2 == 0)
        return true;
    // If n1 and n2 are equal, they should be equal entirely otherwise return false
    if (n2 == n1)
    {
        for(int k = 0; k < n2; k++)
        {
            if (! (a1[k] == a2[k]))
                return false;
        }
    }
    
    // Keep track of the position where we found a match
    int pos = 0;
    for(int k = 0; k < n2; k++)
    {
        // Continue looping starting from the last position of a match
        for(int l = pos; l < n1; l++)
        {
            // If there is a match, we want to keep that position and break to look at the next element
            if(a2[k] == a1[l])
            {
                pos = l + 1;
                break;
            }
            // If a1 does not contain a2 as a subsequence, we return false
            else if(l == n1 - 1)
            {
                return false;
            }
        }
    }
    // At this point, a1 contains a2 as a subsequence so we return true
    return true;
}

int makeMerger(const string a1[], int n1, const string a2[], int n2, string result[], int max)
{
    if (n1 + n2 > max)  // If result has more than max elements, we return -1
        return -1;
    if (n1 < 0 || n2 < 0)
        return -1;
    
    // Loops to check if a1 and a2 are in nondecreasing order
    for(int k = 0; k < n1 - 1; k++)
    {
        if (a1[k] > a1[k+1])
            return -1;
    }
    for(int l = 0; l < n2 - 1; l++)
    {
        if (a2[l] > a2[l+1])
            return -1;
    }
    
    // Put a1 and a2 into result array as is
    int position = 0;
    
    for (int k = 0; k < n1; k++)
    {
        result[position] = a1[k];
        position++;
    }
    for (int j = 0; j < n2; j++)
    {
        result[position] = a2[j];
        position++;
    }

    string currentWord;
    
    // Loop through each element in result array
    for(int k = 0; k < n1 + n2; k++)
    {
        // Store the string at the current element we are looking at
        currentWord = result[k];
        
        // Loop through to compare the current element with the ones past it
        for(int l = k + 1; l < n1 + n2; l++)
        {
            // If there is a word that is less than currentWord, we swap their places and re-compare the string
            // This basically sets result in nondecreasing order
            if(currentWord > result[l])
            {
                string temp = currentWord;
                currentWord = result[l];
                result[k] = currentWord;
                result[l] = temp;
                l = k + 1;
            }
        }
    }
    
    return n1 + n2;
}

int divide(string a[], int n, string divider)
{
    if (n < 0)
        return -1;
    
    int k = 0;
    int pos = 0;
    
    // Loop to compare elements to divider
    while (k < n)
    {
        // If the string at the current position is less than divider, we move it to the beginning
        if(a[pos] < divider)
        {
            int doesNothing = moveToBeginning(a, n, pos);
            pos++;
        }
        // If the string at current position is equal to divider, we want to ignore it and continue checking
        else if(a[pos] == divider)
        {
            pos++;
        }
        // If the string at current position is greater than divider, we move it to the end
        else if(a[pos] > divider)
        {
            int doesNothing = moveToEnd(a, n, pos);
        }
        // Increment k to indicate every element we examined
        k++;
    }

    // Loop to find the position of the first element that is not less than divider
    for(int l = 0; l < n; l++)
    {
        if(a[l] >= divider)
            return l;
    }
    
    // Otherwise, we return n if all of the elements are < divider
    return n;
}
