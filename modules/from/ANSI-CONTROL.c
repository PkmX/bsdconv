#include <stdlib.h>
#include <string.h>
#include "../../src/bsdconv.h"

#define F_CLEAR 0
#define F_A 1
#define F_B 2

struct my_s {
	char *buf;
	char *p,f;
};

int cbcreate(struct bsdconv_instance *ins, struct bsdconv_hash_entry *arg){
	struct my_s *r=malloc(sizeof(struct my_s));
	r->buf=malloc(32);
	THIS_CODEC(ins)->priv=r;
	return 0;
}

void cbinit(struct bsdconv_instance *ins){
	struct my_s *r=THIS_CODEC(ins)->priv;
	r->p=r->buf;
	r->f=0;
}

void cbdestroy(struct bsdconv_instance *ins){
	struct my_s *r=THIS_CODEC(ins)->priv;
	free(r->buf);
	free(r);
}

void cbconv(struct bsdconv_instance *ins){
	struct bsdconv_phase *this_phase=THIS_PHASE(ins);
	struct my_s *t=THIS_CODEC(ins)->priv;
	char d=CP(this_phase->curr->data)[this_phase->i];

	if(t->f){
		*(t->p)=d;
		t->p+=1;
		this_phase->state.status=CONTINUE;
		if((d>='a' && d<='z') || (d>='A' && d<='N') || (d>='P' && d<='Z') || (t->p - t->buf)==30 || ((t->p - t->buf)==2 && d!='[')){
			DATA_MALLOC(ins, this_phase->data_tail->next);
			this_phase->data_tail=this_phase->data_tail->next;
			this_phase->data_tail->next=NULL;
			this_phase->data_tail->len=t->p - t->buf;
			this_phase->data_tail->flags=F_FREE;
			this_phase->state.status=NEXTPHASE;
			this_phase->data_tail->data=t->buf;
			t->f=0;
			t->buf=malloc(32);
			t->p=t->buf;
		}
	}else if(d==0x1b){
		t->f=1;
		*(t->p)=d;
		t->p+=1;
		this_phase->state.status=CONTINUE;
	}else{
		this_phase->state.status=DEADEND;
	}
}
