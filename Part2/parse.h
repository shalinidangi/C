#ifndef PARSE_H_   /* Include guard */
#define PARSE_H_

void parse(int argc, char **argv);

 	
/*	============= EXTERN VARIABLES ============= 
	main.c uses these to get the values we parse  
	============================================ */
	extern int n_threads;
	extern int n_iters;
	extern int set_yield;
	extern char sync_type;

/*	================= OPTIONS ================== 
	All the options we're parsing 
	============================================ */
	#define THREADS 	'a'
	#define ITERATIONS 	'b'
	#define YIELD		'c'
	#define SYNC		'd'

/*	================ CONSTANTS ================= 
	Constants to help main interpret results 
	of parsing
	============================================ */
	#define NOSYNC		'n'
	#define MUTEX_SYNC	'm'
	#define SPINLK_SYNC	's'
	

#endif // PARSE_H_