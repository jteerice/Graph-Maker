#include <stdio.h>
#include <stdlib.h>

#define N 10  

struct pointArray {
	int x;
	int y;
};
typedef struct pointArray point2d;


void fill(char filename[], point2d P[]);
int getdist(point2d p, point2d q);
void closest(point2d P[], int G[2*N][2*N]);
void grid(point2d P[], int G[2*N][2*N]);
void printpoints(char filename[], point2d P[]);
void printgridxy(char filename[], int G[2*N][2*N]);

int main(int argc, char *argv[]) {

	if (argc != 3)
	{
		printf("Syntax Error: ./a.out <infile> <outfile>\n");
		exit(1);
	}

	point2d P[N];
	int G[2*N][2*N] = {0};

	fill(argv[1], P);
	grid(P, G);
	printpoints(argv[2], P);
	printgridxy(argv[2], G);


	return 0;
}

// Fill struct array with values from input file
void fill(char filename[], point2d P[]) {
	
	int i = 0;
	FILE *ifp = NULL;
	ifp = fopen(filename, "r");
	if (ifp == NULL) {
		printf("Could not open %s for reading.\n", filename);
		exit(1);
	}
	
	for (i = 0; i < N; i++) {
		fscanf(ifp, "%d %d", &P[i].x, &P[i].y);
	}
	fclose(ifp);
}

int getdist(point2d p, point2d q) {

	int totalDistance = 0;

	totalDistance = ((p.x - q.x) * (p.x - q.x)) + ((p.y - q.y) * (p.y - q.y)); // Pythagorean theorem to find distance -- returned integer is the squared value of the distance
	
	return totalDistance;
}

// Locating two closest points in the point2d struct array
void closest(point2d P[], int G[2 * N][2 * N]) {

	int i = 0;
	int j = 0;
	int closestDistance = ((2 * N) * (2 * N)) + ((2 * N) * (2 * N)); // Max distance value
	point2d closestPoints[2]; // Temporary point2d struct array to hold the closest point values

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (i != j) {
				if (getdist(P[i], P[j]) < closestDistance) {
					closestDistance = getdist(P[i], P[j]);
					closestPoints[0].x = P[i].x;
					closestPoints[0].y = P[i].y;
					closestPoints[1].x = P[j].x;
					closestPoints[1].y = P[j].y;
				} 
			}
		}
	}
	// Filling designated indicies for grid array with 2 for closest points
	G[20 - closestPoints[0].y][closestPoints[0].x] = 2;
	G[20 - closestPoints[1].y][closestPoints[1].x] = 2;
}

// Filling grid array with 0 (indicating no point exists) and 1 (indicating a point exists)
void grid(point2d P[], int G[2 * N][2 * N]) {

	int i = 0;
	int j = 0;

	for (i = 0; i < N; i++) {
		G[20 - P[i].y][P[i].x] = 1;
	}

	for (i = 0; i < (2 * N); i ++) {
		for (j = 0; j < (2 * N); j++) {
			if (G[i][j] != 1)
				G[i][j] = 0;
		}
	}

	closest(P, G);
}

// Print to terminal AND output file
void printpoints(char filename[], point2d P[]) {

	int i = 0;

	FILE *ofp = NULL;
	ofp = fopen(filename, "w");
	if (ofp == NULL){
		printf("Could not open %s for writing.\n", filename);
		exit(1);
	}

	for (i = 0; i < N; i++) {
		printf("%d: (%2d, %2d)\n", i, P[i].x, P[i].y);
		fprintf(ofp, "%d: (%2d, %2d)\n", i, P[i].x, P[i].y);
	}
	fclose(ofp);
}

// Print to terminal AND output file
void printgridxy(char filename[], int G[2 * N][2 * N]) {

	int i = 0;
	int j = 0;

	FILE *ofp = NULL;
	ofp = fopen(filename, "a");
	if (ofp == NULL){
		printf("Could not open %s for writing.\n", filename);
		exit(1);
	}

	printf("--------------------------------------------------\n");
	fprintf(ofp, "--------------------------------------------------\n");
	for (i = 0; i < 2 * N; i++) {
		for (j = 0; j < 2 * N; j++) {
			if (G[i][j] == 2) {
				printf("X ");
				fprintf(ofp, "X ");
			}
			else if (G[i][j] == 1) {
				printf("* ");
				fprintf(ofp, "* ");
			}
			else {
				printf("  ");
				fprintf(ofp, "  ");
			}
		}
		printf("\n");
		fprintf(ofp, "\n");
	}
	
	printf("--------------------------------------------------\n");
	fprintf(ofp, "--------------------------------------------------\n");
	fclose(ofp);
}
