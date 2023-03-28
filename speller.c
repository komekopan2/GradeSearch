// Implements a spell-checker

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "dictionary.h"

// Undefine any definitions
#undef calculate
#undef getrusage

// Default dictionary
#define DICTIONARY "dictionaries/large"

// Prototype
double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char *argv[])
{
    // Check for correct number of args
    if (argc != 2 && argc != 3 && argc != 4)
    {
        printf("Usage: ./speller [DICTIONARY] text\n");
        return 1;
    }

    // Structures for timing data
    struct rusage before, after;

    // Benchmarks
    // double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

    // Calculate time to load dictionary
    // time_load = calculate(&before, &after);

    // Try to open text
    char *text = (argc == 3) ? argv[2] : argv[1];
    /*char *text2 = argv[3];
    FILE *file2 = fopen(text2, "w");*/
    char *text3 = "student3.txt";
    FILE *file3 = fopen(text3, "w");
    /*if (file2 == NULL)
    {
        printf("Could not open %s.\n", text2);
        unload();
        return 1;
    }*/
    if (file3 == NULL)
    {
        printf("Could not open %s.\n", text3);
        unload();
        return 1;
    }

    // Prepare to report misspellings
    // fprintf(file2,"MISSPELLED WORDS\n");

    // Prepare to spell-check
    int index, misspellings[6], words[6];
    char c;
    int n[6];
    char word[6][LENGTH + 1];
    bool loaded[6];
    bool misspelled[6];
    bool unloaded[6];

    // Determine dictionary to use
    // char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;
    char dictionary[6][30] = {"dictionaries/0", "dictionaries/1", "dictionaries/2", "dictionaries/3", "dictionaries/4", "dictionaries/5"};
    char miss[6][30] = {"miss/0", "miss/1", "miss/2", "miss/3", "miss/4", "miss/5"};

    for (int aa = 0; aa < 6; aa++)
    {
        char *text2 = miss[aa];
        FILE *file2 = fopen(text2, "w");
        if (file2 == NULL)
        {
            printf("Could not open %s.\n", text2);
            unload();
            return 1;
        }
        if (aa < 3)
        {
            // fprintf(file2, "中学%d年生\n", aa + 1);
        }
        else
        {
            // fprintf(file2, "高校%d年生\n", aa - 2);
        }
        FILE *file = fopen(text, "r");
        if (file == NULL)
        {
            printf("Could not open %s.\n", text);
            unload();
            return 1;
        }

        // Load dictionary----------------------------------------------------------------------------------------
        // getrusage(RUSAGE_SELF, &before);
        loaded[aa] = load(dictionary[aa]);
        index = 0;
        misspellings[aa] = 0;
        words[aa] = 0;
        // getrusage(RUSAGE_SELF, &after);

        // Exit if dictionary not loaded
        if (!loaded[aa])
        {
            printf("Could not load %s.\n", dictionary[aa]);
            return 1;
        }

        // Spell-check each word in text

        while (fread(&c, sizeof(char), 1, file))
        {
            // Allow only alphabetical characters and apostrophes
            if (isalpha(c) || (c == '\'' && index > 0))
            {
                // Append character to word
                word[aa][index] = c;
                index++;

                // Ignore alphabetical strings too long to be words
                if (index > LENGTH)
                {
                    // Consume remainder of alphabetical string
                    while (fread(&c, sizeof(char), 1, file) && isalpha(c))
                        ;

                    // Prepare for new word
                    index = 0;
                }
            }

            // Ignore words with numbers (like MS Word can)
            else if (isdigit(c))
            {
                // Consume remainder of alphanumeric string
                while (fread(&c, sizeof(char), 1, file) && isalnum(c))
                    ;

                // Prepare for new word
                index = 0;
            }

            // We must have found a whole word
            else if (index > 0)
            {
                // Terminate current word
                word[aa][index] = '\0';

                // Update counter
                words[aa]++;

                if (index > 3)
                {

                    // Check word's spelling
                    // getrusage(RUSAGE_SELF, &before);
                    misspelled[aa] = !check(word[aa]);
                    // getrusage(RUSAGE_SELF, &after);

                    // Update benchmark
                    // time_check += calculate(&before, &after);

                    // Print word if misspelled
                    if (misspelled[aa])
                    {
                        fprintf(file2, "%s\n", word[aa]);
                        misspellings[aa]++;
                    }
                }

                // Prepare for next word
                index = 0;
            }
        }

        // Check whether there was an error
        if (ferror(file))
        {
            fclose(file);
            printf("Error reading %s.\n", text);
            unload();
            return 1;
        }

        // Close text
        fclose(file);

        // Determine dictionary's size
        // getrusage(RUSAGE_SELF, &before);
        n[aa] = size();
        for (int ac = 0; ac < 6; ac++)
        {
            // printf("%d\n",n[ac]);
        }
        // getrusage(RUSAGE_SELF, &after);

        // Calculate time to determine dictionary's size
        // time_size = calculate(&before, &after);

        // Unload dictionary-------------------------------------------------------------------
        // getrusage(RUSAGE_SELF, &before);
        unloaded[aa] = unload();
        // getrusage(RUSAGE_SELF, &after);

        // Abort if dictionary not unloaded
        if (!unloaded[aa])
        {
            printf("Could not unload %s.\n", dictionary[aa]);
            return 1;
        }
        // fprintf(file2, "weblioトップページへ遷移");
    }

    // Calculate time to unload dictionary
    // time_unload = calculate(&before, &after);

    // Report benchmarks
    for (int ab = 0; ab < 6; ab++)
    {
        if (ab < 3)
        {
            fprintf(file3, "%d%%\n", (words[ab] - misspellings[ab]) * 100 / words[ab]);
        }
        else
        {
            fprintf(file3, "%d%%\n", (words[ab] - misspellings[ab]) * 100 / words[ab]);
        }
        /*
        fprintf(file3, "WORDS MISSPELLED:     %d\n", misspellings[ab]);
        fprintf(file3, "WORDS SPELLED:     %d\n", words[ab] - misspellings[ab]);

        fprintf(file3, "WORDS IN DICTIONARY:  %d\n", n[ab]);
        fprintf(file3, "WORDS IN TEXT:        %d\n", words[ab]);
        */
    }
    // printf("TIME IN load:         %.2f\n", time_load);
    // printf("TIME IN check:        %.2f\n", time_check);
    // printf("TIME IN size:         %.2f\n", time_size);
    // printf("TIME IN unload:       %.2f\n", time_unload);
    // printf("TIME IN TOTAL:        %.2f\n\n",
    // time_load + time_check + time_size + time_unload);

    // Success
    return 0;
}

// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec))) /
                1000000.0);
    }
}
