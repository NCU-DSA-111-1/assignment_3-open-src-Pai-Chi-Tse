#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#include <cstdlib>

#include "arth.h"
#include "huffman.h"

static int memory_encode_file(FILE* in, FILE* out);
static int memory_decode_file(FILE* in, FILE* out);

void print_usage(char *file)
{
	printf("%s -[d,e] [input file] [output file_arth] [output file_huff]\n", file);
}

int main(int argc, char** argv)
{
	clock_t start_arth, finish_arth, start_huff, finish_huff;
	FILE *os, *is;
	double duration_arth, duration_huff;
	int symbol;

	if(argc!=5)
	{
		print_usage(argv[0]);
		return 1;
	}
    is = fopen(argv[2], "rb");
	if(is)
	{
		if(argv[1][0]=='-')
		{
			os = fopen(argv[3], "wb");

			switch(argv[1][1])
			{
			case 'e':

				printf("start Arithmetic encoding...\n");

				init_arth(os);

				start_arth = clock();

				while((symbol=fgetc(is))!=EOF)
				{
					encode(symbol);
				}
				encode(-1);
				close_encode();

				finish_arth = clock();

				break;
			case 'd':

				printf("start Arithmetic decoding...\n");

				init_arth(is);

				start_arth = clock();

				while((symbol=decode())>=0)
				{
					putc(symbol, os);
				}

				finish_arth = clock();

				break;
			}

			fclose(os);
		}
		fclose(is);
	}
	////////////////////huffman/////////////////////////
	is = fopen(argv[2], "rb");
	if(is)
	{
		if(argv[1][0]=='-')
		{
			os = fopen(argv[4], "wb");

			switch(argv[1][1])
			{
			case 'e':

				printf("start Huffman encoding...\n");

				start_huff = clock();

				memory_encode_file(is, os);

				finish_huff = clock();

				break;
			case 'd':

				printf("start Huffman decoding...\n");

				start_huff = clock();

				memory_decode_file(is, os);

				finish_huff = clock();

				break;
			}

			fclose(os);
		}
		fclose(is);
	}
    ////////////////////////////////////////////////////
	duration_arth = (double)(finish_arth - start_arth) / CLOCKS_PER_SEC;
    duration_huff = (double)(finish_huff - start_huff) / CLOCKS_PER_SEC;

	printf("time cost of arithmetic coding: %f ms\n", duration_arth);
    printf("time cost of huffman coding: %f ms\n", duration_huff);

	return 0;
}
/////////////////huffman encoding///////////////////
static int memory_encode_file(FILE* in, FILE* out)
{
	unsigned char *buf = NULL, *bufout = NULL;
	unsigned int len = 0, cur = 0, inc = 1024, bufoutlen = 0;

	assert(in && out);

	/* Read the file into memory. */
	while (!feof(in))
	{
		unsigned char* tmp;
		len += inc;
		tmp = (unsigned char*)realloc(buf, len);
		if (!tmp)
		{
			if (buf)
				free(buf);
			return 1;
		}

		buf = tmp;
		cur += fread(buf + cur, 1, inc, in);
	}

	if (!buf)
		return 1;

	/* Encode the memory. */
	if (huffman_encode_memory(buf, cur, &bufout, &bufoutlen))
	{
		free(buf);
		return 1;
	}

	free(buf);

	/* Write the memory to the file. */
	if (fwrite(bufout, 1, bufoutlen, out) != bufoutlen)
	{
		free(bufout);
		return 1;
	}

	free(bufout);

	return 0;
}
/////////////////huffman decoding///////////////////
static int memory_decode_file(FILE* in, FILE* out)
{
	unsigned char *buf = NULL, *bufout = NULL;
	unsigned int len = 0, cur = 0, inc = 1024, bufoutlen = 0;
	assert(in && out);

	/* Read the file into memory. */
	while (!feof(in))
	{
		unsigned char* tmp;
		len += inc;
		tmp = (unsigned char*)realloc(buf, len);
		if (!tmp)
		{
			if (buf)
				free(buf);
			return 1;
		}

		buf = tmp;
		cur += fread(buf + cur, 1, inc, in);
	}

	if (!buf)
		return 1;

	/* Decode the memory. */
	if (huffman_decode_memory(buf, cur, &bufout, &bufoutlen))
	{
		free(buf);
		return 1;
	}

	free(buf);

	/* Write the memory to the file. */
	if (fwrite(bufout, 1, bufoutlen, out) != bufoutlen)
	{
		free(bufout);
		return 1;
	}

	free(bufout);

	return 0;
}
