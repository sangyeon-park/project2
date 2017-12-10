#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<stdbool.h>


#define MAX_TMP 15
#define MAX_LINKED_NUMBER 5
int savet_ = 0, save_g= 0, save_d= 0, save_y= 0, save_r= 0, save_a= 0;//옵션을 받았다면 1값으로 바뀌어야 한다
int save_n = 0, save_s = 0, save_b = 0, save_m = 0;
int updatet_ = 0, update_g= 0, update_d= 0, update_y= 0, update_r= 0, update_a= 0;//옵션을 받았다면 1값으로 바뀌어야 한다
int update_n = 0, update_s = 0, update_b = 0, update_m = 0;
int update_num=0;
FILE *ofp;
int file_number=0;

struct sigaction ctrlc;

struct movie{
	int serial_number; // 영화 시리얼 넘버
	char *title; // 영화 이름 포인터
	char *genre; // 장르 이름 포인터
	struct director_in_movie *director_m; // 감독명 및, 해당 디렉터 노드 정보 저장
	int year;
	int movie_time;
	struct actor_in_movie *actor_m ; // 배우명 및,  다음 배우 구조체 노드, 해당 배우 구조체 노드
	struct movie *next; // 다음 movie의 구조체
} ;

struct director_in_movie { // 감독명 및, 해당 디렉터 노드 정보 저장
	char *name;
	struct director *director_node;
} ;

struct actor_in_movie { // 배우명 및,  다음 배우 구조체 노드, 해당 배우 구조체 노드
	char *name;
	struct actor_in_movie *next;
	struct actor *actor_node;
} ;

struct director {
	int serial_number;
	char *name; // 감독 이름 포인터
	char sex; //성별
	char *birth; // 생년월일 포인터
	struct movie_in_director *movie_d; // 대표작 포인터로 대표작명, 다음 대표작 자기참조 포인터, 해당 대표작 구조체 노드
	struct director *next; // 다음 감독 노드
} ;

struct movie_in_director { // 대표작 포인터로 대표작명, 다음 대표작 자기참조 포인터, 해당 대표작 구조체 노드
	char *name;  // 영화 이름
	struct movie_in_director *next; // 다음 영화 노드
	struct movie *movie_node; // 해당 영화 구조체 노드
} ;

struct actor {
	int serial_number; //시리얼 넘버
	char *name; // 이름 포인터
	char sex; // 성별 정보
	char *birth; // 생일 포인터
	struct movie_in_actor *movie_a; // 출연작 영화 구조체 퐁니터
	struct actor *next; // 다음 배우 구조체 노드
} ;

struct movie_in_actor {
	char *name; // 영화 이름 포인터
	struct movie_in_actor *next; //다음 영화 노드
	struct movie *movie_node;  // 해당 영화 구조체 노드
};

struct main_struct_ptr {
	struct movie *movie_ptr;
	struct actor *actor_ptr;
	struct director *director_ptr;
};



void get_data(struct main_struct_ptr *data_ptr);
void scan_word(FILE *optr, char *tmp_data);
int str_devider (char *str);
void get_movie(struct main_struct_ptr *data_ptr);
void add_movie (FILE *optr, struct movie *movie_ptr);
void scan_serial_number_m(FILE *optr, struct movie *movie_ptr);
void scan_title_m(FILE *optr, struct movie *movie_ptr);
void scan_genre_m(FILE *optr, struct movie *movie_ptr);
void scan_director_m(FILE *optr, struct movie *movie_ptr);
void scan_year_m(FILE *optr, struct movie *movie_ptr);
void scan_movie_time_m(FILE *optr, struct movie *movie_ptr);
void scan_actor_m(FILE *optr, struct movie *movie_ptr);
void get_director(struct main_struct_ptr *data_ptr);
void add_director (FILE *optr, struct director *director_ptr);
void scan_serial_number_d(FILE *optr, struct director *director_ptr);
void scan_name_d(FILE *optr, struct director *director_ptr);
void scan_sex_d(FILE *optr, struct director *director_ptr);
void scan_birth_d(FILE *optr, struct director *director_ptr);
void scan_title_d(FILE *optr, struct director *director_ptr);
void get_actor(struct main_struct_ptr *data_ptr);
void add_actor (FILE *optr, struct actor *actor_ptr);
void scan_serial_number_a(FILE *optr, struct actor *actor_ptr);
void scan_name_a(FILE *optr, struct actor *actor_ptr); // actor_name
void scan_title_a(FILE *optr, struct actor *actor_ptr);
void scan_sex_a(FILE *optr, struct actor *actor_ptr);
void scan_birth_a(FILE *optr, struct actor *actor_ptr);
void scan_title_a(FILE *optr, struct actor *actor_ptr);
void menu(char *input, struct main_struct_ptr *data_ptr );
void Print_m(struct main_struct_ptr *data_ptr);
void Print_d(struct main_struct_ptr *data_ptr);
void Print_a(struct main_struct_ptr *data_ptr);
void Sort_m_g(struct main_struct_ptr *data_ptr);
void Sort_m_d(struct main_struct_ptr *data_ptr);
void Sort_m_y(struct main_struct_ptr *data_ptr);
void Sort_m_r(struct main_struct_ptr *data_ptr);
void Sort_m_a(struct main_struct_ptr *data_ptr);
void Sort_m_t(struct main_struct_ptr *data_ptr);
void Sort_d_m(struct main_struct_ptr *data_ptr);
void Sort_d_n(struct main_struct_ptr *data_ptr);
void Sort_d_s(struct main_struct_ptr *data_ptr);
void Sort_d_b(struct main_struct_ptr *data_ptr);
void Sort_a_n(struct main_struct_ptr *data_ptr);
void Sort_a_s(struct main_struct_ptr *data_ptr);
void Sort_a_b(struct main_struct_ptr *data_ptr);
void Sort_a_m(struct main_struct_ptr *data_ptr);
int	 update_movie(FILE *optr, struct movie *tmp_movie_ptr);
struct movie* move2place_m (struct movie *movie_ptr, int update_sn);
int scan_serial_number_mud(FILE *optr, struct movie *movie_ptr);
struct movie* move2preplace_m (struct movie *movie_ptr, int update_sn);
struct director *move2preplace_d (struct director *director_ptr, int update_sn);
struct actor * move2preplace_a (struct actor *actor_ptr, int update_sn);

int mov(struct main_struct_ptr *, char*);
int dir(struct main_struct_ptr *, char*);
int act(struct main_struct_ptr *, char*);
bool pattern_match(const char *, const char *);
void QorM_m(struct main_struct_ptr *, char*);
void QorM_d(struct main_struct_ptr *, char*);
void QorM_a(struct main_struct_ptr *, char*);
void ordersearch(struct main_struct_ptr*);

void sigint_handler(int sig)
{
	char answer;
	printf("\n2번 신호가 발생했습니다.\n");
	printf("종료하시겠습니까? (y/n) : ");
	scanf("%c", &answer);
	if(answer == 'y' || answer == 'Y')
		exit(1);
	else
		printf("프로그램을 종료하지 않습니다.\n");
	fseek(stdin, 0, SEEK_END);
	getchar();

}

void scan_word(FILE *optr, char *tmp_data){
	for (int i = 0 ; i < 100 ; i++ ) {
		fscanf(optr, "%c", (tmp_data + i));
		if ( *(tmp_data + i) == ':'){
			*(tmp_data + i) = '\0';
			return;
		}
		if ( *(tmp_data + i) == '\n'){
			*(tmp_data + i) = '\0';
			return;
		}
		if ( *(tmp_data+i) == EOF){
			*(tmp_data + i) = '\0';
			return;
		}
	}
}

int str_devider (char *str) {
	int count = 0;
	for (int i=0; i<5*15; i++){
		if (*(str+i) == ',')
			break;
		if(*(str+i) == '\n')
			break;
		if(*(str+i) == '\0' ){
			return 0;
		}
		count ++;
	}
	return count;
}

void get_data(struct main_struct_ptr *data_ptr){
	get_movie(data_ptr);
	printf(" \n \n \n");
	get_director(data_ptr);
	printf(" \n \n \n");
	get_actor(data_ptr);
	printf(" \n \n \n");
}

int check_skip (char *tmp_name) {
	if (strcmp(tmp_name, "=") == 0){
		printf("%s\n", tmp_name);
		free(tmp_name);
		return 0;
	}
	else if (*tmp_name == '='){
		return 0;
	}
	else {
		return 1;
	}
}

void free_movie(struct movie *delete_movie_ptr){
	free(delete_movie_ptr->title);
	free(delete_movie_ptr->genre);
	free(delete_movie_ptr->director_m->name);
	free(delete_movie_ptr->actor_m);
}//

void delete_movie(FILE *optr, struct movie *tmp_movie_ptr){
	int delete_sn;
	char *trash = malloc (100);
	delete_sn = scan_serial_number_mud (optr, tmp_movie_ptr);
	struct movie *delete_movie_ptr;
	printf("%d\n", delete_sn);
	delete_movie_ptr = move2place_m(tmp_movie_ptr,delete_sn);
	free_movie(delete_movie_ptr);
	for (int i=0; i<6 ; i++){
		scan_word(optr, trash);
	}

	struct movie *pre_delm_ptr;
	if (delete_sn == 1){
		printf("you can't delete first data (serial number 1)\n");
		return;
	}
	else {
		pre_delm_ptr = move2preplace_m(tmp_movie_ptr,(delete_sn));
		struct movie *aft_delm_ptr;
		aft_delm_ptr = delete_movie_ptr -> next;
		(pre_delm_ptr -> next) = aft_delm_ptr;
	}
	free(delete_movie_ptr);
	printf("********************\n  ");
}

void get_movie(struct main_struct_ptr *data_ptr){
	FILE *optr;
	optr = fopen ("test1.txt", "r");
	(data_ptr -> movie_ptr) = malloc(sizeof(struct movie));
	struct movie *tmp_movie_ptr;
	tmp_movie_ptr = (data_ptr->movie_ptr);
	struct movie *tmp_movie_memory;
	tmp_movie_memory = (data_ptr->movie_ptr);

	while (1) //(끝까지 읽기 전까지, 맨앞의 명령어만 읽어들임
	{
		char *mode;
		mode = malloc(1*7); //모드 최고 글자수가 6개 + 1이므로
		scan_word(optr, mode);
		if (strcmp("add", mode) == 0) {
			printf("1: %s\n", mode);
			add_movie(optr, (tmp_movie_ptr));
			(tmp_movie_ptr -> next) = malloc (sizeof(struct movie));
			tmp_movie_ptr = (tmp_movie_ptr -> next);
			(tmp_movie_ptr -> next) = NULL;
		}

		else if (strcmp("update", mode) == 0  ){
			printf("1: %s\n", mode);
			// tmp_movie_ptr = (data_ptr->movie_ptr);
			update_movie(optr, (tmp_movie_memory));
		}

		else if (strcmp("delete", mode) == 0  ){
			printf("1: %s\n", mode);
			// tmp_movie_ptr = (data_ptr->movie_ptr);
			delete_movie(optr, (tmp_movie_memory));
		}


		else{
			printf("shit\n");
			break;
		}

		free(mode);
	}

	tmp_movie_ptr = data_ptr->movie_ptr;

	while (1){
		if(tmp_movie_ptr->next->next == NULL){
			tmp_movie_ptr->next = NULL;
			break;
		}
		else
			tmp_movie_ptr = tmp_movie_ptr->next;
	}
	fclose(optr);
}

void add_movie (FILE *optr, struct movie *movie_ptr) {
	scan_serial_number_m(optr, movie_ptr);
	scan_title_m(optr, movie_ptr);
	scan_genre_m(optr, movie_ptr);
	scan_director_m(optr,movie_ptr);
	scan_year_m(optr,movie_ptr);
	scan_movie_time_m(optr, movie_ptr);
	scan_actor_m(optr, movie_ptr);
	printf("********************\n  ");
}

void scan_serial_number_m(FILE *optr, struct movie *movie_ptr) {
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저
	(movie_ptr -> serial_number) = atoi(tmp_name);
	printf("2:%d\n",(movie_ptr -> serial_number));
	free(tmp_name);
}

void scan_title_m(FILE *optr, struct  movie *movie_ptr){
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저장
	(movie_ptr->title) = malloc ((strlen(tmp_name)+1)); // 메모리에 데이터 저장 전, 임시 공간에 저장된 이름의 크기만큼 동적메모리 할당해줌
	strcpy((movie_ptr->title),tmp_name);
	printf("3:%s\n", movie_ptr->title);
	free(tmp_name);
}

void scan_genre_m(FILE *optr,struct movie * movie_ptr){
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name);
	(movie_ptr->genre) = malloc ((strlen(tmp_name)+1));
	strcpy((movie_ptr->genre),tmp_name);
	printf("4:%s\n", movie_ptr->genre);
	free(tmp_name);
}

void scan_director_m(FILE *optr, struct movie *movie_ptr){
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name);
	(movie_ptr->director_m) = malloc (sizeof(struct director_in_movie)); // (이름 크기 + 구조체 내의 struct director 포인터의 크기) 동적할당
	((movie_ptr->director_m)->name) = malloc ((strlen(tmp_name)+1));
	strcpy(((movie_ptr->director_m)->name), tmp_name);
	printf("5:%s\n", movie_ptr->director_m->name);
	free(tmp_name);
}

void scan_year_m(FILE *optr, struct movie *movie_ptr){
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name);
	(movie_ptr -> year) = atoi(tmp_name);
	printf("6:%d\n",movie_ptr -> year);
	free(tmp_name);
}

void scan_movie_time_m(FILE *optr, struct movie *movie_ptr){
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name);
	(movie_ptr -> movie_time) = atoi(tmp_name);
	printf("7:%d\n",movie_ptr-> movie_time);
	free(tmp_name);
}

void scan_actor_m(FILE *optr, struct movie *movie_ptr){

	(movie_ptr->actor_m) = malloc (sizeof(struct actor_in_movie)); // (이름 크기 + 구조체 내의 struct director 포인터의 크기) 동적할당
	movie_ptr->actor_m->next = 0;
	struct actor_in_movie *tmp_actor_ptr;
	tmp_actor_ptr = movie_ptr->actor_m;

	char *tmp_str, *tmp_memory;
	int flag = 1;
	tmp_str = malloc(MAX_LINKED_NUMBER*MAX_TMP);
	tmp_memory = tmp_str;
	scan_word(optr, tmp_str);
	printf("%s\n", tmp_str);
	while ((flag = str_devider(tmp_memory)) != 0) {
		printf("\nfuck here : %d\n", flag);
		char *tmp_actor;
		tmp_actor = malloc (flag + 2);
		for (int i = 0; i< flag ; i++){
			*(tmp_actor + i) = *(tmp_memory + i);
		}
		*(tmp_actor+flag) = '\0';
		tmp_memory = tmp_memory + flag + 1 ;

		(tmp_actor_ptr->name) = malloc (flag + 1);
		strcpy((tmp_actor_ptr->name), tmp_actor);
		(tmp_actor_ptr->next) = malloc (sizeof(struct actor_in_movie));
		printf("8:%s\n", tmp_actor_ptr->name);
		tmp_actor_ptr = tmp_actor_ptr -> next;
		tmp_actor_ptr->next = NULL;
		free(tmp_actor);
	}

	int cnt = 0;
	for (; cnt< 16 ; cnt++){
		if (*(tmp_memory + cnt) == '\0'){
			break;
		}
	}
	char *tmp_actor;
	printf("\nfuck here : %d\n",  cnt );
	tmp_actor = malloc (cnt + 2);
	for (int i = 0; i < cnt-1; i++){
		*(tmp_actor + i) = *(tmp_memory + i);
	}
	*(tmp_actor + cnt - 1) = '\0';
	(tmp_actor_ptr->name) = malloc (cnt + 1);
	strcpy((tmp_actor_ptr->name), tmp_actor);
	printf("8:%s\n", tmp_actor_ptr->name);
	tmp_actor_ptr->next = NULL;
	free(tmp_actor);
	free(tmp_str);
}

void scan_actor_mu(FILE *optr, struct movie *update_movie_ptr){
	struct actor_in_movie *tmp_actor_ptr;
	tmp_actor_ptr = update_movie_ptr->actor_m;
	char *tmp_str;
	tmp_str = malloc(MAX_LINKED_NUMBER*MAX_TMP);
	scan_word(optr, tmp_str);
	int flag = 1;

	while ((flag = str_devider(tmp_str)) != 0) {
		printf("\nfuck here : %d\n", flag);
		char *tmp_actor;
		tmp_actor = malloc (flag + 2);
		for (int i = 0; i< flag ; i++){
			*(tmp_actor + i) = *(tmp_str + i);
		}
		*(tmp_actor+flag) = '\0';
		tmp_str = tmp_str + flag + 1;

		if((check_skip(tmp_actor)) == 0){
			tmp_actor_ptr = tmp_actor_ptr -> next;
			continue;
		}

		else {
			if((tmp_actor_ptr->name) != NULL)
				free((tmp_actor_ptr->name));
			(tmp_actor_ptr->name) = malloc (flag + 1);
			strcpy((tmp_actor_ptr->name), tmp_actor);
			if ((tmp_actor_ptr -> next) == NULL){
				(tmp_actor_ptr->next) = malloc (sizeof(struct actor_in_movie));
				printf("8:%s\n", tmp_actor_ptr->name);
				tmp_actor_ptr = tmp_actor_ptr -> next;
				tmp_actor_ptr->name = NULL;
				tmp_actor_ptr->next = NULL;
				free(tmp_actor);
			}
			else {
				printf("8:%s\n", tmp_actor_ptr->name);
				tmp_actor_ptr = tmp_actor_ptr -> next;
				free(tmp_actor);
			}
		}
	}
	int cnt = 0;
	for (; cnt< 16 ; cnt++){
		if (*(tmp_str + cnt) == '\0'){
			break;
		}
	}
	char *tmp_actor;
	printf("\nfuck here : %d\n",  cnt );
	tmp_actor = malloc (cnt + 2);
	for (int i = 0; i < cnt+2 ; i++){
		*(tmp_actor + i) = *(tmp_str + i);
	}

	if((check_skip(tmp_actor)) == 0){
		return;
	}

	else {
		if((tmp_actor_ptr->name) != NULL)
			free((tmp_actor_ptr->name));

		(tmp_actor_ptr->name) = malloc (cnt + 1);
		strcpy((tmp_actor_ptr->name), tmp_actor);
		printf("8:%s\n", tmp_actor_ptr->name);
		tmp_actor_ptr->next = NULL;
		free(tmp_actor);
	}
}

int scan_serial_number_mud(FILE *optr, struct movie *movie_ptr) { // update, delete를 위한 scan함수
	char *tmp_name;
	int return_val;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저
	return_val = atoi(tmp_name);
	printf("2:%d\n",return_val);
	free(tmp_name);
	return return_val;
}

struct movie* move2place_m (struct movie *movie_ptr, int update_sn){
	struct movie *tmp_movie_ptr;
	tmp_movie_ptr = movie_ptr;
	while((tmp_movie_ptr) != NULL) {
		if (update_sn == (tmp_movie_ptr -> serial_number)){
			return tmp_movie_ptr;
		}
		else
			tmp_movie_ptr = tmp_movie_ptr -> next;
	}
	printf("There are no member of <%d serial number>\n", update_sn );
	return NULL;
}

struct movie* move2preplace_m (struct movie *movie_ptr, int update_sn) {
	struct movie *tmp_movie_ptr;
	tmp_movie_ptr = movie_ptr;
	while((tmp_movie_ptr->next) != NULL) {
		if (update_sn == (tmp_movie_ptr -> next -> serial_number)){
			return tmp_movie_ptr;
		}
		else
			tmp_movie_ptr = tmp_movie_ptr -> next;
	}
	printf("There are no member of <%d serial number>\n", update_sn );
	return NULL;
}

void scan_title_mu(FILE *optr, struct  movie *update_movie_ptr){
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저장

	if ((check_skip(tmp_name)) == 0){
		return;
	}

	else {
		free((update_movie_ptr)->title);
		(update_movie_ptr)->title = malloc(strlen(tmp_name) + 2);

		strcpy((update_movie_ptr->title),tmp_name);
		printf("3:%s\n", update_movie_ptr->title);
		free(tmp_name);
	}
}

void scan_genre_mu(FILE *optr,struct movie * update_movie_ptr){

	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name);

	if ((check_skip(tmp_name)) == 0){
		return;
	}
	else {
		free((update_movie_ptr)->genre);
		(update_movie_ptr)->genre = malloc(strlen(tmp_name) + 2);
		strcpy((update_movie_ptr->genre),tmp_name);
		printf("4:%s\n", update_movie_ptr->genre);
		free(tmp_name);
	}
}

void scan_director_mu(FILE *optr, struct movie *update_movie_ptr){
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name);

	if ((check_skip(tmp_name)) == 0){
		return;
	}
	else {
		free((update_movie_ptr)->director_m->name);
		(update_movie_ptr)->director_m->name = malloc(strlen(tmp_name) + 2);
		strcpy(((update_movie_ptr->director_m)->name), tmp_name);
		printf("5:%s\n", update_movie_ptr->director_m->name);
		free(tmp_name);
	}
}

void scan_year_mu(FILE *optr, struct movie *update_movie_ptr){
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name);

	if ((check_skip(tmp_name)) == 0){
		return;
	}
	else {
		(update_movie_ptr -> year) = atoi(tmp_name);
		printf("6:%d\n",update_movie_ptr -> year);
		free(tmp_name);
	}
}

void scan_movie_time_mu(FILE *optr, struct movie *update_movie_ptr){
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name);

	if ((check_skip(tmp_name)) == 0){
		return;
	}
	else {
		(update_movie_ptr -> movie_time) = atoi(tmp_name);
		printf("7:%d\n",update_movie_ptr-> movie_time);
		free(tmp_name);
	}
}

int update_movie(FILE * optr, struct movie *movie_ptr){
	int update_sn; // update serial number
	update_sn =scan_serial_number_mud(optr, movie_ptr);
	struct movie *update_movie_ptr;
	update_movie_ptr = move2place_m(movie_ptr,update_sn);
	if (update_movie_ptr==NULL)
		return 0;
	scan_title_mu(optr,update_movie_ptr);
	scan_genre_mu(optr,update_movie_ptr);
	scan_director_mu(optr, update_movie_ptr);
	scan_year_mu(optr, update_movie_ptr);
	scan_movie_time_mu(optr, update_movie_ptr);
	scan_actor_mu(optr,update_movie_ptr);
	printf("********************\n  ");
	return 1;
}

int scan_serial_number_dud(FILE *optr, struct director *director_ptr) { // update, delete를 위한 scan함수
	char *tmp_name;
	int return_val;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저
	return_val = atoi(tmp_name);
	printf("2:%d\n",return_val);
	free(tmp_name);
	return return_val;
}

struct director * move2place_d (struct director *director_ptr, int update_sn){
	struct director *tmp_director_ptr;
	tmp_director_ptr = director_ptr;
	while((tmp_director_ptr) != NULL) {
		if (update_sn == (tmp_director_ptr -> serial_number)){
			return tmp_director_ptr;
		}
		else
			tmp_director_ptr = tmp_director_ptr -> next;
	}
	printf("There are no member of <%d serial number>\n", update_sn );
	return NULL;
}

struct director * move2preplace_d (struct director *director_ptr, int update_sn) {
	struct director *tmp_director_ptr;
	tmp_director_ptr = director_ptr;
	while((tmp_director_ptr->next) != NULL) {
		if (update_sn == (tmp_director_ptr -> next -> serial_number)){
			return tmp_director_ptr;
		}
		else
			tmp_director_ptr = tmp_director_ptr -> next;
	}
	printf("There are no member of <%d serial number>\n", update_sn );
	return NULL;
}

void scan_name_du(FILE *optr, struct  director *update_director_ptr){
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저장

	if ((check_skip(tmp_name)) == 0){
		return;
	}

	else {
		free((update_director_ptr)->name);
		(update_director_ptr)->name = malloc(strlen(tmp_name) + 2);

		strcpy((update_director_ptr->name),tmp_name);
		printf("3:%s\n", update_director_ptr->name);
		free(tmp_name);
	}
}

void scan_birth_du(FILE *optr,struct director * update_director_ptr){

	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name);

	if ((check_skip(tmp_name)) == 0){
		return;
	}
	else {
		free((update_director_ptr)->birth);
		(update_director_ptr)->birth = malloc(strlen(tmp_name) + 2);
		strcpy((update_director_ptr->birth),tmp_name);
		printf("4:%s\n", update_director_ptr->birth);
		free(tmp_name);
	}
}

void scan_title_du(FILE *optr, struct director *update_director_ptr){
	struct movie_in_director *tmp_movie_ptr;
	tmp_movie_ptr = update_director_ptr->movie_d;
	char *tmp_str;
	tmp_str = malloc(MAX_LINKED_NUMBER*MAX_TMP);
	scan_word(optr, tmp_str);
	int flag = 1;

	while ((flag = str_devider(tmp_str)) != 0) {
		printf("\nfuck here : %d\n", flag);
		char *tmp_movie;
		tmp_movie = malloc (flag + 2);
		for (int i = 0; i< flag ; i++){
			*(tmp_movie + i) = *(tmp_str + i);
		}
		*(tmp_movie+flag) = '\0';
		tmp_str = tmp_str + flag + 1;

		if((check_skip(tmp_movie)) == 0){
			tmp_movie_ptr = tmp_movie_ptr -> next;
			continue;
		}

		else {
			if((tmp_movie_ptr->name) != NULL)
				free((tmp_movie_ptr->name));
			(tmp_movie_ptr->name) = malloc (flag + 1);
			strcpy((tmp_movie_ptr->name), tmp_movie);
			if ((tmp_movie_ptr -> next) == NULL){
				(tmp_movie_ptr->next) = malloc (sizeof(struct movie_in_director));
				printf("8:%s\n", tmp_movie_ptr->name);
				tmp_movie_ptr = tmp_movie_ptr -> next;
				tmp_movie_ptr->name = NULL;
				tmp_movie_ptr->next = NULL;
				free(tmp_movie);
			}
			else {
				printf("8:%s\n", tmp_movie_ptr->name);
				tmp_movie_ptr = tmp_movie_ptr -> next;
				free(tmp_movie);
			}
		}
	}
	int cnt = 0;
	for (; cnt< 16 ; cnt++){
		if (*(tmp_str + cnt) == '\0'){
			break;
		}
	}
	char *tmp_movie;
	printf("\nfuck here : %d\n",  cnt );
	tmp_movie = malloc (cnt + 2);
	for (int i = 0; i < cnt+2 ; i++){
		*(tmp_movie + i) = *(tmp_str + i);
	}

	if((check_skip(tmp_movie)) == 0){
		return;
	}

	else {
		if((tmp_movie_ptr->name) != NULL)
			free((tmp_movie_ptr->name));

		(tmp_movie_ptr->name) = malloc (cnt + 1);
		strcpy((tmp_movie_ptr->name), tmp_movie);
		printf("8:%s\n", tmp_movie_ptr->name);
		tmp_movie_ptr->next = NULL;
		free(tmp_movie);
	}
}

void scan_sex_du (FILE *optr, struct director *update_director_ptr){
	char *tmp_name;
	tmp_name = malloc(1*3);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저

	if ((check_skip(tmp_name)) == 0){
		return;
	}
	else {
		(update_director_ptr -> sex) = *tmp_name;
		printf("4:%c\n",(update_director_ptr -> sex));
		free(tmp_name);
	}
}

int update_director(FILE * optr, struct director *director_ptr){
	int update_sn; // update serial number
	update_sn =scan_serial_number_dud(optr, director_ptr);
	struct director *update_director_ptr;
	update_director_ptr = move2place_d(director_ptr,update_sn);
	if (update_director_ptr==NULL)
		return 0;
	scan_name_du(optr,update_director_ptr);
	scan_sex_du(optr,update_director_ptr);
	scan_birth_du(optr,update_director_ptr);
	scan_title_du(optr,update_director_ptr);
	return 1;
}

void 	free_director(struct director *delete_director_ptr) {
	free(delete_director_ptr->name);
	free(delete_director_ptr->birth);
	free(delete_director_ptr->movie_d);
}

void delete_director(FILE *optr, struct director *tmp_director_ptr){
	int delete_sn;
	char *trash = malloc (100);
	delete_sn = scan_serial_number_dud (optr, tmp_director_ptr);
	struct director *delete_director_ptr;
	printf("%d\n", delete_sn);
	delete_director_ptr = move2place_d(tmp_director_ptr,delete_sn);
	free_director(delete_director_ptr);
	for (int i=0; i<4 ; i++){
		scan_word(optr,trash	);
	}

	struct director *pre_delm_ptr;
	if (delete_sn == 1){
		printf("you can't delete first data (serial number 1)\n");
		return;
	}
	else {
		pre_delm_ptr = move2preplace_d(tmp_director_ptr,(delete_sn));
		struct director *aft_delm_ptr;
		aft_delm_ptr = delete_director_ptr -> next;
		(pre_delm_ptr -> next) = aft_delm_ptr;
	}
	free(delete_director_ptr);
	printf("********************\n  ");
}

void get_director(struct  main_struct_ptr *data_ptr){
	FILE *optr;
	optr = fopen ("test2.txt", "r");
	(data_ptr -> director_ptr) = malloc(sizeof(struct director));
	struct director *tmp_director_ptr;
	tmp_director_ptr = (data_ptr->director_ptr);
	struct director *tmp_director_memory;
	tmp_director_memory = (data_ptr->director_ptr);

	while (1) //(끝까지 읽기 전까지, 맨앞의 명령어만 읽어들임
	{
		char *mode;
		mode = malloc(1*8); //모드 최고 글자수가 6개 + 1이므로
		scan_word(optr, mode);

		if ( *mode == 0)
			break;

		if (strcmp("add", mode) == 0) {
			printf("1: %s\n", mode);
			free(mode);
			add_director(optr, (tmp_director_ptr));
			(tmp_director_ptr -> next) = malloc (sizeof(struct director));
			tmp_director_ptr = (tmp_director_ptr -> next);
			(tmp_director_ptr -> next) = NULL;
		}

		else if (strcmp("update", mode) == 0  ){
			printf("1: %s\n", mode);
			update_director(optr, (tmp_director_memory));
		}

		else if (strcmp("delete", mode) == 0){
			printf("1: %s\n", mode);
			delete_director(optr, (tmp_director_memory));
		}

		else
			continue;
	}
	tmp_director_ptr = data_ptr->director_ptr;

	while (1){
		if(tmp_director_ptr->next->next == NULL){
			tmp_director_ptr->next = NULL;
			break;
		}
		else
			tmp_director_ptr = tmp_director_ptr->next;
	}
	fclose(optr);
}

void add_director (FILE *optr, struct director *director_ptr) {
	scan_serial_number_d(optr, director_ptr);
	scan_name_d(optr, director_ptr); // title
	scan_sex_d(optr, director_ptr); // new one
	scan_birth_d(optr, director_ptr); // genre
	scan_title_d(optr, director_ptr); //acotr
	printf("********************\n");
}

void scan_serial_number_d(FILE *optr, struct director *director_ptr) {
	char *tmp_name;
	tmp_name = malloc(1*15);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저
	(director_ptr -> serial_number) = atoi(tmp_name);
	printf("2:%d\n",(director_ptr -> serial_number));
	free(tmp_name);
}

void scan_name_d(FILE *optr, struct director *director_ptr){
	char *tmp_name;
	tmp_name = malloc(1*15);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저장
	(director_ptr->name) = malloc ((strlen(tmp_name)+1)); // 메모리에 데이터 저장 전, 임시 공간에 저장된 이름의 크기만큼 동적메모리 할당해줌
	strcpy((director_ptr->name),tmp_name);
	printf("3:%s\n", director_ptr->name);
	free(tmp_name);
}

void scan_sex_d (FILE *optr, struct director *director_ptr){
	char *tmp_name;
	tmp_name = malloc(1*3);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저
	(director_ptr -> sex) = *tmp_name;
	printf("4:%c\n",(director_ptr -> sex));
	free(tmp_name);
}

void scan_birth_d(FILE *optr, struct director *director_ptr){
	char *tmp_name;
	tmp_name = malloc(1*15);
	scan_word(optr, tmp_name);
	(director_ptr->birth) = malloc ((strlen(tmp_name)+1));
	strcpy((director_ptr->birth),tmp_name);
	printf("5:%s\n", director_ptr->birth);
	free(tmp_name);
}

void scan_title_d(FILE *optr, struct director *director_ptr){
	(director_ptr->movie_d) = malloc (sizeof(struct movie_in_director)); // (이름 크기 + 구조체 내의 struct director 포인터의 크기) 동적할당
	director_ptr->movie_d->next = 0;
	struct movie_in_director *tmp_movie_ptr;
	tmp_movie_ptr = director_ptr->movie_d;

	char *tmp_str;
	int flag = 1;
	tmp_str = malloc(5*15);
	scan_word(optr, tmp_str);

	while ((flag = str_devider(tmp_str)) != 0) {

		if (*tmp_str == 0)
			break;

		char *tmp_title;
		tmp_title = malloc (flag + 1);

		for (int i = 0; i< flag ; i++){
			*(tmp_title + i) = *(tmp_str + i);
		}

		*(tmp_title+flag) = '\0';
		tmp_str = tmp_str + flag + 1;
		printf("\nfuck here : %d\n", flag);
		(tmp_movie_ptr->name) = malloc (flag + 1);
		strcpy((tmp_movie_ptr->name), tmp_title);
		(tmp_movie_ptr->next) = malloc (sizeof(struct movie_in_director));
		printf("6:%s\n", tmp_movie_ptr->name);
		tmp_movie_ptr = tmp_movie_ptr -> next;
		tmp_movie_ptr->next = NULL;
		free(tmp_title);
	}
	int cnt = 0;
	for (; cnt< 14 ; cnt++){
		if (*(tmp_str + cnt) == '\0'){
			break;
		}
	}

	char *tmp_title;
	printf("%d\n", cnt );
	tmp_title = malloc (cnt + 2);
	for (int i = 0; i < cnt-1 ; i++){
		*(tmp_title + i) = *(tmp_str + i);
	}
	*(tmp_title + cnt - 1) = '\0';

	printf("\nfuck here : %d\n", cnt);

	(tmp_movie_ptr->name) = malloc (cnt + 2);
	strcpy((tmp_movie_ptr->name), tmp_title);
	printf("6:%s\n", tmp_movie_ptr->name);
	tmp_movie_ptr->next = NULL;
	free(tmp_title);
}

int scan_serial_number_aud(FILE *optr, struct actor *actor_ptr) { // update, delete를 위한 scan함수
	char *tmp_name;
	int return_val;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저
	return_val = atoi(tmp_name);
	printf("2:%d\n",return_val);
	free(tmp_name);
	return return_val;
}

struct actor * move2place_a (struct actor *actor_ptr, int update_sn){
	struct actor *tmp_actor_ptr;
	tmp_actor_ptr = actor_ptr;
	while((tmp_actor_ptr) != NULL) {
		if (update_sn == (tmp_actor_ptr -> serial_number)){
			return tmp_actor_ptr;
		}
		else
			tmp_actor_ptr = tmp_actor_ptr -> next;
	}
	printf("There are no member of <%d serial number>\n", update_sn );
	return NULL;
}

struct actor * move2preplace_a (struct actor *actor_ptr, int update_sn) {
	struct actor *tmp_actor_ptr;
	tmp_actor_ptr = actor_ptr;
	while((tmp_actor_ptr->next) != NULL) {
		if (update_sn == (tmp_actor_ptr -> next -> serial_number)){
			return tmp_actor_ptr;
		}
		else
			tmp_actor_ptr = tmp_actor_ptr -> next;
	}
	printf("There are no member of <%d serial number>\n", update_sn );
	return NULL;
}

void scan_name_au(FILE *optr, struct  actor *update_actor_ptr){
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저장

	if ((check_skip(tmp_name)) == 0){
		return;
	}

	else {
		free((update_actor_ptr)->name);
		(update_actor_ptr)->name = malloc(strlen(tmp_name) + 2);

		strcpy((update_actor_ptr->name),tmp_name);
		printf("3:%s\n", update_actor_ptr->name);
		free(tmp_name);
	}
}

void scan_sex_au (FILE *optr, struct actor *update_actor_ptr){
	char *tmp_name;
	tmp_name = malloc(1*3);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저

	if ((check_skip(tmp_name)) == 0){
		return;
	}
	else {
		(update_actor_ptr -> sex) = *tmp_name;
		printf("4:%c\n",(update_actor_ptr -> sex));
		free(tmp_name);
	}
}

void scan_birth_au(FILE *optr,struct actor * update_actor_ptr){

	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name);

	if ((check_skip(tmp_name)) == 0){
		return;
	}
	else {
		free((update_actor_ptr)->birth);
		(update_actor_ptr)->birth = malloc(strlen(tmp_name) + 2);
		strcpy((update_actor_ptr->birth),tmp_name);
		printf("4:%s\n", update_actor_ptr->birth);
		free(tmp_name);
	}
}

void scan_title_au(FILE *optr, struct actor *update_actor_ptr){
	struct movie_in_actor *tmp_actor_ptr;
	tmp_actor_ptr = update_actor_ptr->movie_a;
	char *tmp_str;
	tmp_str = malloc(MAX_LINKED_NUMBER*MAX_TMP);
	scan_word(optr, tmp_str);
	int flag = 1;

	while ((flag = str_devider(tmp_str)) != 0) {
		printf("\nfuck here : %d\n", flag);
		char *tmp_actor;
		tmp_actor = malloc (flag + 2);
		for (int i = 0; i< flag ; i++){
			*(tmp_actor + i) = *(tmp_str + i);
		}
		*(tmp_actor+flag) = '\0';
		tmp_str = tmp_str + flag + 1;

		if((check_skip(tmp_actor)) == 0){
			tmp_actor_ptr = tmp_actor_ptr -> next;
			continue;
		}

		else {
			if((tmp_actor_ptr->name) != NULL)
				free((tmp_actor_ptr->name));
			(tmp_actor_ptr->name) = malloc (flag + 1);
			strcpy((tmp_actor_ptr->name), tmp_actor);
			if ((tmp_actor_ptr -> next) == NULL){
				(tmp_actor_ptr->next) = malloc (sizeof(struct movie_in_actor));
				printf("8:%s\n", tmp_actor_ptr->name);
				tmp_actor_ptr = tmp_actor_ptr -> next;
				tmp_actor_ptr->name = NULL;
				tmp_actor_ptr->next = NULL;
				free(tmp_actor);
			}
			else {
				printf("8:%s\n", tmp_actor_ptr->name);
				tmp_actor_ptr = tmp_actor_ptr -> next;
				free(tmp_actor);
			}
		}
	}
	int cnt = 0;
	for (; cnt< 16 ; cnt++){
		if (*(tmp_str + cnt) == '\0'){
			break;
		}
	}
	char *tmp_actor;
	printf("\nfuck here : %d\n",  cnt );
	tmp_actor = malloc (cnt + 2);
	for (int i = 0; i < cnt+2 ; i++){
		*(tmp_actor + i) = *(tmp_str + i);
	}

	if((check_skip(tmp_actor)) == 0){
		return;
	}

	else {
		if((tmp_actor_ptr->name) != NULL)
			free((tmp_actor_ptr->name));

		(tmp_actor_ptr->name) = malloc (cnt + 1);
		strcpy((tmp_actor_ptr->name), tmp_actor);
		printf("8:%s\n", tmp_actor_ptr->name);
		tmp_actor_ptr->next = NULL;
		free(tmp_actor);
	}
}

int update_actor(FILE * optr, struct actor *actor_ptr){
	int update_sn; // update serial number
	update_sn =scan_serial_number_aud(optr, actor_ptr);
	struct actor *update_actor_ptr;
	update_actor_ptr = move2place_a(actor_ptr,update_sn);
	if (update_actor_ptr==NULL)
		return 0;
	scan_name_au(optr,update_actor_ptr);
	scan_sex_au(optr,update_actor_ptr);
	scan_birth_au(optr, update_actor_ptr);
	scan_title_au(optr, update_actor_ptr);
	return 1;
}

void free_actor(struct actor *delete_actor_ptr){
	free(delete_actor_ptr->name);
	free(delete_actor_ptr->birth);
	free(delete_actor_ptr->movie_a);
}

void delete_actor(FILE *optr, struct actor *tmp_actor_ptr){
	int delete_sn;
	char *trash = malloc (100);
	delete_sn = scan_serial_number_aud (optr, tmp_actor_ptr);
	struct actor *delete_actor_ptr;
	printf("%d\n", delete_sn);
	delete_actor_ptr = move2place_a(tmp_actor_ptr,delete_sn);
	free_actor(delete_actor_ptr);
	for (int i=0; i<4 ; i++){
		scan_word(optr, trash);
	}

	struct actor *pre_delm_ptr;
	if (delete_sn == 1){
		printf("you can't delete first data (serial number 1)\n");
		return;
	}
	else {
		pre_delm_ptr = move2preplace_a(tmp_actor_ptr,(delete_sn));
		struct actor *aft_delm_ptr;
		aft_delm_ptr = delete_actor_ptr -> next;
		(pre_delm_ptr -> next) = aft_delm_ptr;
	}
	free(delete_actor_ptr);
	printf("********************\n  ");
}

void get_actor(struct  main_struct_ptr *data_ptr){
	FILE *optr;
	optr = fopen ("test3.txt", "r");
	(data_ptr -> actor_ptr) = malloc(sizeof(struct actor));
	struct actor *tmp_actor_ptr;
	tmp_actor_ptr = (data_ptr->actor_ptr);
	struct actor *tmp_actor_memory;
	tmp_actor_memory = (data_ptr->actor_ptr);
	while (1) //(끝까지 읽기 전까지, 맨앞의 명령어만 읽어들임
	{
		char *mode;
		mode = malloc(1*8); //모드 최고 글자수가 6개 + 1이므로
		scan_word(optr, mode);
		printf("%s\n", mode);

		if (*mode == 0)
			break;

		if (strcmp("add", mode) == 0) {
			printf("1: %s\n", mode);
			free(mode);
			add_actor(optr, (tmp_actor_ptr));
			(tmp_actor_ptr -> next) = malloc (sizeof(struct actor));
			tmp_actor_ptr = (tmp_actor_ptr -> next);
			tmp_actor_ptr -> next = NULL;
		}

		else if (strcmp("update", mode) == 0){
			printf("1: %s\n", mode);
			free(mode);
			tmp_actor_memory = (data_ptr->actor_ptr);
			update_actor(optr, (tmp_actor_memory));
		}

		else if (strcmp("delete", mode) == 0){
			printf("1: %s\n", mode);
			free(mode);
			tmp_actor_memory = (data_ptr->actor_ptr);
			delete_actor(optr, (tmp_actor_memory));
		}


		else
			continue;


		// else
		//   printf("잘못된 데이터 형식입니다\n");
	}

	tmp_actor_ptr = data_ptr->actor_ptr;

	while (1){
		if(tmp_actor_ptr->next->next == NULL){
			tmp_actor_ptr->next = NULL;
			break;
		}
		else
			tmp_actor_ptr = tmp_actor_ptr->next;
	}
	fclose(optr);
}

void add_actor (FILE *optr, struct actor *actor_ptr) {
	scan_serial_number_a(optr, actor_ptr); // serial_number
	scan_name_a(optr, actor_ptr); // actor_name
	scan_sex_a(optr, actor_ptr); // new one
	scan_birth_a(optr, actor_ptr); // birth
	scan_title_a(optr, actor_ptr); //title
	printf("********************\n");
}

void scan_serial_number_a(FILE *optr, struct actor *actor_ptr) {
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저
	(actor_ptr -> serial_number) = atoi(tmp_name);
	printf("2:%d\n",(actor_ptr -> serial_number));
	free(tmp_name);
}

void scan_name_a(FILE *optr, struct  actor *actor_ptr){
	char *tmp_name;
	tmp_name = malloc(1*MAX_TMP);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저장
	(actor_ptr->name) = malloc ((strlen(tmp_name)+1)); // 메모리에 데이터 저장 전, 임시 공간에 저장된 이름의 크기만큼 동적메모리 할당해줌
	strcpy((actor_ptr->name),tmp_name);
	printf("3:%s\n", actor_ptr->name);
	free(tmp_name);
}

void scan_sex_a (FILE *optr, struct actor *actor_ptr){
	char *tmp_name;
	tmp_name = malloc(1*3);
	scan_word(optr, tmp_name); //파일에서 타이틀 읽어서 임시메모리에 저
	(actor_ptr -> sex) = *tmp_name;
	printf("4:%c\n",(actor_ptr -> sex));
	free(tmp_name);
}

void scan_birth_a(FILE *optr,struct actor * actor_ptr){
	char *tmp_birth;
	tmp_birth = malloc(1*MAX_TMP);
	scan_word(optr, tmp_birth);
	(actor_ptr->birth) = malloc ((strlen(tmp_birth)+1));
	strcpy((actor_ptr->birth),tmp_birth);
	printf("5:%s\n", actor_ptr->birth);
	free(tmp_birth);
}

void scan_title_a(FILE *optr, struct actor *actor_ptr){
	(actor_ptr->movie_a) = malloc (sizeof(struct movie_in_actor)); // (이름 크기 + 구조체 내의 struct director 포인터의 크기) 동적할당
	actor_ptr->movie_a->next = 0;
	struct movie_in_actor *tmp_movie_ptr;
	tmp_movie_ptr = actor_ptr->movie_a;

	char *tmp_str;
	int flag = 1;
	tmp_str = malloc(MAX_LINKED_NUMBER*MAX_TMP);
	scan_word(optr, tmp_str);
	while ((flag = str_devider(tmp_str)) != 0) {

		if (*tmp_str == 0)
			break;

		char *tmp_movie;
		tmp_movie = malloc (flag + 1);
		for (int i = 0; i< flag ; i++){
			*(tmp_movie + i) = *(tmp_str + i);
		}
		*(tmp_movie+flag) = '\0';
		tmp_str = tmp_str + flag + 1;

		(tmp_movie_ptr->name) = malloc (flag + 1);
		strcpy((tmp_movie_ptr->name), tmp_movie);
		(tmp_movie_ptr->next) = malloc (sizeof(struct movie_in_actor));
		printf("\nfuck here : %d\n", flag);
		printf("6:%s\n", tmp_movie_ptr->name);
		tmp_movie_ptr = tmp_movie_ptr -> next;
		tmp_movie_ptr -> next = NULL;
		free(tmp_movie);
	}

	int cnt = 0;
	for (; cnt< 16 ; cnt++){
		if (*(tmp_str + cnt) == '\0'){
			break;
		}
	}

	char *tmp_movie;
	tmp_movie = malloc (cnt + 2);
	for (int i = 0; i < cnt-1 ; i++){
		*(tmp_movie + i) = *(tmp_str + i);
	}
	*(tmp_movie + cnt - 1) = '\0';

	printf("\nfuck here : %d\n", cnt);

	(tmp_movie_ptr->name) = malloc (cnt + 2);
	strcpy((tmp_movie_ptr->name), tmp_movie);
	printf("6:%s\n", tmp_movie_ptr->name);
	tmp_movie_ptr->next = NULL;
	free(tmp_movie);
}

void Print_m(struct main_struct_ptr *data_ptr){
	struct actor_in_movie *temp; //정렬된 배우 저장을 위한 변수
	struct movie *current;
	current = data_ptr->movie_ptr;

	// 데이터가 없는 경우
	if(data_ptr->movie_ptr == NULL){
		printf(" 입력된 데이터가 없습니다 \n\n");
		return;
	}
	if(file_number==0){ // -f 가 없어 파일로 저장하지않고 화면에 출력
		while(current != NULL){
			temp=current->actor_m;
			printf("%s:%s:%s:%d:%d:",  current->title,  current->genre,  current->director_m->name,  current->year,  current->movie_time);
			while(temp -> next != NULL){
				printf("%s",temp->name);
				printf(",");
				temp=temp->next;
			}
			printf("%s\n",temp->name);
			current = current->next;
		}
	}
	else if(file_number==1){ // -f가 있어 파일에 저장.
		while(current != NULL){
			temp=current->actor_m;
			fprintf(ofp,"%s:%s:%s:%d:%d:",  current->title,  current->genre,  current->director_m->name,  current->year,  current->movie_time);
			while(temp != NULL){
				fprintf(ofp,"%s",temp->name);
				if(temp->next != NULL)
				{
					fprintf(ofp,", ");
				}
				temp=temp->next;
			}
			fprintf(ofp,"\n");
			current = current->next;
		}
		file_number=0;
	}
	printf("\n");
}

void Print_d(struct main_struct_ptr *data_ptr)
{
	struct movie_in_director *temp; //정렬된 영화 저장을 위한 변수
	struct director *current; // 감독정보를 저장할 변수
	current = data_ptr->director_ptr;

	// 데이터가 없는 경우
	if(data_ptr->director_ptr == NULL){
		printf(" 입력된 데이터가 없습니다 \n\n");
		return;
	}
	if(file_number==0){ // -f 가 없어 파일로 저장하지않고 화면에 출력
		while(current != NULL){
			temp=current->movie_d;
			printf("%s:%c:%s:",  current->name,  current->sex,  current->birth);
			while(temp != NULL){
				printf("%s",temp->name);
				if(temp->next != NULL)
				{
					printf(",");
				}
				temp=temp->next;
			}
			printf("\n");
			current = current->next;
		}
	}
	else if(file_number==1){ // -f가 있어 파일에 저장.
		while(current != NULL){
			temp=current->movie_d;
			fprintf(ofp,"%s:%c:%s:",  current->name,  current->sex,  current->birth);
			while(temp != NULL){
				fprintf(ofp,"%s",temp->name);
				if(temp->next != NULL)
				{
					fprintf(ofp,",");
				}
				temp=temp->next;
			}
			fprintf(ofp,"\n");
			current = current->next;
		}
		file_number=0;
	}
	printf("\n");
}


void Print_a(struct main_struct_ptr *data_ptr)
{
	struct movie_in_actor *temp; //정렬된 영화 저장을 위한 변수
	struct actor *current; // 배우정보를 저장하기 위한 변수
	current = data_ptr->actor_ptr;

	// 데이터가 없는 경우
	if(data_ptr->actor_ptr == NULL){
		printf(" 입력된 데이터가 없습니다 \n\n");
		return;
	}
	if(file_number==0){ // -f 가 없어 파일로 저장하지않고 화면에 출력
		while(current != NULL){
			temp=current->movie_a;
			printf("%s:%c:%s:",  current->name,  current->sex,  current->birth);
			while(temp != NULL){
				printf("%s",temp->name);
				if(temp->next != NULL)
				{
					printf(",");
				}
				temp=temp->next;
			}
			printf("\n");
			current = current->next;
		}
	}
	else if(file_number==1){ // -f가 있어 파일에 저장.
		while(current != NULL){
			temp=current->movie_a;
			fprintf(ofp,"%s:%c:%s:",  current->name,  current->sex,  current->birth);
			while(temp != NULL){
				fprintf(ofp,"%s",temp->name);
				if(temp->next != NULL)
				{
					fprintf(ofp,",");
				}
				temp=temp->next;
			}
			fprintf(ofp,"\n");
			current = current->next;
		}
		file_number=0;
	}
	printf("\n");
}

void Sort_m_g(struct main_struct_ptr *data_ptr){ //영화이름대로 정렬
	struct movie *current, **ptr;
	int i, j,cnt;

	if(data_ptr->movie_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->movie_ptr, cnt = 1;

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}

	ptr = (struct movie**)malloc(sizeof(struct movie*) * cnt);
	for(i = 0, current = data_ptr->movie_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current;
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if(strcmp((*(ptr+i))->genre , (*(ptr+j))->genre) > 0){
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}

	for(data_ptr->movie_ptr = *(ptr+0), current = data_ptr->movie_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i);
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}

void Sort_m_d(struct main_struct_ptr *data_ptr){ // 감독이름별로 정렬 나머지는 장르와 동일
	struct movie *current, **ptr;
	int i, j,cnt;

	if(data_ptr->movie_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->movie_ptr;
	cnt = 1;

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}
	ptr = (struct movie**)malloc(sizeof(struct movie*) * cnt);
	for(i = 0, current = data_ptr->movie_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current;
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if(strcmp((*(ptr+i))->director_m->name , (*(ptr+j))->director_m->name) > 0){
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}
	for(data_ptr->movie_ptr = *(ptr+0), current = data_ptr->movie_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i);
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}

void Sort_m_y(struct main_struct_ptr *data_ptr){ //년도별로 정렬
	struct movie *current, **ptr;
	int i, j,cnt;

	if(data_ptr->movie_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->movie_ptr, cnt = 1;

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}
	ptr = (struct movie**)malloc(sizeof(struct movie*) * cnt);
	for(i = 0, current = data_ptr->movie_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current;
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if((*(ptr+i))->year > (*(ptr+j))->year) {
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}
	for(data_ptr->movie_ptr = *(ptr+0), current = data_ptr->movie_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i);
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}

void Sort_m_r(struct main_struct_ptr *data_ptr){ //영화시간별로 정렬
	struct movie *current, **ptr;
	int i, j,cnt;

	if(data_ptr->movie_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->movie_ptr, cnt = 1;

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}
	ptr = (struct movie**)malloc(sizeof(struct movie*) * cnt);
	for(i = 0, current = data_ptr->movie_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current;
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if((*(ptr+i))->movie_time > (*(ptr+j))->movie_time){
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}
	for(data_ptr->movie_ptr = *(ptr+0), current = data_ptr->movie_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i);
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}

void Sort_m_a(struct main_struct_ptr *data_ptr){ //배우 이름별로 정렬
	struct movie *current, **ptr;
	int i, j,cnt;

	if(data_ptr->movie_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->movie_ptr, cnt = 1;

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}
	ptr = (struct movie**)malloc(sizeof(struct movie*) * cnt);
	for(i = 0, current = data_ptr->movie_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current;
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if(strcmp((*(ptr+i))->actor_m->name , (*(ptr+j))->actor_m->name) > 0){
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}
	for(data_ptr->movie_ptr = *(ptr+0), current = data_ptr->movie_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i);
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}

void Sort_m_t(struct main_struct_ptr *data_ptr){ //영화이름대로 정렬
	struct movie *current, **ptr;
	int i, j,cnt;

	if(data_ptr->movie_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->movie_ptr, cnt = 1;

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}

	ptr = (struct movie**)malloc(sizeof(struct movie*) * cnt);
	for(i = 0, current = data_ptr->movie_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current;
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if(strcmp((*(ptr+i))->title , (*(ptr+j))->title) > 0){
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}

	for(data_ptr->movie_ptr = *(ptr+0), current = data_ptr->movie_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i);
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}

void Sort_d_n(struct main_struct_ptr *data_ptr){ //감독을 이름별로 정렬
	struct director *current, **ptr; //정렬할때 이용하는 변수들
	int i, j,cnt;

	if(data_ptr->director_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->director_ptr;
	cnt = 1; // 레코드가 몇개인지 알려줌.

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}

	ptr = (struct director**)malloc(sizeof(struct director*) * cnt);
	for(i = 0, current = data_ptr->director_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current; //이중포인터를 이용하여 파일저장
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if(strcmp((*(ptr+i))->name , (*(ptr+j))->name) > 0){ //앞에 있는 이름이 더 크다면 정렬해줌. 나머지 Sort_함수도 이와같음.
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}

	for(data_ptr->director_ptr = *(ptr+0), current = data_ptr->director_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i); //위에서 이중포인터에 저장해둔것을 다시 원래파일에 저장.
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}

void Sort_d_s(struct main_struct_ptr *data_ptr){ //성별로 정렬
	struct director *current, **ptr; //정렬할때 이용하는 변수들
	int i, j,cnt;

	if(data_ptr->director_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->director_ptr;
	cnt = 1; // 레코드가 몇개인지 알려줌.

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}

	ptr = (struct director**)malloc(sizeof(struct director*) * cnt);
	for(i = 0, current = data_ptr->director_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current; //이중포인터를 이용하여 파일저장
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if(((*(ptr+i))->sex) > ((*(ptr+j))->sex)){ //앞에 있는 이름이 더 크다면 정렬해줌. 나머지 Sort_함수도 이와같음.
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}

	for(data_ptr->director_ptr = *(ptr+0), current = data_ptr->director_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i); //위에서 이중포인터에 저장해둔것을 다시 원래파일에 저장.
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}

void Sort_d_b(struct main_struct_ptr *data_ptr){ //생일별로 정렬
	struct director *current, **ptr; //정렬할때 이용하는 변수들
	int i, j,cnt;

	if(data_ptr->director_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->director_ptr;
	cnt = 1; // 레코드가 몇개인지 알려줌.

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}

	ptr = (struct director**)malloc(sizeof(struct director*) * cnt);
	for(i = 0, current = data_ptr->director_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current; //이중포인터를 이용하여 파일저장
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if(strcmp((*(ptr+i))->birth , (*(ptr+j))->birth) > 0){ //앞에 있는 이름이 더 크다면 정렬해줌. 나머지 Sort_함수도 이와같음.
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}

	for(data_ptr->director_ptr = *(ptr+0), current = data_ptr->director_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i); //위에서 이중포인터에 저장해둔것을 다시 원래파일에 저장.
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}

void Sort_d_m(struct main_struct_ptr *data_ptr){ //영화 이름대로 정렬
	struct director *current, **ptr; //정렬할때 이용하는 변수들
	int i, j,cnt;

	if(data_ptr->director_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->director_ptr;
	cnt = 1; // 레코드가 몇개인지 알려줌.

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}

	ptr = (struct director**)malloc(sizeof(struct director*) * cnt);
	for(i = 0, current = data_ptr->director_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current; //이중포인터를 이용하여 파일저장
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if(strcmp((*(ptr+i))->movie_d->name , (*(ptr+j))->movie_d->name) > 0){ //앞에 있는 이름이 더 크다면 정렬해줌. 나머지 Sort_함수도 이와같음.
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}

	for(data_ptr->director_ptr = *(ptr+0), current = data_ptr->director_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i); //위에서 이중포인터에 저장해둔것을 다시 원래파일에 저장.
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}

void Sort_a_n(struct main_struct_ptr *data_ptr){ //배우를 이름별로 정렬
	struct actor *current, **ptr; //정렬할때 이용하는 변수들
	int i, j,cnt;

	if(data_ptr->actor_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->actor_ptr;
	cnt = 1; // 레코드가 몇개인지 알려줌.

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}

	ptr = (struct actor**)malloc(sizeof(struct actor*) * cnt);
	for(i = 0, current = data_ptr->actor_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current; //이중포인터를 이용하여 파일저장
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if(strcmp((*(ptr+i))->name , (*(ptr+j))->name) > 0){ //앞에 있는 이름이 더 크다면 정렬해줌. 나머지 Sort_함수도 이와같음.
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}

	for(data_ptr->actor_ptr = *(ptr+0), current = data_ptr->actor_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i); //위에서 이중포인터에 저장해둔것을 다시 원래파일에 저장.
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}

void Sort_a_s(struct main_struct_ptr *data_ptr){ //성별로 정렬
	struct actor *current, **ptr; //정렬할때 이용하는 변수들
	int i, j,cnt;

	if(data_ptr->actor_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->actor_ptr;
	cnt = 1; // 레코드가 몇개인지 알려줌.

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}

	ptr = (struct actor**)malloc(sizeof(struct actor*) * cnt);
	for(i = 0, current = data_ptr->actor_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current; //이중포인터를 이용하여 파일저장
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if(((*(ptr+i))->sex) > ((*(ptr+j))->sex)){ //앞에 있는 이름이 더 크다면 정렬해줌. 나머지 Sort_함수도 이와같음.
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}

	for(data_ptr->actor_ptr = *(ptr+0), current = data_ptr->actor_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i); //위에서 이중포인터에 저장해둔것을 다시 원래파일에 저장.
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}

void Sort_a_b(struct main_struct_ptr *data_ptr){ // 생일별로 정렬
	struct actor *current, **ptr; //정렬할때 이용하는 변수들
	int i, j,cnt;

	if(data_ptr->actor_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->actor_ptr;
	cnt = 1; // 레코드가 몇개인지 알려줌.

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}

	ptr = (struct actor**)malloc(sizeof(struct actor*) * cnt);
	for(i = 0, current = data_ptr->actor_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current; //이중포인터를 이용하여 파일저장
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if(strcmp((*(ptr+i))->birth , (*(ptr+j))->birth) > 0){ //앞에 있는 이름이 더 크다면 정렬해줌. 나머지 Sort_함수도 이와같음.
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}

	for(data_ptr->actor_ptr = *(ptr+0), current = data_ptr->actor_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i); //위에서 이중포인터에 저장해둔것을 다시 원래파일에 저장.
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}

void Sort_a_m(struct main_struct_ptr *data_ptr){ // 영화이름대로 배우정렬
	struct actor *current, **ptr; //정렬할때 이용하는 변수들
	int i, j,cnt;

	if(data_ptr->actor_ptr == NULL){
		printf("데이타가 없습니다.\n");
		return;
	}

	current = data_ptr->actor_ptr;
	cnt = 1; // 레코드가 몇개인지 알려줌.

	while(current->next != NULL){
		cnt++;
		current = current->next;
	}

	ptr = (struct actor**)malloc(sizeof(struct actor*) * cnt);
	for(i = 0, current = data_ptr->actor_ptr; i < cnt; i++, current = current->next)
		*(ptr+i) = current; //이중포인터를 이용하여 파일저장
	for(i = 0; i < cnt; i++){
		for(j = i+1; j < cnt; j++){
			if(strcmp((*(ptr+i))->movie_a->name , (*(ptr+j))->movie_a->name) > 0){ //앞에 있는 이름이 더 크다면 정렬해줌. 나머지 Sort_함수도 이와같음.
				current = *(ptr+i);
				*(ptr+i) = *(ptr+j);
				*(ptr+j) = current;
			}
		}
	}

	for(data_ptr->actor_ptr = *(ptr+0), current = data_ptr->actor_ptr, i = 1; i < cnt; i++, current = current->next){
		current->next = *(ptr+i); //위에서 이중포인터에 저장해둔것을 다시 원래파일에 저장.
	}
	current->next = NULL;
	printf("정렬이 완료되었습니다.\n");
	free(ptr);
}
void Print_m_num(struct main_struct_ptr *data_ptr,char *token) // print명령을 영화에 대해서 출력해주는 함수
{
	int i=1;
	struct actor_in_movie *temp;
	struct movie *current;
	current = data_ptr->movie_ptr;
	// 데이터가 없는 경우
	if(data_ptr->movie_ptr == NULL){
		printf(" 입력된 데이터가 없습니다 \n\n");
		return;
	}
	while(current != NULL){
		temp=current->actor_m;
		// temp->actor_node=NULL; 초기값이 널이 아니어서 해준거
		if (current->serial_number==atoi(token)){ // 영화에 저장된 시리얼번호와 토큰에 저장된문자열을 숫자로 바꾸어 비교함
			printf("%d, %s, %s\n",  current->serial_number,  current->title,  current->genre);
			if(current->director_m->director_node!=NULL) // 영화에 대한 감독이 감독레코드에 있을경우
			{
				printf("D : %s(%s)\n",current->director_m->director_node->name,current->director_m->director_node->birth);
				while(temp != NULL){
					if(temp->actor_node!=NULL)// 영화에 대한 배우가 배우레코드에 있을경우
					{
						printf("A%d : %s(%s)\n",i, temp->actor_node->name, temp->actor_node->birth);
					}
					else{ // 영화에 대한 배우가 배우레코드에 없을경우
						printf("A%d : %s(-)\n",i, temp->name);
					}
					i++;
					temp=temp->next;
				}
				i=1;
			}
			else //영화에 대한 감독이 감독레코드에 없을경우
			{
				printf("D : %s(-)\n",current->director_m->name);
				while(temp != NULL){
					if(temp->actor_node!=NULL)
					{
						printf("A%d : %s(%s)\n",i, temp->actor_node->name, temp->actor_node->birth);
					}
					else{
						printf("A%d : %s(-)\n",i, temp->name);
					}
					i++;
					temp=temp->next;
				}
				i=1;
			}
			break;
		}
		else{
			printf("\n");
			current = current->next;
		}
	}
}

void Print_d_num(struct main_struct_ptr *data_ptr,char *token) //print명령을 감독에 대해서 출력해주는 함수
{
	struct movie_in_director *temp;
	struct director *current;
	current = data_ptr->director_ptr;

	// 데이터가 없는 경우
	if(data_ptr->movie_ptr == NULL){
		printf(" 입력된 데이터가 없습니다 \n\n");
		return;
	}
	while(current != NULL){
		temp=current->movie_d;
		//temp->movie_node=NULL;  초기값이 널이 아니어서 해준거
		if(current->serial_number==atoi(token)){ //위와동일
			printf("%d, %s, %c, %s\n",  current->serial_number, current->name,  current->sex,  current->birth);
			while(temp != NULL){
				if(temp->movie_node!=NULL) // 감독이 영화레코드에 있을경우
				{
					printf("%s, %d, %d\n",temp->movie_node->title,temp->movie_node->year,temp->movie_node->movie_time);
				}
				else{// 감독이 영화레코드에 없을경우
					printf("%s, - , -\n",temp->name);
				}
				temp=temp->next;
			}
		}
		printf("\n");
		current = current->next;
	}
}

void Print_a_num(struct main_struct_ptr *data_ptr, char *token) //print명령을 배우에 대해서 출력해주는 함수
{
	struct movie_in_actor *temp;
	struct actor *current;
	current = data_ptr->actor_ptr;

	// 데이터가 없는 경우
	if(data_ptr->actor_ptr == NULL){
		printf(" 입력된 데이터가 없습니다 \n\n");
		return;
	}
	while(current != NULL){
		temp=current->movie_a;
		//temp->movie_node=NULL; 초기값이 널이 아니어서 해준거

		if(current->serial_number==atoi(token)){
			printf("%d, %s, %c, %s\n",  current->serial_number, current->name,  current->sex,  current->birth);
			while(temp != NULL){
				if(temp->movie_node!=NULL) // 배우가 영화레코드안에 있을경우
				{
					printf("%s, %d, %d\n",temp->movie_node->title,temp->movie_node->year,temp->movie_node->movie_time);
				}
				else{ // 배우가 영화레코드안에 없을경우

					printf("%s,-,-\n",temp->name);
				}
				temp=temp->next;
			}
		}
		printf("\n");
		current = current->next;
	}
}

void movie_save_m(char *name,struct main_struct_ptr * data_ptr,char save_case){
	struct movie *current;
	struct director * current2;
	struct actor * current3;//각 자료형을 받기위한 변수
	struct actor_in_movie *temp = NULL;
	struct movie_in_director *temp2 = NULL;
	struct movie_in_actor *temp3 = NULL;
	current = data_ptr->movie_ptr;
	current2 = data_ptr->director_ptr;
	current3 = data_ptr->actor_ptr;
	char * save_title = "";
	char * save_genre = "";
	char * save_director = "";
	char * save_name = "";
	char save_sex = '\0';
	char * save_birth = "";//아무것도 없는 상태로 초기화.
	int save_year = '\0';
	int save_time = '\0';//우선은 널문자로 초기화.
	FILE *pof=NULL;
	pof = fopen(name,"w+");//일단은 마이리스트로 저장.

	switch(save_case){
		case 'm' : while(current != NULL){
				   if(savet_)
					   save_title = current->title;
				   if(save_g)
					   save_genre = current->genre;
				   if(save_d)
					   save_director = current->director_m->name;
				   if(save_y)
					   save_year = current->year;
				   if(save_r)
					   save_time = current->movie_time;//옳은 경우들 즉 옵션을 받은 경우에는 정보를 가져온다.
				   if(save_a)
					   temp=current -> actor_m;
				   fprintf(pof,"%s:%s:%s:%d:%d:",save_title,save_genre, save_director,save_year,save_time);
				   while(temp != NULL){
					   fprintf(pof,"%s, ",temp->name);
					   temp=temp->next;//파일에 입력을 한 후 노드를 변경
				   }
				   current = current->next;
				   fprintf(pof,"\n");
			   }
			   fclose(pof);
			   break;
		case 'd' : while(current2 != NULL){
				   if(save_n)//이름
					   save_name = current2->name;
				   if(save_s)//성별
					   save_sex = current2->sex;
				   if(save_b)//생년월일
					   save_birth = current2->birth;
				   if(save_m)//영화
					   temp2 = current2->movie_d;
				   fprintf(pof,"%s:%c:%s:",save_name,save_sex,save_birth);//생일까지만출력
				   while(temp2 != NULL){
					   fprintf(pof,"%s",temp2->name);
					   if(temp2->next != NULL)
						   fprintf(pof,",");
					   temp2 = temp2->next;
				   }
				   current2 = current2->next;
				   fprintf(pof,"\n");
			   }
			   fclose(pof);
			   break;

		case 'a' : while(current3 != NULL){
				   if(save_n)
					   save_name = current3->name;
				   if(save_s)
					   save_sex = current3->sex;
				   if(save_b)
					   save_birth = current3->birth;
				   if(save_m)
					   temp3 = current3->movie_a;
				   fprintf(pof,"%s:%c:%s:",save_name, save_sex,save_birth);
				   while(temp3 != NULL){
					   fprintf(pof,"%s",temp3->name);
					   if(temp3->next != NULL)
						   fprintf(pof,",");
					   temp3 = temp3->next;
				   }
				   current3 = current3-> next;
				   fprintf(pof,"\n");
			   }
			   fclose(pof);
			   break;

		default : break;

	}
}

void Print_m_list(struct main_struct_ptr *data_ptr){ // movie_list파일을 만들기 위한 함수
	FILE *mptr;
	mptr=fopen("movie_list","w"); // movie_list파일을 쓰기로 열음
	struct actor_in_movie *temp; //정렬된 배우 저장을 위한 변수
	struct movie *current;
	current = data_ptr->movie_ptr;

	// 데이터가 없는 경우
	if(data_ptr->movie_ptr == NULL){
		printf(" 입력된 데이터가 없습니다 \n\n");
		return;
	}
		while(current != NULL){ // 파일에 저장
			temp=current->actor_m;
			fprintf(mptr,"%d:%s:%s:%s:%d:%d:", current->serial_number,  current->title,  current->genre,  current->director_m->name,  current->year,  current->movie_time);
			while(temp != NULL){
				fprintf(mptr,"%s",temp->name);
				if(temp->next != NULL)
				{
					fprintf(mptr,",");
				}
				temp=temp->next;
			}
			fprintf(mptr,"\n");
			current = current->next;
		}
	printf("\n");
	fclose(mptr);
}

void Print_d_list(struct main_struct_ptr *data_ptr) //director_list 파일을 만들기 위한 함수
{
	FILE *dptr;
	dptr=fopen("director_list", "w"); //director_list 파일을 쓰기로 열음
	struct movie_in_director *temp; //정렬된 영화 저장을 위한 변수
	struct director *current; // 감독정보를 저장할 변수
	current = data_ptr->director_ptr;

	// 데이터가 없는 경우
	if(data_ptr->director_ptr == NULL){
		printf(" 입력된 데이터가 없습니다 \n\n");
		return;
	}

		while(current != NULL){ //파일에 저장
			temp=current->movie_d;
			fprintf(dptr,"%d:%s:%c:%s:", current->serial_number, current->name,  current->sex,  current->birth);
			while(temp != NULL){
				fprintf(dptr,"%s",temp->name);
				if(temp->next != NULL)
				{
					fprintf(dptr,",");
				}
				temp=temp->next;
			}
			fprintf(dptr,"\n");
			current = current->next;
		}
	printf("\n");
	fclose(dptr);
}

void Print_a_list(struct main_struct_ptr *data_ptr) //actor_list 파일을 만들기 위한 함수
{
	FILE *aptr;
	aptr=fopen("actor_list", "w");// actor_list 파일을 쓰기로 열음
	struct movie_in_actor *temp; //정렬된 영화 저장을 위한 변수
	struct actor *current; // 배우정보를 저장하기 위한 변수
	current = data_ptr->actor_ptr;

	// 데이터가 없는 경우
	if(data_ptr->actor_ptr == NULL){
		printf(" 입력된 데이터가 없습니다 \n\n");
		return;
	}
		while(current != NULL){ //파일저장
			temp=current->movie_a;
			fprintf(aptr,"%d:%s:%c:%s:", current->serial_number, current->name,  current->sex,  current->birth);
			while(temp != NULL){
				fprintf(aptr,"%s",temp->name);
				if(temp->next != NULL)
				{
					fprintf(aptr,",");
				}
				temp=temp->next;
			}
			fprintf(aptr,"\n");
			current = current->next;
		}
	printf("\n");
	fclose(aptr);
}

void menu(char *input, struct main_struct_ptr *data_ptr ) {
	char *get_input;
	char *token;   //명령어 쪼개서 저장함
	char *menu;   //명령 부분을 담는 포인터
	char *factor;   //인자 부분을 담는 포인터
	char *option;   //옵션 부분을 담는 포인터

	get_input = (char *)malloc(100);
	strcpy(get_input, input);
	token = strtok(get_input, " ");
	menu = (char *)malloc(sizeof(char) * strlen(token) + 1);
	strcpy(menu, token);
	if(!strcmp(menu,"end")){
		// movie_save_m("movie_list",data_ptr,'m');
		if(!fopen("director_list","rb"))
			movie_save_m("director_list",data_ptr,'d');
		if(!fopen("actor_list","rb"))
			movie_save_m("actor_list",data_ptr,'a');
		exit(0);
	}
	else if(!strcmp(menu,"add")){ // 명령어가 add일경우
		token = strtok(NULL, " ");   //한번 더 쪼개서 m, d, a중에 하나인걸 확인
 	  factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
 	  strcpy(factor, token);
      if (!strcmp(factor, "m")){ // 인자확인
       // add m
			 Print_m_list(data_ptr);
			}
		 else if (!strcmp(factor, "d")){ // 인자확인
			 // add d
			 Print_d_list(data_ptr);
		 }
		 else if (!strcmp(factor, "a")){ // 인자확인
			// add a
			Print_a_list(data_ptr);
		}
  }
	else if (!strcmp(menu, "delete")) { // 명령어가 delete일경우..
		token = strtok(NULL, " ");   //한번 더 쪼개서 m, d, a중에 하나인걸 확인
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		if (!strcmp(factor, "m")){ // 인자확인
			if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
				// delete m num
				Print_m_list(data_ptr);
			}
		}
		else if (!strcmp(factor, "d")){
			if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
				// delete d num
				Print_d_list(data_ptr);
			}
		}
		else if (!strcmp(factor, "a")){
			if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
			 // delete a num
			 Print_a_list(data_ptr);
			}
		}
	}
	else if (!strcmp(menu, "update")) {   //menu가 update이면
		token = strtok(NULL, " ");   //한번 더 쪼개서 m, d, a중에 하나인걸 확인
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		if (!strcmp(factor, "m")){ // 인자확인
		  if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 문자열이 더 있는지 확인
		      option = (char *)malloc(sizeof(char) * strlen(token) + 1); //뒤에 있는게 옵션이면
		      strcpy(option, token);
		      if (strchr(option,'t')) //옵션확인
		      {
		        updatet_ = 1;
						update_num++;
		      }
		      if (strchr(option,'g'))
		      {
		        update_g = 1;
						update_num++;
		      }
		      if (strchr(option,'d'))
		      {
		        update_d = 1;
						update_num++;
		      }
		      if (strchr(option,'y'))
		      {
		        update_y = 1;
						update_num++;
		      }
		      if (strchr(option,'r'))
		      {
		        update_r = 1;
						update_num++;
		      }
		      if (strchr(option,'a'))
		      {
		        update_a = 1;
						update_num++;
		      }
					if(update_num==0)
					{
					 updatet_ = 1;
					 update_g = 1;
					 update_d = 1;
					 update_y = 1;
					 update_r = 1;
					 update_a = 1;
					 // update m num
					 Print_m_list(data_ptr);
					 updatet_ = 0;
					 update_g = 0;
					 update_d = 0;
					 update_y = 0;
					 update_r = 0;
					 update_a = 0;
				 }
		      if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
		        token = strtok(NULL, " ");
		        // update m option num
						Print_m_list(data_ptr);
						updatet_ = 0;
		        update_g = 0;
		        update_d = 0;
		        update_y = 0;
		        update_r = 0;
		        update_a = 0;
						update_num=0;
		      }
		    }
		  }

		if(!strcmp(factor,"d")){
			if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 문자열이 더 있는지 확인
		      option = (char *)malloc(sizeof(char) * strlen(token) + 1); //뒤에 있는게 옵션이면
		      strcpy(option, token);
					if (strchr(option,'n')) // 각 옵션들이 무엇인지 확인
					{
						update_n = 1;
						update_num++;
					}
					if (strchr(option,'s'))
					{
						update_s = 1;
						update_num++;
					}
					if (strchr(option,'b'))
					{
						update_b = 1;
						update_num++;
					}
					if (strchr(option,'m'))
					{
						update_m = 1;
						update_num++;
					}
					if(update_num==0)
					{
					 update_n = 1;
					 update_s = 1;
					 update_b = 1;
					 update_m = 1;
					 // update d num
					 Print_d_list(data_ptr);
					 update_n = 0;
					 update_s = 0;
					 update_b = 0;
					 update_m = 0;
				 }
		      if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
		        token = strtok(NULL, " ");
		        // update d option num
						Print_d_list(data_ptr);
						update_n = 0;
						update_s = 0;
						update_b = 0;
						update_m = 0;
						update_num=0;
		      }
		    }
			}
			if(!strcmp(factor,"a")){
				if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 문자열이 더 있는지 확인
			      option = (char *)malloc(sizeof(char) * strlen(token) + 1); //뒤에 있는게 옵션이면
			      strcpy(option, token);
						if (strchr(option,'n')) // 각 옵션들이 무엇인지 확인
						{
							update_n = 1;
							update_num++;
						}
						if (strchr(option,'s'))
						{
							update_s = 1;
							update_num++;
						}
						if (strchr(option,'b'))
						{
							update_b = 1;
							update_num++;
						}
						if (strchr(option,'m'))
						{
							update_m = 1;
							update_num++;
						}
						if(update_num==0)
						{
						 update_n = 1;
						 update_s = 1;
						 update_b = 1;
						 update_m = 1;
						 // update a num
						 Print_a_list(data_ptr);
						 update_n = 0;
						 update_s = 0;
						 update_b = 0;
						 update_m = 0;
					 }
			      if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
			        token = strtok(NULL, " ");
			        // update a option num
							Print_a_list(data_ptr);
							update_n = 0;
							update_s = 0;
							update_b = 0;
							update_m = 0;
							update_num=0;
			    }
		    }
		  }
	  }

	else if (!strcmp(menu, "save")) {   //menu가 save이면
		token = strtok(NULL, " ");   //한번 더 쪼개서 m, d, a중에 하나인걸 확인
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		if (!strcmp(factor, "m")){ // 인자확인
		  if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 문자열이 더 있는지 확인
		    if (!strcmp(token, "-f")) {
		      token = strtok(NULL, " ");
		      movie_save_m(token,data_ptr,'m');
		    }
		    else {   //뒤에 있는게 옵션이면
		      option = (char *)malloc(sizeof(char) * strlen(token) + 1);
		      strcpy(option, token);
		      if (strchr(option,'t')) //옵션확인
		      {
		        savet_ = 1;
		      }
		      if (strchr(option,'g'))
		      {
		        save_g = 1;
		      }
		      if (strchr(option,'d'))
		      {
		        save_d = 1;
		      }
		      if (strchr(option,'y'))
		      {
		        save_y = 1;
		      }
		      if (strchr(option,'r'))
		      {
		        save_r = 1;
		      }
		      if (strchr(option,'a'))
		      {
		        save_a = 1;
		      }

		      if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
		        token = strtok(NULL, " ");
		        movie_save_m(token,data_ptr,'m');
						savet_ = 0;
		        save_g = 0;
		        save_d = 0;
		        save_y = 0;
		        save_r = 0;
		        save_a = 0;
		      }
		      else
		      {
		        movie_save_m("movie_list",data_ptr,'m');
		        savet_ = 0;
		        save_g = 0;
		        save_d = 0;
		        save_y = 0;
		        save_r = 0;
		        save_a = 0;
		      }
		    }
		  }
		  else // -f 없이 인자 m만 받음
		  {
		    savet_ = 1;
		    save_g = 1;
		    save_d = 1;
		    save_y = 1;
		    save_r = 1;
		    save_a = 1;
		    movie_save_m("movie_list",data_ptr,'m');
		    savet_ = 0;
		    save_g = 0;
		    save_d = 0;
		    save_y = 0;
		    save_r = 0;
		    save_a = 0;
		  }
		}

		if(!strcmp(factor,"d")){
			if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
				if (!strcmp(token, "-f")) {
					token = strtok(NULL, " ");
					movie_save_m(token,data_ptr,'d');
				}
				else {   //뒤에 있는게 옵션이면
					option = (char *)malloc(sizeof(char) * strlen(token) + 1);
					strcpy(option, token);
					if (strchr(option,'n')) // 각 옵션들이 무엇인지 확인
					{
						save_n = 1;
					}
					if (strchr(option,'s'))
					{
						save_s = 1;
					}
					if (strchr(option,'b'))
					{
						save_b = 1;
					}
					if (strchr(option,'m'))
					{
						save_m = 1;
					}

					if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
						token = strtok(NULL," ");
						movie_save_m(token,data_ptr,'d');
						save_n = 0;
						save_s =0;
						save_b = 0;
						save_m = 0;
					}
					else // 옵션뒤에 -f없으면 화면 출력
					{
						movie_save_m("director_list",data_ptr,'d');
						save_n = 0;
						save_s =0;
						save_b = 0;
						save_m = 0;
					}
				}
			}
			else // d뒤에 아무것도 없음.
			{
				save_n = 1;
				save_s =1;
				save_b = 1;
				save_m = 1;
				movie_save_m("director_list",data_ptr,'d');
				save_n = 1;
				save_s =1;
				save_b = 1;
				save_m = 1;
			}
		}
		if(!strcmp(factor,"a")){
			if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
				if (!strcmp(token, "-f")) {
					token = strtok(NULL, " ");
					movie_save_m(token,data_ptr,'a');
				}
				else {   //뒤에 있는게 옵션이면
					option = (char *)malloc(sizeof(char) * strlen(token) + 1);
					strcpy(option, token);
					if (strchr(option,'n')) // 각 옵션들이 무엇인지 확인
					{
						save_n = 1;
					}
					if (strchr(option,'s'))
					{
						save_s = 1;
					}
					if (strchr(option,'b'))
					{
						save_b = 1;
					}
					if (strchr(option,'m'))
					{
						save_m = 1;
					}

					if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
						token = strtok(NULL," ");
						movie_save_m(token,data_ptr,'a');
						save_n = 0;
						save_s =0;
						save_b = 0;
						save_m = 0;
					}
					else // 옵션뒤에 -f없으면 화면 출력
					{
						movie_save_m("actor_list",data_ptr,'a');
						save_n = 0;
						save_s =0;
						save_b = 0;
						save_m = 0;
					}
				}
			}
			else // a뒤에 아무것도 없음.
			{
				save_n = 1;
				save_s =1;
				save_b = 1;
				save_m = 1;
				movie_save_m("actor_list",data_ptr,'a');
				save_n = 0;
				save_s =0;
				save_b = 0;
				save_m = 0;
			}
		}
	}

	else if (!strcmp(menu, "sort")) {   //menu가 sort이면
		token = strtok(NULL, " ");   //한번 더 쪼개서 m, d, a중에 하나인걸 확인
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		if (!strcmp(factor, "m")){ // 인자확인
			if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 문자열이 더 있는지 확인
				if (!strcmp(token, "-f")) {   //옵션없이 -f이면 영화이름대로 정렬
					token = strtok(NULL, " ");
					ofp=fopen(token,"w");
					file_number++;
					Sort_m_t(data_ptr);
					Print_m(data_ptr);
					fclose(ofp);
				}
				else {   //뒤에 있는게 옵션이면
					option = (char *)malloc(sizeof(char) * strlen(token) + 1);
					strcpy(option, token);
					if (!strcmp(option, "t")) //옵션확인
					{
						Sort_m_t(data_ptr);
					}
					else if (!strcmp(option, "g"))
					{
						Sort_m_g(data_ptr);
					}
					else if (!strcmp(option, "d"))
					{
						Sort_m_d(data_ptr);
					}
					else if (!strcmp(option, "y"))
					{
						Sort_m_y(data_ptr);
					}
					else if (!strcmp(option, "r"))
					{
						Sort_m_r(data_ptr);
					}
					else if (!strcmp(option, "a"))
					{
						Sort_m_a(data_ptr);
					}

					if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
						token = strtok(NULL, " ");
						ofp=fopen(token,"w");
						file_number++;
						Print_m(data_ptr);
						fclose(ofp);
					}
					else
					{
						Print_m(data_ptr); // -f 없음
						fclose(ofp);
					}
				}
			}
			else // -f 없이 인자 d만 받음
			{
				Sort_m_t(data_ptr);
				Print_m(data_ptr);
				fclose(ofp);
			}
		}
		else if(!strcmp(factor, "d")){ // 나머지 인자도 m일떄와 같음
			if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
				if (!strcmp(token, "-f")) {
					token = strtok(NULL, " ");
					ofp=fopen(token,"w");
					file_number++;
					Sort_d_n(data_ptr); // d뒤에 바로 -f이면 영화 이름별로 정렬해줌
					Print_d(data_ptr);
					fclose(ofp);
				}
				else {   //뒤에 있는게 옵션이면
					option = (char *)malloc(sizeof(char) * strlen(token) + 1);
					strcpy(option, token);
					if (!strcmp(option, "n")) // 각 옵션들이 무엇인지 확인
					{
						Sort_d_n(data_ptr);
					}
					else if (!strcmp(option, "s"))
					{
						Sort_d_s(data_ptr);
					}
					else if (!strcmp(option, "b"))
					{
						Sort_d_b(data_ptr);
					}
					else if (!strcmp(option, "m"))
					{
						Sort_d_m(data_ptr);
					}

					if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
						token = strtok(NULL, " ");
						ofp=fopen(token,"w");
						file_number++;
						Print_d(data_ptr);
						fclose(ofp);
					}
					else // 옵션뒤에 -f없으면 화면 출력
					{
						Print_d(data_ptr);
						fclose(ofp);
					}
				}
			}
			else // d뒤에 아무것도 없음.
			{
				Sort_d_n(data_ptr);
				Print_d(data_ptr);
				fclose(ofp);
			}
		}
		else if(!strcmp(factor, "a")){
			if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
				if (!strcmp(token, "-f")) {
					token = strtok(NULL, " ");
					ofp=fopen(token,"w");
					file_number++;
					Sort_a_n(data_ptr); // d뒤에 바로 -f이면 영화 이름별로 정렬해줌
					Print_a(data_ptr);
					fclose(ofp);
				}
				else {   //뒤에 있는게 옵션이면
					option = (char *)malloc(sizeof(char) * strlen(token) + 1);
					strcpy(option, token);
					if (!strcmp(option, "n")) // 각 옵션들이 무엇인지 확인
					{
						Sort_a_n(data_ptr);
					}
					else if (!strcmp(option, "s"))
					{
						Sort_a_s(data_ptr);
					}
					else if (!strcmp(option, "b"))
					{
						Sort_a_b(data_ptr);
					}
					else if (!strcmp(option, "m"))
					{
						Sort_a_m(data_ptr);
					}

					if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
						token = strtok(NULL, " ");
						ofp=fopen(token,"w");
						file_number++;
						Print_a(data_ptr);
						fclose(ofp);
					}
					else // 옵션뒤에 -f없으면 화면 출력
					{
						Print_a(data_ptr);
						fclose(ofp);
					}
				}
			}
			else // d뒤에 아무것도 없음.
			{
				Sort_a_n(data_ptr);
				Print_a(data_ptr);
				fclose(ofp);
			}
		}
	}
	else if (!strcmp(menu, "print")) { // 명령어가 print일경우..
		token = strtok(NULL, " ");   //한번 더 쪼개서 m, d, a중에 하나인걸 확인
		factor = (char *)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(factor, token);
		if (!strcmp(factor, "m")){ // 인자확인
			if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
				Print_m_num(data_ptr,token);
			}
		}
		else if (!strcmp(factor, "d")){
			if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
				Print_d_num(data_ptr,token);
			}
		}
		else if (!strcmp(factor, "a")){
			if ((token = strtok(NULL, " ")) != NULL) {   //뒤에 뭐가 더 있는지 확인
				Print_a_num(data_ptr,token);
			}
		}
	}
}

int mov(struct main_struct_ptr* data_ptr, char *s2){
	if(strchr(s2, '?') != NULL || strchr(s2, '*') != NULL){
		QorM_m(data_ptr, s2);
		return 0;
	}
	int i  = 0;
	while(1){
		int ser, tit, gen, dir, yea, tim, act, i, check, getout;
		char *Ser, *Yea, *Tim;
		char ** actstring;
		i = 0;
		check = 0;
		getout = 0;
		actstring = (char**)malloc(sizeof(char*) * 50);
		for(int i = 0; i < 50 ; i++)
			*(actstring + i) = (char*)malloc(sizeof(char)*20);
		Ser = (char*)malloc(sizeof(char*)*50);
		Yea = (char*)malloc(sizeof(char*)*50);
		Tim = (char*)malloc(sizeof(char*)*50);
		sprintf(Ser, "%d", data_ptr->movie_ptr->serial_number);
		sprintf(Yea, "%d", data_ptr->movie_ptr->year);
		sprintf(Tim, "%d", data_ptr->movie_ptr->movie_time);
		ser = strcmp(Ser, s2);
		tit = strcmp(data_ptr->movie_ptr->title, s2);
		gen = strcmp(data_ptr->movie_ptr->genre, s2);
		dir = strcmp(data_ptr->movie_ptr->director_m->name, s2);
		yea = strcmp(Yea, s2);
		tim = strcmp(Tim, s2);
		act = strcmp(data_ptr->movie_ptr->actor_m->name, s2);
		if(data_ptr->movie_ptr->actor_m->next == NULL){
			*actstring = data_ptr->movie_ptr->actor_m->name;
		}

		else  {
		while(1){
			if(act == 0)
				check = 1;
			printf("%d, %s\n",i, data_ptr->movie_ptr->actor_m->name);
			*(actstring + i) = data_ptr->movie_ptr->actor_m->name;
			if(getout == 1)
				break;
			data_ptr->movie_ptr->actor_m = data_ptr->movie_ptr->actor_m->next;
			act = strcmp(data_ptr->movie_ptr->actor_m->name, s2);
			i++;
			if(data_ptr->movie_ptr->actor_m->next == NULL)
				getout = 1;
		}
		if(check == 1)
			act = 0;
	}
		printf("%d %d %d %d %d %d %d\n", ser, tit, gen, dir, yea, tim, act);
	// 	printf("%d:", data_ptr->movie_ptr->serial_number);
	// 	printf("%s:", data_ptr->movie_ptr->title);
	// 	printf("%s:", data_ptr->movie_ptr->genre);
	// 	printf("%s:", data_ptr->movie_ptr->director_m->name);
	// 	printf("%d:", data_ptr->movie_ptr->year);
	// 	printf("%d:", data_ptr->movie_ptr->movie_time);
	// 	printf("%s", *(actstring));
	// 	if(i){
	// 	for(int k = 1 ; k < i+1; k++)
	// 		printf(",%s", *(actstring + k ));
	// 	printf("\n");
	// }
		if(ser * tit * gen * dir * yea * tim * act == 0){
			printf("%d:", data_ptr->movie_ptr->serial_number);
			printf("%s:", data_ptr->movie_ptr->title);
			printf("%s:", data_ptr->movie_ptr->genre);
			printf("%s:", data_ptr->movie_ptr->director_m->name);
			printf("%d:", data_ptr->movie_ptr->year);
			printf("%d:", data_ptr->movie_ptr->movie_time);
			printf("%s", *(actstring));
			if(i)
				for(int k = 1 ; k < i+1; k++)
					printf(",%s", *(actstring + k ));
			printf("\n");

		}
		if(data_ptr->movie_ptr->next  == NULL)
			break;
		data_ptr->movie_ptr = data_ptr->movie_ptr->next;
		free(Ser);
		free(Yea);
		free(Tim);
	}
	return 0;
}

int dir(struct main_struct_ptr* data_ptr,char *s2){
	if(strchr(s2, '?') != NULL || strchr(s2, '*') != NULL){
		QorM_d(data_ptr, s2);
		return 0;
	}
	while(1){
		int ser, nam, sex, bir, mov, i, check, getout;
		char* Ser, *Sex;
		char** movstring;
		i = 0;
		check = 0;
		getout = 0;
		movstring = (char**)malloc(sizeof(char*) * 50);
		for(int i = 0; i < 50 ; i++)
			*(movstring + i) = (char*)malloc(sizeof(char)*20);

		Ser = (char*)malloc(sizeof(char*)*50);
		Sex = (char*)malloc(sizeof(char*)*50);
		sprintf(Ser, "%d", data_ptr->director_ptr->serial_number);
		sprintf(Sex, "%c", data_ptr->director_ptr->sex);
		ser = strcmp(Ser, s2);
		nam = strcmp(data_ptr->director_ptr->name, s2);
		sex = strcmp(Sex, s2);
		bir = strcmp(data_ptr->director_ptr->birth, s2);
		mov = strcmp(data_ptr->director_ptr->movie_d->name, s2);
		if(data_ptr->director_ptr->movie_d->next == NULL)
			*movstring = data_ptr->director_ptr->movie_d->name;
		else{
		while(1){
			if(mov == 0)
				check = 1;
			// printf("%d, %s\n",i, data_ptr->director_ptr->movie_d->name);
			*(movstring + i) = data_ptr->director_ptr->movie_d->name;
			if(getout == 1)
				break;
			data_ptr->director_ptr->movie_d = data_ptr->director_ptr->movie_d->next;
			mov = strcmp(data_ptr->director_ptr->movie_d->name, s2);
			i++;
			if(data_ptr->director_ptr->movie_d->next == NULL)
				getout = 1;
		}
		if(check == 1)
			mov = 0;
		}
			// printf("i : %d\n", i);
			// printf("%d %d %d %d %d\n", ser, nam, sex, bir, mov);
			// printf("%d:", data_ptr->director_ptr->serial_number);
			// printf("%s:", data_ptr->director_ptr->name);
			// printf("%c:", data_ptr->director_ptr->sex);
			// printf("%s:", data_ptr->director_ptr->birth);
			// printf("%s", *(movstring));
			// for(int k = 1 ; k < i+1; k++)
			// 	printf(",%s", *(movstring + k ));
			// printf("\n");
		if(ser * nam * sex * bir * mov == 0){
			printf("%d:", data_ptr->director_ptr->serial_number);
			printf("%s:", data_ptr->director_ptr->name);
			printf("%c:", data_ptr->director_ptr->sex);
			printf("%s:", data_ptr->director_ptr->birth);
			printf("%s", data_ptr->director_ptr->movie_d->name);
			if(i)
				for(int k = 1 ; k < i+1; k++)
					printf(",%s", *(movstring + k ));
			printf("\n");

		}
		if(data_ptr->director_ptr->next == NULL)
			break;
		data_ptr->director_ptr = data_ptr->director_ptr->next;


	}
	return 0;
}

int act(struct main_struct_ptr* data_ptr, char *s2){
	if(strchr(s2, '?') != NULL || strchr(s2, '*') != NULL){
		QorM_a(data_ptr, s2);
		return 0;
	}
	while(1){
		int ser, nam, sex, bir, mov, i, check, getout;
		char* Ser, *Sex;
		char** movstring;
		i = 0;
		check = 0;
		getout = 0;
		movstring = (char**)malloc(sizeof(char*) * 50);
		for(int i = 0; i < 50 ; i ++)
			*(movstring + i) = (char *)malloc(sizeof(char) * 20);

		Ser = (char*)malloc(sizeof(char*)*50);
		Sex = (char*)malloc(sizeof(char*)*50);
		sprintf(Ser, "%d", data_ptr->actor_ptr->serial_number);
		sprintf(Sex, "%c", data_ptr->actor_ptr->sex);
		ser = strcmp(Ser, s2);
		nam = strcmp(data_ptr->actor_ptr->name, s2);
		sex = strcmp(Sex, s2);
		bir = strcmp(data_ptr->actor_ptr->birth, s2);
		mov = strcmp(data_ptr->actor_ptr->movie_a->name, s2);
		if(data_ptr->actor_ptr->movie_a->next == NULL)
			*movstring = data_ptr->actor_ptr->movie_a->name;
		else{
		while(1){
			if(mov == 0)
				check = 1;
			// printf("%d, %s\n",i, data_ptr->actor_ptr->movie_a->name);
			*(movstring + i) = data_ptr->actor_ptr->movie_a->name;
			if(getout == 1)
				break;
			data_ptr->actor_ptr->movie_a = data_ptr->actor_ptr->movie_a->next;
			mov = strcmp(data_ptr->actor_ptr->movie_a->name, s2);
			i++;
			if(data_ptr->actor_ptr->movie_a->next == NULL)
				getout = 1;
		}
		if(check == 1)
			mov = 0;
		}
		// printf("i : %d\n", i);
		// printf("%d %d %d %d %d\n", ser, nam, sex, bir, mov);
		// printf("%d:", data_ptr->actor_ptr->serial_number);
		// printf("%s:", data_ptr->actor_ptr->name);
		// printf("%c:", data_ptr->actor_ptr->sex);
		// printf("%s:", data_ptr->actor_ptr->birth);
		// printf("%s", *(movstring));
		// for(int k = 1 ; k < i+1; k++)
		// 	printf(",%s", *(movstring + k ));
		// printf("\n");
		printf("%d\n", i);
		if(ser * nam * sex * bir * mov == 0){
			printf("%d:", data_ptr->actor_ptr->serial_number);
			printf("%s:", data_ptr->actor_ptr->name);
			printf("%c:", data_ptr->actor_ptr->sex);
			printf("%s:", data_ptr->actor_ptr->birth);
			printf("%s", *(movstring));
			if(i)
				for(int k = 1 ; k < i+1; k++)
					printf(",%s", *(movstring + k ));
			printf("\n");
		}
		if(data_ptr->actor_ptr->next == NULL)
			break;
		data_ptr->actor_ptr = data_ptr->actor_ptr->next;


	}
		return 0;
}

bool pattern_match(const char *str, const char *pattern) {
	enum State {
		Exact,      	// exact match
		Any,        	// ?
		AnyRepeat    	// *
	};

	const char *s = str;
	const char *p = pattern;
	const char *q = 0;
	int state = 0;

	bool match = true;
	while(match && *p){
		if(*p == '*'){
			state = AnyRepeat;
			q = p+1;
		}
		else if(*p == '?')
			state = Any;
		else
			state = Exact;

		if (*s == 0)
			break;

		switch (state) {
			case Exact:
				match = *s == *p;
				s++;
				p++;
				break;

			case Any:
				match = true;
				s++;
				p++;
				break;

			case AnyRepeat:
				match = true;
				s++;

				if (*s == *q)
					p++;

				break;
		}
	}

	if(state == AnyRepeat)
		return(*s == *q);
	else if(state == Any)
		return(*s == *p);
	else
		return match && (*s == *p);
}

void QorM_m(struct main_struct_ptr *data_ptr, char*s2){
	while(1){
		int ser, tit, gen, dir, yea, tim, act, i, check, getout;
		char *Ser, *Yea, *Tim;
		char **actstring;
		i = 0;
		check = 0;
		getout = 0;
		actstring = (char**)malloc(sizeof(char*) * 50);
		for(int i = 0; i < 50 ; i++)
			*(actstring + i) = (char*)malloc(sizeof(char)*20);

		Ser = (char*)malloc(sizeof(char*)*50);
		Yea = (char*)malloc(sizeof(char*)*50);
		Tim = (char*)malloc(sizeof(char*)*50);
		sprintf(Ser, "%d", data_ptr->movie_ptr->serial_number);
		sprintf(Yea, "%d", data_ptr->movie_ptr->year);
		sprintf(Tim, "%d", data_ptr->movie_ptr->movie_time);
		ser = (pattern_match(Ser, s2)) - 1;
		tit = (pattern_match(data_ptr->movie_ptr->title, s2)) - 1;
		gen = (pattern_match(data_ptr->movie_ptr->genre, s2)) - 1;
		dir = (pattern_match(data_ptr->movie_ptr->director_m->name, s2)) - 1;
		yea = (pattern_match(Yea, s2)) - 1;
		tim = (pattern_match(Tim, s2)) - 1;
		act = (pattern_match(data_ptr->movie_ptr->actor_m->name, s2)) - 1;
		if(data_ptr->movie_ptr->actor_m->next == NULL)
			*actstring = data_ptr->movie_ptr->actor_m->name;
		else  {
		while(1){
			if(act == 0)
				check = 1;
			// printf("%d, %s\n",i, data_ptr->director_ptr->movie_d->name);
			*(actstring + i) = data_ptr->movie_ptr->actor_m->name;
			if(getout == 1)
				break;
			data_ptr->movie_ptr->actor_m  = data_ptr->movie_ptr->actor_m->next;
			act = (pattern_match(data_ptr->movie_ptr->actor_m->name, s2)) - 1;
			i++;
			if(data_ptr->movie_ptr->actor_m->next == NULL)
				getout = 1;
		}
		if(check == 1)
			act = 0;
	}
		printf("%d %d %d %d %d %d %d\n", ser, tit, gen, dir, yea, tim, act);
		// printf("%d:", data_ptr->movie_ptr->serial_number);
		// printf("%s:", data_ptr->movie_ptr->title);
		// printf("%s:", data_ptr->movie_ptr->genre);
		// printf("%s:", data_ptr->movie_ptr->director_m->name);
		// printf("%d:", data_ptr->movie_ptr->year);
		// printf("%d:", data_ptr->movie_ptr->movie_time);
		// printf("%s\n", data_ptr->movie_ptr->actor_m->name);
		if(ser * tit * gen * dir * yea * tim * act == 0){
			printf("%d:", data_ptr->movie_ptr->serial_number);
			printf("%s:", data_ptr->movie_ptr->title);
			printf("%s:", data_ptr->movie_ptr->genre);
			printf("%s:", data_ptr->movie_ptr->director_m->name);
			printf("%d:", data_ptr->movie_ptr->year);
			printf("%d:", data_ptr->movie_ptr->movie_time);
			printf("%s", *actstring);
			if(i)
				for(int k = 1; k < i+1; k++)
					printf(",%s", *(actstring + k));
			printf("\n");
		}
		if(data_ptr->movie_ptr->next == NULL)
			break;

		data_ptr->movie_ptr = data_ptr->movie_ptr->next;


	}
}

void QorM_d(struct main_struct_ptr *data_ptr, char*s2){
	while(1){
		int ser, nam, sex, bir, mov, i, check, getout;
		char* Ser, *Sex;
		char** movstring;
		i = 0;
		check = 0;
		getout = 0;
		movstring = (char**)malloc(sizeof(char*) * 50);
		for(int i = 0; i < 50 ; i++)
			*(movstring + i) = (char*)malloc(sizeof(char)*20);

		Ser = (char*)malloc(sizeof(char*)*50);
		Sex = (char*)malloc(sizeof(char*)*50);
		sprintf(Ser, "%d", data_ptr->director_ptr->serial_number);
		sprintf(Sex, "%c", data_ptr->director_ptr->sex);
		ser = (pattern_match(Ser, s2)) - 1;
		nam = (pattern_match(data_ptr->director_ptr->name, s2)) - 1;
		sex = (pattern_match(Sex, s2)) - 1;
		bir = (pattern_match(data_ptr->director_ptr->birth, s2)) - 1;
		mov = (pattern_match(data_ptr->director_ptr->movie_d->name, s2)) - 1;
		if(data_ptr->director_ptr->movie_d->next == NULL)
			*movstring = data_ptr->director_ptr->movie_d->name;
		else{
		while(1){
			if(mov == 0)
				check = 1;
			// printf("%d, %s\n",i, data_ptr->director_ptr->movie_d->name);
			*(movstring + i) = data_ptr->director_ptr->movie_d->name;
			if(getout == 1)
				break;
			data_ptr->director_ptr->movie_d = data_ptr->director_ptr->movie_d->next;
			mov = (pattern_match(data_ptr->director_ptr->movie_d->name, s2)) - 1;
			i++;
			if(data_ptr->director_ptr->movie_d->next == NULL)
				getout = 1;
		}
		if(check == 1)
			mov = 0;
		}
		if(ser * nam * sex * bir * mov == 0){
			printf("%d:", data_ptr->director_ptr->serial_number);
			printf("%s:", data_ptr->director_ptr->name);
			printf("%c:", data_ptr->director_ptr->sex);
			printf("%s:", data_ptr->director_ptr->birth);
			printf("%s", data_ptr->director_ptr->movie_d->name);
			if(i)
				for(int k = 1 ; k < i+1; k++)
					printf(",%s", *(movstring + k ));
			printf("\n");
		}
		if(data_ptr->director_ptr->next == NULL)
			break;
		data_ptr->director_ptr = data_ptr->director_ptr->next;


	}
}

void QorM_a(struct main_struct_ptr *data_ptr, char*s2){
	while(1){
		int ser, nam, sex, bir, mov, i, check, getout;
		char* Ser, *Sex;
		char** movstring;
		i = 0;
		check = 0;
		getout = 0;
		movstring = (char**)malloc(sizeof(char*) * 50);
		for(int i = 0; i < 50 ; i ++)
			*(movstring + i) = (char *)malloc(sizeof(char) * 20);
		Ser = (char*)malloc(sizeof(char*)*50);
		Sex = (char*)malloc(sizeof(char*)*50);
		sprintf(Ser, "%d", data_ptr->actor_ptr->serial_number);
		sprintf(Sex, "%c", data_ptr->actor_ptr->sex);
		ser = (pattern_match(Ser, s2)) - 1;
		nam = (pattern_match(data_ptr->actor_ptr->name, s2)) - 1;
		sex = (pattern_match(Sex, s2)) - 1;
		bir = (pattern_match(data_ptr->actor_ptr->birth, s2)) - 1;
		mov = (pattern_match(data_ptr->actor_ptr->movie_a->name, s2)) - 1;
		if(data_ptr->actor_ptr->movie_a->next == NULL)
			*movstring = data_ptr->actor_ptr->movie_a->name;
		else{
		while(1){
			if(mov == 0)
				check = 1;
			// printf("%d, %s\n",i, data_ptr->actor_ptr->movie_a->name);
			*(movstring + i) = data_ptr->actor_ptr->movie_a->name;
			if(getout == 1)
				break;
			data_ptr->actor_ptr->movie_a = data_ptr->actor_ptr->movie_a->next;
			mov = (pattern_match(*(movstring + i), s2)) -1;
			i++;
			if(data_ptr->actor_ptr->movie_a->next == NULL)
				getout = 1;
		}
		if(check == 1)
			mov = 0;
		}
		// printf("%d %d %d %d %d\n", ser, nam, sex, bir, mov);
		// printf("%d:", data_ptr->actor_ptr->serial_number);
		// printf("%s:", data_ptr->actor_ptr->name);
		// printf("%c:", data_ptr->actor_ptr->sex);
		// printf("%s:", data_ptr->actor_ptr->birth);
		// printf("%s\n", data_ptr->actor_ptr->movie_a->name);

		if(ser * nam * sex * bir * mov == 0){
			printf("%d:", data_ptr->actor_ptr->serial_number);
			printf("%s:", data_ptr->actor_ptr->name);
			printf("%c:", data_ptr->actor_ptr->sex);
			printf("%s:", data_ptr->actor_ptr->birth);
			printf("%s", *(movstring));
			if(i)
				for(int k = 1 ; k < i+1; k++)
					printf(",%s", *(movstring + k ));
			printf("\n");
		}
		if(data_ptr->actor_ptr->next == NULL)
			break;

		data_ptr->actor_ptr = data_ptr->actor_ptr->next;


	}
}

void ordersearch(struct main_struct_ptr*data_ptr) {
	char * s = NULL;
	char * s1 = NULL;
	char * s2 = NULL;
	char * s3 = NULL;
	// char * string = NULL;
	char * p,*q,*r;
	s = (char *)malloc(sizeof(char*));
	char * order = NULL;
	printf("명령을 입력하세요 : ");
	for (int i = 0;1; i++){
		scanf("%c", (s+i));
		s = realloc(s, sizeof(char*) * (i+1));
		if (*(s+i) == '\n') {
			*(s+i) = 0;
			break;
		}
	}
	order = (char *)malloc(sizeof(char*) * 50);
	order = strtok(s, " ");
	s1 = order;
	p = (char *)malloc(sizeof(char*) * 50);
	p = strstr(s1, "search");
	if (p != NULL)
		order = strtok(NULL, " ");
	s2 = order;
	p = strchr(s2, '-');
	if(p != NULL){           // 옵션이 있다면
		p = strchr(s2, 'm');
		q = strchr(s2, 'd');
		r = strchr(s2, 'a');
		order = strtok(NULL, " ");
		s3 = order;
		if(p != NULL)   // movie_list 에서 검색
			mov(data_ptr, s3);

		if(q != NULL)   // director_list에서 검색
			dir(data_ptr, s3);

		if(r != NULL)  // actor_list 에서 검색
			act(data_ptr, s3);

	}
	else{           // 옵션이 없다면
		mov(data_ptr, s2);
		dir(data_ptr, s2);
		act(data_ptr, s2);
	}
}



void add_movie_mode (FILE *optr, struct movie *movie_ptr) {

	int cnt = 0;
	int update_sn;
	struct movie *current, *pre_current;
	pre_current = movie_ptr;
	while (pre_current -> next != NULL){
		update_sn = pre_current -> serial_number;
		pre_current = pre_current -> next;
	}
	update_sn++;
	current = pre_current -> next;
	current = malloc (sizeof (struct movie));
	pre_current -> next = current;
	current -> next = NULL;

	printf("title >");
	scan_title_m(stdin, current);

	printf("genre >");
	scan_genre_m(stdin, current);

	printf("director >");
	scan_director_m(stdin,current);

	printf("year >");
	scan_year_m(stdin,current);

	printf("play time >" );
	scan_movie_time_m(stdin, current);

	printf("actor >");
	scan_actor_m(stdin, current);

	struct actor_in_movie *tmp_actor_m;
	tmp_actor_m = (current->actor_m);
	fprintf(optr,"add:%s:%s:%s:%d:%d:",current->title,current->genre,current->director_m->name,current->year,current->movie_time);
	while(tmp_actor_m != NULL){
		fprintf(optr, "%s", tmp_actor_m->name);
		if (tmp_actor_m -> next != NULL){
			fprintf(optr,"%c", ',');
		}
		tmp_actor_m = tmp_actor_m -> next;
	}
	fprintf(optr, "%c", '\n');
}


void add_director_mode (FILE *optr, struct director *director_ptr) {
	int cnt = 0;
	int update_sn;
	struct director *current, *pre_current;
	pre_current = director_ptr;
	while (pre_current -> next != NULL){
		update_sn = pre_current -> serial_number;
		pre_current = pre_current -> next;
	}
	update_sn++;
	current = pre_current -> next;
	current = malloc (sizeof (struct director));
	pre_current -> next = current;
	current -> next = NULL;

	printf("name >");
	scan_name_d(stdin, current);

	printf("sex >");
	scan_sex_d(stdin, current);

	printf("birth >");
	scan_birth_d(stdin,current);

	printf("title movie >");
	scan_title_d(stdin,current);

	struct movie_in_director *tmp_movie_d;
	tmp_movie_d = (current->movie_d);
	fprintf(optr,"add:%s:%c:%s:",current->name,current->sex,current->birth);
	while(tmp_movie_d != NULL){
		fprintf(optr,"%s",tmp_movie_d ->name);
		if (tmp_movie_d -> next != NULL){
			fprintf(optr,"%c", ',');
		}
		tmp_movie_d = tmp_movie_d -> next;
	}
	fprintf(optr, "%c", '\n');
}

void add_actor_mode (FILE *optr, struct actor *actor_ptr) {
	int cnt = 0;
	int update_sn;
	struct actor *current, *pre_current;
	pre_current = actor_ptr;
	while (pre_current -> next != NULL){
		update_sn = pre_current -> serial_number;
		pre_current = pre_current -> next;
	}
	update_sn++;
	current = pre_current -> next;
	current = malloc (sizeof (struct actor));
	pre_current -> next = current;
	current -> next = NULL;

	printf("name >");
	scan_name_a(stdin, current);

	printf("sex >");
	scan_sex_a(stdin, current);

	printf("birth >");
	scan_birth_a(stdin,current);

	printf("title movie >");
	scan_title_a(stdin,current);

	struct movie_in_actor *tmp_movie_a;
	tmp_movie_a = (current->movie_a);
	fprintf(optr,"add:%s:%c:%s:",current->name,current->sex,current->birth);
	while(tmp_movie_a != NULL){
		fprintf(optr,"%s",tmp_movie_a ->name);
		if (tmp_movie_a -> next != NULL){
			fprintf(optr,"%c", ',');
		}
		tmp_movie_a = tmp_movie_a -> next;
	}
	fprintf(optr, "%c", '\n');
}


int main(){
	struct main_struct_ptr *data_ptr; // 저장될 모든 데이터들
	data_ptr = malloc(sizeof(struct main_struct_ptr));
	get_data(data_ptr); // 파일 읽고, 정보저장
	ctrlc.sa_handler = sigint_handler; // 시그널 핸들러 지정
	sigemptyset(&ctrlc.sa_mask);      // 시그널 처리 중 블록될 시그널은 없음
	sigaction(SIGINT, &ctrlc, NULL);
	char *input;
	input = (char *)malloc(sizeof(char) * 50);
	while(1)
		ordersearch(data_ptr);
	// Print_d_list(data_ptr);
	// 	Print_m_list(data_ptr);
	// 	Print_a_list(data_ptr);
	// Print_m(data_ptr);
	// Sort_m_t(data_ptr);
	// Print_m(data_ptr);
  //
	// Print_d(data_ptr);
	// Sort_d_m(data_ptr);
	// Print_d(data_ptr);
	// //
	// Print_a(data_ptr);
	// Sort_a_s(data_ptr);
	// Print_a(data_ptr);
  //
	// FILE *optr_m = fopen("test1.txt", "a");
	// FILE *optr_d = fopen("test2.txt", "a");
	// FILE *optr_a = fopen("test3.txt", "a");
  // //
	// // add_movie_mode(optr_m, data_ptr->movie_ptr);
	// // Print_m(data_ptr);
	// add_actor_mode(optr_a, data_ptr->actor_ptr);
	// Print_a(data_ptr);
	// while (input != NULL) {
	// 	 printf("(movie) ");
	// 	 gets(input);
	// 	 menu(input,data_ptr);
	//  }
	// printf("오류1\n");
	// Print_m(data_ptr);
	// printf("오류2\n");
	// // ordersearch(data_ptr);
	// if (strcmp((data_ptr -> actor_ptr -> movie_a -> next -> name), "king") == 0)
	// {printf("오류3\n");
	// 	printf("king\n" );}
	// printf("%s",data_ptr -> actor_ptr -> movie_a -> next -> name);
	// printf("오류4\n");
}
