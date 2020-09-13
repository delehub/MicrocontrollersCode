#include<reg51.h>

void View(unsigned long u32ViewData);
void to_BufferData(unsigned long u32Data,unsigned char *pu8Buffer,unsigned char u8Type); 
void SendString(unsigned char *pu8String);    

/*---C����ѧϰ����Ŀ�ʼ��-----------------------------------------------*/
void main() //������
{
   unsigned char a; //����һ������a��
   unsigned int  b; //����һ������b��
   unsigned long c; //����һ������c��
   a=100;          //������a��ֵ��
   b=10000;        //������b��ֵ��
   c=1000000000;   //������c��ֵ��
   View(a);   //�ѵ�1����a���͵����Զ˵Ĵ�����������Ϲ۲졣
   View(b);   //�ѵ�2����b���͵����Զ˵Ĵ�����������Ϲ۲졣
   View(c);   //�ѵ�3����c���͵����Զ˵Ĵ�����������Ϲ۲졣
   while(1)  
   { 
   }
}


/*---C����ѧϰ����Ľ�����-----------------------------------------------*/
void View(unsigned long u32ViewData)
{
    static unsigned char Su8ViewBuffer[43];
		code unsigned char Cu8_0D_0A[]={0x0d,0x0a,0x00};
   	code unsigned char Cu8Start[]={"��ʼ..."};
    static unsigned char Su8FirstFlag=0;
    static unsigned int Su16FirstDelay;
    if(0==Su8FirstFlag)
	    {
	   Su8FirstFlag=1;
	   for(Su16FirstDelay=0;Su16FirstDelay<10000;Su16FirstDelay++);
	   SendString(Cu8Start);  
	   SendString(Cu8_0D_0A);  
	   SendString(Cu8_0D_0A);  
   }
    to_BufferData(u32ViewData,Su8ViewBuffer,1); 
  	SendString(Su8ViewBuffer);  
    to_BufferData(u32ViewData,Su8ViewBuffer,2); 
 	  SendString(Su8ViewBuffer);  
    to_BufferData(u32ViewData,Su8ViewBuffer,3); 
		SendString(Su8ViewBuffer);  
    to_BufferData(u32ViewData,Su8ViewBuffer,4); 
		SendString(Su8ViewBuffer);  
   	SendString(Cu8_0D_0A);  
}

void to_BufferData(unsigned long u32Data,unsigned char *pu8Buffer,unsigned char u8Type) 
{
    code unsigned char Cu8Array1[]={0xB5,0xDA,0x4E,0xB8,0xF6,0xCA,0xFD,0x00};
 	  code unsigned char Cu8Array2[]="ʮ����:";
	  code unsigned char Cu8Array3[]="ʮ������:";
 	  code unsigned char Cu8Array4[]="������:";
    static unsigned char Su8SerialNumber=1;
    static unsigned int  Su16BufferCnt;
    static unsigned int  Su16TempCnt;
    static unsigned int  Su16TempSet;
    static unsigned long Su32Temp1;
    static unsigned long Su32Temp2;
    static unsigned long Su32Temp3;
    static unsigned char Su8ViewFlag;
		
    if(1==u8Type)
  	{
        for(Su16BufferCnt=0;Su16BufferCnt<7;Su16BufferCnt++)
	        {
	           pu8Buffer[Su16BufferCnt]=Cu8Array1[Su16BufferCnt];
  	    }
	        pu8Buffer[2]=Su8SerialNumber+'0';
   	      pu8Buffer[Su16BufferCnt]=0x0d;
   	      pu8Buffer[Su16BufferCnt+1]=0x0a;
	        pu8Buffer[Su16BufferCnt+2]=0;
 	        Su8SerialNumber++;
	        return;
   	}
    else if(2==u8Type)
	    {
	        for(Su16BufferCnt=0;Su16BufferCnt<7;Su16BufferCnt++)
	        {
		       pu8Buffer[Su16BufferCnt]=Cu8Array2[Su16BufferCnt];
	        }
	       Su32Temp1=1000000000;
		   Su32Temp2=10;
		   Su16TempSet=10;
  	}
    else if(3==u8Type)
 	{
	        for(Su16BufferCnt=0;Su16BufferCnt<9;Su16BufferCnt++)
	        {
		       pu8Buffer[Su16BufferCnt]=Cu8Array3[Su16BufferCnt];
	        }
	        Su32Temp1=0x10000000;
		    Su32Temp2=0x00000010;
		    Su16TempSet=8;	
    }
    else 
    {
	        for(Su16BufferCnt=0;Su16BufferCnt<7;Su16BufferCnt++)
	        {
		       pu8Buffer[Su16BufferCnt]=Cu8Array4[Su16BufferCnt];
	        }
	        Su32Temp1=0x80000000;
		    Su32Temp2=0x00000002;
		    Su16TempSet=32;	
   	}
    Su8ViewFlag=0;
    for(Su16TempCnt=0;Su16TempCnt<Su16TempSet;Su16TempCnt++)
    {
       Su32Temp3=u32Data/Su32Temp1%Su32Temp2;
	       if(Su32Temp3<10)
	       {
 	        pu8Buffer[Su16BufferCnt]=Su32Temp3+'0';
	       }
	       else
	       {
 	        pu8Buffer[Su16BufferCnt]=Su32Temp3-10+'A';
	       }
	       if(0==u32Data)
	       {
		       Su16BufferCnt++;
		       break;
	       }
	       else if(0==Su8ViewFlag)
	       {
	           if('0'!=pu8Buffer[Su16BufferCnt])
 	       {
               Su8ViewFlag=1;
			       Su16BufferCnt++;
           }
	       }
	       else
	       {
	           Su16BufferCnt++;
	       }
       Su32Temp1=Su32Temp1/Su32Temp2;
    }
    pu8Buffer[Su16BufferCnt]=0x0d;
    pu8Buffer[Su16BufferCnt+1]=0x0a;
    pu8Buffer[Su16BufferCnt+2]=0;
}

void SendString(unsigned char *pu8String)   
{
  static unsigned int Su16SendCnt;
  static unsigned int Su16Delay;
  SCON=0x50;
  TMOD=0X21;
  TH1=TL1=256-(11059200/12/32/9600);  
  TR1=1;
  ES = 0; 
  TI = 0;
  for(Su16SendCnt=0;Su16SendCnt<43;Su16SendCnt++)
  {
     if(0==pu8String[Su16SendCnt])
	     {
	         break;
	     }
	     else
	     {
					SBUF =pu8String[Su16SendCnt]; 
					for(Su16Delay=0;Su16Delay<800;Su16Delay++);
						TI = 0;
	     }
  }
}
