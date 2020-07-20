void swap(TNODE*b,BTNODE*bnow)
{   if(b==NULL)
	   bnow=NULL;

    else
	{ bnow=(BTNODE*)malloc(sizeof(BTNODE));
      bnow->data=b->data;
	  swap(b->lchild,bnow->rchild);
	  swap(b->rchild,bnow->lchild);
	}
}
