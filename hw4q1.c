
#include <stdio.h>
#include <stdbool.h>

#define N 50
#define M 50

void compute_integral_image(int image[][M], int n, int m,
                            int integral_image[][M]);

int sum_rect(int integral_image[][M], int rect[4]);

void sliding_average(int image[][M], int n, int m, int h, int w,
                     int average[][M]);

int main()
{
    int image[N][M] = {{0}}, integral_image[N][M] = {{0}};
    int n, m;

    printf("Enter image dimensions:\n");
    scanf("%d %d", &n, &m);

    printf("Enter image:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &image[i][j]);
        }
    }

    printf("Original image is:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d  ", image[i][j]);
            if (j == m - 1) {
                printf("\n");
            }
        }
    }

    compute_integral_image(image, n, m, integral_image);


    printf("Integral image is:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", integral_image[i][j]);
            if (j < m - 1) {
                printf(" ");
            }
            else
            {
                printf("\n");
            }
        }
    }

    return 0;
}

void compute_integral_image(int image[][M], int n, int m,
                            int integral_image[][M])
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0) {
                if (j == 0) {
                    integral_image[i][j] = image[i][j];
                }
                else
                {
                    integral_image[i][j] = integral_image[i][j-1] +
                    image[i][j];
                }
            }
            else if (j == 0)
            {
                integral_image[i][j] = integral_image[i-1][j] +
                image[i][j];
            }
            else
            {
                integral_image[i][j] = integral_image[i-1][j] +
                integral_image[i][j-1] + image[i][j] - integral_image[i-1][j-1];
            }
        }
    }
}

