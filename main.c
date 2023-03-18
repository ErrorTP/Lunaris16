#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *strtrim(char *str) {
  while (isspace(*str)) {
    str++;
  }
  char *end = str + strlen(str) - 1;
  while (end > str && isspace(*end)) {
    end--;
  }
  *(end + 1) = '\0';
  return str;
}
char *encode_instruction(char *instruction) {
  char *instruction_copy = strdup(instruction);
  char *opcode = strtok(instruction_copy, " ");
  opcode = strtrim(opcode);
  char *binary_opcode = malloc(sizeof(char) * 17);
  char *binary_argument = malloc(sizeof(char) * 12);
  memset(binary_opcode, '0', 5);
  binary_opcode[5] = '\0';
  binary_opcode[16] = '\0';
  binary_argument[0] = '\0';
  if (strcmp(opcode, "NOP") == 0) {
    strncpy(binary_opcode, "00000000000000000", 16);
  } else if (strcmp(opcode, "LDA") == 0) {
    strncpy(binary_opcode, "00001", 5);
  } else if (strcmp(opcode, "LDB") == 0) {
    strncpy(binary_opcode, "00010", 5);
  } else if (strcmp(opcode, "LDC") == 0) {
    strncpy(binary_opcode, "00011", 5);
  } else if (strcmp(opcode, "LMA") == 0) {
    strncpy(binary_opcode, "00100", 5);
  } else if (strcmp(opcode, "LMB") == 0) {
    strncpy(binary_opcode, "00101", 5);
  } else if (strcmp(opcode, "LMC") == 0) {
    strncpy(binary_opcode, "00110", 5);
  } else if (strcmp(opcode, "STA") == 0) {
    strncpy(binary_opcode, "00111", 5);
  } else if (strcmp(opcode, "STC") == 0) {
    strncpy(binary_opcode, "01000", 5);
  } else if (strcmp(opcode, "JMP") == 0) {
    strncpy(binary_opcode, "01001", 5);
  } else if (strcmp(opcode, "JMPZ") == 0) {
    strncpy(binary_opcode, "01011", 5);
  } else if (strcmp(opcode, "JMPC") == 0) {
    strncpy(binary_opcode, "01100", 5);
  } else if (strcmp(opcode, "JMPNC") == 0) {
    strncpy(binary_opcode, "01101", 5);
  } else if (strcmp(opcode, "JMPE") == 0) {
    strncpy(binary_opcode, "01111", 5);
  } else if (strcmp(opcode, "BSR") == 0) {
    strncpy(binary_opcode, "10000", 5);
  } else if (strcmp(opcode, "BSL") == 0) {
    strncpy(binary_opcode, "10001", 5);
  } else if (strcmp(opcode, "ADD") == 0) {
    strncpy(binary_opcode, "1111000000000000", 16);
  } else if (strcmp(opcode, "SUB") == 0) {
    strncpy(binary_opcode, "1111000000000001", 16);
  } else if (strcmp(opcode, "MULT") == 0) {
    strncpy(binary_opcode, "1111000000000010", 16);
  } else if (strcmp(opcode, "DIV") == 0) {
    strncpy(binary_opcode, "1111000000000011", 16);
  } else if (strcmp(opcode, "MIA") == 0) {
    strncpy(binary_opcode, "1111000000000100", 16);
  } else if (strcmp(opcode, "MOA") == 0) {
    strncpy(binary_opcode, "1111000000000101", 16);
  } else {
    printf("Invalid opcode: %s\n", opcode);
    return NULL;
  }
  char *argument = strtok(NULL, " ");
  if (argument == NULL) {
    binary_argument[0] = '\0';
    if (strlen(binary_opcode) == 16) {
      return binary_opcode;
    }
    printf("Invalid instruction format\n");
    free(binary_opcode);
    free(binary_argument);
    return NULL;
  }
  int arg = atoi(argument);
  binary_argument[11] = '\0';
  for (int i = 10; i >= 0; i--) {
    binary_argument[i] = (arg & 1) + '0';
    arg >>= 1;
  }
  char *result = malloc(sizeof(char) * 34);
  strcpy(result, binary_opcode);
  strcat(result, binary_argument);
  free(binary_opcode);
  free(binary_argument);
  free(instruction_copy);
  return result;
}
char *assemble(char *instruction) {
  char *binary_instruction = encode_instruction(instruction);
  if (binary_instruction == NULL) {
    return NULL;
  }
  return binary_instruction;
}
void toUpperCase(char *str) {
  int i = 0;
  while (str[i] != '\0') {
    str[i] = toupper(str[i]);
    i++;
  }
}
char *binary_to_hex(const char *binary_string) {
  size_t binary_len = strlen(binary_string);
  if (binary_len % 4 != 0) {
    return NULL;
  }
  size_t hex_len = binary_len / 4;
  char *hex_string = malloc(hex_len + 1);
  if (!hex_string) {
    return NULL;
  }
  hex_string[hex_len] = '\0';
  for (size_t i = 0; i < hex_len; i++) {
    unsigned char hex = 0;
    for (size_t j = 0; j < 4; j++) {
      size_t k = i * 4 + j;
      if (binary_string[k] == '1') {
        hex |= 1 << (3 - j);
      } else if (binary_string[k] != '0') {
        free(hex_string);
        return NULL;
      }
    }
    sprintf(hex_string + i, "%X", hex);
  }
  return hex_string;
}
long int findSize(char file_name[]) {
  FILE *fp = fopen(file_name, "r");
  if (fp == NULL) {
    printf("File Not Found!\n");
    return -1;
  }
  fseek(fp, 0L, SEEK_END);
  long int res = ftell(fp);
  fclose(fp);
  return res;
}
int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s input_file [output_file]\n", argv[0]);
    return 0;
  }
  printf("Lunaris and Horizon16 are in early development!\nLunaris for the Horizon16 Version 1.0.0\n")
  #ifdef __linux__
  printf("Currently running on Linux\n");
  #else
  printf("Running on an unsupported operating system!\nBeware of bugs!\n")
  #endif
  FILE *input_file = fopen(argv[1], "r");
  if (!input_file) {
    printf("Error opening input file %s\n", argv[1]);
    return 1;
  }
  FILE *output_file;
  if (argc >= 3) {
    output_file = fopen(argv[2], "w");
    if (!output_file) {
      printf("Error opening output file %s\n", argv[2]);
      fclose(input_file);
      return 1;
    }
  } else {
    output_file = fopen("a.out", "w");
    if (!output_file) {
      printf("Error opening output file %s\n", "a.out");
      fclose(input_file);
      return 1;
    }
  }
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  printf("Assembling...\n");
  while ((read = getline(&line, &len, input_file)) != -1) {
    toUpperCase(line);
    char *AssembledIns = assemble(line);
    char part1[8];
    strncpy(part1, AssembledIns, 8);
    char *part2 = AssembledIns + 16 - 8;
    long int decimal1 = strtol(part1, NULL, 2);
    char ascii1 = (char)decimal1;
    long int decimal2 = strtol(part2, NULL, 2);
    char ascii2 = (char)decimal2;
    char *hexstr = binary_to_hex(AssembledIns);
    fprintf(output_file, "%c%c", ascii1, ascii2);
    printf("%s | %s 0x%s\n", strtrim(line), AssembledIns, hexstr);
    free(AssembledIns);
    free(hexstr);
  }
  fclose(input_file);
  fclose(output_file);
  if (line) {
    free(line);
  }
  if (argv[2]) {
    printf("Your program has been assembled...\n%li bytes\n",
           findSize(argv[2]));
  } else {
    printf("Your program has been assembled...\n%li bytes\n",
           findSize("a.lbin"));
  }
  return 0;
}