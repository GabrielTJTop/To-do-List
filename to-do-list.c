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

int main() {
    // Initialize variables
    int choice, id;
    char description[100];

    // Initialize the head of the linked list
    struct Task* head = NULL;

    printf("To-Do List Application\n");
    
    // Main loop for user input
    while(1) {
        // Display menu options
        printf("1. Add Task\n");
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
                printf("Enter task description: ");
                scanf(" %99[^\n]", description);
                printf("Enter task ID: ");
                scanf("%d", &id);
                addTask(&head, description, id);
                break;

            case 2:
                printf("Enter task ID to remove: ");
                scanf("%d", &id);
                removeTask(&head, id);
                break;
            
            case 3:
                showTasks(head);
                break;
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