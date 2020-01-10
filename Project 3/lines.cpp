#include "graphlib.h"
#include <iostream>
#include <cassert>
using namespace std;

const int HORIZ = 0;
const int VERT = 1;

const int BG = 0;
const int FG = 1;

bool plotLine(int r, int c, int dir, int distance, char plotChar, int fgbg);
int executeCommands(string commandString, char& plotChar, int& mode, int& badPos);

int main()
{
    clearGrid();
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = executeCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
            case 0:
                draw();
                break;
            case 1:
                cout << "Syntax error at position " << position+1 << endl;
                break;
            case 2:
                cout << "Cannot execute command at position " << position+1 << endl;
                break;
            default:
                // It should be impossible to get here.
                cerr << "executeCommands returned " << status << "!" << endl;
        }
    }
}

bool plotLine(int r, int c, int dir, int distance, char plotChar, int fgbg)
{
    // Check for correct parameters when calling plotLine
    if (dir != HORIZ && dir != VERT)
        return false;
    if (fgbg != BG && fgbg != FG)
        return false;
    if (! isprint(plotChar))
        return false;
    if (dir == HORIZ && (c+distance > 30 || c+distance <= 0))
        return false;
    if (dir == VERT && (r+distance > 20 || r+distance <= 0))
        return false;
    
    // Check if distance is negative
    if (distance < 0)
    {
        distance *= -1;
        
        //Checks for FG or BG, true if FG and false if BG
        if (fgbg)
        {
            // Plots negative distance horizontally for FG
            if (!dir)
            {
                for(int k = 0; k <= distance; k++)
                {
                    if(c <= NCOLS && c > 0)
                        setChar(r,c,plotChar);
                    c--;
                }
            }
            // Plots negative distance vertically for FG
            else
            {
                for(int k = 0; k <= distance; k++)
                {
                    if(r > 0 && r <= NROWS)
                        setChar(r,c,plotChar);
                    r--;
                }
            }
        }
        
        else
        {
            // Plots negative distance horizontally for BG
            if (!dir)
            {
                for(int k = 0; k <= distance; k++)
                {
                    if(c <= NCOLS && c > 0)
                    {
                        if(getChar(r,c) == ' ')             // Checks if the char at current position is a space char
                            setChar(r,c,plotChar);          // replaces it if true or does nothing if false
                    }
                    c--;
                }
            }
            // Plots negative distance vertically for BG
            else
            {
                for(int k = 0; k <= distance; k++)
                {
                    if(r > 0 && r <= NROWS)
                    {
                        if(getChar(r,c) == ' ')             // Checks if the char at current position is a space char
                            setChar(r,c,plotChar);          // replaces it if true or does nothing if false
                    }
                    r--;
                }
            }
            
        }
    }
    
    // Distance is positive
    else
    {   // Checks for FG or BG, true if FG and false if BG
        if (fgbg)
        {
            // Plots positive distance horizontally for FG
            if (!dir)
            {
                for(int k = 0; k <= distance; k++)
                {
                    if(c <= NCOLS && c > 0)
                        setChar(r,c,plotChar);
                    c++;
                }
            }
            // Plots positive distance vertically for FG
            else
            {
                for(int k = 0; k <= distance; k++)
                {
                    if(r > 0 && r <= NROWS)
                        setChar(r,c,plotChar);
                    r++;
                }
            }
        }
        
        else
        {
            // Plots positive distance horizontally for BG
            if (!dir)
            {
                for(int k = 0; k <= distance; k++)
                {
                    if(c <= NCOLS && c > 0)
                    {
                        if(getChar(r,c) == ' ')        // Checks if the char at current position is a space char
                            setChar(r,c,plotChar);     // replaces it if true or does nothing if false
                    }
                    c++;
                }
            }
            // Plots positive distance vertically for BG
            else
            {
                for(int k = 0; k <= distance; k++)
                {
                    if(r > 0 && r <= NROWS)
                    {
                        if(getChar(r,c) == ' ')         // Checks if the char at current position is a space char
                            setChar(r,c,plotChar);      // replaces it if true or does nothing if false
                    }
                    r++;
                }
            }
            
        }

    }
    return true;
}


int executeCommands(string commandString, char& plotChar, int& mode, int& badPos)
{
    bool hOffGrid = false;      // Remains false if no plotting error, becomes true if there was a command accessing
    bool vOffGrid = false;      // off the grid
    
    int hPos = 0;                   // Variables to record the position for the bad command
    int vPos = 0;
    
    // Sets row and column to (1,1)
    int r = 1;
    int c = 1;
    
    // Loop to read the command string
    int k = 0;
    do
    {
        // Clears grid and resets to default plotChar, mode, and position (1,1)
        if(commandString[k] == 'c' || commandString[k] == 'C')
        {
            clearGrid();
            plotChar = '*';
            mode = FG;
            r = 1;
            c = 1;
            k++;
        }
        
        // Sets mode to FG
        if (commandString[k] == 'f' || commandString[k] == 'F')
        {
            mode = FG;
            k++;
            if (isprint(commandString[k]))      // Checks that there is a valid character to use for plotChar
            {
                plotChar = commandString[k];
                k++;
            }
            else
            {
                badPos = k;
                return 1;
            }
        }
        
        // Sets mode to BG
        if (commandString[k] == 'b' || commandString[k] == 'B')
        {
            mode = BG;
            k++;
            if (isprint(commandString[k]))      // Checks that there is a valid character to use for plotChar
            {
                plotChar = commandString[k];
                k++;
            }
            else
            {
                badPos = k;
                return 1;
            }
        }
        
        // Checks for the horizontal line command
        if (commandString[k] == 'h' || commandString[k] == 'H')
        {
            int dir = HORIZ;
            int distance;
            
            k++;
            if(commandString[k] == '-')     // Checks if the distance will be negative
            {
                k++;
                if(! isdigit(commandString[k]))     // Checks if character after the '-' is not a digit and returns
                {
                    badPos = k;
                    return 1;
                }
                if(isdigit(commandString[k]))       // There should be a digit after '-' at this point
                {
                    if(isdigit(commandString[k+1]))     // double digit negative distance
                    {
                        distance = 0 - (10 * (commandString[k] - '0') + (commandString[k+1] -'0'));
                        k += 2;
                    }
                    else        // single digit negative distance
                    {
                        distance = 0 - (commandString[k] - '0');
                        k++;
                    }
                }
            }
            else if( ! isdigit(commandString[k]))   //If not negative,check if there's a digit after horizontal command
            {
                badPos = k;
                return 1;
            }
            else        // The character after the horizontal command should be a digit at this point
            {
                if(isdigit(commandString[k]))
                {
                    if(isdigit(commandString[k+1]))     // double digit distance
                    {
                        distance = 10 * (commandString[k] - '0') + (commandString[k+1] - '0');
                        k += 2;
                    }
                    else        // single digit distance
                    {
                        distance = commandString[k] - '0';
                        k++;
                    }
                }
            }
            
            if ( ! plotLine(r, c, dir, distance, plotChar, mode ))      // If plotLine fails, set hPos to position of
            {                                                           // the bad command
                if(hOffGrid == false)       // Checks if this command is the first error plotting off grid
                {                           // if true we will keep position, if false we ignore it
                    if(isdigit(commandString[k-1]))
                    {
                        if(isdigit(commandString[k-2]))
                        {
                            if(commandString[k-3] == '-')   // Looks for position for the 'h' or 'H'
                                hPos = k - 4;
                            else
                                hPos = k - 3;
                        }
                        else if(commandString[k-2] == '-')
                        {
                            hPos = k - 3;
                        }
                        else
                            hPos = k - 2;
                    }
                    hOffGrid = true;        // Since plotting failed, hOffGrid is set to be true
                }
            }
            else
                c += distance;      //If plotLine succeeded, keep track of current column position for further commands
        }
        
        // Checks for vertical line command
        if (commandString[k] == 'v' || commandString[k] == 'V')
        {
            int dir = VERT;
            int distance;
            
            k++;
            if(commandString[k] == '-')     // Checks if distance will be negative
            {
                k++;
                if(! isdigit(commandString[k]))     // Checks if character after the '-' is not a digit
                {
                    badPos = k;
                    return 1;
                }
                if(isdigit(commandString[k]))
                {
                    if(isdigit(commandString[k+1]))     // double digit negative distance
                    {
                        distance = 0 - (10 * (commandString[k] - '0') + (commandString[k+1] -'0'));
                        k += 2;
                    }
                    else        // single digit negative distance
                    {
                        distance = 0 - (commandString[k] - '0');
                        k++;
                    }
                }
            }
            else if( ! isdigit(commandString[k]))   //If not negative, check if there is a digit after vertical command
            {
                badPos = k;
                return 1;
            }
            else        // The character after the vertical command should be a digit at this point
            {
                if(isdigit(commandString[k]))
                {
                    if(isdigit(commandString[k+1]))     // double digit distance
                    {
                        distance = 10 * (commandString[k] - '0') + (commandString[k+1] - '0');
                        k += 2;
                    }
                    else        // single digit distance
                    {
                        distance = commandString[k] - '0';
                        k++;
                    }
                }
            }
            
            if ( ! plotLine(r, c, dir, distance, plotChar, mode ))      // if plotLine fails, set vPos to position of
            {                                                           // the bad command
                if(vOffGrid == false)       // Checks if this command is the first error plotting off grid
                {                           // if true we will keep position, if false we ignore it
                    if(isdigit(commandString[k-1]))
                    {
                        if(isdigit(commandString[k-2]))
                        {
                            if(commandString[k-3] == '-')
                                vPos = k - 4;
                            else
                                vPos = k - 3;
                        }
                        else if(commandString[k-2] == '-')
                        {
                            vPos = k - 3;
                        }
                        else
                            vPos = k - 2;
                    }
                    vOffGrid = true;            // since plotting failed, vOffGrid is set to be true
                }
            }
            else
                r += distance;      //If plotLine succeeded, keep track of current row position for furthur commands
        }
        
        // Checks if the next commandString position is a valid instruction or not
        if (k != commandString.size() && commandString[k] != 'c' && commandString[k] != 'C' && commandString[k] != 'f' && commandString[k] != 'F' && commandString[k] != 'b' && commandString[k] != 'B' && commandString[k] !='h' && commandString[k] != 'H' && commandString[k] != 'v' && commandString[k] != 'V')
        {
            badPos = k;
            return 1;
        }
        
    } while (k != commandString.size());
    
    // At this point, the commandString should have correct syntax and now we check if if ever accessed off the grid
    
    if (hOffGrid == true && vOffGrid == true)    // Check if both a horizontal and vertical command plotted off grid
    {
        if (hPos < vPos)        // Check which error occurred first and set badPos to first occurring error and return
        {
            badPos = hPos;
            return 2;
        }
        else
        {
            badPos = vPos;
            return 2;
        }
    }
    if (hOffGrid == true && vOffGrid == false)  // Check if only horizontal command plotted off grid
    {
        badPos = hPos;
        return 2;
    }
    if (vOffGrid == true && hOffGrid == false)  // Check if only vertical command plotted off grid
    {
        badPos = vPos;
        return 2;
    }
    
    return 0;       // the commandString is valid and never accessed off the grid, thus program succeeded and returns
}













