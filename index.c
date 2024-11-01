#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct settings {
    int unique;
    int alloc;
    char *type;
} settings;

typedef struct model_data {
    char *name;
    settings set;
} model_data;

typedef struct model {
    char *name;
    int nums;
    model_data *data;
} model;

void display(model *mod) {
    printf("%s\n", mod->name);
    for(int j=0; j<mod->nums; j++) {
        printf("%s", mod->data[j]);
    }
}

model *init(char *path) {
    FILE *file;
    file = fopen(path, "r");
    char *line = (char*)malloc(256);
    int started = 0;
    model *mod = (model*)malloc(sizeof(model));
    int modelIndex = 0;
    while(fgets(line, 256, file)) {
        if(strstr(line, "END") == line) {
            started = 0;
        }
        if(started) {
            while(isspace(*line)) *line++;
            char *token = strtok(line, ":");
            mod->data[modelIndex++].name = (char*)malloc(strlen(token) * sizeof(char) + 1);
            strcpy(mod->data[modelIndex++].name, token);
        }
        if(strstr(line, "START") == line) {
            char *token = strtok(line, " ");
            token = strtok(NULL, " ");
            mod->name = (char*)malloc(strlen(token)*sizeof(char) + 1);
            strcpy(mod->name, token);
            token = strtok(NULL, " ");
            mod->nums = atoi(token);
            mod->data = (model_data*)malloc(mod->nums * sizeof(model_data*));
            started = 1;
        }
    }
    fclose(file);
    return mod;
}

int main() {
    model *user = init("./migration/user.chiu");
    display(user);
    // find(user, "name==test", "name,age")
    return 0;
}
