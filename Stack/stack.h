struct Stack {
  struct Node* last_node;
  int size;
};

struct Node {
  ElemType element;
  struct Node* next;
};

void Push(struct Stack* st, ElemType el);
void Pop(struct Stack* st);
ElemType GetTop(struct Stack* st);
void ClearStack(struct Stack* st);
