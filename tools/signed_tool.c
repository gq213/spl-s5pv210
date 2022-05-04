#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

int read_from_file(const char *name, unsigned char *buf, int size)
{
	FILE *fp;
	int ret;
	
	fp = fopen(name, "rb");
	if (fp == NULL) {
		printf("%s: Cannot open %s, errno=%d(%s)\n", __func__, name, errno, strerror(errno));
		return -1;
	}
	
	ret = fread(buf, 1, size, fp);
	
	fclose(fp);
	
	return ret;
}

int save_to_file(const char *name, unsigned char *buf, int size)
{
	FILE *fp;
	int ret;

	fp = fopen(name, "w+b");
	if (fp == NULL) {
		printf("%s: Cannot open %s, errno=%d(%s)\n", __func__, name, errno, strerror(errno));
		return -1;
	}
	
	ret = fwrite(buf, 1, size, fp);
	
	fflush(fp);
	fsync(fileno(fp));

	fclose(fp);
	
	if (ret != size) {
		printf("save %s error!\n", name);
		return -1;
	}

	return 0;
}

struct spl {
	uint32_t spl_size;
	uint32_t reserved0;
	uint32_t spl_checksum;
	uint32_t reserved1;
	uint8_t  spl_data[16 * 1024 - 16];
};

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Usage: %s <infile> <outfile>\n", argv[0]);
		return -1;
	}
	
	struct spl *s = malloc(sizeof(struct spl));
	if (s == NULL) {
		printf("malloc fail\n");
		return -1;
	}
	
	memset(s, 0, sizeof(struct spl));
	
	int size = read_from_file(argv[1], s->spl_data, sizeof(s->spl_data));
	if (size <= 0) {
		printf("size error\n");
		free(s);
		return -1;
	}
	
	s->spl_size = size;
	
	s->spl_checksum = 0;
	int i = 0;
	for (; i<s->spl_size; i++) {
		s->spl_checksum += s->spl_data[i];
	}
	
	s->spl_size += 16;
	
	int ret = save_to_file(argv[2], (unsigned char *)s, s->spl_size);
	
	free(s);
	
	return ret;
}
