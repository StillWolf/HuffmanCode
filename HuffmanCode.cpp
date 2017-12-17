// HuffmanCode.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"

using namespace std;
int NumbersOfChar[500], ptrOfString;
map<char, string> Code;
struct node
{
	int Times;
	char Letter;
	node *Left = NULL, *Right = NULL;
};
struct cmp
{
	bool operator()(node *node1, node *node2)
	{
		return node1->Times > node2->Times;
	}
};
node *root;
priority_queue <node*, vector<node*>, cmp> Heap;
void Traversal(node *root, string Now)
{
	if (root->Left == NULL)
	{
		Code[root->Letter] = Now;
		return;
	}
	Traversal(root->Left, Now + "0");
	Traversal(root->Right, Now + "1");
}
void Compress()
{
	string SourceFileName, CodeFileName, InputFile = "";
	cout << "Please input source file name(size less than 4GB):";
	cin >> SourceFileName;
	cout << "Please input code file name:";
	cin >> CodeFileName;
	cout << "Processing..." << endl;
	ifstream SourceFile;
	SourceFile.open(SourceFileName.data(), ios::in);
	char c = 1;
	while (c != EOF)
	{
		c = SourceFile.get();
		NumbersOfChar[c]++;
		InputFile += c;
	}
	for (int i = 0; i < 300; i++)
	{
		if (!NumbersOfChar[i])
			continue;
		node *point = new node;
		point->Letter = (char)i;
		point->Times = NumbersOfChar[i];
		point->Left = point->Right = NULL;
		Heap.push(point);
	}
	node *left, *right, *parent;
	while (Heap.size() != 1)
	{
		parent = new node;
		left = new node;
		right = new node;
		left = Heap.top();
		Heap.pop();
		right = Heap.top();
		Heap.pop();
		parent->Left = left;
		parent->Right = right;
		parent->Letter = 0;
		parent->Times = left->Times + right->Times;
		Heap.push(parent);
	}
	root = Heap.top();
	Traversal(root, "");
	SourceFile.close();
	ofstream CodeFile;
	CodeFile.open(CodeFileName.data(), ios::out);
	for (int i = 0; i < InputFile.length(); i++)
		CodeFile << Code[InputFile[i]];
	CodeFile.close();
	cout << "Process end." << endl;
}
string visitHuffman(node *root,string Input)
{
	string ans = "";
	node *NowNode = new node;
	NowNode = root;
	while (NowNode->Left != NULL)
	{
		if (Input[ptrOfString] == '0')
			NowNode = NowNode->Left;
		else
			NowNode = NowNode->Right;
		ptrOfString++;
		if (ptrOfString == Input.length())
			break;
	}
	ans += NowNode->Letter;
	return ans;
}
string DecodeHuffman(string Input)
{
	string ans = "";
	ptrOfString = 0;
	while (ptrOfString < Input.length())
		ans += visitHuffman(root,Input);
	return ans;
}
void Decompress()
{
	string TargetFileName, CodeFileName, InputFile = "";
	cout << "Please input code file name(size less than 4GB):";
	cin >> CodeFileName;
	cout << "Please input target file name:";
	cin >> TargetFileName;
	cout << "Processing..." << endl;
	ifstream CodeFile;
	CodeFile.open(CodeFileName.data(), ios::in);
	char c = 1;
	while (c != EOF)
	{
		c = CodeFile.get();
		NumbersOfChar[c]++;
		InputFile += c;
	}
	CodeFile.close();
	ofstream TargetFile;
	TargetFile.open(TargetFileName.data(), ios::out);
	string ans=DecodeHuffman(InputFile);
	TargetFile << ans << endl;
	cout << "Process end." << endl;
	TargetFile.close();
}
int UI()
{
	int id;
	cout << endl;
	cout << "1.Huffman compress." << endl;
	cout << "2.Huffman decompress." << endl;
	cout << "3.Exit." << endl;
	cout << "Please select:";
	cin >> id;
	if (id < 1 || id > 3)
	{
		cout << "Invalid Input!" << endl;
		return 1;
	}
	if (id == 3)
		return 0;
	if (id == 1)
		Compress();
	if (id == 2)
		Decompress();
	return 1;
}
int main()
{
	while (UI());
	return 0;
}