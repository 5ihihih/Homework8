#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);
int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);
void printList(listNode* h);

int main()
{
    printf("[----- [오인화] [2022078036] -----]\n\n");

	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/*리스트를 초기화하는 함수*/
int initialize(listNode** h) {

	/* headNode가 NULL이 아니라면 함수 freeList호출*/
	if(*h != NULL)
		freeList(*h);

	/* headNode에 메모리를 할당하고 링크들이 자기자신을 가리키도록 한다 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/*리스트의 메모리를 해제하는 함수*/
int freeList(listNode* h){
    listNode* p = h;
    listNode* prev = NULL;

    while(p != NULL){
        prev = p;
        p = p->rlink;		//다음 노드를 가리키길 반복하며 메모리 해제
        free(prev);
		if(p == h) break;	//헤드노드만 남았다면 반복문 종료
    }

	free(h);				//헤드노드의 메모리 해제

	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;	//첫번째 노드에 접근

	while(p != NULL && p != h) {		//빈 리스트이거나 마지막 노드까지 출력했을 경우 반복문 종료
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);	//노드의 개수 출력


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

/*리스트의 마지막에 노드를 삽입하는 함수*/
int insertLast(listNode* h, int key) {

    //삽입할 노드 생성
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->llink = node->rlink = NULL;

	//빈 리스트인 경우 헤드노드와 삽입할 노드가 서로를 가리킨다
    if(h->rlink == h){
        h->llink = h->rlink = node;
        node->llink = node->rlink = h;

        return 0;
    }


    node->llink = h->llink; //삽입할 노드의 llink가 마지막 노드를 가리킨다
	node->rlink = h;        //삽입할 노드의 rlink가 헤드노드를 가리킨다
    h->llink->rlink = node; //마지막 노드의 rlink가 삽입할 노드를 가리킨다
    h->llink = node;        //헤드노드의 llink가 삽입할 노드를 가리킨다


	return 1;
}


/*리스트의 마지막 노드를 삭제하는 함수*/
int deleteLast(listNode* h) {
	
	//빈 리스트일 경우 함수 종료
    if(h->rlink == h){
        printf("nothing to delete.\n");
        return 0;
    }

    listNode* p = h->rlink;

    while(p->rlink != h){    //p가 마지막 노드를 가리키면 함수 종료
        p = p->rlink;
    }

    /*(마지막-1)노드의 rlink가 헤드노드를, 헤드노드의 llink가 (마지막-1)노드를 가리키도록 한다*/
    p->llink->rlink = h;
    h->llink = p->llink;

    free(p);

	return 1;
}


/*리스트의 첫부분에 노드를 삽입하는 함수*/
int insertFirst(listNode* h, int key) {

	//삽입할 노드 생성
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->llink = node->rlink = NULL;

	/*빈 리스트일 경우 헤드노드를 선언하고 리스트에 노드 삽입*/
	if(h->rlink == h){
        h->llink = h->rlink = node;
        node->llink = node->rlink = h;

        return 0;
    }

	//node의 llink가 h의 주소, rlink가 첫번째 노드의 주소를 갖는다
	//첫번째 노드의 llink가 node의 주소, h의 rlink가 node의 주소를 갖는다
    node->llink = h;
    node->rlink = h->rlink;
	h->rlink->llink = node;
	h->rlink = node;

	return 1;
}

/*리스트의 첫노드를 삭제하는 함수*/
int deleteFirst(listNode* h) {

	//빈 리스트일 경우
    if(h->rlink == h){
        printf("nothing to delete.\n");
        return 0;
    }

    listNode* p = h->rlink; //p가 첫번째 노드를 가리킨다

    p->rlink->llink = h;    //p의 다음 노드의 llink가 헤드노드를 가리킨다
    h->rlink = p->rlink;    //헤드노드의 rlink가 p의 다음 노드를 가리킨다
	
    free(p); //첫번째 노드의 메모리 해제

	return 1;

}


/*리스트를 역순으로 재배열하는 함수*/
int invertList(listNode* h) {
    if (h->rlink == h) {
        printf("nothing to invert..");
        return 0;
    }

    listNode* p = h->rlink; // invert할 노드의 다음 노드를 가리키는 포인터
    listNode* f = NULL;     // invert할 노드의 이전 노드를 가리키는 포인터
    listNode* iv = h;  	    // invert할 노드를 가리키는 포인터

    while (p != h) {
        f = iv;
        iv = p;
        p = p->rlink; // 마지막은 p가 h를 가리키게 되고 while문 종료
        // invert를 수행한다
        iv->rlink = f;
        iv->llink = p;
    }
    // 헤드노드는 마지막에 invert한다.
    h->llink = h->rlink;
    h->rlink = iv;

    return 1;
}


/*리스트에 노드를 삽입하는 함수*/
int insertNode(listNode* h, int key) {

    //삽입할 노드를 생성하고 초기화
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->llink = node->rlink = NULL;

    if(h->rlink == h){  // 빈리스트라면 헤드노드와 삽입할 노드가 서로를 가리키도록 함
        h->llink = h->rlink = node;
        node->llink = node->rlink = h;

        return 0;
    }


    listNode* p = h->rlink; //p가 첫번째 노드를 가리킨다

    while (p != h){       //p가 헤드노드를 가리키면 반복문 종료
        if(p->key >= key) //삽입할 노드보다 크거나 같은 값이 나타나면 함수 종료
			break;

		p = p->rlink;    
    }

    //node를 p가 가리키는 노드의 앞에 삽입
    node->llink = p->llink;
    node->rlink = p;
    p->llink->rlink = node;
    p->llink = node;

	return 0;
}


/*리스트의 노드를 삭제하는 함수*/
int deleteNode(listNode* h, int key) {

	//빈 노드일 경우 함수 종료
    if(h->rlink == h){
		printf("nothing to delete.\n");
		return 0;
	}

    listNode* p = h->rlink;     //p가 첫번째 노드를 가리킨다

	while(p != h){      //p가 헤드노드를 가리키면 함수 종료
		/*삭제할 노드를 찾았을 경우*/
		if(p->key == key){
			p->llink->rlink = p->rlink;
			p->rlink->llink = p->llink;
			free(p);
		
			return 0;
		}
		p = p->rlink; //p가 다음 노드를 가리키도록 한다
	}

	//인자로 받은 key에 대응하는 값을 가진 노드를 찾지 못했을 경우
	printf("node not found.\n");

	return 1;
}


