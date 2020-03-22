#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>






char my_getc (int fd) /*считываем один символ*/
	{	
		char  c;
		if ( read(fd, &c, 1)==0 )
			return '\0';
		return c;
	}


char* RSF (int fd) /*считываем строку*/
{
	char* Sum;
	char c;
	int i,num=-1;
	i=1;
	Sum=malloc(128*sizeof(char));
	while (((c=my_getc(fd))!='\n') && (c!='\0'))
		{
			num++;
			if ((num+1)>(i*128))
					Sum=realloc(Sum, (++i)*128);			
			Sum[num]=c;
		}
	

	Sum=realloc(Sum, ((i+1)*128) +1); 
	Sum[num+1]='\0';
		
	return Sum;			
}


int file_string_count (int fd) /*считаем количество строк в файле*/
{
	int count=0;
	char c;
	while ( (c=my_getc(fd))!='\0' )
		if (c=='\n')
			count++;
	lseek (fd, 0, SEEK_SET);
	return count;	
}







double* read_coords (char* S)
{
	double* coord;
	char* buf;
	int i, j, n;
	
	buf=malloc(8*sizeof(char)*sizeof(double));
	coord=malloc(9*sizeof(double));
	
	i=0;
	n=0;
	
	while ( (S[i]!='#') && (S[i]!='\0') && (S[i]!='\n') ) 
		{
			j=0;
			while ( (S[i]!=' ') && (S[i]!='\0') && (S[i]!='#') && (S[i]!='\n') )
				{
					buf[j]=S[i];
					j++;
					i++;
				}
			buf[j]='\0';
			coord[n]=atof(buf);
			
			n++;
			i++;
		}
	free(buf);
	return coord;
}

double side_pred (double x1, double y1, double x2, double y2, double x3, double y3)
{
	return( (x2-x1)*(y3-y1)-(y2-y1)*(x3-x1) );
}

void outwork (double* Arr)
{
	double x1=Arr[0], x2=Arr[2], x3=Arr[4], x4=Arr[6], y1=Arr[1], y2=Arr[3], y3=Arr[5], y4=Arr[7], answer=Arr[8], d0, d1, d2, d3, d4, d5, d6,ab,ac,ad, bd, cd, bc;
	
	d0=(x2-x1)*(y3-y4)-(x3-x4)*(y2-y1);
	d1=(x3-x1)*(y3-y4)-(x3-x4)*(y3-y1);
	d2=(x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
	
	d3=side_pred(x1, y1, x2, y2, x3, y3);
	d4=side_pred(x1, y1, x2, y2, x4, y4);
	d5=side_pred(x3, y3, x4, y4, x1, y1);
	d6=side_pred(x3, y3, x4, y4, x2, y2);
	
	ab=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
	ac=(x1-x3)*(x1-x3)+(y1-y3)*(y1-y3);
	ad=(x1-x4)*(x1-x4)+(y1-y4)*(y1-y4);
	bd=(x2-x4)*(x2-x4)+(y2-y4)*(y2-y4);
	cd=(x3-x4)*(x3-x4)+(y3-y4)*(y3-y4);
	bc=(x2-x3)*(x2-x3)+(y2-y3)*(y2-y3);
	
	
	if (d0==0)
		{
			if  ( (d1==0) && (d2==0) )
				{
					/*5-6-7-8*/
					if ((ac<ab)&&(bd<ab)&&(ad<ab)&&(bc<ab))
						{
							printf("my answ: 5 | Right Answer: %f | ", answer);
							if (answer==5.0)
								printf("Correct!\n");
							else 
								printf("Incorrect\n");
						}
					else
						{
							if ( ((ac<ab)&&(ad<ab))||((bd<cd)&&(ad<cd)) )
								{
									printf("my answ: 6 | Right Answer: %f | ", answer);
									if (answer==6.0)
										printf("Correct!\n");
									else 
										printf("Incorrect\n");
								}
							else
								{
									if ( ((x2==x3)&&(y2==y3)) || ((x2==x4)&&(y2==y4)) || ((x1==x3)&&(y1==y3)) || ((x1==x4)&&(y1==y4)) )
										{
											printf("my answ: 7 | Right Answer: %f | ", answer);
											if (answer==7.0)
												printf("Correct!\n");
											else 
												printf("Incorrect\n");
										}
									else 
										{
											if ( ((ab<ac)&&(ac<ad))||((ab<ad)&&(ad<ac)) )
												{
													printf("my answ: 8 | Right Answer: %f | ", answer);
													if (answer==8.0)
														printf("Correct!\n");
													else 
														printf("Incorrect\n");
												}
										}
								}
						}
				}
			else
				{
					printf("my answ: 4 | Right Answer: %f | ", answer);
					if (answer==4.0)
						printf("Correct!\n");
					else 
						printf("Incorrect\n");
				}
		}
	else
		{
			/*0-1-2-3*/
			if ((d3*d4<=0)&&(d5*d6<=0))
				{
					if ( ((x2==x3)&&(y2==y3)) || ((x2==x4)&&(y2==y4)) || ((x1==x3)&&(y1==y3)) || ((x1==x4)&&(y1==y4)) )
						{
							printf("my answ: 3 | Right Answer: %f | ", answer);
							if (answer==3.0)
								printf("Correct!\n");
							else 
								printf("Incorrect\n");
						}
					else
						{
							if (d3*d4*d5*d6==0)
								{
									printf("my answ: 2 | Right Answer: %f | ", answer);
									if (answer==2.0)
										printf("Correct!\n");
									else 
										printf("Incorrect\n");
								}
							else
								{
									printf("my answ: 1 | Right Answer: %f | ", answer);
									if (answer==1.0)
										printf("Correct!\n");
									else 
										printf("Incorrect\n");
								}
						}
				}
			else
				{
					printf("my answ: 0 | Right Answer: %f | ", answer);
					if (answer==0.0)
						printf("Correct!\n");
					else 
						printf("Incorrect\n");
				}
		}
}


int main(int argc, char **argv)
{
	int fd, i, n;
	
	if ((fd=open(argv[1], O_RDONLY))==-1) /*открыли файл с данными*/ 
		{
			printf("wrong file\n");
			return 1;
		}
		
	
	n=file_string_count(fd);
	
	for (i=1; i<=n; i++) /*пошли обрабатывать построчно*/
		{
			outwork(read_coords(RSF(fd))); /*считали одну строку из файла, распилили ее в массив координат, отправили в обработку*/
		}
	printf("ПОСЛЕДНЯЯ СТРОЧКА ФИКТИВНАЯ \n");
	return 0;
}

