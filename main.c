#include <stdio.h>
#include <ctype.h>
#define VERSION "0.0"
#define NAME "ac"
#define BUFFER_SIZE 64

char add(char c1, char c2)
{
  int lower = islower(c1);
  c1 = toupper(c1);
  c2 = toupper(c2);
  c1 = (c1 + c2 - 0x82) % 26;
  c1 += 0x41;
  if (lower) {
    c1 = tolower(c1);
  }
  return c1;
}
char minus(char c1, char c2)
{
  int lower = islower(c1);
  c1 = toupper(c1);
  c2 = toupper(c2);
  c1 = (26 + c1 - c2) % 26;
  c1 += 0x41;
  if (lower) {
    c1 = tolower(c1);
  }
  return c1;
}
void ac_encrypt(char *restrict text, const char *restrict keyword)
{
  char key[BUFFER_SIZE];
  char *inptr = key;
  char *outptr = key;
  while (*text && *keyword) {
    if (!isalpha(*keyword)) {
      ++keyword;
      continue;
    }
    if (isalpha(*text)) {
      *inptr++ = *text;
      *text = add(*text, *keyword++);
    } // else do nothing
    ++text;
  }
  while (*text) {
    if (isalpha(*text)) {
      *inptr++ = *text;
      *text = add(*text, *outptr++);
    }
    ++text;
  }
}

void ac_decrypt(char *restrict text, const char *restrict keyword)
{
  char key[BUFFER_SIZE];
  char *inptr = key;
  char *outptr = key;
  while (*text && *keyword) {
    if (!isalpha(*keyword)) {
      ++keyword;
      continue;
    }
    if (isalpha(*text)) {
      *text = minus(*text, *keyword++);
      *inptr++ = *text;
    } // else do nothing
    ++text;
  }
  while (*text) {
    if (isalpha(*text)) {
      *text = minus(*text, *outptr++);
      *inptr++ = *text;
    }
    ++text;
  }
}

void mode_e(const char * keyword, FILE * in, FILE * out)
{
  char buf[64];
  while (1) {
    fgets(buf, sizeof(buf), in);
    ac_encrypt(buf, keyword);
    fputs(buf, out);
  }
}

void mode_d(const char * keyword, FILE * in, FILE * out)
{
  char buf[64];
  while (1) {
    fgets(buf, sizeof(buf), in);
    ac_decrypt(buf, keyword);
    fputs(buf, out);
  }
}
/*
void file_mode_e(char * keyword, int key_len, FILE * in, FILE * out)
{
  char key;
  char text;
  int key_cnt = 0;
  while ((text = fgetc(in)) != EOF) {
    if (key_cnt < key_len) {
    }
  }
}
*/

int main(int argc, char * argv[])
{
  if (argc <= 2) {
    puts("Autokey Cipher\nVersion: "VERSION"\nUsage: "NAME
        " e/d keyword\n");
    return 0;
  } else if (argc == 3) {
    int mode = toupper(argv[1][0]) == 'E';
    if (mode) {
      mode_e(argv[2], stdin, stdout);
    } else {
      mode_d(argv[2], stdin, stdout);
    }
  } else if (argc == 5) {
    //int mode = toupper(argv[1][0]) == 'E';
  }
}
