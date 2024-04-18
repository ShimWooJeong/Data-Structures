//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next; //포인터 변수 next, 다음 노드를 가리키는 듯
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size; //연결 리스트의 크기?
	ListNode *head; //헤더 노드
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll; //linked list 구조체
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			//removeAllItems(&ll);
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

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	/*
	item 입력받고 linked list에 오름차순으로 삽입
	현재 linked list에 이미 있는 정수면 삽입할 수 없음
	return: 새 항목이 추가된 index 위치 반환, 삽입할 수 없으면 -1 반환
	*/
	ListNode *newNode = malloc(sizeof(ListNode)); //새로운 노드 동적 할당
	newNode->item = item;
	newNode->next = NULL;

	//연결 리스트 순회하면서 이미 있는 정수인지 check하는 과정
	ListNode *check = ll->head;
	while(check != NULL){ //이거 왜 밑에 current 안에 if문으로 판단하는 건 안 되는거지???ㅠ 따로 빼니까 됨;;
		if(check->item == item){ //이미 존재하는 item이므로 -1 반환
			free(newNode); //할당 해제
			return -1;
		}
		check = check->next;
	}

	//삽입할 값이 연결 리스트에 있는 값들보다 작을 때, 연결 리스트의 Head가 됨
	if(ll->size == 0 || item <= ll->head->item){ //연결 리스트가 비어있거나 넣을 값이 head보다 작은 경우
		newNode->next = ll->head; //새 노드의 next를 head로 연결
		ll->head = newNode; //head를 newNode로
		ll->size++; //연결 리스트 size+1
		return 0; //헤드에 삽입 완료
	}

	//연결 리스트가 비어있지 않거나, item이 head보다 큰 경우,, 올바른 위치를 찾아감
	ListNode *current = ll->head; //current = 연결 리스트의 head 노드
	while(current->next != NULL && current->next->item < item){
		//head 노드부터 시작해서 다음 노드가 존재하고,
		//다음 노드의 item이 삽입하려는 아이템보다 작을 때 while문 반복
		current = current->next;
	}
	//결과: current는 삽입하려는 item보다 큰 값을 가진 노드의 이전 노드가 됨
	//그러니까 current는 newNode에 연결 & newNode는 current->next에 연결해서 삽입

	newNode->next = current->next;
	current->next = newNode;
	ll->size++;

	int index = 1;
	//인덱스 반환 부분, 만나기 전까지 반복하니까 처음 index값을 1로 초기화
	ListNode *current_ = ll->head;
	while(current_->next != newNode){ //연결 리스트 순회하면서 newNode 만나기 전까지 ++
		current_ = current_->next;
		index++;
	}
	return index;

}

///////////////////////////////////////////////////////////////////////////////////

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


ListNode *findNode(LinkedList *ll, int index){

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
	// 연결 리스트의 헤더 노드가 비어있거나, 값을 넣으려는 index 위치가 0일 때 head pointer 업데이트
	if (ll->head == NULL || index == 0){
		cur = ll->head; // 연결 리스트의 head 노드
		ll->head = malloc(sizeof(ListNode)); // head 노드 동적 할당
		ll->head->item = value; // head 노드의 값에 value 값 넣어줌
		ll->head->next = cur; // head 노드에 다음 노드를 가리키는 걸 cur로
		ll->size++; // 연결리스트 크기 +1
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	// 값을 넣으려는 index 전에 노드가 NULL이 아니라면, 그니까 연결 리스트가 비어있지 않은 상태겠지??
	if ((pre = findNode(ll, index - 1)) != NULL){ // pre = 이전 노드
		cur = pre->next; // 이전 노드의 next를 가리키는 부분
		pre->next = malloc(sizeof(ListNode)); // 동적 할당
		pre->next->item = value; // 이전 노드의 next.item에 value 값 넣어줌
		pre->next->next = cur; //이전 노드의 next의 next를 cur로
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
