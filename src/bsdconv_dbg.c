#include <stdio.h>
#include <string.h>
#include "bsdconv.h"

extern int loadcodec(struct bsdconv_codec_t *cd, int type);
extern void unloadcodec(struct bsdconv_codec_t *cd);

void print_state(struct state_rt *state){
	const char *s=NULL;
	switch(state->status){
		case CONTINUE: s="CONTINUE"; break;
		case DEADEND: s="DEADEND"; break;
		case MATCH: s="MATCH"; break;
		case SUBMATCH: s="SUBMATCH"; break;
		case SUBROUTINE: s="SUBROUTINE"; break;
		case NEXTPHASE: s="NEXTPHASE"; break;
		case PASSTHRU: s="PASSTHRU"; break;
		case DUMMY: s="DUMMY"; break;
		case NOOP: s="NOOP"; break;
	}
	printf("State: %s\n", s);
	printf("Data: %p\n", state->data);
}

int main(int argc, char *argv[]){
	if(argc!=3)
		return 1;

	int type;
	struct bsdconv_codec_t cd;

	if(strcmp(argv[1], "FROM")==0){
		type=FROM;
	}else if(strcmp(argv[1], "INTER")==0){
		type=INTER;
	}else if(strcmp(argv[1], "TO")==0){
		type=TO;
	}else{
		return 1;
	}

	cd.desc=argv[2];
	loadcodec(&cd, type);


	struct state_rt state;
	struct data_rt data;
	offset_t offset;
	char op[16];
	unsigned char c;
	uintptr_t val;
	int i;
	memcpy(&state, cd.z, sizeof(struct state_rt));
	while(!feof(stdin)){
		printf("bsdconv_dbg> ");
		scanf("%s %p", op, (void **) &val);
		if(strcmp(op, "input")==0){
			c=val;
			if(c>=state.beg && c<state.end)
				memcpy(&offset, cd.z + (uintptr_t)state.base + (c - state.beg) * sizeof(offset_t), sizeof(offset_t));
			else
				offset=0;
			memcpy(&state, cd.z + offset, sizeof(struct state_st));
			print_state(&state);
		}else if(strcmp(op, "data")==0){
			while(val){
				memcpy(&data, (char *)(cd.z+val), sizeof(struct data_st));
				data.data=(cd.z+(uintptr_t)data.data);
				for(i=0;i<data.len;++i){
					printf("%02X", UCP(data.data)[i]);
				}
				printf("\n");
				val=(uintptr_t)data.next;
			}
		}else if(strcmp(op, "reset")==0){
			memcpy(&state, cd.z, sizeof(struct state_rt));
		}else{
			break;
		}
	}

	unloadcodec(&cd);

	return 0;
}