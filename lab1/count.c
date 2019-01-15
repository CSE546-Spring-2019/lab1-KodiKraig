/**
 * @Author: Cody Craig <codycraig>
 * @Date:   08-Jan-2019, 5:06:13 pm
 * @Email:  cody.craig500@gmail.com
 * @Filename: count.c
 * @Last modified by:   codycraig
 * @Last modified time: 14-Jan-2019, 9:29:58 pm
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>



int main(int argc, char * argv[])
{
    FILE *stringFile, *outputFile;
    char *stringFileName, *searchString, *outputFileName, *buffer, *outputText;
    long sizeOfFile = 0, occurrences = 0, newSearchPosition;
    size_t bytesRead;
    int isMatch;

    // Parse arguments
    if (argc != 4) {
        printf("Invalid argument count. <input-filename> <search-string> <output-filename>\n");
        return EXIT_FAILURE;
    }
    stringFileName = argv[1];
    searchString = argv[2];
    outputFileName = argv[3];

    // Open the input file
    stringFile = fopen(stringFileName, "r");
    if (stringFile == NULL) {
        printf("Unable to open file: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    // Begin searching the file for the string
    buffer = (char *) malloc(sizeof(char));
    while (1) {
        bytesRead = fread(buffer, sizeof(char), 1, stringFile);
        if (bytesRead == 0) break; sizeOfFile += bytesRead;

        if (buffer[0] == (searchString[0] & 0xff)) {
            // Cache the current file position so we know where to start searching again
            newSearchPosition = ftell(stringFile);
            if (newSearchPosition < 0) {
                printf("Unable to get file position: %s\n", strerror(errno));
                return EXIT_FAILURE;
            }

            // Check each character to see if the string is match
            isMatch = 1;
            for (int i = 1; i < strlen(searchString); i++) {
                bytesRead = fread(buffer, sizeof(char), 1, stringFile);
                if (bytesRead == 0 || (buffer[0] != (searchString[i] & 0xff))) {
                    isMatch = 0;
                    break;
                }
            }

            // Increment count if a match was found
            if (isMatch) occurrences += 1;

            // Move back to the correct file location to resume searching
            if (fseek(stringFile, newSearchPosition, SEEK_SET) < 0) {
                printf("Unable to move file position back to searching location: %s\n", strerror(errno));
                return EXIT_FAILURE;
            }
        }
    }
    free(buffer);

    // Print output to screen
    printf("Size of file is %ld\nNumber of matches = %ld\n", sizeOfFile, occurrences);

    // Attempt to open/create output file
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Unable to create output file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Write to output file
    if (fprintf(outputFile, "Size of file is %ld\nNumber of matches = %ld\n", sizeOfFile, occurrences) < 0) {
        printf("Unable to write output file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Close files
    if (fclose(stringFile) != 0) {
        printf("Unable to close %s\nError: %s", stringFileName, strerror(errno));
    }
    if (fclose(outputFile) != 0) {
        printf("Unable to close %s\nError: %s", outputFileName, strerror(errno));
    }

    return EXIT_SUCCESS;
}
