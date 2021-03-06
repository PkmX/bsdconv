#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../../src/bsdconv.h"

struct my_s{
	FILE *bak;
	FILE *score;
	FILE *list;
};

int cbcreate(struct bsdconv_instance *ins, struct bsdconv_hash_entry *arg){
	struct my_s *r=malloc(sizeof(struct my_s));
	char buf[256]={0};
	char *p=getenv("BSDCONV_SCORE");
	if(p==NULL){
		strcpy(buf,getenv("HOME"));
		strcat(buf,"/.bsdconv.score");
		p=buf;
	}
	r->bak=fopen(p,"a"); //ensure file existence
	fclose(r->bak);
	r->bak=r->score=fopen(p,"rb+");
	r->list=NULL;
	THIS_CODEC(ins)->priv=r;
	return 0;
}

void cbdestroy(struct bsdconv_instance *ins){
	struct my_s *r=THIS_CODEC(ins)->priv;
	fclose(r->bak);
	free(r);
}

void cbctl(struct bsdconv_instance *ins, int ctl, void *ptr, size_t v){
	struct my_s *r=THIS_CODEC(ins)->priv;
	switch(ctl){
		case BSDCONV_CTL_ATTACH_SCORE:
			r->score=ptr;
			break;
		case BSDCONV_CTL_ATTACH_OUTPUT_FILE:
			r->list=ptr;
			break;
	}
}

void cbconv(struct bsdconv_instance *ins){
	unsigned char *data;
	struct bsdconv_phase *this_phase=THIS_PHASE(ins);
	struct my_s *r=THIS_CODEC(ins)->priv;
	data=this_phase->curr->data;
	unsigned char v=0;
	int i;
	uint32_t ucs=0;
	uint32_t ucs4;

	this_phase->data_tail->next=dup_data_rt(ins, this_phase->curr);
	this_phase->data_tail=this_phase->data_tail->next;
	this_phase->data_tail->next=NULL;

	if(data[0]==0x1){
		for(i=1;i<this_phase->curr->len;++i){
			ucs<<=8;
			ucs|=data[i];
		}
		fseek(r->score, ucs*sizeof(unsigned char), SEEK_SET);
		fread(&v, sizeof(unsigned char), 1, r->score);
		if(v==0 && r->list){
			ucs4=htobe32(ucs);
			fwrite(&ucs4, sizeof(uint32_t), 1, r->list);
		}
		if(v<3){
			v+=1;
			fseek(r->score, ucs*sizeof(unsigned char), SEEK_SET);
			fwrite(&v, sizeof(unsigned char), 1, r->score);
		}
	}

	this_phase->state.status=NEXTPHASE;
	return;
}
