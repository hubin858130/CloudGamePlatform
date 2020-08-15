#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include "Base64CodecApi.h"

#define BASE64_PAD64 '='

const char base64_alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a',
'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1',
'2', '3', '4', '5', '6', '7', '8', '9', '+',
'/'};

const char base64_suffix_map[256] = {
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255,  62, 255, 255, 255,  63,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 255, 255,
	255, 255, 255, 255, 255,  0,   1,    2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,
	15,   16,  17,  18,  19,  20,  21,  22,  23,  24,  25, 255, 255, 255, 255, 255, 255,  26,  27,  28,
	29,   30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
	49,   50,  51, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};

static char cmove_bits(unsigned char src, unsigned lnum, unsigned rnum) {
	src <<= lnum;
	src >>= rnum;
	return src;
}

char* base64_encode(const char *data,int nInputLen) {
	char *ret, *retpos;
	int m = 0;
	int padnum = 0;
	int retsize = 0;
	int dlen = nInputLen;

	if(dlen == 0) return NULL;

	/* Account the result buffer size and alloc the memory for it. */
	if((dlen % 3) != 0)
		padnum = 3 - dlen % 3;
	retsize = (dlen + padnum) + ((dlen + padnum) * 1/3) + 1;
	if((ret = (char*)malloc(retsize)) == NULL) 
		return NULL;
	retpos = ret;

	/* Starting to convert the originality characters to BASE64 chracaters. 
	Converting process keep to 4->6 principle. */
	for(m = 0; m < (dlen + padnum); m += 3) {
		/* When data is not suffice 24 bits then pad 0 and the empty place pad '='. */
		*(retpos) = base64_alphabet[cmove_bits(*data, 0, 2)];
		if(m == dlen + padnum - 3 && padnum != 0) {  /* Whether the last bits-group suffice 24 bits. */
			if(padnum == 1) {   /* 16bit need pad one '='. */
				*(retpos + 1) = base64_alphabet[cmove_bits(*data, 6, 2) + cmove_bits(*(data + 1), 0, 4)];
				*(retpos + 2) = base64_alphabet[cmove_bits(*(data + 1), 4, 2)];
				*(retpos + 3) = BASE64_PAD64;
			} else if(padnum == 2) { /* 8bit need pad two'='. */
				*(retpos + 1) = base64_alphabet[cmove_bits(*data, 6, 2)];
				*(retpos + 2) = BASE64_PAD64;
				*(retpos + 3) = BASE64_PAD64;
			}
		} else {  /* 24bit normal. */
			*(retpos + 1) = base64_alphabet[cmove_bits(*data, 6, 2) + cmove_bits(*(data + 1), 0, 4)];
			*(retpos + 2) = base64_alphabet[cmove_bits(*(data + 1), 4, 2) + cmove_bits(*(data + 2), 0, 6)];
			*(retpos + 3) = base64_alphabet[*(data + 2) & 0x3f];
		}

		retpos += 4;
		data += 3;
	}

	ret[retsize - 1] =0;

	return ret;
}

char* base64_decode(int &nSize,const char *bdata) 
{
	char *ret = NULL;
	char *retpos = NULL;
	int  m= 0;
	int padnum = 0;
	int retsize = 0;
	int bdlen = strlen(bdata);

	if(bdlen == 0) return NULL;
	if(bdlen % 4 != 0) return NULL;

	/* Whether the data have invalid base-64 characters? */
	for(m = 0; m < bdlen; ++m) 
	{
		if(bdata[m] != BASE64_PAD64 && base64_suffix_map[bdata[m]] == 255)
			goto LEND;
	}

	/* Account the output size. */
	if(bdata[bdlen - 1] ==  '=')  padnum = 1;
	if(bdata[bdlen - 1] == '=' && bdata[bdlen - 2] ==  '=') padnum = 2;
	retsize = (bdlen - 4) - (bdlen - 4) / 4 + (3 - padnum);

	ret = (char*)malloc(retsize);
	if(ret == NULL) 
		return NULL;
	retpos = ret;

	/* Begging to decode. */
	for(m = 0; m < bdlen; m += 4) 
	{
		*retpos = cmove_bits(base64_suffix_map[*bdata], 2, 0) + cmove_bits(base64_suffix_map[*(bdata + 1)], 0, 4);
		if(m == bdlen - 4 && padnum != 0) {  /* Only deal with last four bits. */
			if(padnum == 1)   /* Have one pad characters, only two availability characters. */
				*(retpos + 1) = cmove_bits(base64_suffix_map[*(bdata + 1)], 4, 0) + cmove_bits(base64_suffix_map[*(bdata + 2)], 0, 2);
			/*
			Have two pad characters, only two availability characters.
			if(padnum == 2) { 
			}
			*/
			retpos += 3 - padnum;
		} else {
			*(retpos + 1) = cmove_bits(base64_suffix_map[*(bdata + 1)], 4, 0) + cmove_bits(base64_suffix_map[*(bdata + 2)], 0, 2);
			*(retpos + 2) = cmove_bits(base64_suffix_map[*(bdata + 2)], 6, 0) + base64_suffix_map[*(bdata + 3)];
			retpos += 3;
		}
		bdata += 4;
	}

	nSize = retsize;
LEND: return ret;
}

void base64_ReleaseDataBuffer(char **data)
{
	if (NULL != *data)
	{
		free(*data);
		*data = NULL;
	}
}