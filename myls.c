#include <stdio.h>
#include <sys/dir.h>
#include <unistd.h>

struct Option{
       int showHidden; 
       int a;
};

struct Option parse_cmd(int argc, char* argv[]){
    int opt;
    const char *optString="ah";

    struct Option option;
    while ((opt = getopt(argc, argv, optString)) != -1){
        printf("opt is: %d\n", opt);
        switch (opt){

            case 'h':
                option.showHidden = 1;
                break;
            case '?':
                printf("unknow option: %c\n", optopt);
                break;
        }
    }
    for(; optind < argc; optind++){ //when some extra arguments are passed
    //   printf("Given extra arguments: %s\n", argv[optind]);
    }

    return option;
}

int list(char* dir_name, struct Option option){
    DIR *dp;
    struct direct *dir;

    if ((dp = opendir(dir_name)) == NULL){
        fprintf(stderr, "Cannot access %s.\n", dir_name);
        return 1;
    }
    printf("%s\n", dir_name);
    while ((dir = readdir(dp)) != NULL){

        // Skip all the deleted files
        if (dir->d_ino == 0)
            continue;

        if (option.showHidden == 0 && dir->d_name[0] == '.')
            continue;

        printf("%s\t ", dir->d_name);
    }
    printf("\n");
    closedir(dp);
    return 0;
}

void myls(int argc, char*argv[]){

    struct Option option = parse_cmd(argc, argv);

    while(argc){
        --argc;
        printf("argc is: %d \n",argc);
        printf("argv is: %s \n",*argv);
        if (*argv[0] != '-'){
            list(*argv, option);
        }
        argv++;
    }
}
// myls -h p4 
int main(int argc, char *argv[]){
   
    myls(argc, argv);

    return 0;
}