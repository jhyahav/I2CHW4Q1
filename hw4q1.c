
#include <stdio.h>
#include <stdbool.h>

#define N 50
#define M 50

int GetImageInput(int image[][M], int n, int m);

int GetWindowDimensions(int *h_ptr, int *w_ptr);

int GetImageDimensions(int *n_ptr, int *m_ptr);

void compute_integral_image(int image[][M], int n, int m,
                            int integral_image[][M]);

void PrintIntegralImage(int integral_image[][M], int n, int m);

int sum_rect(int integral_image[][M], int rect[4]);

void sliding_average(int image[][M], int n, int m, int h, int w,
                     int average[][M]);

void PrintSmoothedImage(int smoothed_image[][M], int n, int m);

//Length = 18 lines.
int main()
{
    int image[N][M] = {{0}}, integral_image[N][M] = {{0}};
    int average[N][M] = {{0}};
    int n, m, h, w;
    int *n_ptr = &n, *m_ptr = &m, *h_ptr = &h, *w_ptr = &w;

    int scanf_ret = GetImageDimensions(n_ptr, m_ptr);
    if (scanf_ret != 0)
    {
        return scanf_ret;
    }

    scanf_ret = GetImageInput(image, n, m);
    if (scanf_ret != 0)
    {
        return scanf_ret;
    }

    scanf_ret = GetWindowDimensions(h_ptr, w_ptr);
    if (scanf_ret != 0)
    {
        return scanf_ret;
    }

    compute_integral_image(image, n, m, integral_image);

    PrintIntegralImage(integral_image, n, m);

    sliding_average(image, n, m, h, w, average);

    PrintSmoothedImage(average, n, m);


    return 0;
}
/*This function gets the image's dimensions as input from the user and
checks the input's validity, returning an error code if the input is not
valid.*/
int GetImageDimensions(int *n_ptr, int *m_ptr)
{
    printf("Enter image dimensions:\n");
    if (scanf("%d %d", n_ptr, m_ptr) != 2)
    {
        return -1;
    }

    if (*n_ptr > 50 || *m_ptr > 50 || *n_ptr < 1 || *m_ptr < 1)
    {
        return 1;
    }

    return 0;
}

/*This function gets the sliding window's dimensions as input from the user
and checks the input's validity, returning an error code if the input is
not valid.*/
int GetWindowDimensions(int *h_ptr, int *w_ptr)
{
    printf("Enter sliding window dimensions:\n");
    if (scanf("%d %d", h_ptr, w_ptr) != 2)
    {
        return -1;
    }

    if (*h_ptr > 50 || *w_ptr > 50 || *h_ptr < 1 || *w_ptr < 1)
    {
        return 1;
    }

    return 0;
}

/*This function gets the input for each pixel in the image from the user.
If the input is invalid, an error code is returned.*/
int GetImageInput(int image[][M], int n, int m)
{
    printf("Enter image:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (scanf("%d", &image[i][j]) != 1)
            {
                printf("Input error!\n");
                return -1;
            }

            if (image[i][j] < 1)
            {
                printf("Input error!\n");
                return 1;
            }
        }
    }

    return 0;
}

/*This function, given the original image, its dimensions n and m,
and a destination 2d array, calculates the integral image and saves it
in the destination array.
The function runs with O(n*m) complexity, since it iterates through every
element in the original image. The amount of additional space used by the
function is independent of any input, so it is O(1).
Length = 14 lines.*/
void compute_integral_image(int image[][M], int n, int m,
                            int integral_image[][M])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
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
                                       integral_image[i][j-1] +
                                       image[i][j] -
                                       integral_image[i-1][j-1];
            }
        }
    }
}

/*This function, given the integral image and its dimensions n and m,
prints the integral image.
Length = 8 lines.*/
void PrintIntegralImage(int integral_image[][M], int n, int m)
{
    printf("Integral image is:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d", integral_image[i][j]);
            if (j < m - 1)
            {
                printf(" ");
            }
            else
            {
                printf("\n");
            }
        }
    }
}

/*This function, given the smoothed image and its dimensions n and m,
prints the smoothed image.
Length = 8 lines.*/
void PrintSmoothedImage(int smoothed_image[][M], int n, int m)
{
    printf("Smoothed image is:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d", smoothed_image[i][j]);
            if (j < m - 1)
            {
                printf(" ");
            }
            else
            {
                printf("\n");
            }
        }
    }
}

/*This function, given the integral image and the rectangle that contains
the desired part of the image, calculates the sum of the pixels within
the rectangle. It does so with O(1) runtime complexity because the number
of operations it runs is constant for every input. Its space complexity
is also O(1), since a constant number of variables is allocated when the
function runs.*/
int sum_rect(int integral_image[][M], int rect[4])
{
    int i_top = rect[0], i_bottom = rect[2];
    int j_left = rect[1], j_right = rect[3];

    int integ_img_top_r = integral_image[i_top - 1][j_right];
    int integ_img_top_l = integral_image[i_top - 1][j_left - 1];
    int integ_img_bottom_r = integral_image[i_bottom][j_right];
    int integ_img_bottom_l = integral_image[i_bottom][j_left - 1];

    if (i_top < 1)
    {
        integ_img_top_r = integ_img_top_l = 0;
    }

    if (j_left < 1)
    {
        integ_img_top_l = integ_img_bottom_l = 0;
    }

    int rect_sum = integ_img_bottom_r;
    rect_sum -= integ_img_top_r;
    rect_sum -= integ_img_bottom_l;
    rect_sum += integ_img_top_l;

    return rect_sum;
}

/*This function, given an original image, its dimensions n and m,
the dimensions of a sliding window h and w, and a 2d destination array,
saves the average value for the sliding windows of which each cell is the
center in the corresponding index within the destination array. This gives
us a smoothed (averaged) image.
Since this function entails allocation of an N x M array for the integral
image used in the sliding average calculations, its space complexity is
O(N*M). The runtime complexity of the function is O(n*m), since we iterate
through all the cells in an n x m array twice.
Length = 18 lines.*/
void sliding_average(int image[][M], int n, int m, int h, int w,
                     int average[][M])
{
    int rect[4], sum, rounded_avg;
    double avg;

    int integral_image[N][M] = {{0}};
    //O(n*m)
    compute_integral_image(image, n, m, integral_image);

    //O(n*m). Additive to the complexity of compute_integral_image.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            rect[0] = i - (h/2);
            rect[1] = j - (w/2);
            rect[2] = i + (h/2);
            //Handles bottom out-of-bounds cases.
            if (rect[2] >= n)
            {
                rect[2] = n - 1;
            }
            //Handles right out-of-bounds cases.
            rect[3] = j + (w/2);
            if (rect[3] >= m)
            {
                rect[3] = m - 1;
            }

            sum = sum_rect(integral_image, rect);

            avg = (double)sum/(h*w);

            rounded_avg = avg + 0.5;

            average[i][j] = rounded_avg;
        }
    }
}
