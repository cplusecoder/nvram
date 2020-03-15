<<<<<<< HEAD
/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */
=======
#include <QCoreApplication>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <stdio.h>

typedef struct _NvRamHeader
{
    unsigned int map_size;
    unsigned int dat_size;
    unsigned int ________;
    unsigned int checksum;

    //unsigned char map_file[4/*map_size*/];

} NvRamHeader;

typedef struct _NvImei {
    unsigned int imei;
}imei;
>>>>>>> 89c53ae079565e472be83de32999f9643a598d43

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <limits.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/reboot.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <cutils/properties.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/mount.h>
#include <sys/statfs.h>
#include <sys/ioctl.h>

#include "libfile_op.h"
#include "libnvram.h"

#include "Custom_NvRam_LID.h"

#include "CFG_Wifi_File.h"
#include "CFG_WIFI_Default.h"

#include "CFG_PRODUCT_INFO_File.h"

#include "imei.h"

//xx-xx-xx-xx-xx-xx
//xx:xx:xx:xx:xx:xx
#define IMEI_LEN	(15)

#define DEBUG  1

typedef struct __THREAD_DATA__
{
#define TYPE_AUTO	(0x01)
#define TYPE_SPEC	(0x02)
    unsigned char type ;	// 1 -> auto gen , 2 -> filled with field mac_addr.
    unsigned char imei[IMEI_LEN+1];	//
}THREAD_DATA;

static void usage(const char * name);
static int read_wifi_addr_from_nvram(unsigned char * ucBDAddr);
static int write_wifi_addr_to_nvram(unsigned char * ucBDAddr);
static int convert_str_to_byte(unsigned char * mac_addr ,int mac_addr_len,char * addr);
static int check_imei_is_valid(char * addr);
static void * imei_process_thread(void *priv);
static int generator_imei_radom_value(unsigned char string[6]);

static int read_imei_from_nvram(unsigned char  * data)
{
<<<<<<< HEAD
    char imei[IMEI_LEN] = { 0 };
    int i = 0 ;

    PRODUCT_INFO nvram_data;
    memset(&nvram_data,0,sizeof(PRODUCT_INFO));

    F_ID nvram_fd = {
    .iFileDesc = -1,
    .ifile_lid = 0,
    .bIsRead = 0
    };

    int nvram_rec_lid = AP_CFG_REEB_PRODUCT_INFO_LID;
    int nvram_rec_size = 0 ;
    int nvram_rec_num  = 0 ;
    int nbytes = 0 ;

    nvram_fd = NVM_GetFileDesc(nvram_rec_lid,&nvram_rec_size,&nvram_rec_num,ISREAD);
    if(nvram_fd.iFileDesc < 0)
    {
        return -1;
    }
    if(nvram_rec_num != CFG_FILE_PRODUCT_INFO_TOTAL)
    {
        NVM_CloseFileDesc(nvram_fd);
        return -1;
    }

    if( nvram_rec_size != CFG_FILE_PRODUCT_INFO_SIZE)
    {
        NVM_CloseFileDesc(nvram_fd);
        return -1;
    }
=======
    QCoreApplication a(argc, argv);
    const char *bin_file = "nvram.bin";
    FILE *stream = fopen(bin_file, "rb");

    quint64 byte_postion = 0x21000;
    NvRamHeader header;
    memset(&header, 0, sizeof(NvRamHeader));
    fseek(stream, 0, SEEK_SET);
    fread(&header, 1, sizeof(header), stream);

    qInfo() << "Header Map size: " << header.dat_size;

    fclose(stream);

    QFile file("nvram_1.bin");
    file.open(QIODevice::ReadWrite);
    file.seek(byte_postion);

    QByteArray buffer =  file.read(12);

    QByteArray hex_to;
    hex_to.fromHex(buffer);
    hex_to.mid(0x2).left(2);


    qInfo() << buffer;

    qInfo() << hex_to;

    file.close();
>>>>>>> 89c53ae079565e472be83de32999f9643a598d43

    lseek(nvram_fd.iFileDesc,0, 0);

    nbytes=read(nvram_fd.iFileDesc,&nvram_data,nvram_rec_size*nvram_rec_num);

    if(nbytes < 0)
    {
        NVM_CloseFileDesc(nvram_fd);
        return -1;
    }
    NVM_CloseFileDesc(nvram_fd);

    memset(imei,0,sizeof(imei));

    printf("nvram imei:");

    i = 0 ;
    while(i < (IMEI_LEN/2))
    {
        char data = nvram_data.IMEI[0].imei[i];
        printf("0x%02x ",data);
        imei[2*i+0] = (data & 0x0f ) + '0';
        imei[2*i+1] = ((data & 0xf0 ) >> 4 )+ '0';
        i++;
    }
    imei[IMEI_LEN-1] = (nvram_data.IMEI[0].imei[i] & 0x0f) + '0';
    printf("0x%02x\n",nvram_data.IMEI[0].imei[i]);

    memcpy(data,imei,IMEI_LEN);

    printf("read nvram success.\n");

    return 0;
}

static int write_imei_to_nvram(unsigned char * imei_str)
{
    PRODUCT_INFO nvram_data;

    char imei[8] =  { 0 };

    int cfgfile_fd = -1;

    F_ID nvram_fd = {
    .iFileDesc = -1,
    .ifile_lid = 0,
    .bIsRead = 0
    };

    int nvram_rec_lid = AP_CFG_REEB_PRODUCT_INFO_LID;
    int nvram_rec_size = 0 ;
    int nvram_rec_num  = 0 ;
    int nbytes = 0 ;

    //read data
    nvram_fd = NVM_GetFileDesc(nvram_rec_lid,&nvram_rec_size,&nvram_rec_num,ISREAD);
    if(nvram_fd.iFileDesc < 0)
    {
        return -1;
    }
    if(nvram_rec_num != CFG_FILE_PRODUCT_INFO_TOTAL)
    {
        NVM_CloseFileDesc(nvram_fd);
        return -1;
    }

    if( nvram_rec_size != CFG_FILE_PRODUCT_INFO_SIZE)
    {
        NVM_CloseFileDesc(nvram_fd);
        return -1;
    }

    lseek(nvram_fd.iFileDesc,0, 0);

    nbytes=read(nvram_fd.iFileDesc,&nvram_data,nvram_rec_size*nvram_rec_num);

    if(nbytes < 0)
    {
        NVM_CloseFileDesc(nvram_fd);
        return -1;
    }
    NVM_CloseFileDesc(nvram_fd);

    // writer
    nvram_fd = NVM_GetFileDesc(nvram_rec_lid, &nvram_rec_size, &nvram_rec_num, ISWRITE);
    if(nvram_fd.iFileDesc < 0){
        return -1;
    }

    if(nvram_rec_num != CFG_FILE_PRODUCT_INFO_TOTAL){
        NVM_CloseFileDesc(nvram_fd);
        return -1;
    }

    if(nvram_rec_size != CFG_FILE_PRODUCT_INFO_SIZE){
        NVM_CloseFileDesc(nvram_fd);
        return -1;
    }

    lseek(nvram_fd.iFileDesc, 0, 0);

    memset(imei,0,sizeof(imei));

    printf("write imei :");

    int i = 0 ;
    while( i < (IMEI_LEN/2))
    {
        nvram_data.IMEI[0].imei[i] = (imei_str[2*i+0]-'0') | ((imei_str[2*i+1]-'0')<<4);
        nvram_data.IMEI[1].imei[i] = (imei_str[2*i+0]-'0') | ((imei_str[2*i+1]-'0')<<4);
        nvram_data.IMEI[2].imei[i] = (imei_str[2*i+0]-'0') | ((imei_str[2*i+1]-'0')<<4);
        nvram_data.IMEI[3].imei[i] = (imei_str[2*i+0]-'0') | ((imei_str[2*i+1]-'0')<<4);

        printf("0x%02x ",nvram_data.IMEI[0].imei[i]);

        i++;
    }
    nvram_data.IMEI[0].imei[7] = 0x0f & (imei_str[2*i+0]-'0');
    nvram_data.IMEI[1].imei[7] = 0x0f & (imei_str[2*i+0]-'0');
    nvram_data.IMEI[2].imei[7] = 0x0f & (imei_str[2*i+0]-'0');
    nvram_data.IMEI[3].imei[7] = 0x0f & (imei_str[2*i+0]-'0');
    printf("0x%02x\n",nvram_data.IMEI[0].imei[7]);

    nvram_data.IMEI[0].svn = 0x87;
    nvram_data.IMEI[1].svn = 0x87;
    nvram_data.IMEI[2].svn = 0x87;
    nvram_data.IMEI[3].svn = 0x87;

    nvram_data.IMEI[0].pad = 0x01;
    nvram_data.IMEI[1].pad = 0x01;
    nvram_data.IMEI[2].pad = 0x01;
    nvram_data.IMEI[3].pad = 0x01;

    memset(nvram_data.barcode,0x32,63);

    if (write(nvram_fd.iFileDesc,&nvram_data,nvram_rec_num*nvram_rec_size) < 0)
    {
        printf("write nvram error.\n");
        NVM_CloseFileDesc(nvram_fd);
        return -1;
    }

    NVM_CloseFileDesc(nvram_fd);

    printf("write nvram success.\n");

    return  0;
}

static void * imei_process_thread(void *priv)
{
    THREAD_DATA * data = (THREAD_DATA*)priv;

    static unsigned char imei[IMEI_LEN+1] = { 0 };
    static unsigned char default_imei[IMEI_LEN+1] = { 0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30 };
    int ret = -1 ;

    memset(imei,0,sizeof(imei));
    ret = read_imei_from_nvram(&imei[0]);
    if(ret < 0 )
    {
        printf("get imei from nvram failed. \n");
        pthread_exit((void*)-1);
    }

    #if defined(DEBUG)
    {
        int i = 0 ;
        printf("read nvram imei: [");
        while(1)
        {
            if(i >= IMEI_LEN)
                break;
            printf("%c ",imei[i]);
            i++;
        }
        printf("]\n");
    }
    #endif

    if(memcmp(imei,default_imei,IMEI_LEN) == 0)
    {
        //printf("nvram wifi addr default .\n");
        if(data->type == TYPE_AUTO)
        {
            // auto gen imei
            printf("write autogen imei. \n");
            generator_imei_radom_value(imei);
            check_imei_is_valid(imei);
            write_imei_to_nvram(imei);
            pthread_exit((void*)0);
        }
        else
        {
            printf("write spec imei. \n");
            check_imei_is_valid(data->imei);
            write_imei_to_nvram(data->imei);
            pthread_exit((void*)0);
        }
    }
    else
    {
        if(data->type == TYPE_AUTO)
        {
            // auto gen bt addr
            printf("skip imei generator.\n");
        }
        else
        {
            //write spec mac addr.
            printf("overwrite with spec imei.\n");
            write_imei_to_nvram(data->imei);
            pthread_exit((void*)0);
        }
    }

    pthread_exit((void*)-1);
    return (void *)-1;
}

static void usage(const char * name)
{
        printf("\r\n%s usage :\r\n",name);
        printf("%s xxxxxxxxxxxxxxx\r\n",name);
        printf("eg:\r\n");
        printf("%s 111111111111119 #set imei \r\n",name);
        printf("\r\nAuthor:huyanwei\r\n");
        printf("Email :srclib@hotmail.com\r\n");
        return ;
}

static int generator_imei_radom_value(unsigned char string[IMEI_LEN+1])
{
#if 1
        int iRandom = 0;
        int fd = 0;
        unsigned long seed;

        struct timeval tv;
        gettimeofday(&tv, NULL);

    //fix first 3 byte
#if 1
        string[0] = 0x33;
        string[1] = 0x35;
        string[2] = 0x39;
        string[3] = 0x32;
        string[4] = 0x30;
        string[5] = 0x39;
        string[6] = 0x30;
        string[7] = 0x32;
#else
        //sunmontech
        string[0] = 0x30;
        string[1] = 0x92;
        string[2] = 0xF6;
#endif

        //printf("Enable Random\n");

        /* initialize random seed: */
        srand (tv.tv_usec);
        iRandom = rand();
        if(iRandom != 0)
        {
           printf("iRandom1 = 0x%08X\n", iRandom);
           string[8] = ((((iRandom>>8)&0xff)&0x0f)%10)+'0';
           string[9] = ((((((iRandom>>8)&0xff)&0xf0)>>4)%10))+'0';

           iRandom = rand();
           printf("iRandom2 = 0x%08X\n", iRandom);
           string[10] = ((((iRandom>>8)&0xff)&0x0f)%10)+'0';
           string[11] = ((((((iRandom>>8)&0xff)&0xf0)>>4)%10))+'0';

           iRandom = rand();
           printf("iRandom3 = 0x%08X\n", iRandom);
           string[12] = ((((iRandom>>8)&0xff)&0x0f)%10)+'0';
           string[13] = ((((((iRandom>>8)&0xff)&0xf0)>>4)%10))+'0';

           iRandom = rand();
           printf("iRandom4 = 0x%08X\n", iRandom);
           string[14] = ((((iRandom>>8)&0xff)&0x0f)%10)+'0';
           string[15] = ((((((iRandom>>8)&0xff)&0xf0)>>4)%10))+'0';
        }
        return 0;
#else
        int iRandom = 0;
        int fd = 0;
        unsigned long seed;

    //fix first 3 byte
    string[0] = 0x5C;
    string[1] = 0x4C;
    string[2] = 0xA9;

    /* initialize random seed */
        srand (time(NULL));
    iRandom = rand();
    printf("iRandom1 = 0x%08x \n",iRandom);
        string[3] = ((iRandom>>8) & 0xff );

    /* second seed */
        struct timeval tv;
        gettimeofday(&tv, NULL);
        srand (tv.tv_usec);
    iRandom = rand();
    printf("iRandom2 = 0x%08x \n",iRandom);
        string[4] = ((iRandom>>8) & 0xff );

    /* third seed */
    fd = open("/dev/urandom", O_RDONLY);
    if (fd > 0)
    {
        if (read(fd, &seed, sizeof(unsigned long)) > 0)
        {
                srand (seed);
                iRandom = rand();
                printf("iRandom3 = 0x%08x \n",iRandom);
                string[5] = ((iRandom) & 0xff );
        }
        close(fd);
    }

#endif
    return 1;
}

static int check_imei_is_valid(char * addr)
{
    char * IMEI = addr;
    int len = strlen(addr);

    int i = 0 ;
    char c = '\0';

    int check = 0 ;
    int sum = 0 ;

    if(addr == NULL)
        return 0;

    i = 0 ;
    while(i < (IMEI_LEN-1))
    {
        if( (IMEI[i+0] < '0') || (IMEI[i+0] > '9') || (IMEI[i+1] < '0') ||( IMEI[i+1] > '9' ))
        {
            return -1;
        }
        int res = (IMEI[i+1]-'0')*2;
        int num1 = res / 10;
        int num2 = res % 10;
        sum += 	(IMEI[i+0]-'0') + num1 + num2 ;
        i+=2;
    }

    if(sum % 10 == 0)
    {
        check = 0;
    }
    else
    {
        check = 10 - (sum %10);
    }

    if( (IMEI[i+0]-'0') == check)
    {
        return 1;
    }
    else
    {
        addr[IMEI_LEN-1] = check + '0' ; // update check
        return 0;
    }
}

/********************************************
** Func : convert xx[:-]xx[:-]xx[:-]xx[:-]xx[:-]xx
**             to 0x112233445566
********************************************************/

static int convert_str_to_byte(unsigned char * mac_addr ,int mac_addr_len,char * addr)
{
    int len = strlen(addr);
    int i = 0 ;
    int index = 0 ;
    unsigned char c = '\0';
    int data = 0;

        if(mac_addr == NULL)
        {
                return -1;
        }
        memset(mac_addr,0,mac_addr_len);

        while(i < len)
    {
        c = addr[i];
        switch(i%3)
        {
            case 0:
                if(( c >= '0') && ( c <= '9'))
                {
                    data = c-'0';
                }
                else if( ( c  >= 'a') && ( c  <= 'f') )
                {
                    data = 10+c-'a';

                }
                else if( ( c >= 'A') && ( c  <= 'F') )
                {
                    data = 10+c-'A';
                }
                else
                {
                    return -1;
                }
                mac_addr[index] = mac_addr[index] | ((data & 0x0f)<<4);
                break;
            case 1:
                if(( c >= '0') && ( c <= '9'))
                {
                    data = c-'0';
                }
                else if( ( c  >= 'a') && ( c  <= 'f') )
                {
                    data = 10+c-'a';
                }
                else if( ( c >= 'A') && ( c  <= 'F') )
                {
                    data = 10+c-'A';
                }
                else
                {
                    return -1;
                }
                mac_addr[index] = mac_addr[index] | (data & 0x0f);

                index ++;

                if(index >= mac_addr_len)
                {
                    #if defined(DEBUG)
                    int len = 0;
                    printf("convert to byte addr: [");
                    while(1)
                    {
                        if(len >= 6)
                            break;

                        printf("%02x ",mac_addr[len]);

                        len ++;
                    }
                    printf("]\n");
                    #endif
                    return 0;
                }

                break;
            case 2:
                if(( c != '-') && ( c != ':'))
                {
                    return -1;
                }
                break;
        }
        i++ ;
    }
    return 0;
}


int main(int argc, char* argv[])
{

    int  ret = -1;
    char c = '-';

    pthread_t imei_thread_id = 0 ;
    int imei_thread_result = 0;
    THREAD_DATA  imei_thread_data;

    memset(&imei_thread_data,0,sizeof(imei_thread_data));

    unsigned int backup_flag = 0;

    char imei[IMEI_LEN+1] = { 0 } ;
    memset(imei,0,sizeof(imei));

    int uid= -1;
    int euid= -1;
    uid= getuid();
    euid= geteuid();
    if(euid != 0)
    {
        // request root.
        printf("request root permission.[%d-%d]\n",uid,euid);
        return -1;
    }

    do
    {
        c = getopt(argc, argv, "bh");

        #if 0
        printf("optarg=%s \n",optarg);
        printf("optopt=%c \n",optopt);
        printf("optind=%d \n",optind);
        printf("c=0x%x \n",c);
        #endif

        if (c == 0xff )
            break;

        switch (c)
        {
            case 'b':
                backup_flag = 1 ;
                break;
            case 'h':
                usage(argv[0]);
                return -1;
            case '?':
                fprintf(stderr, "%s: invalid option -%c\n",argv[0], optopt);
                usage(argv[0]);
                exit(1);
        }
    } while (1);

    //printf("stage 1 .\n");

    if(optind+1 == argc)
    {
        if(strlen(argv[optind])!= IMEI_LEN)
        {
            printf("IMEI length Invaild,need 15 digitals.\n");
            usage(argv[0]);
            return -1;
        }
        memcpy(imei,argv[optind],IMEI_LEN);

        int check_res = check_imei_is_valid(imei);
        if( check_res < 0 )
        {
            printf("check IMEI [%s] result:[invalid]\n",imei);
            usage(argv[0]);
            return -1;
        }
        else if ( check_res == 0 )
        {
            printf("check IMEI [%s] result:[fixed]\n",imei);
        }
        else
        {
            printf("check IMEI [%s] result:[valid]\n",imei);
        }

        //printf("spec_flag=0x%04x\n",spec_flag);

        {
            printf("[ IMEI ]:\t");
            imei_thread_data.type = TYPE_SPEC;
            memcpy(imei_thread_data.imei,imei,IMEI_LEN);
        }
    }
    else
    {
        imei_thread_data.type   = TYPE_AUTO;

        //skip more paramers
    }

    //printf("stage 2 .\n");

    pthread_create(&imei_thread_id, NULL, imei_process_thread,&imei_thread_data);

    pthread_join(imei_thread_id, &imei_thread_result);

    //printf("bt_thread_result=%d\n",bt_thread_result);
    //printf("wifi_thread_result=%d\n",wifi_thread_result);

#if 0
    //make sure if modify mac addr ,at sometimes ,backup nvram partition.
    if(imei_thread_result == 0)
        backup_flag = 1;

    // backup data to nvram partition
    if(backup_flag == 1)
    {
        bool backup_res = false ;
        //printf("backup date to nvram partition. \n");

        backup_res = FileOp_BackupToBinRegion_All();
        if(backup_res)
        {
            FileOp_SetCleanBootFlag(1);
            printf("backup nvram data success.\n");
        }
        else
        {
            printf("backup nvram data failed.\n");
        }
    }
#endif
    return 1;
}
