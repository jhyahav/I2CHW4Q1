
#include <stdio.h>
#include <stdbool.h>

#define N 50
#define M 50

void compute_integral_image(int image[][M], int n, int m,
                            int integral_image[][M]);
void PrintIntegralImage(int integral_image[][M], int n, int m);

int sum_rect(int integral_image[][M], int rect[4]);

void sliding_average(int image[][M], int n, int m, int h, int w,
                     int average[][M]);

int main()
{
    int image[N][M] = {{0}}, integral_image[N][M] = {{0}};
    int average[N][M];
    int n, m;
    //int rect[4] = {0, 0, 3, 3};

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

    PrintIntegralImage(integral_image, n, m);



    //int rect_sum = sum_rect(integral_image, rect);

    //printf("Rect sum: %d\n", rect_sum);

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

void PrintIntegralImage(int integral_image[][M], int n, int m)
{
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
}
//Remember to add exceptions for out of bounds bottom and right.
int sum_rect(int integral_image[][M], int rect[4])
{
    int i_top = rect[0], i_bottom = rect[2];
    int j_left = rect[1], j_right = rect[3];
    int integ_img_top_r, integ_img_top_l, integ_img_bottom_l;
    int integ_img_bottom_r = integral_image[i_bottom][j_right];
    if (i_top < 1) {
        integ_img_top_r = integ_img_top_l = 0;
        integ_img_bottom_l = integral_image[i_bottom][j_left - 1];
    }
    else if (j_left < 1){
        integ_img_top_l = integ_img_bottom_l = 0;
        integ_img_top_r = integral_image[i_top - 1][j_right];
    }
    else
    {
        integ_img_top_r = integral_image[i_top - 1][j_right];
        integ_img_top_l = integral_image[i_top - 1][j_left - 1];
        integ_img_bottom_l = integral_image[i_bottom][j_left - 1];
    }

    int rect_sum = integ_img_bottom_r;
    //printf("%d\n", integ_img_bottom_r);
    rect_sum -= integ_img_top_r;
    //printf("%d\n", integ_img_top_r);
    rect_sum -= integ_img_bottom_l;
    //printf("%d\n", integ_img_bottom_l);
    rect_sum += integ_img_top_l;
    //printf("%d\n", integ_img_top_l);
    return rect_sum;
}

void sliding_average(int image[][M], int n, int m, int h, int w,
                     int average[][M])
{

}
