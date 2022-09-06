#include<map>
#include<iostream>

using namespace std;

int N;

int Maxdist = 0;
//lookup inorder idx in O(1)
map<int, int> inorder_idx;

int BuildTree(int preorder[], int ps, int pe, int inorder[], int is, int ie)
{
	if (ps >= pe || is >= ie)
		return 0;
	else
	{
		int root = preorder[ps];
		int inorder_root_idx = inorder_idx[root];

		int leftTree_ver_cnt = inorder_root_idx - is;
		int rightTree_ver_cnt = ie - inorder_root_idx;

		int Height1 = 1 + BuildTree(preorder, ps + 1, ps + leftTree_ver_cnt, inorder, is, inorder_root_idx - 1);
		int Height2 = 1 + BuildTree(preorder, ps + leftTree_ver_cnt + 1, pe, inorder, inorder_root_idx + 1, ie);

		Maxdist = (Maxdist > Height1 + Height2) ? (Maxdist) : (Height1 + Height2);
		return (Height1 > Height2) ? (Height1) : (Height2);
	}
}

int main()
{
	cin >> N;
	int* preorder = new int[N];
	int* inorder = new int[N];

	for (int i = 0; i < N; ++i)
		cin >> preorder[i];
	for (int i = 0; i < N; ++i)
	{
		cin >> inorder[i];
		inorder_idx[inorder[i]] = i;
	}

	int Height = BuildTree(preorder, 0, N - 1, inorder, 0, N - 1);

	cout << "I have read the rules about plagiarism punishment\n";
	cout << Height << endl << Maxdist;
}