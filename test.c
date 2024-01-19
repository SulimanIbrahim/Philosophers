#include<unistd.h>
#include<stdarg.h>
#include<stdio.h>


int putnum(long long n, int div,char *base)
{
    int i = 0;
    int len = 0;

    int tempnum;

    if(n == 0)
    {
        write(1, "0",1);
        return(1);
    }
    tempnum = n;
    if(n < 0)
    {
        len += write(1, "-", 1);
        n = -n;
    }
    while(tempnum != 0)
    {
        tempnum /= div;
        len++;
    }
    if(n >= div)
        putnum(n / div, div,"0123456789abcdef");
    write(1, &base[n % div], 1);

    return (len);
}

int putstring(char *str)
{
    int i = 0;
    int len = 0;
    if(!str)
        {
            write(1,"(null)",6);
            return (6);
        }
    while(str[i] != '\0')
    {
        len += write(1,&str[i],1);
        i++;
    }
    return(len);
}

int ft_printf(char *format, ...)
{
    va_list arg;
    int i;
    int len;

    va_start(arg, format);
    i = 0;
    len = 0;
    while(format[i] != '\0')
    {
        if(format[i] != '%')
            len += write(1, &format[i], 1);
        else if(format[i] == '%')
        {
            if(format[i + 1] == 'd')
               {
                    len += putnum((long long int)va_arg(arg, int), 10, "0123456789abcdef");
                   i++;
               } 
            else if(format[i + 1] == 'x')
               {
                    len += putnum((long long int)va_arg(arg, unsigned int), 16, "0123456789abcdef");
                   i++;
               }
            else if(format[i + 1] == 's')
               {
                    len += putstring(va_arg(arg, char *));
                   i++;
               }
            else if(format[i + 1] == '%')
               {
                    len += write(1, &format[i], 1);
                   i++;
               }
        }
        i++;
    }
    va_end(arg);
    return len;
}

int main()
{
  printf("\nlenght = %d\n", ft_printf("%x", 43324324)); 
   printf("\nlenght = %d\n", printf("%x", 43324324)); 
   
}