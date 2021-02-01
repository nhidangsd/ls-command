#include <stdio.h>
#include <sys/dir.h>
#include <unistd.h>

struct Option{
       int h; 
};

int list(char* dir_name, struct Option option){
    DIR *dp;
    struct direct *dir;

    if ((dp = opendir(dir_name)) == NULL){
        fprintf(stderr, "Cannot access %s\n", dir_name);
        return 1;
    }
    printf("%s\n", dir_name);
    while ((dir = readdir(dp)) != NULL){

        // Skip all the deleted files
        if (dir->d_ino == 0)
            continue;

        // Skip all hidden files when -h flag is not specified
        if (option.h == 0 && dir->d_name[0] == '.')
            continue;

        // Print the file's name
        printf("%s\t ", dir->d_name);
    }
    printf("\n");
    closedir(dp);
    return 0;
}

void myls(int argc, char*argv[]){
    struct Option option = {0}; // init option flag object

    int opt;
    const char *optString="h"; // only take '-h' as option arg 
    while ((opt = getopt(argc, argv, optString)) != -1){
        
        switch (opt){

            // turn on option h to show all hidden files
            case 'h':
                option.h = 1;
                break;
            
            // Exit if option arg is illegal
            case '?':
                return;
        }
    }
    // When no directory is specified, list all files in current dir
    if(optind == argc){
        list(".", option);
        return;
    }

    // Else list all files in specified directories
    for(; optind < argc; optind++){ 
        list(argv[optind], option);
    }

}

int main(int argc, char *argv[]){
   
    myls(argc, argv);

    return 0;
}