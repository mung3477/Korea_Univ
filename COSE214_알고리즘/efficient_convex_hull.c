#include <stdlib.h> // atoi, rand, qsort, malloc
#include <stdio.h>
#include <assert.h> // assert
#include <time.h> //time

#define RANGE 100.0

typedef struct
{
	float x;
	float y;
} point;

typedef struct
{
	point from;
	point to;
} line_segment;

////////////////////////////////////////////////////////////////////////////////
// function declaration

// distance = | ( ax+by-c ) / sqrt(a^2 + b^2) |
float distance( float a, float b, float c, point p)
{
	float dist = a*p.x + b * p.y - c;
	dist = (int)(dist * 1000) / 1000.0;
	//if (dist >= 0.0) return dist;
	return (dist);
}

// p1 : upper(left)  ax+by-c = minus
// p2 : lower(right) ax+by-c = plus
void separate_points( point *p, int n, point from, point to, point *s1, point *s2, int *n1, int *n2)
{	
	int i = 0;
	*n1 = 0;
	*n2 = 0;
	float a, b, c;
	a = to.y - from.y;
	b = from.x - to.x;
	c = from.x * to.y - from.y * to.x;

	while(i < n) {
		if (a * p[i].x + b * p[i].y - c < -0.001){
			s1[*n1] = p[i];
			(*n1)++;
		}
		else if (a * p[i].x + b * p[i].y - c > 0.001) {
			s2[*n2] = p[i];
			(*n2)++;
		}
		i++;
	}
}

// convex hull
int convex_hull_main( point *p, int n, point p1, point pn, line_segment *l, int *num_l)
{
	/*if(n == 0) {
		l[*num_l].from.x = p1.x;
		l[*num_l].from.y = p1.y;
		l[*num_l].to.x = pn.x;
		l[*num_l].to.y = pn.y;
		(*num_l)++;
		return 1;
	}*/
	
	if(1) {
		float max_dist = 0.0;
		int max_index = -1, i = 0;
		float a, b, c;
		a = pn.y - p1.y;
		b = p1.x - pn.x;
		c = p1.x * pn.y - p1.y * pn.x;
		
		//max 점 구하기
		for(i; i < n; i++) {
			if(max_dist > distance(a, b, c, p[i])) {
				max_dist = distance(a, b, c, p[i]);	
			    	max_index = i;
			}
		}

		if(max_index == -1) {
			l[*num_l].from.x = p1.x;
			l[*num_l].from.y = p1.y;
			l[*num_l].to.x = pn.x;
			l[*num_l].to.y = pn.y;
			(*num_l)++;
			return 1;
		}
		
		//printf( "\n\npoints(%.3f,%.3f)\n\n\n", p[max_index].x, p[max_index].y);

		point max;
		max.x = p[max_index].x;
		max.y = p[max_index].y;

		int n1, n2, n3, n4;
		point *s1 = (point*)malloc(sizeof(point) * n);
		if(s1 == NULL) {
		    printf("Not enough memeory\n");
		    return -1;
		}
		point *s2 = (point*)malloc(sizeof(point) * n);
		if(s2 == NULL) {
		    printf("Not enough memeory\n");
		    return -1;
		}
		separate_points(p, n, p1, p[max_index], s1, s2, &n1, &n2);
		//printf( "segments(%.3f,%.3f,%.3f,%.3f)\n", p1.x, p1.y, max.x, max.y);
		//free(p);
		free(s2);
		
		point *s3 = (point*)malloc(sizeof(point) * n);
		if(s3 == NULL) {
		    printf("Not enough memeory\n");
		    return -1;
		}
		point *s4 = (point*)malloc(sizeof(point) * n);
		if(s4 == NULL) {
		    printf("Not enough memeory\n");
		    return -1;
		}

		//separate_points(s2, n2, max, pn, s3, s4, &n3, &n4);
		//printf( "segments(%.3f,%.3f,%.3f,%.3f)\n", max.x, max.y, pn.x, pn.y);
		separate_points(p, n, max, pn, s3, s4, &n3, &n4);
		free(s4);

		convex_hull_main(s1, n1, p1, max, l, num_l);
		convex_hull_main(s3, n3, max, pn, l, num_l);
		free(p);
		if(s1 != NULL) free(s1);
		if(s3 != NULL) free(s3);
		return 1;

	}

}


////////////////////////////////////////////////////////////////////////////////
void print_header(char *filename)
{
	printf( "#! /usr/bin/env Rscript\n");
	printf( "png(\"%s\", width=700, height=700)\n", filename);
	
	printf( "plot(1:%.3f, 1:%.3f, type=\"n\")\n", RANGE, RANGE);
}

////////////////////////////////////////////////////////////////////////////////
void print_footer(void)
{
	printf( "dev.off()\n");
}

////////////////////////////////////////////////////////////////////////////////
//x값으로 비교. p1이 더 크면 1, 같으면 0, p2가 더 크면 -1 return.
int cmp_x( const void *p1, const void *p2)
{
	point *p = (point *)p1;
	point *q = (point *)p2;
	
	float diff = p->x - q->x;
	
    return ((diff >= 0.0) ? ((diff > 0.0) ? +1 : 0) : -1);
}

////////////////////////////////////////////////////////////////////////////////
void print_points( point *p, int n)
{
	int i;
	printf( "\n#points\n");
	
	for (i = 0; i < n; i++)
		printf( "points(%.3f,%.3f)\n", p[i].x, p[i].y);
}

////////////////////////////////////////////////////////////////////////////////
void print_line_segments( line_segment *l, int num_line)
{
	int i;

	printf( "\n#line segments\n");
	
	for (i = 0; i < num_line; i++)
		printf( "segments(%.3f,%.3f,%.3f,%.3f)\n", l[i].from.x, l[i].from.y, l[i].to.x, l[i].to.y);
}

////////////////////////////////////////////////////////////////////////////////
// [input] p : set of points
// [input] n : number of points
// [output] l : set of line segments that forms the convex hull
// return value : number of line segments (num_l)
// n1, n2 : number of points in s1, s2 respectively
int convex_hull( point *p, int n, int min_index, int max_index, line_segment *l)
{
	int num_l = 0;
	int n1, n2;
	
	//s1 : points which are left to the line
	point *s1 = (point *)malloc(sizeof (point) * n);
	assert( s1 != NULL);

	//s2 : points which are right to the line
	point *s2 = (point *)malloc(sizeof (point) * n);
	assert( s2 != NULL);
	
	// p[0] = min x point
	// p[n-1] = max x point
	//*** uncomment the below 2 lines
	//separate_points( p, n, p[0], p[n-1], s1, s2, &n1, &n2);
	separate_points( p, n, p[min_index], p[max_index], s1, s2, &n1, &n2);

	//printf( "segments(%.3f,%.3f,%.3f,%.3f)\n", p[min_index].x, p[min_index].y, p[max_index].x, p[max_index].y);

	//convex_hull_main( s1, n1, p[0], p[n-1], l, &num_l);
	//convex_hull_main( s2, n2, p[n-1], p[0], l, &num_l);
	
	//*** uncomment the below 2 lines
	//print_points( s1, n1);
	//print_points( s2, n2);

	convex_hull_main( s1, n1, p[min_index], p[max_index], l, &num_l);
	convex_hull_main( s2, n2, p[max_index], p[min_index], l, &num_l);

	//free( s1);
	//free( s2);
	
	return num_l;
}

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	float x, y;
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

	point *p;
	p = (point *)malloc(sizeof (point *) * n);
	assert( p != NULL);
	
	line_segment *l;
	l = (line_segment *)malloc(sizeof (line_segment *) * n);
	assert( l != NULL);

	fprintf( stderr, "Create %d points\n", n);

	float min_x = RANGE;
	float max_x = 0;
	int min_index = 0;
	int max_index = 0;
	
	// making n points
	srand( time(NULL));
	for (int i = 0; i < n; i++)
	{
		x = (float)rand() / (float)(RAND_MAX) * RANGE; // 0 ~ RANGE random float number
		y = (float)rand() / (float)(RAND_MAX) * RANGE; // 0 ~ RANGE random float number
	
		p[i].x = x;
		p[i].y = y;
		
		if (x < min_x) { min_x = x; min_index = i; }
		if (x > max_x) { max_x = x; max_index = i; }
 	}

	// sort by x-axis
	//qsort( p, n, sizeof(point), cmp_x);

	print_header( "convex.png");
	
	print_points( p, n);

	// convex hull algorithm
	int num_line = convex_hull( p, n, min_index, max_index, l);

	print_line_segments( l, num_line);
	
	print_footer();
	
	free( p);
	free( l);
	
	return 0;
}
