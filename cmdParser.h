/*
 * cmdVNH7070.h
 *
 *  Created on: Feb 23, 2021
 *      Author: Raymond
 */

#ifndef CMDPARSER_H_
#define CMDPARSER_H_

#define     MAX_CMDS             3

#define     CMD0                 "target"
#define     CMD0_NARGS           1
#define     TARGET_IDX           0

#define     CMD1                 "move"
#define     CMD1_NARGS           1
#define     MOVE_IDX             1

//#define     CMD2                 "nokLcdClear"
//#define     CMD2_NARGS           0
//#define     CLEAR_IDX            2

#define     DELIM                " ,\t"
#define     NULL                 '\0'          // null char
#define     ARGS                 cmds[cmdIndex].args
#define     MAX_ARGS             1

#define     QUIT_IDX             6

typedef struct CMD {
    const char *name; // command name
    int nArgs; // number of input arguments for a command
    int args[MAX_ARGS]; // arguments
}CMD;

//-------------- func prototypes-------------

void initCmds(CMD* cmds);
int parseCmd(CMD* cmds, char* cmdLine);
int validateCmd(CMD* cmds, char* cmdName);
int executeCmd(CMD* cmds, int cmdIndex);

#endif /* CMDPARSER_H_ */
