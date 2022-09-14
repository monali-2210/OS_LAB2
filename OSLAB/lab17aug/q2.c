#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


void swap (int *a, int *b)
{
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

int main ()
{

  int arr[] = { 2, 5, 6, 3, 7, 8, 10, 12, 1, 4, 9 };
  int n = sizeof (arr) / sizeof (arr[0]);
  int fd1[2];
  pid_t p;
  if (pipe (fd1) == -1)
    {
      printf ("Pipe Failed\n");
    }
  p = fork ();
  if (p == -1)
    {
      printf ("Fork Failed\n");
    }
  else
    {
      if (p == 0)
	{
	  printf ("\nHello I am Child. I will sort. My ID : %d\n", getpid ());
	  read (fd1[0], arr, sizeof (arr));
	  close (fd1[0]);
	  for (int i = 0; i < n - 1; i++)
	    {
	      for (int j = 0; j < n - i - 1; j++)
		{
		  if (arr[j] > arr[j + 1])
		    {
		      swap (&arr[j], &arr[j + 1]);
		    }
		}
	    }
	  write (fd1[1], arr, sizeof (arr));
	  close (fd1[1]);
	  exit (0);

	}
      else
	{

	  printf ("\n Hello I am Parent. I have this array. My ID : %d\n",
		  getpid ());
	  for (int i = 0; i < n; i++)
	    {
	      printf ("%d ", arr[i]);
	    }
	  printf ("\n");
	  write (fd1[1], arr, sizeof (arr));
	  close (fd1[1]);
	  wait (NULL);
	  printf
	    ("\n Hello I am Parent Again. My child has completed it's work. Here is the final array. \n");
	  read (fd1[0], arr, sizeof (arr));
	  close (fd1[0]);
	  for (int i = 0; i < n; i++)
	    {
	      printf ("%d ", arr[i]);
	    }
	  printf ("\n");

	}

    }


}

