#include "fdf.h"
int x_start;
int x_finish;
int y_start;
int y_finish;

// int main()
// {
//     float xi = 0;
//     float y = 0;

//     while(xi < x_finish)
//     {
//         y = (int)(y_finish - y_start)/(int)(x_finish - x_finish) * (xi - x_start) + y_start ;
//         output(xi, y);
//     }
//     // =========================================================================================
//     float xi = 0;
//     float y = 0;
    
//     float e = 0; //端数
//     float d = (int)(y_finish - y_start)/(int)(x_finish - x_start);
//     y = y_start;
//     while(xi < x_finish)
//     {
//         e = e + d * (xi - x_start);
//         if( e > 0.5){
//             y = y + 1;
//             e = e - 1.0; //yが増加した分次のループで矛盾しないように
//         }

//         output(xi, y);

//         e = 0;
//     }
//     // =========================================================================================
//     int xi = 0;
//     int y = 0;
    
//     int e = 0; //端数
//     int d = 2 * (int)(y_finish - y_start);
//     int dx = (int)(x_finish - x_start);
//     y = y_start;
//     while(xi < x_finish)
//     {
//         e = e + d * (xi - x_start);
//         if( e > dx){
//             y = y + 1;
//             e = e - 2 * dx; //yが増加した分次のループで矛盾しないように
//         }

//         output(xi, y);
//     }

// }