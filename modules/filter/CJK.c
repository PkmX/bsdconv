/*
 * Reference: http://blog.oasisfeng.com/2006/10/19/full-cjk-unicode-range/
 * Some code come from http://www.cl.cam.ac.uk/~mgk25/ucs/wcwidth.c
 *
 * Copyright (c) 2012-2014 Kuan-Chung Chiu <buganini@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "../../src/bsdconv.h"

struct range {
	int first;
	int last;
};

static const struct range zhrange[] = {
	{ 0x3100, 0x312F },	//Chinese Bopomofo
	{ 0x3400, 0x4DB5 },	//CJK Unified Ideographs Extension A	;Unicode3.0
	{ 0x4E00, 0x6FFF },	//CJK Unified Ideographs	;Unicode 1.1	;HF
	{ 0x7000, 0x9FA5 },	//CJK Unified Ideographs	;Unicode 1.1	;LF
	{ 0x9FA6, 0x9FBB },	//CJK Unified Ideographs	;Unicode 4.1
	{ 0xF900, 0xFA2D },	//CJK Compatibility Ideographs	;Unicode 1.1
	{ 0xFA30, 0xFA6A },	//CJK Compatibility Ideographs	;Unicode 3.2
	{ 0xFA70, 0xFAD9 },	//CJK Compatibility Ideographs	;Unicode 4.1
	{ 0x20000, 0x2A6D6 },//CJK Unified Ideographs Extension B	;Unicode 3.1
	{ 0x2F800, 0x2FA1D },//CJK Compatibility Supplement	;Unicode 3.1
};

unsigned char cbfilter(struct data_rt *data){
	uint32_t ucs=0;
	int i;
	int max=sizeof(zhrange) / sizeof(struct range) - 1;
	int min = 0;
	int mid;

	if(UCP(data->data)[0]!=1){
		return 0;
	}

	for(i=1;i<data->len;++i){
		ucs<<=8;
		ucs|=UCP(data->data)[i];
	}

	if (ucs < zhrange[0].first || ucs > zhrange[max].last){
		//noop
	}else while (max >= min) {
		mid = (min + max) / 2;
		if (ucs > zhrange[mid].last)
			min = mid + 1;
		else if (ucs < zhrange[mid].first)
			max = mid - 1;
		else{
			return 1;
		}
	}

	return 0;
}