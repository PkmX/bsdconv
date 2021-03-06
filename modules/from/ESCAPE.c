#define USE_HEX_MAP
#define USE_OCT_MAP

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "../../src/bsdconv.h"

struct my_s{
	int status;
	int *tbl;
	int b;
	char buf[4];
};

int cbcreate(struct bsdconv_instance *ins, struct bsdconv_hash_entry *arg){
	THIS_CODEC(ins)->priv=malloc(sizeof(struct my_s));
	return 0;
}

void cbinit(struct bsdconv_instance *ins){
	struct my_s *r=THIS_CODEC(ins)->priv;
	r->status=0;
}

void cbdestroy(struct bsdconv_instance *ins){
	void *p=THIS_CODEC(ins)->priv;
	free(p);
}

#define DEADEND() do{	\
	this_phase->state.status=DEADEND;	\
	t->status=0;	\
	return;	\
}while(0);

void cbconv(struct bsdconv_instance *ins){
	char *p;
	int i,j;
	struct bsdconv_phase *this_phase=THIS_PHASE(ins);
	struct my_s *t=this_phase->codec[this_phase->index].priv;
	char d;

	for(;this_phase->i<this_phase->curr->len;this_phase->i+=1){
		d=CP(this_phase->curr->data)[this_phase->i];
		switch(t->status){
			case 0:
				if(d=='%'){
					t->status=10;
					continue;
				}else if(d=='\\'){
					t->status=11;
					continue;
				}else{
					DEADEND();
				}
			case 10:
				if(d=='u'){
					t->status=40;
					continue;
				}else if(hex[(unsigned char)d]==-1){
					DEADEND();
				}else{
					t->status=21;
					t->buf[0]=hex[(unsigned char)d];
					continue;
				}
				break;
			case 11:
				if(d=='u'){
					t->status=40;
					continue;
				}else if(d=='x'){
					t->status=20;
					continue;
				}else if(oct[(unsigned char)d]==-1){
					DEADEND();
				}else{
					t->status=31;
					t->buf[0]=oct[(unsigned char)d];
					continue;
				}
				break;
			case 20:
				if(hex[(unsigned char)d]==-1){
					DEADEND();
				}else{
					t->status=21;
					t->buf[0]=hex[(unsigned char)d];
					continue;
				}
				break;
			case 21:
				if(hex[(unsigned char)d]==-1){
					DEADEND();
				}else{
					t->buf[0]*=16;
					t->buf[0]+=hex[(unsigned char)d];
					DATA_MALLOC(ins, this_phase->data_tail->next);
					this_phase->data_tail=this_phase->data_tail->next;
					this_phase->data_tail->next=NULL;
					this_phase->data_tail->flags=F_FREE;
					this_phase->data_tail->len=2;
					p=this_phase->data_tail->data=malloc(2);
					p[0]=0x03;
					p[1]=t->buf[0];
					this_phase->state.status=NEXTPHASE;
					t->status=0;
					return;
				}
				break;
			case 31:
				if(oct[(unsigned char)d]==-1){
					DEADEND();
				}else{
					t->status=32;
					t->buf[0]*=8;
					t->buf[0]+=oct[(unsigned char)d];
					continue;
				}
				break;
			case 32:
				if(oct[(unsigned char)d]==-1){
					DEADEND();
				}else{
					i=t->buf[0];
					i*=8;
					i+=oct[(unsigned char)d];
					if(i>377)
						DEADEND();
					t->buf[0]=i;
					DATA_MALLOC(ins, this_phase->data_tail->next);
					this_phase->data_tail=this_phase->data_tail->next;
					this_phase->data_tail->next=NULL;
					this_phase->data_tail->flags=F_FREE;
					this_phase->data_tail->len=2;
					p=this_phase->data_tail->data=malloc(2);
					p[0]=0x03;
					p[1]=t->buf[0];
					this_phase->state.status=NEXTPHASE;
					t->status=0;
					return;
				}
				break;
			case 40:
				if(hex[(unsigned char)d]==-1){
					DEADEND();
				}else{
					t->status=41;
					t->buf[0]=hex[(unsigned char)d];
					continue;
				}
				break;
			case 41:
				if(hex[(unsigned char)d]==-1){
					DEADEND();
				}else{
					t->status=42;
					t->buf[0]*=16;
					t->buf[0]+=hex[(unsigned char)d];
					continue;
				}
				break;
			case 42:
				if(hex[(unsigned char)d]==-1){
					DEADEND();
				}else{
					t->status=43;
					t->buf[1]=hex[(unsigned char)d];
					continue;
				}
				break;
			case 43:
				if(hex[(unsigned char)d]==-1){
					DEADEND();
				}else{
					i=0;
					t->buf[1]*=16;
					t->buf[1]+=hex[(unsigned char)d];
					while(t->buf[i]==0)++i;
					DATA_MALLOC(ins, this_phase->data_tail->next);
					this_phase->data_tail=this_phase->data_tail->next;
					this_phase->data_tail->next=NULL;
					this_phase->data_tail->flags=F_FREE;
					this_phase->data_tail->len=3-i;
					p=this_phase->data_tail->data=malloc(3-i);
					p[0]=0x01;
					for(j=1;i<2;++i,++j){
						p[j]=t->buf[i];
					}
					this_phase->state.status=NEXTPHASE;
					t->status=0;
					return;
				}
				break;
		}
	}
	this_phase->state.status=CONTINUE;
	return;
}
