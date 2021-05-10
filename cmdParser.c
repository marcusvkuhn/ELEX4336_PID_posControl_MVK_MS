#include <cmdParser.h>
#include <msp430.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pid.h"

/************************************************************************************
* Function: initCmds
* Purpose: initialize each index of the array with its correspondent string and nArgs
* arguments:
*   cmds   -   CMD
* return:  none
* Author: Marcus Kuhn
* Date: 22/04/2020
* Modified: 22/04/2020
*************************************************************************************/
void initCmds(CMD* cmds){
    cmds[0].name = CMD0;        // initialize the first command name
    cmds[0].nArgs = CMD0_NARGS; // initialize num of arguments in first command
    cmds[1].name = CMD1;
    cmds[1].nArgs = CMD1_NARGS;
}

/************************************************************************************
* Function: parseCmd
* Purpose: splits strings into separate tokens for specific purposes
* arguments:
*   cmds   -   CMD
*   cmdLine   -   char*
* return:  if command was valid
* Author: Marcus Kuhn
* Date: 22/04/2020
* Modified: 22/04/2020
*************************************************************************************/
int parseCmd(CMD* cmds, char* cmdLine){
    char* token;  // a pointer variable to a string.
    int i = 0;

    token = strtok(cmdLine, DELIM);        // token is assigned the pointer to the token returned by strtok_s

    int cmdIndex = validateCmd(cmds, token);     // finds which index to use for subsequent parsing

    if (cmdIndex != -1 && cmds[cmdIndex].nArgs != 0){
        if (cmdIndex == TARGET_IDX || cmdIndex == MOVE_IDX){                          // for cmd "target", nArgs = 1
                token = strtok(NULL, DELIM);

                if (token)                      // checks if token exists, is of length 1 and is alphabetic
                    ARGS[0] = atoi(token);      // casts as integer the value (of a char) token is pointing to
                else
                    cmdIndex = -1;

                token = strtok(NULL, DELIM);

                if (token)     // if there is more than one argument, function will also return -1
                    cmdIndex = -1;
        }
    }
    return cmdIndex;
}

/************************************************************************************
* Function: validadeCmd
* Purpose: uses cmdIndex to execute a scaraCmds[cmdIndex] Scara command.
* It will perform data type casting (double -> int or char) when necessary.
* arguments:
*   scaraCmds   -   CMD*
*   cmdName     -   char*
* return:  if command was valid
* Author: Marcus Kuhn
* Date: 22/04/2020
* Modified: 22/04/2020
*************************************************************************************/
int validateCmd(CMD* cmds, char* cmdName){
    unsigned int i = 0;
    int idx = -1;
    int invalidCmd = 1;
    while (invalidCmd && i < MAX_CMDS)
        invalidCmd = strcmp(cmdName, cmds[i++].name);
    if (!invalidCmd)
        idx = i - 1;
    return idx;
}

/************************************************************************************
* Function: executeCMD
* Purpose: uses cmdIndex to execute a scaraCmds[cmdIndex] Scara command.
* It will perform data type casting (double -> int or char) when necessary.
* arguments:
*   scaraCmds   -   CMD*
*   cmdIndex   -   int
*   scaraState   -   SCARA_ROBOT*
* return:  if command was valid
* Author: Marcus Kuhn
* Date: 22/04/2020
* Modified: 22/04/2020
*************************************************************************************/
int executeCmd(CMD* cmds, int cmdIndex){
    switch (cmdIndex) {
    case TARGET_IDX:
            posTargetDeg = ARGS[0];
        break;
    case MOVE_IDX:
            posTargetDeg = posCountDeg + ARGS[0];
        break;
    default:
        break;
    }
    return cmdIndex;
}
