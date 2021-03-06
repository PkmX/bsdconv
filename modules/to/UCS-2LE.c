#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../src/bsdconv.h"

#define SWAP(a,b,i) ((i)=(a), (a)=(b), (b)=(i))

void cbconv(struct bsdconv_instance *ins){
	char *data;
	unsigned int len, i;
	struct bsdconv_phase *this_phase=THIS_PHASE(ins);
	data=this_phase->curr->data;
	if(this_phase->curr->len > 3){
		this_phase->state.status=DEADEND;
		return;
	}
	this_phase->state.status=NEXTPHASE;
	data+=1;
	len=this_phase->curr->len-1;

	DATA_MALLOC(ins, this_phase->data_tail->next);
	this_phase->data_tail=this_phase->data_tail->next;
	this_phase->data_tail->next=NULL;
	this_phase->data_tail->len=2;
	this_phase->data_tail->flags=F_FREE;
	this_phase->data_tail->data=malloc(2);
	for(i=0;i<2-len;++i){
		CP(this_phase->data_tail->data)[i]=0x0;
	}
	memcpy(CP(this_phase->data_tail->data)+i, data, len);
	data=this_phase->data_tail->data;

	SWAP(data[0],data[1],i);
	return;
}
