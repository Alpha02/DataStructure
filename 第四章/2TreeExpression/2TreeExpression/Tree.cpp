#include <iostream>
using namespace std;
class NoParent{};
class treeMisMatch{};
bool getPriority(char ch){
	if(ch=='*' || ch=='/')return 1;
	return 0;
}
class treeNode{
public:
	char my_char;
	treeNode * child_L;
	treeNode * child_R;
	treeNode * parent;
	bool LR;
	void replace(treeNode* target){
		child_L=target->child_L;
		child_R=target->child_R;
		if(child_L)child_L->parent=this;
		if(child_R)child_R->parent=this;
		my_char=target->my_char;
	}
	bool getLR(){
		if(!parent)throw NoParent();
		if(parent->child_L==this)return 0;
		if(parent->child_R==this)return 1;
		throw treeMisMatch();
	}
	treeNode(char ch,treeNode * pr=NULL,bool newLR=0){
		parent=pr;
		my_char=ch;
		child_L=NULL;
		child_R=NULL;
		LR=newLR;
		if(parent){
			if(LR)parent->child_R=this;
			else parent->child_L=this;
		}
	}
	void setChild(bool LR,treeNode * new_child){
		if(LR)child_R=new_child;
		else child_L=new_child;
		new_child->parent=this;
	}
	int countLeaves(int max_depth=-1){
		if((max_depth<0) && (child_L==NULL && child_R==NULL))return 1;
		if(max_depth==0)return 1;
		int res=0;
		if(child_L)res+=child_L->countLeaves(max_depth-1);
		if(child_R)res+=child_R->countLeaves(max_depth-1);
		return res;
	}
	void MirrorChild(){
		treeNode * child_tmp=child_L;
		child_L=child_R;
		child_R=child_tmp;
		if(child_L){
			child_L->LR=0;
			child_L->MirrorChild();
		}
		if(child_R){
			child_R->LR=1;
			child_R->MirrorChild();
		}
	}
	int getWidth(){
		int width=0;
		int i=0;
		int width_temp;
		do{
			width_temp=countLeaves(i);
			if(width_temp>width)width=width_temp;
			i++;
		}while(width_temp>0);
		return width;
	}
};

treeNode * the_root;
void buildWholeTreeFrom(treeNode * node_root,istream & in);
void buildTree(treeNode *node_a,istream & in,int pre_prio=0){
	bool priority;
	char op=in.get();
	if(op==')' || in.eof())return;
	if(op=='\n'){
		return;
	}
	char ch=in.get();
	priority=getPriority(op);

	if(priority>pre_prio){
		treeNode * left_node=new treeNode(node_a->my_char);
		left_node->replace(node_a);
		node_a->setChild(0,left_node);
		node_a->my_char=op;
		treeNode * right_node=new treeNode(ch,node_a,1);
		if(ch=='('){
			buildWholeTreeFrom(right_node,in);
		}
		buildTree(right_node,in,priority);
	}else{
		while(node_a->LR){
			node_a=node_a->parent;
		}
		treeNode * root_node=new treeNode(op);
		root_node->setChild(0,node_a);
		treeNode * right_node=new treeNode(ch,root_node,1);
		if(ch=='('){
			buildWholeTreeFrom(right_node,in);
		}
		buildTree(right_node,in,priority);
	}
}
treeNode * getRoot(treeNode * node){
	while(node->parent){
		node=node->parent;
	}
	return node;
}
void buildWholeTreeFrom(treeNode * node_root,istream & in){
	char ch=in.get();
	treeNode * new_root=new treeNode(ch);
	if(ch=='('){
		buildWholeTreeFrom(new_root,in);
	}
	buildTree(new_root,in,0);
	new_root=getRoot(new_root);
	if(node_root->my_char=='('){
		node_root->replace(new_root);
	}
}
void DrawTree(treeNode * node,int depth=0){
	if(!node)return;
	DrawTree(node->child_R,depth+1);
	for(int i=0;i<depth;i++){
		cout<<"   ";
	}
	cout<<node->my_char<<endl;
	DrawTree(node->child_L,depth+1);
}
void visit(treeNode * node){
	cout<<node->my_char<<' ';
}
void VisitByLevel(treeNode * root){
	const int maxsize=100;
	treeNode * nodelist[maxsize];
	int head=0;
	int tail=1;
	nodelist[head]=root;
	while(head!=tail){
		treeNode * node_temp=nodelist[head];
		visit(node_temp);
		if(node_temp->child_L){
			nodelist[tail++]=node_temp->child_L;
			if(tail>=maxsize)tail=0;
		}
		if(node_temp->child_R){
			nodelist[tail++]=node_temp->child_R;
			if(tail>=maxsize)tail=0;
		}
		head++;
		if(head>=maxsize)head=0;
	}
	cout<<endl;	
}
int main(){
	while(1){
		treeNode nodeA('(');
		buildWholeTreeFrom(&nodeA,cin);
		treeNode * root=getRoot(&nodeA);
		DrawTree(root);
		cout<<"Leaves number:"<<root->countLeaves()<<endl;
		cout<<"Tree Width:"<<root->getWidth()<<endl;
		cout<<"Travel by level:";
		VisitByLevel(root);
		cout<<"MirrorLR:"<<endl;
		root->MirrorChild();
		DrawTree(root);

	}

}