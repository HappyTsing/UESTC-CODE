//û������һ��û���Һ���
//��ĳ�ڵ�û�����ӣ��������Һ��ӣ������Һ��� ����bj=false�������ڵ㶼û�к���
//cm==true ��ʾ����ȫ������
bool fullT (BTNode *b)
{
	BTNode *Qu[maxSize],*p;
	int front=rear=0;
	bool cm=true;
	bool bj=true;
	if(b==NULL)
	return true;
	rear++
	Qu[rear]=b;
	while(front!=rear) //���в���
	{
		front=(front+1)%maxSize;
		p=QU[front];
		if(p->lchild==NULL)
		{
		    bj=false;
	      	if(p->rchild!=NULL)
		         cm=false;
	    }
	    else //������ڵ� 
	    {
	    	if(!b) cm=false;  //b=FASE��ʾ�Ѿ�����ȱʧ��ڵ�����ҽڵ�������������ȫ���������������еĽڵ㶼�����ں��ӣ�
			rear=(rear+1)%maxSzie;
			QU[rear]=p->lchild;
			if(p->rchild==NULL)
			bj=false;  //�������ҽڵ�
			else{
				rear=(rear+1)%maxSize;
				Qu[rear]=p->rchild;
			} 
		}
	 } 
}
