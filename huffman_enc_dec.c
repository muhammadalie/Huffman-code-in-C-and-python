#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	char data;
	int size;
	char *code;
	struct node* next;
	struct node* left;
	struct node* right;
};

void Push(struct node** headRef, char data) {
	struct node* newNode = malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = *headRef;
	*headRef = newNode;
}
int counts(struct node* head){
	int count=0;
	 while(head->next!=NULL){
               head=head->next;
		count++;
              }
	return count;
}


void disp(struct node* head){
        struct node* n=head;
	printf("\n");
        while(n!=0){
                printf(" %c ",n->data);
                n=n->next;
        }
	printf("\n");
	n=head;
	while(n!=0){
                printf(" %d ",n->size);
                n=n->next;
        }
}

struct node* srtins(struct node** head,char n)
{
	int t;
	struct node* h=*head;

	if(h!=NULL){
		if(n==h->data)
			h->size+=1;
		if(n < h->data){
			Push(&*head,n);
			}
		else if(n>h->data){
			while(h->next!=NULL&&n>=(h->next->data) ){
				h=h->next;
			}
			if(n==h->data){
				h->size+=1;}
			else{
			struct node* ali=malloc(sizeof(struct node));
			ali->data=n;
			ali->size=1;
			ali->next=h->next;
			h->next=ali;}
		}
	}
	else{
		*head=malloc(sizeof(struct node));
		struct node* h= *head;
		h->data=n;
		h->size=1;
		h->next=NULL;
	}
}



void SortedInsert(struct node** headRef, struct node* newNode) {

	if (*headRef == NULL || (*headRef)->size > newNode->size){
		newNode->next = *headRef;
		*headRef = newNode;
	}
	else {
		struct node* current = *headRef;
		while (current->next!=NULL &&
			 current->next->size<=newNode->size){
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
}

void InsertSort(struct node** headRef) {
	struct node* result = NULL;
	struct node* current = *headRef;
	struct node* next;
	struct node* a;

	while (current!=NULL) {
		next = current->next;
		SortedInsert(&result, current);
		current = next;
		}
	*headRef =result;

}

struct node* split(struct node* head){
	struct node* h= head;
	struct node* k;
	struct node* a;
	struct node* b;
	struct node* km;
	struct node* m=malloc(sizeof(struct node));
	int t;
	if(h->next->next!=NULL){
		k=h->next->next;
		h->next->next=NULL;}
	else{
		m->right=h->next;m->left=h;
        	m->size=h->size + h->next->size;
		InsertSort(&m);
		return m;
	}

	km=k;
	m->right=h->next;m->left=h;
	m->size=h->size + h->next->size;
	while(k->next!=NULL)
		k=k->next;
	k->next=m;
	InsertSort(&km) ;
	return km;
}
struct node* tree(struct node* head){
	struct node* h=head;
	struct node* m;
	while(h->next!=NULL){
		m=split(h);
		h=m;}
	return m;
}
struct node* assigncode(struct node* h,char* k,char* p){
	if(h!=NULL){
	h->code=malloc(sizeof(char));
	strcpy(h->code,p);
	strcat(h->code,k);
	assigncode(h->left,"0",h->code);
	assigncode(h->right,"1",h->code);}
}
void play(struct node* h)
{
        if(h!=NULL)
                printf("%c\n",h->data);
        if(h->left!=0){
		printf("left");
                play(h->left);}
        if(h->right!=0){
		printf("right");
                play(h->right);}
}
char* find(struct node* h,char a){
		char* m=malloc(sizeof(char));
		char* p=malloc(sizeof(char));
		strcpy(m,"");
		if(h!=NULL){
			if(h->data==a)
				return h->code;
			if(strcmp(m,"")!=0) return m;
			m=find(h->left,a);
			if(strcmp(m,"")!=0) return m;
			m=find(h->right,a);}


}

char* encode(struct node* h,char* a){
	char* m=malloc(sizeof(char));
	int i;
	strcpy(m,"");
	for(i=0;i<strlen(a);i++){
        	strcat(m,find(h,a[i]));
        }
	return m;
}
char* decode(struct node* h,char*a){
	int i;
	struct node* k=h;
        for(i=0;i<strlen(a);i++){
		if(a[i]=='0')
			k=k->left;
		else k=k->right;
		if(k->data){
			printf("%c",k->data);k=h;}
        }
}

main(){
	int i;
	struct node* h;
	struct node* r;
	struct node* n;
	char* m;
	char* p="000000101001101110111111111111100100010";
	char b='a';
	h=NULL;
	char *a="aaabccdeeeeeffg";
	for(i=0;i<strlen(a);i++){
	srtins(&h,a[i]);
	}
	InsertSort(&h);
	r=tree(h);
	assigncode(r,"","");
	m=encode(r,a);
	printf("%s\n",m);
	decode(r,m);
}
