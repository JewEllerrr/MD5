#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <clocale>
#include "MD5.h"
#pragma warning(disable : 4996)

#define MD5_DIGEST_LENGTH 16

static void MD5File (const char*);
static void MD5Print (unsigned char[MD5_DIGEST_LENGTH]);

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    //MD5File("Path to file");
    const char* string = "md5";
    MD5(string);

    return (0);
}

void MD5(const char* string)
{
    MD5_CTX context;
    unsigned int len = strlen(string);
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5Init(&context);
    MD5Update(&context, (unsigned char*)string, len);
    MD5Final(digest, &context);
    printf("MD5 (\"%s\") = ", string);
    MD5Print(digest);
    printf("\n");
}

/* Digests a file and prints the result.*/
static void MD5File(const char* filename) {
    FILE* file;
    FILE* file_result;
    char endline[] = "_resulllt.txt";
    char* md;
    MD5_CTX context;
    int len;
    unsigned char buffer[1024], digest[MD5_DIGEST_LENGTH];

    if ((fopen_s(&file, filename, "r")) != 0) {
        printf("cannot open file");
    } else {
        MD5Init(&context);
        while (len = fread(buffer, 1, sizeof(buffer), file))
            MD5Update(&context, buffer, len);
        MD5Final(digest, &context);

        fclose(file);

        md = (char*)malloc((strlen(filename)+(strlen(endline)+1))*sizeof(char));
        strcpy(md, filename);
        strcat(md, endline);
        fopen_s(&file_result, md, "w");
        printf("MD5 (%s) = ", md);
        MD5Print(digest);
        for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
            fprintf(file_result, "%02X", unsigned char(digest[i]));
        printf("\n");

        free(md);
        fclose(file_result);
    }
}

/* Prints a message digest in hexadecimal.*/
static void MD5Print(unsigned char digest[MD5_DIGEST_LENGTH]) {
    unsigned int i;
    for (i = 0; i < MD5_DIGEST_LENGTH; i++)
        printf("%02X", digest[i]);
}
