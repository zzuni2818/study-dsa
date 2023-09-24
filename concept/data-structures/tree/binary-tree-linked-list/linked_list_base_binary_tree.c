#include <stdio.h>
#include <stdlib.h>

struct BTreeNode {
	int data;
	struct BTreeNode *left;
	struct BTreeNode *right;
};

struct BTreeNode *make_btree_node();
int get_data(struct BTreeNode *bt);
void set_data(struct BTreeNode *bt, int data);

struct BTreeNode *get_left_sub_tree(struct BTreeNode *bt);
struct BTreeNode *get_right_sub_tree(struct BTreeNode *bt);

void make_left_sub_tree(struct BTreeNode *main, struct BTreeNode *sub);
void make_right_sub_tree(struct BTreeNode *main, struct BTreeNode *sub);

//traverse
void preorder_traverse(struct BTreeNode *bt);
void inorder_traverse(struct BTreeNode *bt);
void postorder_traverse(struct BTreeNode *bt);

int main()
{
	struct BTreeNode *bt1 = make_btree_node();
	struct BTreeNode *bt2 = make_btree_node();
	struct BTreeNode *bt3 = make_btree_node();
	struct BTreeNode *bt4 = make_btree_node();
	
	set_data(bt1, 1);
	set_data(bt2, 2);
	set_data(bt3, 3);
	set_data(bt4, 4);

	make_left_sub_tree(bt1, bt2);
	make_right_sub_tree(bt1, bt3);
	make_left_sub_tree(bt2, bt4);

	printf("expect: 2 3 4\n");
	printf("%d\n", get_data(get_left_sub_tree(bt1)));
	printf("%d\n", get_data(get_right_sub_tree(bt1)));
	printf("%d\n", get_data(get_left_sub_tree(get_left_sub_tree(bt1))));

	
	printf("preorder traverse, expect 1 2 4 3\n");
	preorder_traverse(bt1);
	printf("\n");

	printf("inorder traverse, expect 4 2 1 3\n");
	inorder_traverse(bt1);
	printf("\n");

	printf("postorder traverse, expect: 4 2 3 1\n");
	postorder_traverse(bt1);
	printf("\n");


	return 0;
}

struct BTreeNode *make_btree_node()
{
	struct BTreeNode *nd = (struct BTreeNode*) malloc(sizeof(struct BTreeNode));
	nd->left = NULL;
	nd->right = NULL;

	return nd;
}
int get_data(struct BTreeNode *bt)
{
	return bt->data;
}
void set_data(struct BTreeNode *bt, int data)
{
	bt->data = data;
}

struct BTreeNode *get_left_sub_tree(struct BTreeNode *bt)
{
	return bt->left;
}
struct BTreeNode *get_right_sub_tree(struct BTreeNode *bt)
{
	return bt->right;
}

void make_left_sub_tree(struct BTreeNode *main, struct BTreeNode *sub)
{
	if(main->left != NULL) {
		free(main->left);
	}

	main->left = sub;
}
void make_right_sub_tree(struct BTreeNode *main, struct BTreeNode *sub)
{
	if(main->right != NULL) {
		free(main->right);
	}

	main->right = sub;
}
void preorder_traverse(struct BTreeNode *bt)
{
	if(bt == NULL) {
		return;
	}
	
	printf("%d ", bt->data);
	preorder_traverse(bt->left);
	preorder_traverse(bt->right);
}
void inorder_traverse(struct BTreeNode *bt)
{
	if(bt == NULL) {
		return;
	}
	
	inorder_traverse(bt->left);
	printf("%d ", bt->data);
	inorder_traverse(bt->right);
}
void postorder_traverse(struct BTreeNode *bt)
{
	if(bt == NULL) {
		return;
	}

	postorder_traverse(bt->left);
	postorder_traverse(bt->right);
	printf("%d ", bt->data);
}
