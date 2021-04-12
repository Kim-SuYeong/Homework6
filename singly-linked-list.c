#include<stdio.h>
#include<stdlib.h>

typedef struct Node {   //연결 리스트의 노드 정의
	int key;
	struct Node* link; //다음 노드의 주소값 가리킴 
} listNode;

typedef struct Head {   //리스트의 헤드 노드(연결 리스트의 가장 맨 처음 부분) 정의
	struct Node* first;  //연결 리스트의 첫 번째 노드를 가리킴
}headNode;

headNode* initialize(headNode* h); //헤드노드에 대한 메모리 할당 후 리턴하는 함수
int freeList(headNode* h); //저장된 노드들의 모든 메모리 해제 함수

int insertFirst(headNode* h, int key); //가장 맨 앞의 노드에 key값을 저장하는 함수
int insertNode(headNode* h, int key); //key값에 따라 오름차순으로 노드에 key값을 저장하는 함수
int insertLast(headNode* h, int key); //가장 맨 뒤의 노드에 key값을 저장하는 함수

int deleteFirst(headNode* h); //가장 맨 앞의 노드를 삭제하는 함수
int deleteNode(headNode* h, int key); //입력받은 key값을 데이터 영역에 갖고 있는 노드를 삭제하는 함수
int deleteLast(headNode* h); //가장 맨 뒤의 노드를 삭제하는 함수
int invertList(headNode* h); //노드들을 순서를 바꾸어 정렬하는 함수

void printList(headNode* h); //노드들을 출력하는 함수

int main()
{
	printf("-----------------[김수영]------[2020039042]-----------------");
	char command;
	int key;
	headNode* headnode=NULL; //헤드노드를 NULL로 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) 
{
	if(h != NULL) //headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
		freeList(h);

	headNode* temp = (headNode*)malloc(sizeof(headNode)); //헤드노드 temp를 선언하면서 메모리를 할당함
	temp->first = NULL; //리스트의 처음을 NULL로 초기화
	return temp; //headNode에 대한 메모리를 할당한 것을 리턴
}

int freeList(headNode* h)
{
	listNode* p = h->first; //연결 리스트 노드 p에 리스트의 처음을 저장하면서 선언

	listNode* prev = NULL; //prev : 삭제할 노드의 선행 노드를 가리키는 포인터
	while(p != NULL) {
		prev = p; //포인터 p를 prev에 저장
		p = p->link; //p가 가리키는 주소를 p에 저장
		free(prev); //가장 맨 앞의 노드부터 맨 마지막 노드 순으로 노드 해제
	}
	free(h); //헤드노드도 해제
	return 0;
}



//list 처음에 key에 대한 노드하나를 추가
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //노드 하나를 메모리 할당을 받아서 생성
	node->key = key; //노드의 키에 키 값 저장

	node->link = h->first; // ==(node->link = NULL;)
	h->first = node; //리스트 가장 맨 앞의 노드로 node를 지정

	return 0;
}


//리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertNode(headNode* h, int key) 
{	
	listNode* keysearch = (listNode*)malloc(sizeof(listNode)); //key값을 비교해나갈 keysearch 노드를 메모리 할당 받아서 생성
	keysearch->key = key; //keysearch의 데이터 영역에 key값 저장
	keysearch->link = NULL; //keysearch가 가리키는 주소를 NULL로 지정
	listNode* compare = h->first; //compare : keysearch와 key값을 비교할 노드
	if (keysearch->key < h->first->key) //입력받은 노드의 key의 개수가 1개일 때
    {
        keysearch->link = h->first;
        h->first = keysearch;
    }
    else //입력받은 노드의 key의 개수가 2개 이상일 때
	{
		while (1)
			{
				if (compare->link == NULL) //아무것도 없을 때
				{
					compare->link = keysearch; //compare가 가리키는 주소를 keysearch로 지정 = keysearch가 가장 맨 처음의 노드가 됨
					break; //break로 반복문 탈출
				}
				else if (keysearch->key < compare->link->key) //입력받은 key값보다 기존의 노드의 key값이 작을 때까지 다음 과정 반복
				{
					keysearch->link = compare->link; //기존의 노드가 가리키는 주소를 keysearch가 가리키게 함
					compare->link = keysearch; //compare는 keysearch의 선행 노드가 됨
					break; //break로 반복문 탈출
				}
				compare = compare->link; //입력받은 key값보다 더 큰 기존의 key값이 없을 경우
			}
	}
	return 0;
}


//list에 key에 대한 노드하나를 추가
int insertLast(headNode* h, int key) 
{
	listNode* cup; //임의의 노드 cup 생성
	listNode* new = (listNode*)malloc(sizeof(listNode)); //마지막 노드인 new를 메모리 할당받아 생성
	new->key = key; //마지막 노드에 키 값을 저장
	new->link = NULL; //가리키는 주소의 값을 NULL로 지정
	cup = h->first; //처음부터 비교하기 위해 헤드노드를 cup에 저장함
	while(cup->link != NULL) //cup이 가리키는 주소값이 NULL일 때까지 반복
	{
		cup = cup->link; //cup이 가리키는 주소를 cup에 저장
		                //배열이 인덱스를 하나씩 증가해 나가는 것처럼 증가 -> cup[i++]
	}
	cup->link = new; //cup이 가리키는 주소가 NULL이면 반복문을 나와서 cup이 가리키는 주소를 마지막 노드로 지정
	return 0;
}



//list의 첫 번째 노드 삭제
int deleteFirst(headNode* h) 
{	
	listNode* begin = h->first; //삭제할 노드(첫 번째 노드)
	if(h->first == NULL) //빈 리스트이면 에러 메세지 출력
	{
		printf("error!\n");
	}
	h->first = h->first->link; //첫 번째 노드가 다음 노드(새로운 첫 번째 노드)를 가리키게 함
	free(begin); //첫 번째 노드 메모리 해제
	return 0;
}


//list에서 key에 대한 노드 삭제
int deleteNode(headNode* h, int key) 
{
	listNode* trail = h->first; //trail은 search의 전 노드
	listNode* search = h->first; //trail과 search에 리스트의 처음을 저장함
	while(search->key != key) //입력한 키값과 같은 값을 갖고 있는 노드를 찾을 때까지 반복
	{
		search = search->link; //search가 가리키는 주소를 search에 저장 -> 배열의 인덱스를 증가시키면서 나아가는 것과 비슷
	}
	trail->link = search->link; //메모리 해제 전, search가 가리키던 주소를 trail이 가리키게 함
	free(search); //찾은 노드의 메모리 해제
	return 0;
}

//list의 마지막 노드 삭제
int deleteLast(headNode* h) 
{
	listNode* old; // 삭제할 노드(마지막 노드)
	listNode* trail; //삭제할 노드(마지막 노드)의 선행 노드를 가리키는 노드
	if(h->first == NULL) //빈 리스트이면 에러 메세지 출력
	{
		printf("error!\n");
	}
	trail = h->first; //==(trail = NULL;)
	old = h->first->link; //old에 헤드노드가 가리키는 주소값을 저장
	while(old->link != NULL) //삭제하고자 하는 노드가 가리키는 주소가 NULL일 때까지 반복
	{
		trail = old; 
		old = old->link; //old가 가리키는 주소를 old에 저장 -> 배열의 인덱스를 증가시키면서 나아가는 것과 비슷
	}
	free(old); //NULL이면(=마지막 노드이면) 해당 노드를 메모지 해제하여 삭제
	trail->link = NULL; //trail이 가장 마지막 노드가 되므로 NULL을 가리키게 함
	return 0;
}


//리스트의 링크를 역순으로 재 배치
int invertList(headNode* h) 
{
	listNode* middle = NULL; //공백 노드 middle 생성 -> lead의 이전 노드
	listNode* trail; //trail : middle의 이전 노드
	listNode* lead = h->first; //현재 노드 
	while(lead != NULL) //현재 노드(반전이 되면 가장 맨 끝의 노드가 됨)가 NULL을 가리킬 때까지 반복
	{
		trail = middle; //trail을 middle쪽으로 이동
		middle = lead; //middle을 lead쪽으로 이동
		lead = lead->link; //lead를 다음 링크로 이동
		middle->link = trail; //middle이 middle의 이전 노드인 trail을 가리킴
	}
	h->first = middle; //현재 노드가 현재 노드의 이전 노드인 middle을 가리킴
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p; //리스트 노드 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) { //헤드노드가 비어있으면 Nothing to print....출력
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //리스트 노드에 맨 처음 노드 저장

	while(p != NULL) { //p가 가리키는 주소가 NULL일 때까지 반복
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i); //입력받은 키의 수 출력
}
