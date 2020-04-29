#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSERT 0x100
#define FIND   0x200

struct node {
	int data;
	struct node *left;
	struct node *right;
	int level;
	int name;
	char dataset[128];
} ; 

struct node root;

struct node *alloc_node(int data)
{
	struct node *nodeptr;
	nodeptr = (struct node *) malloc(sizeof(struct node));
	if (nodeptr == NULL)
		exit(1);
	nodeptr->data = data;
	nodeptr->left = NULL;
	nodeptr->right = NULL;
	nodeptr->level = 0;
	return nodeptr;
}

struct node *add_node(int data)
{
	static int rl = 0;
	struct node *nodeptr;
	struct node *ptr = (struct node *) &root;
	int level = 1;

	nodeptr = alloc_node(data);

	if (!(rl % 2)) {
leftT:
		if (ptr->left == NULL)
		{
			ptr->left = nodeptr;
			nodeptr->level = level;
			nodeptr->dataset[0] = '\0';
		}
		else if (ptr->right == NULL)
		{
			ptr->right = nodeptr;
			nodeptr->level = level;
			nodeptr->dataset[0] = '\0';
		}
		else
		{
			ptr = ptr->left;
			level++;
			goto leftT;
		}
	} else {
rightT:
		if (ptr->right == NULL)
		{
			ptr->right = nodeptr;
			nodeptr->level = level;
			nodeptr->dataset[0] = '\0';
		}
		else if (ptr->left == NULL)
		{
			ptr->left = nodeptr;
			nodeptr->level = level;
			nodeptr->dataset[0] = '\0';
		}
		else
		{
			ptr = ptr->right;
			level++;
			goto rightT;
		}
	}

	rl++;

	return (nodeptr);
}

struct node *result = NULL;

struct node *find_element_and_insert_data(struct node *nodeptr, struct node *parent, int name, void *data, int size, int fori)
{
	if (!nodeptr)
		return 0;


	find_element_and_insert_data(nodeptr->left, nodeptr, name, data, size, fori);

	switch(fori) {

	case INSERT :
		if (nodeptr->data == name)
		{
			memcpy(nodeptr->dataset, data, size);
			return 0;
		}
		break;

	case FIND   :
		if (nodeptr->data == name)
		{
			result = nodeptr;
			return 0;
		}
		break;

	default :
		break;
	}

	find_element_and_insert_data(nodeptr->right, nodeptr, name, data, size, fori);

	return result;

}

char buf[1024];
char dataset[] =  "zerofind this";
char dataset1[] = "one find this";
char dataset2[] = "two find this";
char dataset3[] = "threfind this";
char dataset4[] = "fourfind this";

int print_tree(struct node *nodeptr, char *helpstr, struct node *parent)
{
	int ii;


	if (!nodeptr)
		return 0;


	print_tree(nodeptr->left, "LEFT", nodeptr);

	buf[0] = '\0';

	for (ii = 0; ii < nodeptr->level; ii++)
		strcat(buf,"    ");

	if (!strcmp(helpstr,"LEFT"))
	{
		printf("%s%5d %d %s lev=%d ***->%s\n", buf, parent->data, nodeptr->data, helpstr, nodeptr->level, nodeptr->dataset);
	}
	else if (!strcmp(helpstr, "RIGHT"))
	{
		printf("%s%5d %d %s lev=%d ***->%s\n", buf, parent->data, nodeptr->data, helpstr, nodeptr->level, nodeptr->dataset);
	}
	else 
		printf("%d %d %s lev=%d\n", parent->data, nodeptr->data, helpstr, 0);

	print_tree(nodeptr->right, "RIGHT", nodeptr);

	return 0;

}

void print_node(struct node *nodeptr)
{
	printf("%d level=%d data=%s\n", nodeptr->data, nodeptr->level, nodeptr->dataset);
}
	

int main(int argc, char *argv[])
{
	struct node *nodeptr;

	root.data = 100;
	root.left = NULL;
	root.right = NULL;
	root.level = 0;

	add_node(10);
	add_node(11);
	add_node(12);
	add_node(13);
	add_node(14);
	add_node(15);
	add_node(16);
	add_node(17);
	add_node(18);
	add_node(19);
	add_node(21);
	add_node(22);
	add_node(23);
	add_node(24);
	add_node(25);
	add_node(26);
	add_node(27);
	add_node(28);
	add_node(29);
	add_node(31);
	add_node(32);
	add_node(33);
	add_node(291);
	add_node(292);
	add_node(293);
	add_node(294);
	add_node(295);
	add_node(296);
	add_node(297);
	add_node(299);
	add_node(281);
	add_node(282);
	add_node(283);
	add_node(284);
	add_node(285);
	add_node(286);
	add_node(287);
	add_node(288);
	add_node(289);
	add_node(300);
	add_node(301);
	add_node(302);
	add_node(303);
	add_node(304);
	add_node(305);
	add_node(306);
	add_node(307);
	add_node(308);
	add_node(309);

	print_tree(&root, "ROOT", &root);

	find_element_and_insert_data(&root, &root, 22, dataset, 14, INSERT);
	find_element_and_insert_data(&root, &root, 302, dataset1, 14, INSERT);
	find_element_and_insert_data(&root, &root, 303, dataset2, 14, INSERT);
	find_element_and_insert_data(&root, &root, 304, dataset3, 14, INSERT);
	find_element_and_insert_data(&root, &root, 305, dataset4, 14, INSERT);

	print_tree(&root, "ROOT", &root);

	print_node(nodeptr = find_element_and_insert_data(&root, &root, 22, NULL, 0, FIND));
	print_node(nodeptr = find_element_and_insert_data(&root, &root, 302, NULL, 0, FIND));
	print_node(nodeptr = find_element_and_insert_data(&root, &root, 303, NULL, 0, FIND));
	print_node(nodeptr = find_element_and_insert_data(&root, &root, 304, NULL, 0, FIND));
	print_node(nodeptr = find_element_and_insert_data(&root, &root, 305, NULL, 0, FIND));

	printf("\n");

	exit(0);
}

// TODO 
// Print the ascii tree. Use level properly and print indentation
// Write a randomizer routine that splits a hashed password to its N  constituent datasets (a)
// Place datasets in the tree (within a file) or (within a directory of files)
// Splitter number sequence from (a) is stored encrypted in the machine
// Read the split number sequence
// Fetch the parts of the hashed password from the tree using the routines in this file
// Reconstruct the hashed password
// Fetch the key that hashed it using the same routine as above.
// Unhash the password
// Use the extracted password for getting into login account, database login or other purposes.
// Write a routine to read a file or directory of files and construct the tree with hashed password partitions of bits
// Then use the routines in this file to read the partitions of bits
// Reconstruct the hashed password and key.

// All within a single file encrypted.
// Within a directory structure.
// Vault based concept.
// Bit wise storage for keys.
// Random spew. Based on random spew move it to tree (file or directory of files)
