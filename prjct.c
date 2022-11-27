#include "prjct.h"

/*------------------------------ GLOBAL DECLARATIONS --------------------------------------*/
char utilizador[MAX_USERS][MAX_CAR_USER];
char atividade[MAX_ACTIVITIES][MAX_CAR_ACTIVITY] = {"TO DO" , "IN PROGRESS" , "DONE"};

int time=0,id_task=0, id_user=0, id_activity=3;


struct task {
    int id;
    int dur;
    int instant;
    char user[MAX_CAR_USER];
    char activity[MAX_CAR_ACTIVITY];
    char dscr[MAX_DESCRIPTION_TASK];
};

struct task tasks[MAX_NUM_TASKS];

void t() , next_line() ,l(),n(),u(),a(),m(),d(), sort_letter(),sort_instant();
int errors();

/*---------------------------------FUNCTIONS----------------------------------------------- */
int main() {
    int finish=1;

    while (finish!=0){
        int c = getchar();
        switch(c){
            case 'q':
                finish=0;
                break;
            case 't':
                t();
                break;
            case 'l':
                l();
                break;
            case 'n':
                n();
                break;
            case 'u':
                u();
                break;
            case 'm':
                m();
                break;
            case 'd':
                d();
                break;
            case 'a':
                a();
                break;
        }
    }
    return 0;
}

/* This auxiliary function allows to move to the next terminal line*/
void next_line(){
    int c;
    while ((c=getchar() )!= '\n' && c!=EOF );
}

/* Function that adds a new task to the system.Can print errors.*/
void t(){
    if (id_task >= MAX_NUM_TASKS){
        printf("%s\n",ERROR_T1);
        next_line();
    }
    else {
        int i;
        scanf("%d", &tasks[id_task].dur);

        getchar();
        fgets(tasks[id_task].dscr, MAX_DESCRIPTION_TASK, stdin);
        tasks[id_task].dscr[strlen(tasks[id_task].dscr) - 1] = '\0';
        strcpy(tasks[id_task].activity, atividade[0]);

        for (i=0; i<id_task ; i++){
            if (strcmp(tasks[id_task].dscr,tasks[i].dscr) == 0 ){
                printf("%s\n",ERROR_T2);
                return;
            }
        }
        if (tasks[id_task].dur <= 0 ){
            printf("%s\n",ERROR_T3);
            return;
        }
        tasks[id_task].id = id_task+1;
        id_task++;

        printf("task %d\n",id_task);
    }
}

/* This auxiliary function prints tasks in alphabetical order from their description */
void sort_letter(){
    int vec[MAX_NUM_TASKS];
    int i  , ind , j;
    struct task v;
    for(i = 0; i < MAX_NUM_TASKS; i++) vec[i] = i;
    for (i = 1 ; i < id_task ; i++){
        v = tasks[i];
        j = i - 1 ;
        while ( j >= 0 && (strcmp(v.dscr ,tasks[vec[j]].dscr)< 0  )){
            vec[j+1] = vec[j];
            j--;
        }
        vec[j+1]=i;
    }
    for (i = 0 ; i < id_task ; i ++){
        ind = vec[i];
        printf("%d %s #%d %s\n",tasks[ind].id,tasks[ind].activity,tasks[ind].dur,tasks[ind].dscr);
    }
}

/* This auxiliary function prints tasks in ascending order of instant (if two
  tasks have equal instants prints by alphabetic order of description.) */
void sort_instant(char activ[MAX_CAR_ACTIVITY]){
    int vec1[MAX_NUM_TASKS];
    int vec2[MAX_NUM_TASKS];
    int i  , ind , j, lim = 0;
    struct task v;
    for(i = 0; i < MAX_NUM_TASKS; i++) {
        if (strcmp(activ, tasks[i].activity) == 0) {
            vec2[i] = vec1[i] = i;
            lim++;
        }
    }
    for (i = 1 ; i < lim ; i++) {
        v = tasks[vec1[i]];
        j = i - 1;
/*In case of equal instants, sort by alphabetic order.*/
        while (j >= 0 && (v.instant < tasks[vec2[vec1[j]]].instant ||
                          (v.instant == tasks[vec2[vec1[j]]].instant && strcmp(v.dscr, tasks[vec2[vec1[j]]].dscr) < 0))) {
            vec2[vec1[j + 1]] = vec2[vec1[j]];
            j--;
        }
        vec2[vec1[j + 1]] = i;
    }
    for (i = 0 ; i < lim ; i ++){
        ind = vec2[vec1[i]];
        printf("%d %d %s\n",tasks[ind].id,tasks[ind].instant,tasks[ind].dscr);
    }
}

/* This functions lists the desired ( or all ) tasks.Can print errors. */
void l(){
    int c,ha_ids=0,x;
    while (1) {
        c = getchar();
        if (c == '\n'  || c== EOF ){
            if (ha_ids == 0){
                sort_letter();
            }
            return;
        }
        ha_ids =1;
        scanf("%d",&x);
        if (x <= 0 || x > id_task){
            printf("%d: %s\n",x,ERROR_L1);
            continue;
        }
        printf("%d %s #%d %s\n",x,tasks[x-1].activity,tasks[x-1].dur,tasks[x-1].dscr);
    }
}

/*This function advances the system time.  */
void n(){
    int duracao;
    scanf("%d",&duracao);
    if (duracao < 0){
        printf("%s\n",ERROR_N1);
    }
    else {
        if (duracao != 0) {
            time = time + duracao;
            printf("%d\n", time);
        } else {
            printf("%d\n", time);
        }
    }
}

/*  This function adds a new user or lists all users.Can print errors.  */
void u(){
    char test[MAX_CAR_USER];
    int c=getchar(),i ;
    if (c=='\n' || c==EOF ){
        for (i=0; i < id_user ; i++){
            printf("%s\n",utilizador[i]);
        }
    }
    else {
        scanf("%s", test);
        getchar();
        for (i=0 ; i < id_user ; i++){
            if (strcmp(utilizador[i],test) == 0){
                printf("%s\n",ERROR_U1);
                return;
            }
        }
        if (id_user >= MAX_USERS){
            printf("%s\n",ERROR_U2);
            return;
        }
        strcpy(utilizador[id_user],test);
        id_user++;
    }
}

/* This auxiliary function prints the errors of function m() */
int errors(char user[MAX_CAR_USER] , char ativ[MAX_CAR_ACTIVITY],int x){
    int i, existe=0 , existe_a=0;
    if (x <= 0 || x > id_task){
        printf("%s\n",ERROR_M1);
        return 0;
    }
    if (strcmp( ativ, "TO DO") == 0){
        if(strcmp(tasks[x-1].activity, "TO DO") != 0)
            printf("%s\n",ERROR_M2);
        return 0;
    }
    for ( i = 0 ; i  < id_user ; i++){
        if (strcmp(utilizador[i], user) == 0){
            existe=1;
        }
    }
    if (existe==0){
        printf("%s\n",ERROR_M3);
        return 0;
    }

    for ( i = 0 ; i  < id_activity ;i++){

        if (strcmp( atividade[i], ativ) == 0){
            existe_a=1;
        }
    }
    if (existe_a==0){
        printf("%s\n",ERROR_M4);
        return 0;
    }
    return 1;
}

/* This function moves a task from one activity to another.Can print errors.*/
void m(){
    int duration ,x,slack;
    char user[MAX_CAR_USER] ,ativ[MAX_CAR_ACTIVITY];
    scanf("%d%s",&x,user);
    getchar();
    fgets(ativ , MAX_CAR_USER , stdin);
    ativ[strlen(ativ)-1]='\0';

    if (errors(user,ativ,x) == 0 ){
        return;
}
    if ( errors(user,ativ,x) == 1) {

        if (strcmp(tasks[x - 1].activity, "TO DO") == 0) {
            tasks[x - 1].instant = time;
        }
        if (strcmp(ativ, "DONE") == 0) {
            duration = time - tasks[x - 1].instant;
            slack = duration - tasks[x - 1].dur;
            printf("duration=%d slack=%d\n", duration, slack);
        }
        strcpy(tasks[x - 1].activity, ativ);
        strcpy(tasks[x - 1].user, user);
    }
}

/*This function lists all tasks that are in a given activity.
  Can print errors.*/
void d() {
    int i, existe = 0;
    char x[MAX_CAR_ACTIVITY];
    getchar();
    fgets(x, MAX_CAR_ACTIVITY, stdin);
    x[strlen(x)-1] = '\0';
/* check if the activity passed as an argument exists */
    for (i = 0; i < id_activity; i++) {
        if (strcmp(x, atividade[i]) == 0) {
            existe = 1;
        }
    }
    if (existe == 0) {
        printf("%s\n",ERROR_D1);
        return;
    }
    else {
        sort_instant(x);
    }
}

/*This function adds an activity or lists all activities.
  Can print errors.*/
void a(){
    char test[MAX_CAR_ACTIVITY];
    int len;
    int c,i ;
    while(isspace(c = getchar())) {
        if (c=='\n' || c==EOF ){
            for (i=0 ; i< id_activity ; i++){
                printf("%s\n",atividade[i]);
            }
            return;
        }
    }
    test[0] = c;
    fgets(test+1, MAX_CAR_ACTIVITY-1 , stdin);
    test[strlen(test)-1] = '\0';

    for (i=0 ; i < id_activity ; i++){
        if (strcmp(atividade[i],test) == 0){
            printf("%s\n",ERROR_A1);
            return;
        }
    }
    len =1 * strlen(test);
    for (i=0 ; i < len ; i++){
        if(islower(test[i]) != 0){
            printf("%s\n",ERROR_A2);
            return;
        }
    }
    if (id_activity >= MAX_ACTIVITIES){
        printf("%s\n",ERROR_A3);
        return;
    }
    strcpy(atividade[id_activity],test);
    id_activity++;
}
