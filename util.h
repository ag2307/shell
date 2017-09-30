
#define TRUE 1
#define FALSE !TRUE

static char* currentDirectory;
extern char** environ;
char history[1024][1024];
int number;

int no_reprint_prmpt;

pid_t pid;

// signal handler for SIGCHLD */
void signalHandler_child(int p);
// signal handler for SIGINT
void signalHandler_int(int p);


int changeDirectory(char * args[]);
