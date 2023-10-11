#include <stdio.h>
#include <unistd.h>

//lineが新しくなるごとにobserverを初期化しないといけない
# define BITMASK 0x0000ff

int ft_abs_i(int n)
{
    if(n < 0)
        return n * -1;
    return n;
}

//return i = 0 : (finish - start)/zoomをそのままつかう  
//return i > 0 : xがiになるごとに1くわえる
//return i = 30 : xがどんな値でも不変
int bresenham_color_create_observer(int start_color, int finish_color, int zoom)
{
    int e = 0;
    int i = 0;
    int diff = 0;
    int delta_color = ft_abs_i(2 * (finish_color - start_color)); 
    while(i < zoom)
    {
        e = e + delta_color;
        if(e > zoom)
        {
            diff = diff + 1;
            e = e - (2 * zoom);
            break;
        }
        i++;
    }
    return i;
}

void  get_step(int decreace_flag, int start_color, int finish_color, int zoom)
{
    int r_diff;
    int g_diff;
    int b_diff;
    int color_step;
    if(decreace_flag == -1)
    {
        color_step = 0;
        printf("この線は緑\n");
    }
    else
    {   
        //diff < zoomの状態になると浮動小数計算になるのでbresenhamを使う
        int f_temp = (finish_color>>16)&(BITMASK);//直接書き込んで演算すると負にならなかった
        int s_temp = (start_color>>16)&(BITMASK);
        int r_observer = bresenham_color_create_observer(s_temp, f_temp, 30);
        r_diff = (f_temp - s_temp)/zoom;
        printf("r_diff = %d\n",f_temp- s_temp);
        printf("r_observer = %d\n", r_observer);
        printf("r_diff/zoom = %d\n", r_diff);

        f_temp = (finish_color>>8)&(BITMASK);//直接書き込んで演算すると負にならなかった
        s_temp = (start_color>>8)&(BITMASK);
        int g_observer = bresenham_color_create_observer(s_temp, f_temp, 30);
        g_diff = (f_temp - s_temp)/zoom;
        printf("g_diff = %d\n",f_temp- s_temp);
        printf("g_observer = %d\n", g_observer);
        printf("g_diff/zoom = %d\n", g_diff);

        f_temp = finish_color&(BITMASK);//直接書き込んで演算すると負にならなかった
        s_temp = start_color&(BITMASK);
        int b_observer = bresenham_color_create_observer(s_temp, f_temp, 30);
        b_diff = (f_temp - s_temp)/zoom;
        printf("b_diff = %d\n",(f_temp - s_temp));
        printf("b_observer = %d\n", b_observer);
        printf("b_diff/zoom = %d\n", b_diff);

        //----------------------------------------
        //ここはpixelput_hubの先頭で作ってfdf_info->color_info->colorに足し合わせる
        //注意：10進数になっているので16進数に変換し、R,G,Bそれぞれ2桁になるように足し合わせていく必要がある
        // if(r_observer == 0)
        //     color_step = (r_diff/zoom) * x;
        // else if(x == r_observer)
        // {
        //     color_step++;
        //     r_observer += observer_step;
        // }
        // color_step = (color_step << 8);
        // if(g_observer == 0)
        //     color_step += (g_diff/zoom) * x;
        // else if(x == g_observer)
        // {
        //     color_step++;
        //     g_observer += observer_step;
        // }
        // color_step = (color_step << 8);
        // if(b_observer == 0)
        //     color_step += (b_diff/zoom) * x;
        // else if(x == b_observer)
        // {
        //     color_step++;
        //     b_observer += observer_step;
        // }
        //----------------------------------------
    }

}

int main(){
    // get_step(1, 0x0000ff, 0x010000, 30);
    int color = 0x12;
    color = color << 8;
    color += 0x34;
    color = color << 8;
    color += 0x56;
    printf("%x\n", color);



    int base = 0;
    int r_dcolor = 7;
    // printf("%x\n", (base >> 16)&BITMASK);
    // printf("%x\n", (base >> 8)&BITMASK);
    // printf("%x\n", (base)&BITMASK);
    base = base + (r_dcolor << 16);
    printf("r_decimal to hex by 16 bit shift %x\n", base);
    int g_dcolor = 7;

    base = base + (g_dcolor << 8);
    printf("decimal to hex by 16 bit shift %x\n", base);
    int b_dcolor = 7;

    base = base + (b_dcolor);
    printf("decimal to hex by 16 bit shift %x\n", base);


    return 0;
}