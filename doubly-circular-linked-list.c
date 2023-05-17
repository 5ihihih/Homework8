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
    printf("[----- [����ȭ] [2022078036] -----]\n\n");

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

/*����Ʈ�� �ʱ�ȭ�ϴ� �Լ�*/
int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴ϶�� �Լ� freeListȣ��*/
	if(*h != NULL)
		freeList(*h);

	/* headNode�� �޸𸮸� �Ҵ��ϰ� ��ũ���� �ڱ��ڽ��� ����Ű���� �Ѵ� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/*����Ʈ�� �޸𸮸� �����ϴ� �Լ�*/
int freeList(listNode* h){
    listNode* p = h;
    listNode* prev = NULL;

    while(p != NULL){
        prev = p;
        p = p->rlink;		//���� ��带 ����Ű�� �ݺ��ϸ� �޸� ����
        free(prev);
		if(p == h) break;	//����常 ���Ҵٸ� �ݺ��� ����
    }

	free(h);				//������� �޸� ����

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

	p = h->rlink;	//ù��° ��忡 ����

	while(p != NULL && p != h) {		//�� ����Ʈ�̰ų� ������ ������ ������� ��� �ݺ��� ����
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);	//����� ���� ���


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

/*����Ʈ�� �������� ��带 �����ϴ� �Լ�*/
int insertLast(listNode* h, int key) {

    //������ ��� ����
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->llink = node->rlink = NULL;

	//�� ����Ʈ�� ��� ������ ������ ��尡 ���θ� ����Ų��
    if(h->rlink == h){
        h->llink = h->rlink = node;
        node->llink = node->rlink = h;

        return 0;
    }


    node->llink = h->llink; //������ ����� llink�� ������ ��带 ����Ų��
	node->rlink = h;        //������ ����� rlink�� ����带 ����Ų��
    h->llink->rlink = node; //������ ����� rlink�� ������ ��带 ����Ų��
    h->llink = node;        //������� llink�� ������ ��带 ����Ų��


	return 1;
}


/*����Ʈ�� ������ ��带 �����ϴ� �Լ�*/
int deleteLast(listNode* h) {
	
	//�� ����Ʈ�� ��� �Լ� ����
    if(h->rlink == h){
        printf("nothing to delete.\n");
        return 0;
    }

    listNode* p = h->rlink;

    while(p->rlink != h){    //p�� ������ ��带 ����Ű�� �Լ� ����
        p = p->rlink;
    }

    /*(������-1)����� rlink�� ����带, ������� llink�� (������-1)��带 ����Ű���� �Ѵ�*/
    p->llink->rlink = h;
    h->llink = p->llink;

    free(p);

	return 1;
}


/*����Ʈ�� ù�κп� ��带 �����ϴ� �Լ�*/
int insertFirst(listNode* h, int key) {

	//������ ��� ����
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->llink = node->rlink = NULL;

	/*�� ����Ʈ�� ��� ����带 �����ϰ� ����Ʈ�� ��� ����*/
	if(h->rlink == h){
        h->llink = h->rlink = node;
        node->llink = node->rlink = h;

        return 0;
    }

	//node�� llink�� h�� �ּ�, rlink�� ù��° ����� �ּҸ� ���´�
	//ù��° ����� llink�� node�� �ּ�, h�� rlink�� node�� �ּҸ� ���´�
    node->llink = h;
    node->rlink = h->rlink;
	h->rlink->llink = node;
	h->rlink = node;

	return 1;
}

/*����Ʈ�� ù��带 �����ϴ� �Լ�*/
int deleteFirst(listNode* h) {

	//�� ����Ʈ�� ���
    if(h->rlink == h){
        printf("nothing to delete.\n");
        return 0;
    }

    listNode* p = h->rlink; //p�� ù��° ��带 ����Ų��

    p->rlink->llink = h;    //p�� ���� ����� llink�� ����带 ����Ų��
    h->rlink = p->rlink;    //������� rlink�� p�� ���� ��带 ����Ų��
	
    free(p); //ù��° ����� �޸� ����

	return 1;

}


/*����Ʈ�� �������� ��迭�ϴ� �Լ�*/
int invertList(listNode* h) {
    if (h->rlink == h) {
        printf("nothing to invert..");
        return 0;
    }

    listNode* p = h->rlink; // invert�� ����� ���� ��带 ����Ű�� ������
    listNode* f = NULL;     // invert�� ����� ���� ��带 ����Ű�� ������
    listNode* iv = h;  	    // invert�� ��带 ����Ű�� ������

    while (p != h) {
        f = iv;
        iv = p;
        p = p->rlink; // �������� p�� h�� ����Ű�� �ǰ� while�� ����
        // invert�� �����Ѵ�
        iv->rlink = f;
        iv->llink = p;
    }
    // ������ �������� invert�Ѵ�.
    h->llink = h->rlink;
    h->rlink = iv;

    return 1;
}


/*����Ʈ�� ��带 �����ϴ� �Լ�*/
int insertNode(listNode* h, int key) {

    //������ ��带 �����ϰ� �ʱ�ȭ
    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;
    node->llink = node->rlink = NULL;

    if(h->rlink == h){  // �󸮽�Ʈ��� ������ ������ ��尡 ���θ� ����Ű���� ��
        h->llink = h->rlink = node;
        node->llink = node->rlink = h;

        return 0;
    }


    listNode* p = h->rlink; //p�� ù��° ��带 ����Ų��

    while (p != h){       //p�� ����带 ����Ű�� �ݺ��� ����
        if(p->key >= key) //������ ��庸�� ũ�ų� ���� ���� ��Ÿ���� �Լ� ����
			break;

		p = p->rlink;    
    }

    //node�� p�� ����Ű�� ����� �տ� ����
    node->llink = p->llink;
    node->rlink = p;
    p->llink->rlink = node;
    p->llink = node;

	return 0;
}


/*����Ʈ�� ��带 �����ϴ� �Լ�*/
int deleteNode(listNode* h, int key) {

	//�� ����� ��� �Լ� ����
    if(h->rlink == h){
		printf("nothing to delete.\n");
		return 0;
	}

    listNode* p = h->rlink;     //p�� ù��° ��带 ����Ų��

	while(p != h){      //p�� ����带 ����Ű�� �Լ� ����
		/*������ ��带 ã���� ���*/
		if(p->key == key){
			p->llink->rlink = p->rlink;
			p->rlink->llink = p->llink;
			free(p);
		
			return 0;
		}
		p = p->rlink; //p�� ���� ��带 ����Ű���� �Ѵ�
	}

	//���ڷ� ���� key�� �����ϴ� ���� ���� ��带 ã�� ������ ���
	printf("node not found.\n");

	return 1;
}


