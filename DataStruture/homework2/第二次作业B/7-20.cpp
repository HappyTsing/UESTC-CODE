//没有左孩子一定没有右孩子
//若某节点没有左孩子（无左定无右孩子）或者右孩子 ，置bj=false，则后面节点都没有孩子
//cm==true 表示是完全二叉树
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
	while(front!=rear) //队列不空
	{
		front=(front+1)%maxSize;
		p=QU[front];
		if(p->lchild==NULL)
		{
		    bj=false;
	      	if(p->rchild!=NULL)
		         cm=false;
	    }
	    else //存在左节点 
	    {
	    	if(!b) cm=false;  //b=FASE表示已经存在缺失左节点或者右节点的情况，若是完全二叉树接下来所有的节点都不存在孩子；
			rear=(rear+1)%maxSzie;
			QU[rear]=p->lchild;
			if(p->rchild==NULL)
			bj=false;  //不存在右节点
			else{
				rear=(rear+1)%maxSize;
				Qu[rear]=p->rchild;
			} 
		}
	 } 
}
