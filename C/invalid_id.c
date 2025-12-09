// INVALID ID's are ID's that have an even length and first half is equal to second half

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_invalid_id(char * id)
{
	size_t length = strlen(id);

	if (length % 2 != 0)
	{
		return false;
	}

	if (id[0] == '0')
	{
		return false;
	}

	size_t half = length / 2;

	for(size_t i = 0; i < half; i++)
	{
		if(id[i] != id[i + half])
		{
			return false;
		}
	}
	return true;
}

int main()
{

	char * test_id = "5656";

	if(is_invalid_id(test_id))
	{
		printf("%s is an invalid ID\n", test_id);
	}
	else
	{
		printf("%s is a valid ID\n", test_id);
	}

	return 0;
}
