#include <stdio.h>
#include <stdbool.h>


struct SignCount
{
	char sign;
	int amount;
};

int main()
{

	FILE * fp;
	int c;
	size_t total_signs = 0;
	bool sign_added = true;

	struct SignCount sign_arr[1024];

	fp = fopen("text.txt", "r");

	while((c = fgetc(fp)) != EOF)
	{
		if (total_signs == 0)
		{
			sign_arr[0].sign = (char)c;
			(sign_arr[0].amount)++;
			total_signs++;
		}
		else
		{
			for(int i = 0; i < total_signs; i++)
			{
				if ((char)c == sign_arr[i].sign)
				{
					(sign_arr[i].amount)++;
					sign_added = false;
					break;
				}
			}

			if(sign_added)
			{
				sign_arr[total_signs].sign = (char)c;
				sign_arr[total_signs].amount = 1;
				total_signs++;
			}
			sign_added = true;
		}
	}

	for(int i = 0; i < total_signs; i++)
	{
		if(sign_arr[i].sign == '\n')
		{
			printf("Sign: \\n Amount: %d\n", sign_arr[i].amount);

		}
		else
		{
			printf("Sign: %c Amount: %d\n", sign_arr[i].sign, sign_arr[i].amount);
		}
	}

	fclose(fp);

	return 0;
}
