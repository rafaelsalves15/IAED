/*-----------------------------INCLUDES----------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* ------------------------------DEFINES---------------------------------------- */
#define MAX_CAR_USER 22
#define MAX_DESCRIPTION_TASK 52
#define MAX_CAR_ACTIVITY 22
#define MAX_USERS 50
#define MAX_ACTIVITIES 10
#define MAX_NUM_TASKS 10000

#define ERROR_T1 "too many tasks"
#define ERROR_T2 "duplicate description"
#define ERROR_T3 "invalid duration"

#define ERROR_L1 "no such task"

#define ERROR_N1 "invalid time"

#define ERROR_U1 "user already exists"
#define ERROR_U2 "too many users"

#define ERROR_M1 "no such task"
#define ERROR_M2 "task already started"
#define ERROR_M3 "no such user"
#define ERROR_M4 "no such activity"

#define ERROR_D1 "no such activity"

#define ERROR_A1 "duplicate activity"
#define ERROR_A2 "invalid description"
#define ERROR_A3 "too many activities"