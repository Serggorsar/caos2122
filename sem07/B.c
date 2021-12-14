// Написать программу на Си, которая принимает на стандартном входном потоке несколько последовательностей целых чисел. 
// Каждая последовательность оканчивается значением 0, которое формально в эту последовательность не входит.

// Для каждой последовательности требуется отсортировать ее числа и распечатать в убывающем порядке эти числа, 
// а также частоты их встречаемости в этой последовательности.

// Для хранения чисел каждой последовательности использовать бинарное дерево.

#include <stdio.h>
#include <stdlib.h>

struct Node {
	struct Node* left;
	struct Node* right;
	int key, count;
};

struct Node* insert(struct Node *root, int input) {
	if(root == NULL) {
		root = calloc(1, sizeof(*root));
		root->left = NULL;
		root->right = NULL;
		root->key = input;
		root->count = 1;
		return root;
	}
	if(input < root->key) {
		root->left = insert(root->left, input);
	} else if(input == root->key) {
		++root->count;
	} else {
		root->right = insert(root->right, input);
	}
	return root;
}

void walk(struct Node *root) {
	if(root==NULL) {
		return;
	}
	walk(root->right);
	printf("%d: %d\n", root->key, root->count);
	walk(root->left);
}

void clear(struct Node *root) {
	if(root==NULL) {
		return;
	}
	clear(root->left);
	clear(root->right);
	free(root);
}

int main(void) {
	int input;
	struct Node* root = NULL;
	while(scanf("%d", &input) == 1){
		if(input == 0){
			walk(root);
			clear(root);
			root = NULL;
			continue;
		}
		root = insert(root, input);
	}
	walk(root);
	clear(root);
	return 0;
}
