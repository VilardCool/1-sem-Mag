#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <math.h>

struct cache_setting{
	int s; // set bits
	int S; // represents how many sets in a cache. S = 2**s
	int b; // data block bits
	int E; // represents how many lines in a set.
}cache;

struct Line {
	unsigned int valid;
	unsigned int tag;
	unsigned int lru;
};

typedef struct Line Line;
typedef long unsigned int mem_addr;

void print_Usage( char *argv[] ) {
   printf( "\nUsage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0] );
   printf( "Options:\n" );
   printf( "  -h         Print this help message.\n" );
   printf( "  -s <num>   Number of set index bits.\n" );
   printf( "  -E <num>   Number of lines per set.\n" );
   printf( "  -b <num>   Number of block offset bits.\n" );
   printf( "  -t <file>  Trace file.\n\n" );
   printf( "Examples:\n" );
   printf( " > %s -s 4 -E 1 -b 4 -t file\n", argv[0] );
   printf( " > %s -s 0 -E 4 -b 4 -t file\n\n", argv[0] );
   exit( 0 );
}

Line **makeCache(int S, int E);
unsigned int getInfo(mem_addr a, unsigned int *set);
void checkCache(Line **my_cache, unsigned int set, unsigned int tag, unsigned int *hits, unsigned int *misses, unsigned int *evictions);
void update_lru(Line *set, int line);

int main(int argc, char** argv) {

	char *set_verify;
	char *trace_file;
	char option;
    int set_check = 0;
    int line_check = 0;
    int block_check = 0;
    int trace_check = 0;

	while ((option = getopt(argc, argv, "s:E:b:t:h::")) != -1){
		switch(option){
			case 's':
				set_verify = optarg;
				cache.s = atoi(optarg);
				cache.S = pow(2, cache.s);
                set_check = 1;
				break;

			case 'E':
				cache.E = atoi(optarg);
				line_check = 1;
				break;

			case 'b':
				cache.b = atoi(optarg);
                block_check = 1;
				break;

			case 't':
				trace_file = optarg;
				trace_check = 1;
				break;

			case 'h':
				print_Usage(argv);

			default:
				print_Usage(argv);
		}
	}
    if ( set_check == 0 || line_check == 0 || block_check == 0 || trace_check == 0) {
        print_Usage(argv);
    }

	if (set_verify == NULL || cache.E == 0 || cache.b == 0 || trace_file == NULL) {
        	printf("%s: Missing required command line argument\n", argv[0]);
        	print_Usage(argv);
	}

	if(argv[1] == NULL){
		print_Usage(argv);
	}

	typedef long unsigned int mem_addr;
	mem_addr addr;
	unsigned int tag;
	unsigned int set;
	unsigned int hits = 0;
	unsigned int misses = 0;
	unsigned int evictions = 0;

	Line **my_cache = makeCache(cache.S, cache.E);
	FILE *trace = fopen(trace_file, "r");
	int ret = fscanf(trace, "%d", &addr);
	while (ret != -1) {
		tag = getInfo(addr, &set);
        checkCache(my_cache, set, tag, &hits, &misses, &evictions);
		ret = fscanf(trace, "%d", &addr);
	}
	fclose(trace);
	printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
	return 0;
}

Line **makeCache(int S, int E) {
	int i;
	int j;
	if(S==0) S==1;
	Line** cache1 = malloc(sizeof(Line*)*S);
	for(i = 0; i < S; i++) {
		cache1[i] = malloc(sizeof(Line)*E);
		for(j = 0; j < E; j++) {
			cache1[i][j].valid = 0;
			cache1[i][j].lru = j;
		}
	}
	return cache1;
}
int k=0;

void checkCache(Line **my_cache, unsigned int set, unsigned int tag,
unsigned int *hits,  unsigned int *misses, unsigned int *evictions) {
	int i;
	int j;
	/*for(i = 0; i < cache.S; i++){
		for(j = 0; j < cache.E; j++)
            printf("%d", my_cache[i][j].valid);
        printf("\n");
	}
	printf("\n");*/
	for(i = 0; i < cache.E; i++) {
		if(my_cache[set][i].valid != 0 && tag == my_cache[set][i].tag) {
			*hits = *hits + 1;
			update_lru(my_cache[set], i);
			return;
		}

	}
	for(i = 0; i < cache.E; i++) {
		if(my_cache[set][i].lru == (cache.E - 1)) {
			if(my_cache[set][i].valid != 0 && cache.E!=1) *evictions = *evictions + 1;
			my_cache[set][i].valid = 1;
			my_cache[set][i].tag = tag;
			update_lru(my_cache[set], i);
			*misses = *misses + 1;
			return;
		}
	}
}

unsigned int getInfo(mem_addr a, unsigned int *set) {
    if (cache.s == 0) *set=0;
	else *set = (a<<(32 - (cache.s + cache.b)))>>(32 - cache.s);
	return a>>(cache.s + cache.b);
}

void update_lru(Line *set, int line) {
	int i;
	for(i = 0; i < cache.E; i++){
		if(i != line){
			if(set[i].lru < set[line].lru){
				set[i].lru = set[i].lru + 1;
			}
		}
	}
	set[line].lru = 0;
}
