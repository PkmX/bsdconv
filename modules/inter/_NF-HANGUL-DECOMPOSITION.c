#include "../../src/bsdconv.h"

static void decomposeHangul(uint32_t ucs, struct bsdconv_instance *ins);

#define SBase	0xAC00
#define LBase	0x1100
#define VBase	0x1161
#define TBase	0x11A7
#define LCount	19
#define VCount	21
#define TCount	28
#define NCount	(VCount * TCount)
#define SCount	(LCount * NCount)

void cbconv(struct bsdconv_instance *ins){
	unsigned char *data;
	struct bsdconv_phase *this_phase=THIS_PHASE(ins);
	data=this_phase->curr->data;
	int i;
	uint32_t ucs=0;

	if(data[0]==0x1){
		for(i=1;i<this_phase->curr->len;++i){
			ucs<<=8;
			ucs|=data[i];
		}
		int SIndex  = ucs - SBase;
		if(SIndex >= 0 && SIndex < SCount){
			decomposeHangul(ucs, ins);
		}else{
			this_phase->data_tail->next=dup_data_rt(ins, this_phase->curr);
			this_phase->data_tail=this_phase->data_tail->next;
			this_phase->data_tail->next=NULL;
		}
	}

	this_phase->state.status=NEXTPHASE;
	return;
}

static void decomposeHangul(uint32_t ucs, struct bsdconv_instance *ins){
	struct bsdconv_phase *this_phase=THIS_PHASE(ins);
	int SIndex  = ucs - SBase;
	if(SIndex >= 0 && SIndex < SCount){
		int L = LBase + SIndex / NCount;
		int V = VBase + (SIndex % NCount) / TCount;
		int T = TBase + SIndex % TCount;

		decomposeHangul(L, ins);
		decomposeHangul(V, ins);
		if(T != TBase)
			decomposeHangul(T, ins);
	}else{
		int i;
		unsigned char *p;
		unsigned char stack[8];
		int stack_len=0;
		DATA_MALLOC(ins, this_phase->data_tail->next);
		this_phase->data_tail=this_phase->data_tail->next;
		while(ucs && stack_len<sizeof(stack)){
			stack[stack_len] = ucs & 0xff;
			ucs >>= 8;
			stack_len += 1;
		}
		this_phase->data_tail->len=stack_len+=1;
		this_phase->data_tail->data=malloc(this_phase->data_tail->len);
		p=this_phase->data_tail->data;
		*p=1;
		p+=1;
		stack_len-=1;
		for(i=0;i<stack_len;i+=1){
			*p=stack[stack_len-i-1];
			p+=1;
		}
		this_phase->data_tail->flags=F_FREE;
		this_phase->data_tail->next=NULL;
	}
}
