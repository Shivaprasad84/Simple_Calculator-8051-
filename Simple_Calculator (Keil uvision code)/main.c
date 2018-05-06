#include<reg51.h>
#include "lcd.h"

sbit r1 = P1^0;
sbit r2 = P1^1;
sbit r3 = P1^2;
sbit r4 = P1^3;
sbit c1 = P1^4;
sbit c2 = P1^5;
sbit c3 = P1^6;
sbit c4 = P1^7;
void row_scan();
void delay(unsigned char);
void send_num(unsigned int);
void calculate();
unsigned int y, a = 0, b = 0;
unsigned char operator, flag = 0;

void main()
{
    P1 = 0xf0; // To make rows as output and columns as input pins
    lcd_init();
    lcd_cmd(0x85);
    lcd_string("SIMPLE");
    lcd_cmd(0xc3);
    lcd_string("CALCULATOR");
    delay(200);
    lcd_cmd(0x01);
    while(1)
    {
        row_scan();
    }
}

void row_scan()
{
    //---ROW 1---//
    r1 = 0;
    r2 = r3 = r4 = 1;
    if(c1 == 0)
    {
        delay(32);
        while(c1 == 0)
        {
            lcd_dat('7');
            if(flag == 0)
                a = a*10 + 7;
            else
                b = b*10 + 7;
        }
    }
    if(c2 == 0)
    {
        delay(32);
        while(c2 == 0)
        {
            lcd_dat('8');
            if(flag == 0)
                a = a*10 + 8;
            else
                b = b*10 + 8;
        }
    }
    if(c3 == 0)
    {
        delay(32);
        while(c3 == 0)
        {
            lcd_dat('9');
            if(flag == 0)
                a = a*10 + 9;
            else
                b = b*10 + 9;
        }
    }
    if(c4 == 0)
    {
        delay(32);
        while(c4 == 0)
        {
            flag = 1;
            lcd_dat('/');
            operator = '/';
        }
    }

    //---ROW 2---//
    r2 = 0;
    r1 = r3 = r4 = 1;
    if(c1 == 0)
    {
        delay(32);
        while(c1 == 0)
        {
            lcd_dat('4');
            if(flag == 0)
                a = a*10 + 4;
            else
                b = b*10 + 4;
        }
    }
    if(c2 == 0)
    {
        delay(32);
        while(c2 == 0)
        {
            lcd_dat('5');
            if(flag == 0)
                a = a*10 + 5;
            else
                b = b*10 + 5;
        }
    }
    if(c3 == 0)
    {
        delay(32);
        while(c3 == 0)
        {
            lcd_dat('6');
            if(flag == 0)
                a = a*10 + 6;
            else
                b = b*10 + 6;
        }
    }
    if(c4 == 0)
    {
        delay(32);
        while(c4 == 0)
        {
            flag = 1;
            lcd_dat('x');
            operator = 'x';
        }
    }

    //---ROW 3---//
    r3 = 0;
    r2 = r1 = r4 = 1;
    if(c1 == 0)
    {
        delay(32);
        while(c1 == 0)
        {
            lcd_dat('1');
            if(flag == 0)
                a = a*10 + 1;
            else
                b = b*10 + 1;
        }
    }
    if(c2 == 0)
    {
        delay(32);
        while(c2 == 0)
        {
            lcd_dat('2');
            if(flag == 0)
                a = a*10 + 2;
            else
                b = b*10 + 2;
        }
    }
    if(c3 == 0)
    {
        delay(32);
        while(c3 == 0)
        {
            lcd_dat('3');
            if(flag == 0)
                a = a*10 + 3;
            else
                b = b*10 + 3;
        }
    }
    if(c4 == 0)
    {
        delay(32);
        while(c4 == 0)
        {
            flag = 1;
            lcd_dat('-');
            operator = '-';
        }
    }

    //---ROW 4---//
    r4 = 0;
    r2 = r3 = r1 = 1;
    if(c1 == 0)
    {
        delay(32);
        while(c1 == 0)
        {
            lcd_cmd(0x01);
            flag = a = b = 0;
        }
    }
    if(c2 == 0)
    {
        delay(32);
        while(c2 == 0)
        {
            lcd_dat('0');
            if(flag == 0)
                a = a*10 + 0;
            else
                b = b*10 + 0;
        }
    }
    if(c3 == 0)
    {
        delay(32);
        while(c3 == 0)
        {
            lcd_dat('=');
            calculate();
        }
    }
    if(c4 == 0)
    {
        delay(32);
        while(c4 == 0)
        {
            flag = 1;
            lcd_dat('+');
            operator = '+';
        }
    }
}

void delay(unsigned char t)
{
    unsigned int j;
    unsigned char i;
    for(i = 0; i < t; i++)
        for(j = 0; j < 700; j++);
}


void calculate()
{
    lcd_cmd(0xc0);
    if(operator == '+')
    {
        send_num(a + b);
    }

    if(operator == '-')
    {
        if(a > b)
            send_num(a - b);
        else
        {
            lcd_dat('-');
            send_num(b - a);
        }
    }

    if(operator == '/')
    {
        if(b != 0)
            send_num(a/b);
        else
        {
            lcd_cmd(0x01);
            lcd_string("NaN");
        }
    }

    if(operator == 'x')
    {
        send_num(a*b);
    }
}

void send_num(unsigned int x)
{
    if(x > 9999)
    {
        y = x/10000;
        lcd_dat(y + 0x30);
        x = x%10000;
        y = x/1000;
        lcd_dat(y + 0x30);
        x = x%1000;
        y = x/100;
        lcd_dat(y + 0x30);
        x = x%100;
        y = x/10;
        lcd_dat(y + 0x30);
        y = x%10;
        lcd_dat(y + 0x30);
    }
    else if(x > 999 && x < 9999)
    {
        y = x/1000;
        lcd_dat(y + 0x30);
        x = x%1000;
        y = x/100;
        lcd_dat(y + 0x30);
        x = x%100;
        y = x/10;
        lcd_dat(y + 0x30);
        y = x%10;
        lcd_dat(y + 0x30);
    }
    else if(x > 99 && x < 999)
    {
        y = x/100;
        lcd_dat(y + 0x30);
        x = x%100;
        y = x/10;
        lcd_dat(y + 0x30);
        y = x%10;
        lcd_dat(y + 0x30);
    }
    else if(x > 9 && x < 99)
    {
        y = x/10;
        lcd_dat(y + 0x30);
        y = x%10;
        lcd_dat(y + 0x30);
    }
    else
    {
        lcd_dat(x + 0x30);
    }
}
