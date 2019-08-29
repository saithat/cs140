void push_front(const int &din)
{
	node *p = new node(din);
	
	p->next = head->next;
	head->next = p;

	N++;
}
void pop_front()
{
	node *p;

	p = head->next;
	head->next = p->next;

	delete p;

	N--;

}
const int & front()
{
	node *p = head->next;
	return p->data;
}
