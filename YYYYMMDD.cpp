#include<cstdio>
const int maxn = 13;
int j = 0;
int MONTH[maxn] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int judge(int a, int b)
{
	return a > b ? 1 : 2;
}
void leap1(int yl,int* counter)
{
	if ((yl % 4 == 0 && yl % 100 != 0) || (yl %400==0))
		(*counter)++;
	else (*counter) = (*counter);
}
int leap2(int yl)
{
	if ((yl % 4 == 0 && yl % 100 != 0) || (yl % 400 == 0))
		j = 1;
	else j = 0;
	return j;
}
void oneyear(int* diff, int date,int date0)
{
	int k;
	k = (date % 10000) / 100; 
	if ((date / 10000) != (date0 / 10000)) {
		 //printf(" %d ", k);//date,date/10000);
		(*diff) += (MONTH[k] - (date % 100));
		//printf(" %d", date%100);
		for (int i = k + 1; i < 13; i++)
		{
			(*diff) += MONTH[i];
		}
		if (k < 2 || (k == 2 && (date % 100) < 28))
		{
			(*diff) += leap2(date/10000); //printf(" leap1=%d ", leap2(date/10000));
		}
		k = (date0 % 10000) / 100; //printf(" k=%d ", k);
		//(*diff) += (MONTH[k] - (date0 % 100));
		for (int i = 1; i < k ; i++)
			(*diff) += MONTH[i];
		(*diff) += (date0 % 100); 
		//printf(" %d\n", (*diff));
		//(*diff) += leap2(date0);
		if (k > 2|| (k==2 && (date0%100)>28 ))
		{
			(*diff) += leap2(date0 / 10000) ; //printf(" leap2=%d ",leap2(date0/10000));
		}
	}
	else
	{
		for (int i = (date % 10000) / 100; i < (date0 % 10000) / 100; i++)
			(*diff) += MONTH[i];
		if ((k % 4 == 0) && (k % 100 != 0))
			(*diff)++;
		(*diff) += (date0 % 100-date%100);
	}
		printf("%d\n", (*diff));
}
int main()
{
	int date1, date2, tip, sub, diff, counter = 0, date;
	int temp1, temp2;
	while (scanf_s("%d %d", &date1, &date2, 2) != EOF) {
		tip = judge(date1, date2);
		temp1 = date1 / 10000;
		temp2 = date2 / 10000;
		if (tip == 1)
		{
			if (temp1 > temp2)
			{
				sub = (temp1 - 1) - temp2;
				for (int i = temp1 - 1; i >= temp2; i--)
				{
					leap1(i, &counter);
				}
				date = date2 + 10000 * sub;
			}
			else {
				counter = 0; sub = 0; date = (date1 <= date2 ? date1 : date2);
			}
		}
		else if (tip == 2)
		{
			if (temp2 > temp1)
			{
				sub = (temp2 - 1) - temp1;
				for (int i = temp2 - 1; i >= temp1; i--)
				{
					leap1(i, &counter);
				}
				date = date1 + 10000 * sub;
			}
			else {
				counter = 0; sub = 0; date = (date1 <= date2 ? date1 : date2);
			}
		}

		diff = sub * 366 - (sub - counter);// printf(" %d\n", diff);
		//printf("counter=%d",counter);
		if (tip == 1)
		{
			oneyear(&diff, date, date1);
		}
		else if (tip == 2) oneyear(&diff, date, date2);
		counter = 0;
	}
	return 0;
}