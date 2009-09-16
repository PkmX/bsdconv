#include <stdlib.h>
#include <string.h>
#include "../../src/bsdconv.h"


struct my_s{
	int status;
	unsigned char buf[4];
};

void *cbcreate(void){
	return  malloc(sizeof(struct my_s));
}

void cbinit(struct bsdconv_codec_t *cdc, struct my_s *r){
	r->status=0;
}

void cbdestroy(void *p){
	free(p);
}

#define CONTINUE() do{	\
	this_phase->state.status=CONTINUE;	\
	return;	\
}while(0);

void callback(struct bsdconv_instance *ins){
	struct bsdconv_phase *this_phase=&ins->phase[0];
	struct my_s *t=this_phase->codec[this_phase->index].priv;
	unsigned char d=*ins->from_data;
	int i;
	size_t l;
	switch(t->status){
		case 0:
			t->buf[0]=d;
			t->status=1;
			CONTINUE();
			break;
		case 1:
			t->buf[1]=d;
			t->status=2;
			CONTINUE();
			break;
		case 2:
			t->buf[2]=d;
			t->status=3;
			CONTINUE();
			break;
		case 3:
			t->buf[3]=d;
			t->status=0;
			for(i=0;i<4;++i){
				if(t->buf[i]) break;
			}
			l=(4-i)+1;
			this_phase->data_tail->next=malloc(sizeof(struct data_s));
			this_phase->data_tail=this_phase->data_tail->next;
			this_phase->data_tail->next=NULL;
			this_phase->data_tail->len=l;
			this_phase->data_tail->data=malloc(l);
			this_phase->data_tail->data[0]=0x01;
			memcpy(&this_phase->data_tail->data[1], &t->buf[i], l-1);
			this_phase->state.status=NEXTPHASE;
			return;
			break;
	}
}
