#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "binarySearchTreeADT.h"

BST_TREE* bstCreate()
{
	BST_TREE* tree = (BST_TREE*)malloc(sizeof(BST_TREE));
	if (tree)
	{
		tree->root = NULL;
		tree->count = 0;
	}

	return tree;
}

void _bstDestroy(TREE_NODE* root)
{
	if (root)
	{
		_bstDestroy(root->left);
		_bstDestroy(root->right);
		free(root);
	}
}

void bstDestroy(BST_TREE* tree)
{
	if (tree)
	{
		_bstDestroy(tree->root);
		tree->count = 0;

		free(tree);
	}
}

TREE_NODE* _bstInsert(TREE_NODE* root, int data, bool* success) 
{
	//if tree is empty 
	if(root == NULL) {
		TREE_NODE* newNode = (TREE_NODE*)malloc(sizeof(newNode));
		if (newNode == NULL) {
			*success = false;
			return NULL;
		}
		newNode->data = data;
		newNode->left = newNode->right = NULL;
		*success = true;
		return newNode;
	}
	
	//if tree is not empty
	else{
		if(root->data > data) {
			root->left = _bstInsert(root->left, data, success);
		}
		else {
			root->right = _bstInsert(root->right, data, success);
		}
		return root;
	}
}

bool bstInsert(BST_TREE* tree, int data)
{	
	bool success = false;
	tree->root = _bstInsert(tree->root, data, &success); 
	if (success) return true;
	else return false;
}

TREE_NODE* _bstDelete(TREE_NODE* root, int key, bool* success)
{
	//if bst is empty
	if(root == NULL) {
		*success = false;
		return NULL;
	}
	
	//find node
	if(root->data > key) {
		root->left = _bstDelete(root->left, key, success);
	}
	else if (root->data < key) {
		root->right = _bstDelete(root->right, key, success);
	}
	//found the node to delete
	else {
		//if aim is leaf
		if(root->left == NULL && root->right == NULL) {
			*success = true;
			free(root);
			return NULL;
		}
		//if aim has left child
		else if (root->left != NULL && root->right == NULL) {
			TREE_NODE* delNode = root;
			root = root->left;
			*success = true;
			free(delNode);
		} 
		//if aim has right child
		else if (root->left == NULL && root->right != NULL){
			TREE_NODE* delNode = root;
			root = root->right;
			*success = true;
			free(delNode);
		}
		//if aim has both side child
		else {
			TREE_NODE* newRoot = NULL;
			for(newRoot = root->left; newRoot->right != NULL; newRoot = newRoot->right);
			root->data = newRoot->data;
			root->left = _bstDelete(root->left, newRoot->data, success);
		}
	}
	return root;
}

bool bstDelete(BST_TREE* tree, int key)
{
	bool success = false;
	
	//if tree is empty
	if(bstEmpty(tree)) return false;
	
	tree->root = _bstDelete(tree->root, key, &success);
	return success;
}


TREE_NODE* bstSearch(BST_TREE* tree, int key)
{
	TREE_NODE* curNode = tree->root;
	while(curNode) {
		if(curNode->data == key) return curNode;
		else if (curNode->data > key) curNode = curNode->left;
		else curNode = curNode->right;
	}
	return NULL;
}

bool bstEmpty(BST_TREE* tree)
{
	if (tree->count) return true;
	else return false;
}

int bstCount(BST_TREE* tree)
{
	if (tree == NULL) return 0;
	else return tree->count;
}

/*
void showTree(TREE_NODE* root) 
{
	if(root == NULL) {
		return;
	}
	else {
		showTree(root->left);
		printf("%d ", root->data);
		showTree(root->right);
		return;
	}
}
*/

