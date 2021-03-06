#include <stdlib.h>
#include "../../src/bsdconv.h"

void cbconv(struct bsdconv_instance *ins){
	struct bsdconv_phase *this_phase=THIS_PHASE(ins);
	char *data, *p;
	unsigned int len;
	data=this_phase->curr->data;

	this_phase->state.status=NEXTPHASE;
	data+=1;
	len=this_phase->curr->len-1;

	/* exclude ASCII */
	if(len==1 && (*data & bb10000000)==0){
		this_phase->state.status=DEADEND;
		return;
	}

	switch(len){
		case 1:
		case 2:
		case 3:
			break;
		default:
			this_phase->state.status=DEADEND;
			return;
	}

	switch(len){
		case 1:
			/* 1-byte cases have been excluded in "exclude ASCII" section */
			DATA_MALLOC(ins, this_phase->data_tail->next);
			this_phase->data_tail=this_phase->data_tail->next;
			this_phase->data_tail->next=NULL;
			this_phase->data_tail->flags=F_FREE;

			this_phase->data_tail->len=2;
			this_phase->data_tail->data=malloc(2);
			p=this_phase->data_tail->data;
			*p=bb11000000;
			*p |= (*data >> 6) & bb00000011;
			++p;
			*p=bb10000000;
			*p |= *data & bb00111111;
			break;
		case 2:
			DATA_MALLOC(ins, this_phase->data_tail->next);
			this_phase->data_tail=this_phase->data_tail->next;
			this_phase->data_tail->next=NULL;
			this_phase->data_tail->flags=F_FREE;
			switch(*data & bb11111000){
				case 0:
					this_phase->data_tail->len=2;
					this_phase->data_tail->data=malloc(2);
					p=this_phase->data_tail->data;
					*p=bb11000000;
					*p |= (*data << 2) & bb00011100;;
					++data;
					*p |= (*data >> 6) & bb00000011;
					++p;
					*p=bb10000000;
					*p |= *data & bb00111111;
					break;
				default:
					this_phase->data_tail->len=3;
					this_phase->data_tail->data=malloc(3);
					p=this_phase->data_tail->data;
					*p=bb11100000;
					*p |= (*data >> 4) & bb00001111;
					++p;
					*p=bb10000000;
					*p |= (*data << 2) & bb00111100;
					++data;
					*p |= (*data >> 6) & bb00000011;
					++p;
					*p=bb10000000;
					*p |= *data & bb00111111;
					break;
			}
			break;
		case 3:
			switch(*data & bb11100000){
				case 0:
					DATA_MALLOC(ins, this_phase->data_tail->next);
					this_phase->data_tail=this_phase->data_tail->next;
					this_phase->data_tail->next=NULL;
					this_phase->data_tail->flags=F_FREE;

					this_phase->data_tail->len=4;
					this_phase->data_tail->data=malloc(4);
					p=this_phase->data_tail->data;
					*p=bb11110000;
					*p |= (*data >> 2) & bb00000111;
					++p;
					*p=bb10000000;
					*p |= (*data << 4) & bb00110000;
					++data;
					*p |= (*data >> 4) & bb00001111;
					++p;
					*p=bb10000000;
					*p |= (*data << 2) & bb00111100;
					++data;
					*p |= (*data >> 6) & bb00000011;
					++p;
					*p=bb10000000;
					*p |= *data & bb00111111;
					break;
				default:
					/* RFC 3629 */
					this_phase->state.status=DEADEND;
					return;
					break;
			}
			break;
	}
}
