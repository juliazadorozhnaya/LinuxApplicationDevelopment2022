#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define BUF_SIZE 1024

int main(int argc, char *argv[]) {

	if (argc == 1) {
		printf("move - moves contents of infile to outfile and removes infile\n" \
			   "usage:\n\tmove infile outfile\n");
		return 0;
	} else if (argc != 3) {
		fprintf(stderr, "%s\n", "Wrong number of arguments.");
		return 1;
	}

	char *infile_name = argv[1], *outfile_name = argv[2];
	FILE* in_fp = fopen(infile_name, "r");
    if (!in_fp) {
        perror("Failed to open input file.");
        return 2;
    }
    FILE* out_fp = fopen(outfile_name, "w");
	if (!out_fp) {
        perror("Failed to open output file.");
        return 3;
    }

    char* buf = (char*) malloc(BUF_SIZE * sizeof(char));
    if (buf == NULL) {
        perror("Allocation error");

        fclose(out_fp);
        remove(outfile_name);
        return -1;
    }

    size_t count;
    while (!feof(in_fp)) {
        count = fread(buf, sizeof(char), BUF_SIZE, in_fp);
        if (count != BUF_SIZE && !feof(in_fp)) {
            errno = EAGAIN;
            perror("Can't read from infile");
            fclose(out_fp);
            remove(outfile_name);
            return 4;
        }
        int written = fwrite(buf, sizeof(char), count, out_fp);
        if (count != written) {
            errno = EAGAIN;
            perror("Can't write to outfile");
            fclose(out_fp);
            remove(outfile_name);
            return 4;
        }
    }

    if (ferror(in_fp)) {
        perror("I/O error when reading input file");
        return 4;
    } else if (feof(in_fp)) {
        fprintf(stdout, "%s\n", "Contents of input file successfully moved.");
    }

    free(buf);
    fclose(out_fp);
    fclose(in_fp);
    remove(infile_name);

    return 0;
}

