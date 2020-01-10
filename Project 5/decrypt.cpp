#include <iostream>
#include <cstring>
using namespace std;

const int MAX_LEN = 80;

bool decrypt(const char ciphertext[], const char crib[]);

int main()
{
    char c[] = {"DiebjiggY, zyxZYXzyx-- abca abca   bdefg## $$hidbijk6437 wvuWVUwvu\n\n8 9\n"};
    char c1[] = {"    hush???hUsh---     --- until    JanuARY !!  "};
    
    char e[] = {"Zqysrsuu jysqjtsgj bw zrquucwcsx cgwbytqjcbg cu xqgesybmu.\nNrsqus ysrsqus qgo xbzmtsgju obm qzhmcys jb Icfcrsqfu.\nXbg'j ysrsqus qgojdcge stvqyyquucge jb mu; is stvqyyquu bmyusrksu hmcjs isrr.\nzu 31 cu zdqrrsgecge!"};
    char e1[] = {"classified information"};
    
    char d[] = {"Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n"};
    char d1[] = {"my secret"};
    char d2[] = {"shadow"};
    
    bool x = decrypt(c, c1);
    bool y = decrypt(e, e1);
    bool z = decrypt(d, d1);
    bool aa = decrypt(d, d2);
}

bool decrypt(const char ciphertext[], const char crib[])
{
    int cribLength = strlen(crib);
    
    // If crib is empty, return false
    if(cribLength == 0 || (cribLength == 81 && crib[80] != '\n') || cribLength > 82 )
        return false;
    
    // If crib is not empty, but contains no letters then return false
    for(int k = 0; crib[k] != '\0'; k++)
    {
        if (isalpha(crib[k]))
            break;
        else if (k == cribLength - 1)
            return false;
    }
    
    
    // fixedCrib stores the actual words from crib
    char fixedCrib[MAX_LEN+1];
    int pos = 0;
    
    // wordLengths stores the length of each word from crib
    int wordLengths[MAX_LEN];
    int numOfWords = 0;
    int wordLen = 0;
    
    // Get rid of all non-letters to simplify crib and store the actual words into fixedCrib[] and store the length of
    // each word into wordLengths[]
    for(int k = 0; crib[k] != '\0'; k++)
    {
        if(isalpha(crib[k]) && k == cribLength - 1)
        {
            fixedCrib[pos] = tolower(crib[k]);
            pos++;
            wordLen++;
            wordLengths[numOfWords] = wordLen;
            numOfWords++;
        }
        else if(isalpha(crib[k]))
        {
            fixedCrib[pos] = tolower(crib[k]);
            pos++;
            wordLen++;
        }
        else if(k != 0 && (! isalpha(crib[k])) && isalpha(crib[k-1]) )
        {
            wordLengths[numOfWords] = wordLen;
            numOfWords++;
            wordLen = 0;
        }
    }
    fixedCrib[pos] = '\0';  // Set the last position of fixedCrib[] to zero byte to indicate end of c-string
    
    
    // Break ciphertext into its separate messages and store them into decryptText[]
    char decryptText[60][MAX_LEN + 1];
    
    int numOfMessage = 0;
    int currentpos = 0;
    for(int k = 0; ciphertext[k] != '\0'; k++)
    {
        // Store every character from ciphertext into decryptText
        if(ciphertext[k] != '\n')
        {
            decryptText[numOfMessage][currentpos] = tolower(ciphertext[k]);
            currentpos++;
        }
        else if (ciphertext[k] == '\n' && k == 0)
        {
            decryptText[0][0] = '\n';
            numOfMessage++;
        }
        // At every newline, start a new cstring
        else
        {
            decryptText[numOfMessage][currentpos] = '\0';
            currentpos = 0;
            numOfMessage++;
        }
    }
    decryptText[numOfMessage][currentpos] = '\0';
    numOfMessage++;
    
    
    //Loop through decryptText to find matching length patterns
    int begin;
    int end;
    bool beginFound = false;
    int subtractToEnd = 2;
    
    int message = 0;
    int textPos = 0;
    int consecutiveMatches = 0;
    
    // Loop through the number of words from crib
    for(int j = 0; j < numOfWords; j++)
    {
        // Loop through each decryptedText message and keep track of its word lengths
        int matchingLength = 0;
        for(int k = textPos; decryptText[message][k] != '\0'; k++)
        {
            // If we found our first match, we will set begin to the appropriate position and not modify begin again
            // unless our consecutive matches breaks and we find a new beginning
            if(consecutiveMatches == 1 && beginFound == false)
            {
                beginFound = true;
                begin = k - wordLengths[j-1] - 1;
            }
            
            // If the last character in the cstring is a letter
            if(isalpha(decryptText[message][k]) && k + 1 == '\0')
            {
                matchingLength++;
                textPos++;
                subtractToEnd = 1;
                break;
            }
            // Continue looking at the word
            else if(isalpha(decryptText[message][k]))
            {
                matchingLength++;
                textPos++;
            }
            // Indicates we have finished looking at one word, so we break to compare its length
            else if(k != 0 && isalpha(decryptText[message][k - 1]))
            {
                textPos++;
                break;
            }
            // Skip the non-letters
            else
            {
                textPos++;
            }
        }
        
        // Increment matches if the length of the word is equal to the length of the current word at pos j from crib
        if(matchingLength == wordLengths[j])
        {
            consecutiveMatches++;
            beginFound = false;
        }
        // If they do not match, then reset consecutiveMatches and subtract j to continue looking for same word
        else
        {
            consecutiveMatches = 0;
            j = -1;
        }
        
        // If consecutiveMatches is equal to the number of words, then we have found crib in the message and break
        if(consecutiveMatches == numOfWords)
        {
            // If there was only one word, then set begin to appropriate position
            if(consecutiveMatches == 1)
            {
                begin = textPos - wordLengths[0] - 1;
            }
            break;
        }
        // Else if we are finished looking at one message, move to the next message to look for crib
        else if(textPos == strlen(decryptText[message]))
        {
            if(message < numOfMessage)
            {
                message++;
                textPos = 0;
                j = -1;
            }
            // At this point, we have finished looking at all the messages and there were no matches so return false
            else
            {
                return false;
            }
        }
    }
    // At this point, crib exists in one of encrypted messages then we set end to appropriate position
    end = textPos - subtractToEnd;
    
    
    // Copy the encrypted fragment that matched crib's length pattern into key[] using begin and end
    pos = 0;
    char key[MAX_LEN + 1] = {""};
    for(int k = begin; k <= end; k++)
    {
        if(isalpha(decryptText[message][k]))
        {
            key[pos] = tolower(decryptText[message][k]);
            pos++;
        }
    }
    key[pos] = '\0';
    
    
    // Loop through key[] and find any repeat of any characters.
    // If there are repeated characters, then the corresponding characters in crib matching to the key
    // should also be the same and repeating at the same positions.
    for(int k = 0; k < strlen(key); k++)
    {
        for(int pos = 0; pos < strlen(key); pos++)
        {
            if(key[k] == key[pos] && k != pos)
            {
                // Returns false if the chars in corresponding positions are not the same char
                if(fixedCrib[k] != fixedCrib[pos])
                    return false;
            }
        }
    }
    
    
    // Loop through decryptMessage[] and decrypt all of the messages
    for(int m = 0; m < numOfMessage; m++)
    {
        for(int k = 0; decryptText[m][k] != '\0'; k++)
        {
            for(int n = 0; n < strlen(key); n++)
            {
                if(decryptText[m][k] == key[n])
                {
                    decryptText[m][k] = toupper(fixedCrib[n]);
                    break;
                }
            }
        }
    }
    
    //Once all of messages are decrypted, cout the messages
    for(int k = 0; k < numOfMessage; k++)
        cout << decryptText[k] << endl;
    
    return true;
}

