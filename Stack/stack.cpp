

void Push(struct Stack* st, ElemType el) {
  assert(st);
  if (st->size == 0) {
    st->last_node = (Node*)calloc(1, sizeof(struct Node));
    st->last_node->element = el;
    st->last_node->next = NULL;
  } else {
    struct Node* new_node = (Node*)calloc(1, sizeof(struct Node));
    new_node->element = el;
    new_node->next = st->last_node;
    st->last_node = new_node;
  }
  st->size++;
}

void Pop(struct Stack* st) {
  assert(st);
  assert(st->size > 0);
  struct Node* old_node = st->last_node;
  st->last_node = st->last_node->next;
  free(old_node);
  st->size--;
}

ElemType GetTop(struct Stack* st) {
  assert(st);
  assert(st->size > 0);
  return st->last_node->element;
}

void ClearStack(struct Stack* st) {
  while (st->size > 0) {
    Pop(st);
  }
  //free(st);
}
