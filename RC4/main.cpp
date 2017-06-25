#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

vector<char> s;
int i, j;

void swap(vector <char> s, int i, int j)
{
	char temp = s[i];
	s[i] = s[j];
	s[j] = temp;
	return;
}

//KSA
void rc4_init(string key)
{
	s.clear();
	int key_length = key.size();
	for (i = 0;i < 256;i++)
	{
		s.push_back(i);
	}
	for (i = j = 0;i < 256;i++)
	{
		j = (j + key[i%key_length] + s[i]);
		swap(s, i, j);
	}
	i = j = 0;
}

// PRGA
char rc4_output()
{
	i = (i + 1);
	j = (j + s[i]);

	swap(s, i, j);

	return s[(s[i] + s[j])];
}

int main()
{
	string test_vectors[][2] =
	{
		{ "key","plaintext" },
		{ "Wiki","pedia" },
		{ "Secret","Attack at dawn" }
	};
	int x;
	for (x = 0; x < 3; x++) {
		int y;
		rc4_init(test_vectors[x][0]);
		for (y = 0; y < test_vectors[x][1].length(); y++)
			printf("%02X", test_vectors[x][1][y] ^ rc4_output());
		printf("\n");
	}
	cin >> x;
	return 0;
}