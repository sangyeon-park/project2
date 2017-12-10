#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_TMP 15
#define MAX_LINKED_NUMBER 5

FILE *ofp;
int file_number=0;

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
   struct director *directr_node;
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
void SortNode(struct main_struct_ptr *data_ptr);
void menu_func(char *input, struct main_struct_ptr *data_ptr );
void PrintList(struct main_struct_ptr *data_ptr);
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
void menu_func(char *input, struct main_struct_ptr *data_ptr );


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
   for (int i=0; count<5*15; i++){
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

void get_movie(struct main_struct_ptr *data_ptr){
   FILE *optr;
   optr = fopen ("test1.txt", "r");
   (data_ptr -> movie_ptr) = malloc(sizeof(struct movie));
   struct movie *tmp_movie_ptr;
   tmp_movie_ptr = (data_ptr->movie_ptr);

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
         // search_serial(data_ptr);

      }

      else
         break;

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

   char *tmp_str;
   int flag = 1;
   tmp_str = malloc(MAX_LINKED_NUMBER*MAX_TMP);
   scan_word(optr, tmp_str);
   printf("%s\n", tmp_str);
   while ((flag = str_devider(tmp_str)) != 0) {
      printf("\nfuck here : %d\n", flag);
      char *tmp_actor;
      tmp_actor = malloc (flag + 2);
      for (int i = 0; i< flag ; i++){
         *(tmp_actor + i) = *(tmp_str + i);
      }
      *(tmp_actor+flag) = '\0';
      tmp_str = tmp_str + flag + 1;

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
   (tmp_actor_ptr->name) = malloc (cnt + 1);
   strcpy((tmp_actor_ptr->name), tmp_actor);
   printf("8:%s\n", tmp_actor_ptr->name);
   tmp_actor_ptr->next = NULL;
   free(tmp_actor);
}


void get_director(struct  main_struct_ptr *data_ptr){
   FILE *optr;
   optr = fopen ("test2.txt", "r");
   (data_ptr -> director_ptr) = malloc(sizeof(struct director));
   struct director *tmp_director_ptr;
   tmp_director_ptr = (data_ptr->director_ptr);

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
   for (int i = 0; i < cnt+1 ; i++){
      *(tmp_title + i) = *(tmp_str + i);
   }
   printf("\nfuck here : %d\n", cnt);

   (tmp_movie_ptr->name) = malloc (cnt + 2);
   strcpy((tmp_movie_ptr->name), tmp_title);
   printf("6:%s\n", tmp_movie_ptr->name);
   tmp_movie_ptr->next = NULL;
   free(tmp_title);
}


void get_actor(struct  main_struct_ptr *data_ptr){
   FILE *optr;
   optr = fopen ("test3.txt", "r");
   (data_ptr -> actor_ptr) = malloc(sizeof(struct actor));
   struct actor *tmp_actor_ptr;
   tmp_actor_ptr = (data_ptr->actor_ptr);
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
      *(tmp_movie+flag+1) = '\0';
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
   for (int i = 0; i < cnt+1 ; i++){
      *(tmp_movie + i) = *(tmp_str + i);
   }
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
      while(current -> next != NULL){
         temp=current->actor_m;
         printf("%s : %s : %s : %d : %d : ",  current->title,  current->genre,  current->director_m->name,  current->year,  current->movie_time);
         while(temp -> next != NULL){
            printf("%s",temp->name);
            printf(",");
            temp=temp->next;
         }
         printf("%s\n******************************************\n",temp->name);
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

void Print_d(struct main_struct_ptr *data_ptr){
   struct movie_in_director *temp; //정렬된 배우 저장을 위한 변수
   struct director *current;
   current = data_ptr->director_ptr;

   // 데이터가 없는 경우
   if(data_ptr->director_ptr == NULL){
      printf(" 입력된 데이터가 없습니다 \n\n");
      return;
   }
   while(current != NULL){
      temp=current->movie_d;
      printf("%s : %c : %s : ",  current->name,  current->sex,  current->birth);
      while(temp->next != NULL){
         printf("%s",temp->name);
         if(temp->next->next != NULL)
            printf(", " );
         temp=temp->next;
      }
      printf("\n");
      current = current->next;
   }
}

void Print_a(struct main_struct_ptr *data_ptr){
   struct movie_in_actor *temp; //정렬된 배우 저장을 위한 변수
   struct actor *current;
   current = data_ptr->actor_ptr;

   // 데이터가 없는 경우
   if(data_ptr->actor_ptr == NULL){
      printf(" 입력된 데이터가 없습니다 \n\n");
      return;
   }
   if(file_number==0){ // -f 가 없어 파일로 저장하지않고 화면에 출력
      while(current != NULL){
         printf("%s:%c:%s:",  current->name,  current->sex,  current->birth);
         temp=current->movie_a;
         while(temp != NULL){
            printf("%s",temp->name);
            if(temp->next != NULL)
            {
               printf(", ");
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
         fprintf(ofp,"%s:%s:%s:",  current->name,  current->sex,  current->birth);
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
		temp->actor_node=NULL;
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
		temp->movie_node=NULL;
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
		temp->movie_node=NULL;

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

