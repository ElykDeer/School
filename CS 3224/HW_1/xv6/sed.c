// sed.c
// Usage:
//  sed -find -replace FILENME
//  sed FILENME
//  cat FILENAME | sed

#include "types.h"
#include "user.h"

#define INITIAL_STRING_LENGTH 8

typedef struct line
{
    short changed;
    char* line;
    int length;
} line;

typedef struct line_vec
{
    line* lines;
    int length;
} line_vec;


line_vec* read_input(char* filename);
int sed(char* find, char* replace, line_vec* file);
void cleanup(line_vec*);


int main(int argc, char* argv[])
{
    line_vec* file = 0;
    // stdin
    if (argc == 1)
    {
        file = read_input("");
        printf(1, "\n>> %d\n", sed("the", "xyz", file));
    }

    // replace all "the"'s with "xyz"
    else if (argc == 2)
    {
        file = read_input(argv[1]);
        printf(1, "\n>> %d\n", sed("the", "xyz", file));
    }

    // replace all argv[1] with argv[2]
    else if (argc == 4)
    {
        file = read_input(argv[3]);
        printf(1, "\n>> %d\n", sed(argv[1], argv[2], file));
    }

    // error
    else
    {
        printf(1, "Usage:\n sed -find -replace FILENME  # or\n sed FILENME  # or\n cat FILENAME | sed\n");
    }

    if (file != 0)
        cleanup(file);
    
    exit();
}


line_vec* read_input(char* filename)
{
    int fd;
    if (strcmp(filename, ""))
    {
        fd = open(filename, 0);
        if (fd < 0)
        {
            printf(1, "Cannot open file '%s'\n", filename);
            exit();
        }
    }
    else
    {
        fd = 0;
    }

    int lines_len = INITIAL_STRING_LENGTH;
    // line* lines[lines_len];
    line* lines = malloc(sizeof(line)*lines_len);
    int lines_curr = 0;

    char curr_char = '\x0';
    int curr_char_p = 0;
    while (read(fd, &curr_char, 1) == 1)
    {
        // Check if the item we are working on exists (see if the char* has been initialized)
        if (lines[lines_curr].line == 0)
        {
            lines[lines_curr].length = INITIAL_STRING_LENGTH;
            lines[lines_curr].line = malloc(INITIAL_STRING_LENGTH);
            curr_char_p = 0;
            // lines[lines_curr].changed = 0;  // Would be redundant
        }

        // Check if new line
        if (curr_char != '\x0a')
        {
            // Check if we're out of room, do the thing
            if (curr_char_p >= lines[lines_curr].length)
            {
                int new_line_len = (int)((float)lines[lines_curr].length * 1.2);
                char* new_line = malloc(new_line_len);

                // Zero out
                memset(new_line, 0, new_line_len);

                // Copy over old stuff
                memmove(new_line, lines[lines_curr].line, lines[lines_curr].length);

                // Free out old stuff
                free(lines[lines_curr].line);

                lines[lines_curr].line = new_line; 
                lines[lines_curr].length = new_line_len;
            }

            lines[lines_curr].line[curr_char_p] = curr_char;
            curr_char_p += 1;            
        }
        else
        {
            // If we are a new line, advance
            lines_curr += 1;

            // Check if we're out of room, do the thing
            if (lines_curr >= lines_len)
            {
                int new_lines_len = (int)((float)lines_len * 1.2);
                int new_size = sizeof(line)*new_lines_len;
                line* new_lines = malloc(new_size);

                // Zero out
                memset(new_lines, 0, new_size);

                // Copy over old stuff
                memmove(new_lines, lines, sizeof(line)*lines_len);

                free(lines);

                lines = new_lines; 
                lines_len = new_lines_len;
            }
        }
    }

    close(fd);

    // Pack into a line_vec and return
    line_vec* line_vec_p = malloc(sizeof(line_vec_p));
    line_vec_p->lines = lines;
    line_vec_p->length = lines_curr;
    return line_vec_p;
}


int sed(char* find, char* replace, line_vec* file)
{
    int matches = 0;

    int l;
    for (l = 0; l < file->length; ++l)
    {
        int c;
        for (c = 0; c <= file->lines[l].length - strlen(find); ++c)
        {
            short match = 1;
            int m;
            for (m = 0; ((m < strlen(find)) && match); ++m)
            {
                if (file->lines[l].line[c+m] != find[m])
                    match = 0;
            }

            if (match == 1)
            {
                matches += 1;
                char* buf = malloc(file->lines[l].length + (strlen(replace) - strlen(find)) + 1);
                memset(buf, 0, file->lines[l].length + (strlen(replace) - strlen(find)) + 1);

                // Move into the buf upto where we are
                memmove(buf, file->lines[l].line, c);

                // Move into the buf from where we are the replacement
                memmove(buf+c, replace, strlen(replace));

                // Move into the buf the rest of the string
                memmove(buf+c+strlen(replace), file->lines[l].line+c+strlen(find), file->lines[l].length - c - strlen(find)-1);

                free(file->lines[l].line);

                file->lines[l].line = buf;
                file->lines[l].changed = 1;
            }
        }
    }

    for (l = 0; l < file->length; ++l)
    {
        if (file->lines[l].changed == 1)
        {
            char* buf = malloc(file->lines[l].length + 1);
            memset(buf, 0, file->lines[l].length + 1);
            memmove(buf, file->lines[l].line, file->lines[l].length);
            
            printf(1, "%s\n", buf);
            
            free(buf);
        }
    }

    return matches;
}

void cleanup(line_vec* file)
{
    int l;
    for (l = 0; l < file->length; ++l)
    {
        free(file->lines[l].line);
    }

    free(file->lines);
    free(file);
}