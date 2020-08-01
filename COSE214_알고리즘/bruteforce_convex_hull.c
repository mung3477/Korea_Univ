#include <stdlib.h> // atoi, rand
#include <stdio.h>
#include <assert.h> // assert
#include <time.h> //time

#define RANGE 100

typedef struct
{
	int x;
	int y;
} point;

typedef struct
{
	point from;
	point to;
} line_segment;

////////////////////////////////////////////////////////////////////////////////
void print_header(char *filename)
{
	printf( "#! /usr/bin/env Rscript\n");
	printf( "png(\"%s\", width=700, height=700)\n", filename);
	
	printf( "plot(1:%d, 1:%d, type=\"n\")\n", RANGE, RANGE);
}
////////////////////////////////////////////////////////////////////////////////
void print_footer(void)
{
	printf( "dev.off()\n");
}

////////////////////////////////////////////////////////////////////////////////
void print_points( point *p, int n)
{

// [input] p : set of points
// [input] n : number of points
    int i = 0;
    printf("#points\n");
    for(i = 0; i < n; i++) {
	printf("points(%d,%d)\n", p[i].x, p[i].y);
    }
    printf("\n");
}


int Where_On_line(int a, int b, int c, point p)
{
	int where =  a * p.x + b * p.y - c;
	if (where > 0) return 1;
	else if (where == 0) return 0;
	else return -1;
}

int convex_hull( point *p, int n, line_segment *l)
{
    // [input] p : set of points
    // [input] n : number of points
    // [input] l : set of ine segments that form the convex hull
    // return value : number of line segments

    // a, b ,c : eqation's coefficient.
    // i, j, k : index on the set of points. i is for p1, j is for p2
    // m       : index on the set of line segments

    int a, b, c, t, t2;
    int i = 0, j, k, m = 0;
	for(i; i < n - 1; i++){
	    for(j = i + 1; j < n; j++) {
	   	
		a = p[j].y - p[i].y;
		b = p[i].x - p[j].x;
		c = p[i].x * p[j].y - p[i].y * p[j].x;

		for(k = 0; k <  n - 1; k++) {
		    t = Where_On_line(a, b, c, p[k]);
		    t2 = Where_On_line(a, b, c, p[k+1]);

		    if (t == 0 || t2 == 0) continue;
		    else if (t != (Where_On_line(a, b, c, p[k + 1]))) break;
		}

		if (k == n - 1)  {
			l[m].from.x = p[i].x;
			l[m].from.y = p[i].y;
			l[m].to.x = p[j].x;
			l[m].to.y = p[j].y;
			m++;
		}
	    }
	}
	return m;
}

void print_line_segments( line_segment *l, int num_line)
{
	printf("#line segments\n");
	for(int i = 0; i < num_line; i++) {
		printf("segments(%d, %d, %d, %d)\n", l[i].from.x, l[i].from.y, l[i].to.x, l[i].to.y);	
	}

}

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	int x, y;
	int n; // number of points
	
	if (argc != 2)
	{
		printf( "%s number_of_points\n", argv[0]);
		return 0;
	}

	n = atoi( argv[1]);
	if (n <= 0)
	{
		printf( "The number of points should be a positive integer!\n");
		return 0;
	}

	point p[n];
	line_segment l[n];

	fprintf( stderr, "Create %d points\n", n);

	// making n points
	srand( time(NULL));
	for (int i = 0; i < n; i++)
	{
		x = rand() % RANGE + 1; // 1 ~ RANGE random number
		y = rand() % RANGE + 1;
		
		p[i].x = x;
		p[i].y = y;
 	}

	print_header( "convex.png");
	
	print_points( p, n);
	
	int num_line = convex_hull( p, n, l);

	print_line_segments( l, num_line);
	
	print_footer();
	
	return 0;
}
