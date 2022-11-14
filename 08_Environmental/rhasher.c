#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <rhash.h>
#include "config.h"

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

int main(void)
{
    int type_out = 0, rhash_hash = 0, file_flag = 1;
    char *line = NULL, *hash_name = NULL, *user_str = NULL, output[256];
    unsigned char digest[64];
    size_t read = 0, len = 0;
    rhash_library_init();
#ifdef USE_READLINE
    fprintf(stdout, "Using readline!\n");
    	while ((line = readline(NULL)))
#else
    fprintf(stdout, "Using getline!\n");
    while ((read = getline(&line, &len, stdin)) != -1)
#endif
    {
        hash_name = strtok(line, " ");
        user_str = strtok(strtok(NULL, " "), "\n");

        if (!user_str || !hash_name)
        {
            fprintf(stderr, "Usage: <hash name> [file, \"string]\n");
            fprintf(stderr, "Hash names: MD5, SHA1, TTH\n");
            continue;
        }

        if (hash_name[0] == tolower(hash_name[0]))
        {
            type_out = RHPR_BASE64;
        }
        else
        {
            type_out = RHPR_HEX;
        }
        for (size_t i = 0; i < strlen(hash_name); ++i)
        {
            hash_name[i] = tolower(hash_name[i]);
        }

        if (strcmp(hash_name, "md5") == 0)
        {
            rhash_hash = RHASH_MD5;
        }
        else if (strcmp(hash_name, "sha1") == 0)
        {
            rhash_hash = RHASH_SHA1;
        }

        else if (strcmp(hash_name, "tth") == 0)
        {
            rhash_hash = RHASH_TTH;
        }
        else
        {
            fprintf(stderr, "Incorrect hash name. Hash names: MD5, SHA1, TTH\n");
            continue;
        }


        if (user_str[0] == '\"')
        {
            file_flag = 0;
            user_str++;
        }

        if ( file_flag == 0 )
        {
            int res = rhash_msg( rhash_hash, user_str, strlen(user_str), digest);
            if ( res < 0 )
            {
                fprintf( stderr, "Error getting message's digest!\n");
                fprintf(stderr, "%s\n", strerror(errno));
                continue;
            }

        }
        else
        {
            int res = rhash_file( rhash_hash, user_str, digest);
            if ( res < 0 )
            {
                fprintf( stderr, "Error getting message's digest!!\n");
                fprintf(stderr, "%s\n", strerror(errno));
                continue;
            }
        }
        rhash_print_bytes( output, digest, rhash_get_digest_size(rhash_hash), type_out);
        fprintf(stdout, "%s\n", output);


        if (line)
        {
            free(line);
        }

    }

    return 0;
}
