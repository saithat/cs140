list::node *list::findnode(int i)
{
	int tmp;
	if(i == -1) return head;

	node *p = head->next;
	if(i <= (N/2))
	{
		while(i--)
		{
			p = p->next;
		}
	}
	else
	{
		p = p->prev;
		tmp = (N - (2*N)) + i;
		while(tmp != 0)
		{
			p = p->prev;
			tmp++;
		}
	}
	return p;
}
