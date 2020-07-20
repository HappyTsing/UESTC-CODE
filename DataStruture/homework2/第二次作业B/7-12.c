int sumsingle(TNODE*b)
{
   int n1,n2,n;
   if(b==NULL)
	   return 0;
   else if(b->lchild==NULL&&b->rchild!=NULL||b->lchild!=NULL&&b->rchild==NULL)
	   n=1;
   else
	   n=0;
   n1=sumsingle(b->lchild);
   n2=sumsingle(b->rchild);
   return n+n1+n2;
}