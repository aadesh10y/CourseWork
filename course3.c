#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to generate a random password
char *generate_password(int length) {
  // Create a string of all possible characters that the password can contain
  char *possible_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+{}[]<>,.;'?";

  // Create a character array to store the password
  char *password = malloc((length + 1) * sizeof(char));

  // Seed the random number generator
  srand(time(NULL));

  // Generate a random password
  for (int i = 0; i < length; i++) {
    // Select a random character from the string of possible characters
    int index = rand() % strlen(possible_characters);

    // Add the character to the password
    password[i] = possible_characters[index];
  }
  password[length] = '\0'; // Add null terminator to make it a valid string

  // Return the password
  return password;
}

// Function to get the type of account
char *get_account_type() {
  // Print a list of account types
  printf("Select the type of account:\n");
  printf("1. Bank account\n");
  printf("2. Social media account\n");
  printf("3. Email account\n");
  printf("4. Other\n");

  // Get the user's input
  int account_type;
  printf("Enter your type of account: ");
  scanf("%d", &account_type);

  // Validate the user's input
  if (account_type < 1 || account_type > 4) {
    printf("Invalid account type.\n");
    return NULL;
  }

  // Create a character array to store the account type
  char *type = NULL;
  switch (account_type) {
    case 1:
      type = strdup("Bank account");
      break;
    case 2: {
      type = malloc(50 * sizeof(char));  // Allocate memory for the account type
      printf("Select the type of social media account:\n");
      printf("1. Facebook\n");
      printf("2. Twitter\n");
      printf("3. Instagram\n");
      printf("4. TikTok\n");
      printf("5. Other\n");
      int social_media_type;
      printf("Enter the type of social media account: ");
      scanf("%d", &social_media_type);
      switch (social_media_type) {
        case 1:
          strcpy(type, "Facebook");
          break;
        case 2:
          strcpy(type, "Twitter");
          break;
        case 3:
          strcpy(type, "Instagram");
          break;
        case 4:
          strcpy(type, "TikTok");
          break;
        case 5:
          printf("Enter the type of social media account: ");
          scanf(" %[^\n]s", type);
          break;
        default:
          printf("Invalid social media account type.\n");
          free(type);
          return NULL;
      }
      break;
    }
    case 3:
      type = strdup("Email account");
      break;
    case 4: {
      type = malloc(50 * sizeof(char));  // Allocate memory for the account type
      printf("Enter the type of account: ");
      scanf(" %[^\n]s", type);  // Read the account type as a string
      break;
    }
  }

  // Return the account type
  return type;
}

// Function to get the length of the password
int get_password_length() {
  // Print a prompt
  printf("Enter the desired length of the password: ");

  // Get the user's input
  int password_length;
  scanf("%d", &password_length);

  // Validate the user's input
  if (password_length < 8) {
    printf("The password must be at least 8 characters long.\n");
    return -1;
  }

  // Return the password length
  return password_length;
}

// Function to save the password to a file
void save_password_to_file(const char *password, const char *account_type) {
  // Create a directory called "password" if it doesn't exist
#ifdef _WIN32
  system("mkdir password 2> nul");
#else
  system("mkdir -p password");
#endif

  // Generate a unique file name using the current timestamp
  time_t current_time;
  time(&current_time);
  char timestamp[20];
  snprintf(timestamp, sizeof(timestamp), "%ld", current_time);

  // Generate the file path
  char file_path[100];
  snprintf(file_path, sizeof(file_path), "password/%s_%s.txt", account_type, timestamp);

  // Open the file in append mode
  FILE *file = fopen(file_path, "a");
  if (file == NULL) {
    printf("Failed to save the password to file.\n");
    return;
  }

  // Write the password to the file
  fprintf(file, "Account Type: %s\n", account_type);
  fprintf(file, "Password: %s\n", password);

  // Close the file
  fclose(file);

  printf("Password saved to file: %s\n", file_path);
}

// Main function
int main() {
  // Get the type of account
  char *account_type = get_account_type();

  // Print the selected account type
  printf("Selected account type: %s\n", account_type);

  // Get the length of the password
  int password_length = get_password_length();

  // Generate a password
  char *password = generate_password(password_length);

  // Print the password
  printf("Your password is: %s\n", password);

  // Save the password to a file
  save_password_to_file(password, account_type);

  // Free the memory allocated for the account type and password
  free(account_type);
  free(password);

  return 0;
}
