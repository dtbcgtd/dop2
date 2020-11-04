#include <stdio.h>

//Boyer–Moore–Horspool algorithm//
int len(char* str, int max_len) {
	int i;
	for (i = 0; i < max_len; i++) {
		if (str[i] == '\0') {
			break;
		}
	}
	return i;
}

int comp(char* a, char* b, int len) {
	int i;
	for (i = 0; i < len; i++) {
		if (a[i] != b[i]) {
			return 0;
		}
	}
	return 1;
}

int sstr(char* str, char* sub, int strlen, int sublen, char* table) {
	int i, step;
	char c;

	for (i = 0, step = 1; i <= strlen - sublen && step >= 1; i += step) {
		if (1 == comp(str + i, sub, sublen)) {
			return i;
		}
		c = str[i + sublen - 1];
		step = table[c];
	}
	return -1;
}

int main()
{
	char str[10000], mod[10000], table[10000];
	int len_str, len_mod, pos, counter = 0;
	char* cursor;

	printf("Input string: ");
	gets_s(str, 256);
	len_str = len(str, 256);

	if (len_str == 0) {
		printf("Empty string\n");
		return 0;
	}

	printf("Input model: ");
	gets_s(mod, 256);
	len_mod = len(mod, 256);

	int i, n;
	char c;

	for (n = 0; n < 256; n++) {
		table[n] = len_mod;
	}

	for (i = len_mod - 2; i >= 0; i--) {
		c = mod[i];
		if (table[c] == len_mod) {
			table[c] = len_mod - i - 1;
		}
	}
	c = mod[len_mod - 1];
	table[c] = len_mod;

	if (len_mod == 0) {
		printf("No data\n");
		return 0;
	}

	cursor = str;

	while (1) {
		pos = sstr(cursor, mod, len_str, len_mod, table);

		if (pos < 0) {
			if (counter == 0) {
				printf("Model not found\n");
			}
			break;
		}
		counter += 1;

		printf("Position: %d\n", cursor - str + pos);
		cursor += pos + len_mod;
	}
	return 0;
}
