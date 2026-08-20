#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Task structure
typedef struct Task {
    char description[100];
    int id;
    struct Task* next;
} Task;

// Function prototypes
Task* addTask(Task** head, const char* description, int id);
Task* removeTask(Task** head, int id);
void showTasks(Task *tasks);
void freeList(Task** head);

int main() {
    // Initialize variables
    int choice, id;
    int auto_id = 1; // Auto-incrementing ID for tasks
    char description[100];

    // Initialize the head of the linked list
    struct Task* head = NULL;

    printf("To-Do List Application\n");
    
    // Main loop for user input
    while(1) {
        // Display menu options
        printf("\n1. Add Task\n");
        printf("2. Remove Task\n");
        printf("3. Show Tasks\n");
        printf("4. Exit\n");
        // Get user choice
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }
        switch(choice) {
            // Handle user choices
            case 1:
                system("cls"); // Clear the console for better readability
                printf("Enter task description: ");
                scanf(" %99[^\n]", description);
                addTask(&head, description, auto_id++);
                printf("Task added successfully. ID: %d\n", auto_id - 1);
                break;

            case 2:
                system("cls"); // Clear the console for better readability
                printf("Enter task ID to remove: ");
                scanf("%d", &id);
                removeTask(&head, id);
                break;
            
            case 3:
                system("cls"); // Clear the console for better readability
                showTasks(head);
                break;
            
            case 4:
                system("cls"); // Clear the console for better readability
                freeList(&head);
                printf("Exiting...\n");
                return 0;
        }
    }

    return 0;
}

// Function to add a task to the linked list
Task* addTask(Task** head, const char* description, int id) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    if (!newTask) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    strcpy(newTask->description, description);
    newTask->id = id;
    newTask->next = *head;
    *head = newTask;
    return newTask;
}

// Function to remove a task from the linked list
Task* removeTask(Task** head, int id) {
    Task* current = *head;
    Task* previous = NULL;
    while (current != NULL) {
        if (current->id == id) {
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Task with ID %d removed successfully.\n", id);
            return NULL;
        }
        previous = current;
        current = current->next;
    }
    return NULL;
}

// Function to display all tasks in the linked list
void showTasks(Task *tasks) {
    Task* current = tasks;
    while (current != NULL) {
        printf("Task ID: %d, Description: %s\n", current->id,
        current->description);
        current = current->next;
    }
}

void freeList(Task** head) {
    Task* current = *head;
    Task* nextTask;
    while (current != NULL) {
        nextTask = current->next;
        free(current);
        current = nextTask;
    }
}