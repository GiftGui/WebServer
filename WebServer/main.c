#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#define BUF_SIZE 1024
#define SMALL_BUF 100

void error_msg(const char* msg){
	fputs(msg,stderr);
	fputc('\n',stderr);
	exit(1);
}

void* request_handler(void* arg);
void send_data(FILE* fp,char* ct,char* file_name);
char* content_type(char* file);
void send_error(FILE* fp);

int main(int argc, char* argv[])
{
	if(argc!=2){
		printf("Usage: %s <port>",argv[0]);
		exit(1);
	}
	
	int serv_sock,clnt_sock;
	struct sockaddr_in serv_addr,clnt_addr;
	int clnt_adr_size;
	char buf[BUF_SIZE];
	pthread_t t_id;


	serv_sock = socket(PF_INET,SOCK_STREAM,0);
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
		error_msg("bind() error.");
	}
	if(listen(serv_sock,20)==-1){
		error_msg("listen() error.");
	}

	while(1){
		clnt_adr_size = sizeof(clnt_addr);
		clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_adr_size);
		printf("Connection request: %s:%d\n",inet_ntoa(clnt_addr.sin_addr),ntohs(clnt_addr.sin_port));
		pthread_create(&t_id,NULL,request_handler,&clnt_sock);
		pthread_detach(t_id);
	}
	close(serv_sock);
	return 0;
}

void send_data(FILE* fp,char* ct,char* file_name){
	char protocol[] = "HTTP/1.0 200 OK\r\n";
	char server[]="Server:Linux Web Server \r\n";
	char cnt_len[] = "Content-length:2048\r\n";
	char cnt_type[SMALL_BUF];
	char buf[BUF_SIZE];
	FILE* send_file;

	sprintf(cnt_type, "Content_type:%s\r\n\r\n",ct);
	send_file = fopen(file_name, "r");
	if(send_file==NULL){
		send_error(fp);
		return;
	}

	fputs(protocol,fp);
	fputs(server,fp);
	fputs(cnt_len,fp);
	fputs(cnt_type,fp);

	while(fgets(buf,BUF_SIZE,send_file)!=NULL)
	{
		fputs(buf,fp);
		fflush(fp);
	}
	fflush(fp);
	fclose(fp);
}



void* request_handler(void* arg){
	int clnt_sock = *((int*)arg);
	char req_line[SMALL_BUF];
	FILE* clnt_read;
	FILE* clnt_write;

	char method[10];
	char ct[15];
	char filename[30];

	clnt_read = fdopen(clnt_sock,"r");
	clnt_write = fdopen(dup(clnt_sock),"w");
	fgets(req_line,SMALL_BUF,clnt_read);
	if(strstr(req_line,"HTTP/")==NULL){
		send_error(clnt_write);
		fclose(clnt_read);
		fclose(clnt_write);
		return 0;
	}
	strcpy(method,strtok(req_line," /"));
	strcpy(filename,strtok(NULL," /"));
	strcpy(ct,content_type(filename));
	if(strcmp(method,"GET")!=0){
		send_error(clnt_write);
		fclose(clnt_read);
			fclose(clnt_write);
			return 0;
	}
	fclose(clnt_read);
	send_data(clnt_write,ct,filename);
}

char* content_type(char* file){
	char extension[SMALL_BUF];
	char file_name[SMALL_BUF];
	strcpy(file_name,file);
	strtok(file_name,".");
	strcpy(extension,strtok(NULL,"."));
	if(!strcmp(extension,"html")||!strcmp(extension,"htm")){
		return "text/html";
	}
	else{
		return "text/plain";
	}
}

void send_error(FILE* fp){

	char protocol[] = "HTTP/1.0 400 Bad Request\r\n";
	char server[] = "Server:Linux Web Server \r\n";
	char cnt_len[] = "Content-length:2048\r\n";
	char cnt_type[] = "Content-type:text/html\r\n\r\n";
	char content[] = "<html><head><title>NETWORK</title></head>"
		"<body><front size=+5><br>Error happen!Check the filename and request style!"
		"</font></body></html>";
	
	fputs(protocol,fp);
	fputs(server,fp);
	fputs(cnt_len, fp);
	fputs(cnt_type,fp);
	fflush(fp);
}


