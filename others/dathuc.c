#include <stdio.h>
#include <stdlib.h>

typedef struct _Polynom {
	int coeff;
	int pow;
	struct _Polynom *next;
} Polynom;

Polynom *makeNode(int co, int po){
	Polynom *p = (Polynom*) malloc(sizeof(Polynom));
	if(p==NULL){printf("Error in mem allocation\n");exit(1);}
	p->coeff=co;
	p->pow=po;
	p->next=NULL;
	return p;
}

void printList(Polynom *h){
	Polynom *p=h;
	while(p != NULL){
		printf("%d_%d ",p->coeff,p->pow);
		p = p->next;
	}
	printf("\n");
}

Polynom *insertHead(Polynom *h,int co, int po){
	Polynom* q = makeNode(co,po);

	if(h == NULL){
		return q;
	}
	
	q->next = h;
	return q;
}

Polynom *removeHead(Polynom *h){
	if(h==NULL) return NULL;
	
	Polynom* q = h->next;

	free(h);
	
	return q;
}

Polynom *SumTwoPol(Polynom *px, Polynom *qx){
	if(px==NULL && qx==NULL) return NULL;
	Polynom *dsdaura=NULL;
	
	Polynom *p=px,*q=qx,*ptr=NULL,*node=dsdaura;
	
	while(p!=NULL && q!=NULL){
		node=makeNode(0,0);

		if (p->pow > q->pow ) {
			node->coeff=q->coeff;
			node->pow=q->pow;
			q=q->next;
		}
		else if ( p->pow < q->pow )
		{
			node->coeff=p->coeff;
			node->pow=p->pow;
			p=p->next;
		}		
		else
		{
			if(p->coeff+q->coeff != 0){
				node->coeff=p->coeff+q->coeff;
				node->pow=q->pow;
			}
			else{
				if(q->pow==0){
					node->coeff=0;
					node->pow=q->pow;
				} else {
					free(node);
					node=NULL;
				}
			}
			
			p=p->next;
			q=q->next;
		}
		
		if(node!=NULL){
			if(ptr!=NULL) ptr->next=node;
			ptr = node;
			if(dsdaura==NULL) dsdaura = node;
		}
		
		
		
	} //end of while
	
	if (p==NULL)
	{ 		
		while(q!=NULL){
			if(q->coeff==0) q=q->next;
			else{
				node=makeNode(0,0);
				ptr->next=node; 
				node->coeff=q->coeff; 
				node->pow=q->pow;
				q=q->next;
				ptr=node; 
			}
		} 
	}
	
	if (q==NULL)
	{ 		
		while(p!=NULL){
			if(p->coeff==0) p=p->next;
			else{
				node=makeNode(0,0);
				ptr->next=node;
				node->coeff=p->coeff; 
				node->pow=p->pow;
				p=p->next;
				ptr=node; 
			}
		} 
	}
	
	if(dsdaura==NULL) dsdaura = makeNode(0,0);		
	
	return dsdaura;
}

int main(){
	Polynom *px=NULL,*qx=NULL;
	
	//case 1
	/*
	px = insertHead(px,1,4);
	px = insertHead(px,-1,3);
	px = insertHead(px,1,2);
	px = insertHead(px,2,1);
	px = insertHead(px,1,0);	
	printList(px);	
	printf("\n");
	qx = insertHead(qx,-1,3);
	qx = insertHead(qx,-1,2);
	qx = insertHead(qx,-2,1);
	qx = insertHead(qx,-1,0);	
	printList(qx);
	*/
	
	//case 2
	/*
	px = insertHead(px,1,1);
	px = insertHead(px,1,0);
	printList(px);
	printf("\n");
	qx = insertHead(qx,-1,1);
	qx = insertHead(qx,-1,0);
	printList(qx);
	*/
	
	//case 3
	px = insertHead(px,1,2);
	px = insertHead(px,1,1);
	printList(px);
	printf("\n");
	qx = insertHead(qx,-1,2);
	qx = insertHead(qx,-1,1);
	printList(qx);
	
	Polynom *dttong=SumTwoPol(px,qx);
	printf("\n");
	printList(dttong);
	
	return 0;
}
