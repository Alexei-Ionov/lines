#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
const char *valid_extensions[] = { ".js", ".py", ".java", ".c", ".cpp", ".cs", ".rb", ".php", ".html", ".css", ".swift", ".go", ".rs", ".ts", ".kt", ".sh", ".pl", ".lua", ".r", ".sql", ".json", ".xml", ".yaml", ".yml", ".md", ".bat", ".m", ".h", ".scala", ".vb"};
const int num_extensions = sizeof(valid_extensions) / sizeof(valid_extensions[0]);
int max_path_len = 1024;
int has_valid_extension(char* file_name) { 
    for (int i = 0; i < num_extensions; i++) { 
        const char *ext = valid_extensions[i];
        if (strlen(file_name) >= strlen(ext)) { 
            if (strcmp(file_name + strlen(file_name) - strlen(ext), ext) == 0) { 
                return 1;
            }           
        }
    }
    return 0;
       
}
void update_lines(char *file_name, long *num_lines) { 
    FILE *file = fopen(file_name, "r");
    if (file == NULL) { 
        printf("failed to open file %s\n", file_name);
        return;
    }
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            (*num_lines)++;
        }
    }
    fclose(file);
    
}
void update_path(char* path, char*file_name) { 
    if (strlen(path) + strlen(file_name) >= max_path_len) {  //assumes no file name is greater than 1024 bytes lol
        max_path_len = max_path_len + max_path_len;
        path = realloc(path, max_path_len);
        if (path == NULL) { 
            perror("realloc failed");
            exit(1);
        }
    }
    strcat(path, file_name);
}
void traverse_tree(char *path, long* num_lines) {
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (dir == NULL) { 
        perror("failed to open dir");
        exit(1);
    }
    strcat(path, "/");
    while ((entry = readdir(dir)) != NULL) {
        if (has_valid_extension(entry->d_name)) { 
            update_path(path, entry->d_name);
            update_lines(path, num_lines);
            memset(path + strlen(path) - strlen(entry->d_name), 0, strlen(entry->d_name));        
        }
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) { 
                update_path(path, entry->d_name);
                traverse_tree(path, num_lines);
                memset(path + strlen(path) - strlen(entry->d_name), 0, strlen(entry->d_name)); 
            }
                   
        }
    }
    memset(path + strlen(path) - 1, 0, 1); //get rid of the /
    closedir(dir);

}
int main() { 
    long *num_lines = calloc(1, sizeof(long));
    if (num_lines == NULL) { 
        perror("calloc failed");
        return 1;
    }
    char *path = calloc(max_path_len, 1);
    if (path == NULL) { 
        perror("calloc failed");
        return 1;
    }
    path[0] = '.';
    traverse_tree(path, num_lines);
    printf("lines of code: %ld\n", *num_lines);

    free(num_lines);
    free(path);
    return 0;
}
