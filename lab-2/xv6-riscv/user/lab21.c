#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char* argv[])
{
    if(argc < 2){
        fprintf(2, "Give at least one dir in the command");
        exit(1);
    }
    int i;
    for(i = 1; i < argc; i++){
        if(mkdir(argv[i]) < 0){
        fprintf(2, "mkdir: %s failed to create\n", argv[i]);
        break;
        }
    }
    exit(0);
}
