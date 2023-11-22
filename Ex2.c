#include <unistd.h>

#define PASSWORD "123" // Define the predefined password

void alarmHandler(int sig) {
  if (sig == SIGALRM) {
    printf("Time limit exceeded. Terminating program...\n");
    exit(1);
  }
}

void signalHandler(int sig) {
  if (sig == SIGINT) {
    printf("Time limit reset to 10 seconds.\n");
    alarm(10); // Reset time limit to 10 seconds
  }
}

int main() {
  char inputPassword[100];

  // Set signal handlers for SIGALRM and SIGINT
  signal(SIGALRM, alarmHandler);
  signal(SIGINT, signalHandler);

  // Set initial time limit to 10 seconds
  alarm(10);

  printf("Enter password: ");
  fgets(inputPassword, sizeof(inputPassword), stdin);

  // Check if the entered password matches the predefined password
  if (strcmp(inputPassword, PASSWORD) != 0) {
    printf("Invalid password. Terminating program...\n");
    exit(1);
  }

  printf("Correct password entered.\n");

  return 0;
}
