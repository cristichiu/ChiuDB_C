#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char *name;
    int nums;
    char **data;
} model;

int main() {
    FILE *file;
    file = fopen("./migration/user.chiu", "r");
    char *line = (char*)malloc(256);
    int started = 0;
    model models[100];
    int modelsIndex = 0;
    int modelIndex = 0;
    while(fgets(line, 256, file)) {
        if(strstr(line, "END") == line) {
            started = 0;
            modelsIndex++;
            modelIndex = 0;
        }
        if(started) {
            while(isspace(*line)) *line++;
            printf("%s", line);
            strcpy(models[modelsIndex].data[modelIndex++], line);
        }
        if(strstr(line, "START") == line) {
            char *token = strtok(line, " ");
            model cMolde = models[modelsIndex];
            token = strtok(NULL, " "); cMolde.name = token;
            token = strtok(NULL, " "); cMolde.nums = atoi(token);
            cMolde.data = (char**)malloc(cMolde.nums * 256);
            for(int i=0; i<cMolde.nums; i++) cMolde.data[i] = (char*)malloc(256);
            started = 1;
        }
    }
    fclose(file);
    printf("%d", modelsIndex);
    for(int i=0; i<modelsIndex; i++) {
        printf("Modelul %s\n", models[i].name);
        for(int j=0; j<models[i].nums; j++) {
            printf("%d", models[i].data[j]);
        }
    }

    return 0;
}