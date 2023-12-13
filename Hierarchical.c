#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define MAX_NAME_LENGTH 50
#define MAX_FILES 100

// Structure to represent a file
typedef struct {
    char name[MAX_NAME_LENGTH];
    char content[1024];
} File;

// Structure to represent a directory
typedef struct {
    char name[MAX_NAME_LENGTH];
    struct Directory* subdirectories[MAX_FILES];
    File files[MAX_FILES];
    int num_subdirectories;
    int num_files;
} Directory;

// Function to create a new directory
void createDirectory(Directory* parent, const char* name) {
    if (parent->num_subdirectories < MAX_FILES) {
        // Allocate memory for the new directory
        Directory* newDirectory = (Directory*)malloc(sizeof(Directory));
        // Set the name of the new directory
        strcpy(newDirectory->name, name);
        // Initialize counters
        newDirectory->num_subdirectories = 0;
        newDirectory->num_files = 0;
        // Add the new directory to the parent's list
        parent->subdirectories[parent->num_subdirectories++] = newDirectory;
        printf("Directory '%s' created.\n", name);
    } else {
        printf("Directory limit reached. Cannot create '%s'.\n", name);
    }
}

// Function to create a new file
void createFile(Directory* parent, const char* name, const char* content) {
    if (parent->num_files < MAX_FILES) {
        // Create a new file
        File newFile;
        // Set the name and content of the new file
        strcpy(newFile.name, name);
        strcpy(newFile.content, content);
        // Add the new file to the parent's list
        parent->files[parent->num_files++] = newFile;
        printf("File '%s' created.\n", name);
    } else {
        printf("File limit reached. Cannot create '%s'.\n", name);
    }
}

// Function to list the contents of a directory
void listContents(Directory* dir) {
    printf("Contents of directory '%s':\n", dir->name);
    
    // Print subdirectories
    printf("Subdirectories:\n");
    for (int i = 0; i < dir->num_subdirectories; i++) {
        printf("- %s\n", dir->subdirectories[i]->name);
    }

    // Print files
    printf("Files:\n");
    for (int i = 0; i < dir->num_files; i++) {
        printf("- %s\n", dir->files[i].name);
    }
}

int main() {
    // Initialize the root directory
    Directory root;
    strcpy(root.name, "root");
    root.num_subdirectories = 0;
    root.num_files = 0;

    // Prompt user for directory name and create it
    char dirName[MAX_NAME_LENGTH];
    printf("Enter the name of the directory: ");
    scanf("%s", dirName);
    createDirectory(&root, dirName);

    // Prompt user for file name and content, then create the file
    char fileName[MAX_NAME_LENGTH];
    printf("Enter the name of a file: ");
    scanf("%s", fileName);
    char fileContent[1024];
    printf("Enter the content of the file: ");
    scanf("%s", fileContent);
    createFile(&root, fileName, fileContent);

    // List the contents of the root directory
    listContents(&root);

    return 0;
}



