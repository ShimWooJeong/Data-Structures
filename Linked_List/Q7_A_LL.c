//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 7 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void RecursiveReverse(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Reversed the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			RecursiveReverse(&(ll.head)); // You need to code this function
			printf("The resulting linked list after reversed the given linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

void RecursiveReverse(ListNode **ptrHead)
{
	//다음 포인터와 헤드 포인터를 변경해 재귀적으로 reverse하는 문제

	//ptrHead: 연결리스트의 헤드 노드의 메모리 주소를 가리킴
	//*ptrHead: ptrHead가 가리키는 위치의 실제 데이터(역참조)
	//**prtHead = &(ll.head), 포인터 변수의 메모리 주소를 저장
	//함수 내에서 포인터 변수의 값을 변경해야 할 때 사용
	//함수 내에서 ptrHead에 새로운 헤드 노드의 주소를 할당한다면, 외부에서는 헤드 노드의 변경이 반영되지 않음
	//**ptrHead를 사용하면 함수 내에서 ptrHead가 가리키는 포인터 값을 변경 가능

	if(*ptrHead == NULL){
		return;
	}
	
	ListNode *cur = *ptrHead; //cur: 현재 노드를 가리키는 포인터
	ListNode *post = cur->next; //post: 현재 노드의 다음 노드를 가리키는 포인터

	if((post->next) != NULL){ //*재귀 호출을 하니까 끝 노드부터 이전 노드를 가리키게 됨
		RecursiveReverse(&post);
	}
	//재귀 호출이 일어날 때마다 다음 노드를 가리키는 post가 변경됨, 연결 리스트의 끝에 도달할 때까지 반복
	//각각의 노드는 다음 노드를 가리키는 포인터 'next'를 가지고 있음

	(cur->next)->next = cur; //현재 노드의 다음 노드의 next 포인터를 현재 노드로 설정
	cur->next = NULL; //현재 노드의 다음 노드를 NULL로 설정해 역방향으로 연결된 리스트의 끝을 표시

	*ptrHead = post; //마지막으로 헤드 포인터를 역방향으로 연결된 리스트의 맨 끝 'post'로 설정해 전체 리스트를 뒤집음
}
//그럼 위 코드는 예를 들어 ll = 1->2->3->4->5 라면
//재귀가 타고, 타고 내려가면서 4에서 next인 5가 4를 가리키게 되고, 4가 가리키는 건 NULL이 됨
//그치만 그 이전 재귀에서 4가 3을 가리키게 되고, 3이 가리키는 건 NULL이 됨
//그렇게 재귀를 타고, 타고 다시 올라오면서 1까지 오게 되고 1은 NULL을 가리키게 됨
//마지막으로 post가 1이 됐으니까 그걸 HeadPointer로 설정

//그리고 cur->next를 post로 대체할 수 없는 이유는
//RecursiveReverse(&post)부분을 보면 post의 주소값을 넣어줌
//그리고 post는 오염되는 값, 그러니까 변하는 값임. 재귀 실행 이후엔 값이 바뀌어 버려서
//*post = cur->next;의 post와 재귀 이후 post는 다른 값이 되어버려서 대체할 수 없음
//+) 값이 바뀌는 건 &post를 이용한 함수 호출로 함수에서 post를 직접 변경할 수 있는 권한이 생김

//내가 원래 생각한 방식은 next = next->next로 업데이트 되면서
//next가 head를 가리키고, head가 되고
//next의 이전 노드가 next->next를 가리키게 되는 거였는데
//이건 재귀적인 접근 방식이 아니라 반복적인 접근 방식이었듬...ㅠ

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}
