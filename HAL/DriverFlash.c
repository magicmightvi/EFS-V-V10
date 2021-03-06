#ifndef _DRIVER_FLASH
#define _DRIVER_FLASH
  #include "..\DataStruct.h"
#endif

//sst26
#define RSTEN		       	   (0x66)
#define RST			   (0x99)
#define ULBPR			   (0x98)
#define STATUS_REGISTER            (0x05)
#define SECTOR_ERASE		   (0x20)
#define BLOCK_ERASE                (0xD8)
#define CHIP_ERASE		   (0xc7)
#define SST_READ		   (0x03)
#define SST_WRITE		   (0x02)
#define WREN		  	   (0x06)
#define WRDI			   (0x04)
#define RSID			   (0x88)
#define RDID			   (0x90)
#define JEDEC			   (0x9F)

//sst25用到的指令
#define EWSR			   (0x50)
#define WRSR			   (0x01)

#define UNSELECT_CHIP    P8OUT |= BIT1
#define SELECT_CHIP      P8OUT &= ~BIT1


void EraseFlash(INT32U addr)                  //清除FLASH段(512BYTE)
{   
    volatile INT16U * ptr;                    //addr为该段的首地址

    INT16U j;
    
    _DINT();  
    WDTCTL = WDTPW + WDTHOLD;               ////禁止内部看门狗
    for(j = 0; j < 1000; j++)
    {
      if((FCTL3 & BUSY) != BUSY)              //不忙则跳出,完成擦除
      break;
    }    
     
    ptr = (INT16U *)addr;
	WatchDog();
    FCTL1          = 0xA502;                  //ERASE =1
    FCTL3          = 0xA500;                  //LOCK=0
    *ptr           = 0;
    FCTL1          = FWKEY;                   // Clear WRT bit
    FCTL3          = FWKEY + LOCK;            // Set LOCK bit    
    _EINT();
}
void WriteFlashNByte(INT32U dst, INT16U src, INT8U len)            //向指定地址写入len长度的数据,源地址开始的len个数据写到目的地址去
{
    INT16U i,j;
    INT8U *ptr,*ptr1;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////禁止内部看门狗
    WatchDog();                             ////清外部看门狗
    ptr  = (INT8U *)dst;
    ptr1 = (INT8U *)src;
    for(i = 0; i < len; i++)
    {
        for(j = 0; j < 1000; j++)
        {
          if((FCTL3 & BUSY) != BUSY)              //不忙则跳出,完成擦除
          break;
        }
        FCTL3 = FWKEY;                            //  LOCK=0
        FCTL1 = FWKEY+WRT;                        //  WRT=1
        *ptr++ = *(ptr1 + i);
        FCTL1 = FWKEY;                            // Clear WRT bit
        FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    }
    _EINT();
}
void WriteFlashBuffLongWord(INT32U dst, INT32S *data, INT8U len)
{
    INT16U i,j;
    INT32S *ptr;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////禁止内部看门狗
    WatchDog();                             ////清外部看门狗
    ptr  = (INT32S *)dst;
    for(i = 0; i < len; i++)
    {
        for(j = 0; j < 1000; j++)
        {
          if((FCTL3 & BUSY) != BUSY)              //不忙则跳出,完成擦除
          break;
        }
        FCTL3 = FWKEY;                            //  LOCK=0
        FCTL1 = FWKEY+WRT;                        //  WRT=1
        *ptr++ = *(data + i);
        FCTL1 = FWKEY;                            // Clear WRT bit
        FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    }
    _EINT();
}
void WriteFlashBuffWord(INT32U dst, INT16S *data, INT8U len)
{
    INT16U i,j;
    INT16S *ptr;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////禁止内部看门狗
    WatchDog();                             ////清外部看门狗
    ptr  = (INT16S *)dst;
    for(i = 0; i < len; i++)
    {
        for(j = 0; j < 1000; j++)
        {
          if((FCTL3 & BUSY) != BUSY)              //不忙则跳出,完成擦除
          break;
        }
        FCTL3 = FWKEY;                            //  LOCK=0
        FCTL1 = FWKEY+WRT;                        //  WRT=1
        *ptr++ = *(data + i);
        FCTL1 = FWKEY;                            // Clear WRT bit
        FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    }
    _EINT();
}
void WriteFlashWord(INT32U dst, INT16U data)
{
    INT16U i;
    INT16U *ptr;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////禁止内部看门狗
    WatchDog();                             ////清外部看门狗
    ptr  = (INT16U *)dst;
    for(i = 0; i < 1000; i++)
    {
      if((FCTL3 & BUSY) != BUSY)              //不忙则跳出,完成擦除
      break;
    }
    FCTL3 = FWKEY;                            //  LOCK=0
    FCTL1 = FWKEY+WRT;                        //  WRT=1
    *ptr = data;
    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    _EINT();
}
void WriteFlashByte(INT32U dst, INT8U data)
{
    INT16U i;
    INT8U *ptr;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////禁止内部看门狗
    WatchDog();                             ////清外部看门狗
    ptr  = (INT8U *)dst;
    for(i = 0; i < 1000; i++)
    {
      if((FCTL3 & BUSY) != BUSY)              //不忙则跳出,完成擦除
      break;
    }
    FCTL3 = FWKEY;                            //  LOCK=0
    FCTL1 = FWKEY+WRT;                        //  WRT=1
    *ptr = data;
	WatchDog();
    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    _EINT();
}

//**************************************
//  date : 2012-07-17
//  Mender: KYO
//  Modify: FCTL1 = FWKEY + ERASE;   *ptr = 0;
//  fault : write flash oncetime
//  whence: The Flash is not Erase
void WriteFlashBuff(INT32U dst, INT8U *data, INT8U len)
{
    INT16U i;
    INT8U *ptr;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////禁止内部看门狗
    WatchDog();                             ////清外部看门狗
    ptr  = (INT8U *)dst;
    FCTL1 = FWKEY + ERASE; 
    FCTL3 = FWKEY;                            //  LOCK=0
    *ptr = 0;
    FCTL1 = FWKEY+WRT;                        //  WRT=1
    for(i = 0; i < len; i++)
    {
        *ptr++ = *(data + i);
		WatchDog();
    }
    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    _EINT();
}




void WriteFlashBuff1(INT32U dst, INT8U *data, INT8U len)
{
    INT16U i,j;
    INT8U *ptr;
    
    _DINT();
    WDTCTL = WDTPW + WDTHOLD;               ////禁止内部看门狗
    WatchDog();                             ////清外部看门狗
    ptr  = (INT8U *)dst;
    for(i = 0; i < len; i++)
    {
        for(j = 0; j < 1000; j++)
        {
          if((FCTL3 & BUSY) != BUSY)              //不忙则跳出,完成擦除
          break;
        }
        WatchDog();
        FCTL3 = FWKEY;                            //  LOCK=0
        FCTL1 = FWKEY+WRT;                        //  WRT=1
        *ptr++ = *(data + i);
        FCTL1 = FWKEY;                            // Clear WRT bit
        FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    }
    _EINT();
}





//***************************************************************
//    data     : 2012
//    mender   :  KYO
//    Function :  Read Flash Date


void Read_para(long *src, char *des,int count)
{             
  int i;
  
   _DINT();
  WDTCTL = WDTPW + WDTHOLD;          // 停止看门狗
  WatchDog();                             ////清外部看门狗
  //FCTL2 = FWKEY + FSSEL0 + FN0;      // 定义FLASH时序发生器输入时钟
  

  FCTL1 = FWKEY + ERASE;             // 使能擦除操作
  FCTL3 = FWKEY;                     // FLASH解锁
  FCTL1 = FWKEY + WRT;               // 允许写操作
  for (i=0; i<count; i++)
  {
    *des++ = *src++;            // 循环写
  }
    
  FCTL1 = FWKEY;                  
  FCTL3 = FWKEY + LOCK;              //写完了，锁定
  
   _EINT();	

}

//**************************************
//  date : 2012-07-17
//  Mender: KYO
//  Function: write Flash 
//void write_para(INT8U *src, INT8U count)
//{
//  INT8U *Flash_ptr; 
//             
//  char i;
//  
//   _DINT();
//  WDTCTL = WDTPW + WDTHOLD;               ////禁止内部看门狗
//  WatchDog();                             ////清外部看门狗
//  
//  Flash_ptr = (INT8U *) 0x10600;       // 初始化指针
//  FCTL1 = FWKEY + ERASE;             // 使能擦除操作
//  FCTL3 = FWKEY;                     // FLASH解锁
//  *Flash_ptr = 0;                    // 空写，启动擦除
//  FCTL1 = FWKEY + WRT;               // 允许写操作
//  for (i=0; i<count; i++)
//  {
//    *Flash_ptr++ = *src++;            // 循环写
//  }
//    
//  
//  FCTL1 = FWKEY;                  
//  FCTL3 = FWKEY + LOCK;              //写完了，锁定
//    
//   _EINT();	
//}





//==============================================================================
//  函数名称   : SPIWriteBuf
//  功能描述   : SPI发送一字节数据
//  输入参数   : ucData: 待写入数据
//  输出参数   ：<无>
//  返回值     : UCB0TXBUF寄存器数据
//  其他说明   : 
//  作者       ：
//==============================================================================
unsigned char SPIWriteBuf(unsigned char ucData)
{
    unsigned char i;
    UCB2TXBUF = ucData;
    for( i = 0; i < 255; i++ )
    {
    if((UCB2STAT&UCBUSY)==0)
    {    
        break;
    }
    }

    return UCB2TXBUF;
}

//==============================================================================
//  函数名称   : InitSPI
//  功能描述   : SPI接收一字节数据
//  输入参数   : <无>
//  输出参数   ：<无>
//  返回值     : UCB0RXBUF寄存器数据
//  其他说明   : 
//  作者       ：
//==============================================================================
unsigned char SPIReadBuf(void)
{
    unsigned char i;
    SPIWriteBuf(0);
    for( i = 0; i < 250; i++ )
    {
    if((UCB2STAT&UCBUSY)==0)
    {    
        break;
    }
    }
    return UCB2RXBUF;
}

//==============================================================================
//  函数名称   : Sst_Reset
//  功能描述   : 复位芯片
//  输入参数   : <无>
//  输出参数   ：<无>
//  返回值     : <无>
//  其他说明   : 
//  作者       ：
//==============================================================================
 void Sst_Reset(void)
{
    SELECT_CHIP;
    SPIWriteBuf(RSTEN);
    UNSELECT_CHIP;
    SELECT_CHIP;
    SPIWriteBuf(RST);
    UNSELECT_CHIP;
}
 //==============================================================================
 //  函数名称   : Sst_Unlock
 //  功能描述   : 解锁芯片
 //  输入参数   : <无>
 //  输出参数   ：<无>
 //  返回值     : <无>
 //  其他说明   :
 //  作者       ：
 //==============================================================================
void Sst_Unlock(void)
{
	unsigned char temp[3];
	Sst_ReadJEDECID(temp,3);
	if(temp[2]==0x4B)
		{//SST25VF064C
     SELECT_CHIP;
     SPIWriteBuf(WREN);
     UNSELECT_CHIP;
     SELECT_CHIP;
     SPIWriteBuf(ULBPR);
     UNSELECT_CHIP;
	 SELECT_CHIP;         //sst25上电需要手动清除块保护状态
     SPIWriteBuf(EWSR);
     UNSELECT_CHIP;
     SELECT_CHIP;
     SPIWriteBuf(WRSR);
     SPIWriteBuf(0x00);  //解除块保护
     UNSELECT_CHIP;
		}
	else if(temp[2]==0x43)
		{//SST26VF064B
     SELECT_CHIP;
     SPIWriteBuf(WREN);
     UNSELECT_CHIP;
     SELECT_CHIP;
     SPIWriteBuf(ULBPR);
     UNSELECT_CHIP;	
     SELECT_CHIP;
     SPIWriteBuf(WRSR);
     SPIWriteBuf(0x00); 	 
     SPIWriteBuf(0x0a);  //解除块保护
     UNSELECT_CHIP;	 
		}
}
//==============================================================================
//  函数名称   : SpiWaitBusy
//  功能描述   : 通过读状态寄存器检测忙状态
//  输入参数   : <无>
//  输出参数   ：<无>
//  返回值     : <无>
//  其他说明   :
//  作者       ：
//==============================================================================
 void SpiWaitBusy(void)
{
    unsigned char temp = 0;
    unsigned int a = 0;
	
	SELECT_CHIP;
        SPIWriteBuf(STATUS_REGISTER);
        //SPIWriteBuf(0x35);

	for(a=0;a<2000;a++)
	{
		temp = SPIReadBuf();
		//k=temp;
		temp&=0x01;//temp&=0x81;
		if(temp==0)
		{
		    break;
		}
	}
	UNSELECT_CHIP;
}
 //==============================================================================
 //  函数名称   : Sst_ReadID
 //  功能描述   : 读取ID
 //  输入参数   : <无>
 //  输出参数   ：<无>
 //  返回值     : <无>
 //  其他说明   :
 //  作者       ：
 //==============================================================================
void Sst_ReadID(unsigned char *PcData,unsigned int Size)
{
     unsigned int i;
     SpiWaitBusy();

 	SELECT_CHIP;
 	SPIWriteBuf(RDID);
 	SPIWriteBuf((unsigned char)(0));
	SPIWriteBuf((unsigned char)(0));
	SPIWriteBuf((unsigned char)(0));
    for(i = 0;i < Size;i++)
    {
    	*PcData= SPIReadBuf();//SPIReadBuf();
     	PcData++;
    }
 	UNSELECT_CHIP;
}

 void Sst_ReadJEDECID(unsigned char *PcData,unsigned int Size)
{
     unsigned int i;
     SpiWaitBusy();

 	SELECT_CHIP;
 	SPIWriteBuf(JEDEC);
    for(i = 0;i < Size;i++)
    {
    	*PcData= SPIReadBuf();//SPIReadBuf();
     	PcData++;
    }
 	UNSELECT_CHIP;
}
 //==============================================================================
 //  函数名称   :Sector_Erase
 //  功能描述   : 块擦除 (4k Bytes)
 //  输入参数   : 块地址，低12位无效
 //  输出参数   ：<无>
 //  返回值     : <无>
 //  其他说明   :
 //  作者       ：
 //==============================================================================
 void Sector_Erase(long unBlock)
 {
     SpiWaitBusy();

     SELECT_CHIP;
     SPIWriteBuf(WREN);
     UNSELECT_CHIP;

     SELECT_CHIP;
     SPIWriteBuf(SECTOR_ERASE);
     SPIWriteBuf((unsigned char)(unBlock >> 16));
     SPIWriteBuf((unsigned char)(unBlock >> 8));
     SPIWriteBuf((unsigned char)unBlock);
     UNSELECT_CHIP;

     SELECT_CHIP;
     SPIWriteBuf(WRDI);
     UNSELECT_CHIP;
     delayms(50);
 }

//==============================================================================
 //  函数名称   :Block_Erase
 //  功能描述   : 块擦除 (根据存储器区域block划分进行8k、32k或64k擦除)
 //  输入参数   : 块地址，低12位无效15-13位根据块大小改变
 //  输出参数   ：<无>
 //  返回值     : <无>
 //  其他说明   :
 //  作者       ：
 //==============================================================================
 void Block_Erase(long unBlock)
 {
     SpiWaitBusy();

     SELECT_CHIP;
     SPIWriteBuf(WREN);
     UNSELECT_CHIP;

     SELECT_CHIP;
     SPIWriteBuf(BLOCK_ERASE);
     SPIWriteBuf((unsigned char)(unBlock >> 16));
     SPIWriteBuf((unsigned char)(unBlock >> 8));
     SPIWriteBuf((unsigned char)unBlock);
     UNSELECT_CHIP;

     SELECT_CHIP;
     SPIWriteBuf(WRDI);
     UNSELECT_CHIP;
     
     delay(30000);//擦除之后延时一段时间ERASE_DELAY
     
 }
 //==============================================================================
 //  函数名称   :Chip_Erase
 //  功能描述   : 芯片片擦除
 //  输入参数   : <无>
 //  输出参数   ：<无>
 //  返回值     : 	<无>
 //  其他说明   :
 //  作者       ：
 //==============================================================================
 void Chip_Erase(void)
 {
     SpiWaitBusy();

     SELECT_CHIP;
     SPIWriteBuf(WREN);
     UNSELECT_CHIP;

     SELECT_CHIP;
     SPIWriteBuf(CHIP_ERASE);
     UNSELECT_CHIP;

     SELECT_CHIP;
     SPIWriteBuf(WRDI);
     UNSELECT_CHIP;
 }
 //==============================================================================
 //  函数名称   : Sst26vf064b_Read
 //  功能描述   : 读数据
 //  输入参数   : unAddr：缓冲区绝对地址 ； PcData：目标数据存储指针 ；Size：读取数据个数最；
 //  输出参数   ：<无>
 //  返回值     : 	<无>
 //  其他说明   :
 //  作者       ：
 //==============================================================================
 void Sst26vf064b_Read(long unAddr,unsigned char *PcData,unsigned int Size)
 {
     unsigned int i;
     SpiWaitBusy();

 	SELECT_CHIP;
 	SPIWriteBuf(SST_READ);
 	SPIWriteBuf((unsigned char)(unAddr >> 16));
 	SPIWriteBuf((unsigned char)(unAddr >> 8));
    SPIWriteBuf((unsigned char) unAddr);
    for(i = 0;i < Size;i++)
    {
    	*PcData= SPIReadBuf();//SPIReadBuf();
     	PcData++;
    }
 	UNSELECT_CHIP;
 }
 //==============================================================================
 //  函数名称   : Sst26vf064b_Page_Write
 //  功能描述   : 写数据
 //  输入参数   : unAddr：缓冲区绝对地址；  PcData：目标数据存储指针； Size：写入数据个数(<=256，注意跨页)
 //  输出参数   ：<无>
 //  返回值     : <无>
 //  其他说明   :
 //  作者       ：
 //==============================================================================
 void Sst26vf064b_Page_WriteBytes(long unAddr,unsigned char *PcData,unsigned int Size)
 {
     unsigned int i;
     SpiWaitBusy();

     //Flash_cs=0;
     SELECT_CHIP;
    // delay(1);
     SPIWriteBuf(WREN);							//允许写
    // Flash_cs=1;
    // delay(1);
     UNSELECT_CHIP;

    // Flash_cs=0;
     SELECT_CHIP;
     SPIWriteBuf(SST_WRITE);						//写指令
     SPIWriteBuf((unsigned char)(unAddr >> 16));	//地址
     SPIWriteBuf((unsigned char)(unAddr >> 8));
     SPIWriteBuf((unsigned char) unAddr);
     for(i = 0;i < Size;i++)					//数据
     {
    	SPIWriteBuf(*PcData);
    	PcData++;
     }
     delay(20);
     UNSELECT_CHIP;

     SELECT_CHIP;
  //   delay(1);
     SPIWriteBuf(WRDI);							//禁止写
     //Flash_cs=1;
  //   delay(1);
     UNSELECT_CHIP;
 }

 //==============================================================================
 //  函数名称   : Sst26vf064b_Page_Write
 //  功能描述   : 写数据
 //  输入参数   : unAddr：缓冲区绝对地址；  PcData：目标数据存储指针； Size：写入数据个数(<=256，注意跨页)
 //  输出参数   ：<无>
 //  返回值     : <无>
 //  其他说明   :
 //  作者       ：
 //==============================================================================
 void Sst26vf064b_Page_WriteWords(long unAddr,unsigned int *PcData,unsigned int Size)
 {
     unsigned int i;
     unsigned char *PcBufTemp;

     Size *= 2;
     PcBufTemp = (unsigned char*)PcData;
     SpiWaitBusy();

     //Flash_cs=0;
     SELECT_CHIP;
    // delay(1);
     SPIWriteBuf(WREN);							//允许写
    // Flash_cs=1;
    // delay(1);
     UNSELECT_CHIP;

    // Flash_cs=0;
     SELECT_CHIP;
   //  delay(1);
     SPIWriteBuf(SST_WRITE);						//写指令
     SPIWriteBuf((unsigned char)(unAddr >> 16));	//地址
     SPIWriteBuf((unsigned char)(unAddr >> 8));
     SPIWriteBuf((unsigned char) unAddr);
     for(i = 0;i < Size;i++)					//数据
     {
    	SPIWriteBuf(*PcBufTemp);
    	PcBufTemp++;
     }
     
     UNSELECT_CHIP;
     delayms(2);
   /*  
     SELECT_CHIP;
  //   delay(1);
     SPIWriteBuf(WRDI);							//禁止写
     //Flash_cs=1;
  //   delay(1);
     UNSELECT_CHIP;
     */
 }


//==============================================================================
//  函数名称   : CopySoeEepToFlash
//  功能描述   : EEPROM中的SOE数据导入FLASH
//  输入参数   : <无>
//  输出参数   ：<无>
//  返回值     : <无>
//  其他说明   : 
//  作者       ：
//==============================================================================
//void CopySoeEepToFlash(void)
//{
//    unsigned int j;
//    unsigned int tSoeBuff[SOE_DATA_LEN * 10];
//    for(j = 0; j < 4; j++)   //每次最多写入256字节，所以分4次写入
//    {
//       // for(i = 0; i < 10; i++)    //由于内存中的SOE数据可能随时更新，因此不直接采用内存的数据，而从EEPROM中一条一条取出
//        {
//            //CAT_SpiReadWords(EEPADD_SOE_DATA + j * 240 , SOE_DATA_LEN * 10, tSoeBuff);   //依次从EEPROM中取出SOE数据，放到tSoeBuff中
//        }  
//           // Sst26vf064b_Page_WriteWords((FADDR_SOE_START) * 256, tSoeBuff,SOE_DATA_LEN * 10);      //把数据保存进入FLASH中
//        
//          //  Sst26vf064b_Read((FADDR_SOE_START + g_sSoeData.m_unSoeFlashPos + j) * 256, stSoeBuff,240);
//    }
//   // WritePageFromBuffer(g_sSoeData.m_unSoeFlashPos,DB_2_BUFFER);
//}
//
